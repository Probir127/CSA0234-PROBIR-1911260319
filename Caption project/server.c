#define _POSIX_C_SOURCE 200809L
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "protocol.h"
#include "http.h"

#define MAX_BOOKS 1000
#define FIELD 160
typedef struct { int id, stock_state; char title[FIELD], author[FIELD], borrower[FIELD]; } Book;
static Book books[MAX_BOOKS];
typedef struct { int id; char name[FIELD], email[FIELD]; } Member;
typedef struct { int id, book, member; long issued, due, returned; int renewals; } Loan;
typedef struct { int id, book, member; long placed; int state; } Hold; /* 0 queued, 1 filled, 2 cancelled */
static Member members[1000];
static Loan loans[10000];
static Hold holds[10000];
static int member_count, loan_count, hold_count;
static int count, next_id = 1;
static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
static const char *database = "library.tsv";

static int number(const char *s) {
    char *end; errno = 0;
    long n = strtol(s, &end, 10);
    return !errno && *s && !*end && n > 0 && n < 1000000000 ? (int)n : -1;
}
static int field_ok(const char *s) {
    return s && *s && strlen(s) < FIELD && !strpbrk(s, "\t\r\n|");
}
/* Write a replacement file first; rename commits the complete snapshot. */
static int save(void) {
    char tmp[1024];
    if (snprintf(tmp, sizeof(tmp), "%s.tmp", database) >= (int)sizeof(tmp)) return -1;
    FILE *f = fopen(tmp, "w");
    if (!f) return -1;
    int failed = 0;
    for (int i = 0; i < count; i++)
        if (fprintf(f, "B\t%d\t%s\t%s\t%s\t%d\n", books[i].id, books[i].title,
                    books[i].author, *books[i].borrower ? books[i].borrower : "-", books[i].stock_state) < 0) failed = 1;
    for (int i = 0; i < member_count; i++)
        if (fprintf(f, "M\t%d\t%s\t%s\n", members[i].id, members[i].name, members[i].email) < 0) failed = 1;
    for (int i = 0; i < loan_count; i++)
        if (fprintf(f, "L\t%d\t%d\t%d\t%ld\t%ld\t%ld\t%d\n", loans[i].id, loans[i].book, loans[i].member, loans[i].issued, loans[i].due, loans[i].returned, loans[i].renewals) < 0) failed = 1;
    for (int i = 0; i < hold_count; i++)
        if (fprintf(f, "H\t%d\t%d\t%d\t%ld\t%d\n", holds[i].id, holds[i].book, holds[i].member, holds[i].placed, holds[i].state) < 0) failed = 1;
    if (fflush(f) || fsync(fileno(f))) failed = 1;
    if (fclose(f)) failed = 1;
    if (failed || rename(tmp, database)) { unlink(tmp); return -1; }
    return 0;
}
static int load(void) {
    FILE *f = fopen(database, "r");
    if (!f) return errno == ENOENT ? 0 : -1;
    char line[LINE_SIZE]; int failed = 0;
    while (fgets(line, sizeof(line), f)) {
        if (!strncmp(line, "M\t", 2)) {
            Member m;
            if (member_count >= 1000 || sscanf(line, "M\t%d\t%159[^\t]\t%159[^\n]", &m.id, m.name, m.email) != 3) { failed = 1; break; }
            members[member_count++] = m; continue;
        }
        if (!strncmp(line, "L\t", 2)) {
            Loan l = {0};
            int fields = sscanf(line, "L\t%d\t%d\t%d\t%ld\t%ld\t%ld\t%d", &l.id, &l.book, &l.member, &l.issued, &l.due, &l.returned, &l.renewals);
            if (loan_count >= 10000 || (fields != 6 && fields != 7)) { failed = 1; break; }
            loans[loan_count++] = l; continue;
        }
        if (!strncmp(line, "H\t", 2)) {
            Hold h = {0};
            if (hold_count >= 10000 || sscanf(line, "H\t%d\t%d\t%d\t%ld\t%d", &h.id, &h.book, &h.member, &h.placed, &h.state) != 5 || h.state < 0 || h.state > 2) { failed = 1; break; }
            holds[hold_count++] = h; continue;
        }
        if (!strncmp(line, "B\t", 2)) {
            char *state, *tag = strtok_r(line, "\t", &state);
            char *id = strtok_r(NULL, "\t", &state);
            char *title = strtok_r(NULL, "\t", &state);
            char *author = strtok_r(NULL, "\t", &state);
            char *borrower = strtok_r(NULL, "\t", &state);
            char *stock_text = strtok_r(NULL, "\n", &state);
            int n = id ? number(id) : -1;
            int stock = stock_text && *stock_text >= '0' && *stock_text <= '3' && !stock_text[1] ? *stock_text - '0' : -1;
            if (!tag || count == MAX_BOOKS || n < 0 || stock < 0 || !field_ok(title) || !field_ok(author) || !field_ok(borrower) || (stock && strcmp(borrower, "-"))) { failed = 1; break; }
            for (int i = 0; i < count; i++) if (books[i].id == n) failed = 1;
            if (failed) break;
            Book *b = &books[count++]; memset(b, 0, sizeof(*b));
            b->id = n; b->stock_state = stock;
            strcpy(b->title, title); strcpy(b->author, author);
            if (strcmp(borrower, "-")) strcpy(b->borrower, borrower);
            if (n >= next_id) next_id = n + 1;
            continue;
        }
        char *state, *id = strtok_r(line, "\t", &state);
        char *title = strtok_r(NULL, "\t", &state);
        char *author = strtok_r(NULL, "\t", &state);
        char *borrower = strtok_r(NULL, "\n", &state);
        int n = id ? number(id) : -1;
        if (count == MAX_BOOKS || n < 0 || !field_ok(title) || !field_ok(author) || !field_ok(borrower)) { failed = 1; break; }
        for (int i = 0; i < count; i++) if (books[i].id == n) failed = 1;
        if (failed) break;
        Book *b = &books[count++]; memset(b, 0, sizeof(*b)); b->id = n;
        strcpy(b->title, title); strcpy(b->author, author);
        if (strcmp(borrower, "-")) strcpy(b->borrower, borrower);
        if (n >= next_id) next_id = n + 1;
    }
    if (ferror(f)) failed = 1;
    fclose(f);
    if (failed) return -1;
    /* Older data stored a borrower name on the book without a loan record.
       Reconstruct an active loan so that these copies can be returned in the UI.
       Unknown issue/due dates remain zero rather than inventing dates. */
    for (int i = 0; i < count; i++) {
        if (!*books[i].borrower) continue;
        int linked = 0;
        for (int j = 0; j < loan_count; j++)
            if (loans[j].book == books[i].id && !loans[j].returned) linked = 1;
        if (linked) continue;
        int member = 0;
        for (int j = 0; j < member_count; j++)
            if (!strcmp(members[j].name, books[i].borrower)) member = members[j].id;
        if (!member) {
            if (member_count == 1000) return -1;
            Member *m = &members[member_count++];
            m->id = member_count;
            strcpy(m->name, books[i].borrower);
            snprintf(m->email, sizeof(m->email), "imported-%d@local.invalid", m->id);
            member = m->id;
        }
        if (loan_count == 10000) return -1;
        loans[loan_count] = (Loan){loan_count + 1, books[i].id, member, 0, 0, 0, 0};
        loan_count++;
    }
    return 0;
}
static void row(int fd, const Book *b) {
    char out[LINE_SIZE];
    const char *status = "Available", *who = "";
    if (b->stock_state == 1) status = "Damaged";
    else if (b->stock_state == 2) status = "Lost";
    else if (b->stock_state == 3) status = "Removed";
    else if (*b->borrower) { status = "Borrowed by: "; who = b->borrower; }
    else for (int i = 0; i < hold_count; i++) if (holds[i].book == b->id && !holds[i].state) {
        status = "Reserved for: ";
        for (int j = 0; j < member_count; j++) if (members[j].id == holds[i].member) who = members[j].name;
        break;
    }
    snprintf(out, sizeof(out), "%d | %s | %s | %s%s\n", b->id, b->title, b->author, status, who);
    send_text(fd, out);
}
static Hold *first_hold(int book_id) {
    for (int i = 0; i < hold_count; i++)
        if (holds[i].book == book_id && !holds[i].state) return &holds[i];
    return NULL;
}
/* Called with the library mutex held. All changes share one atomic snapshot. */
static int circulation(int fd, int argc, char **a) {
    char out[LINE_SIZE];
    if (!strcmp(a[0], "STOCK_ADD") && argc == 4) {
        int quantity = number(a[3]);
        if (!field_ok(a[1]) || !field_ok(a[2]) || quantity < 1 || quantity > 50)
            send_text(fd, "ERROR Enter a title, author and quantity from 1 to 50\n");
        else if (quantity > MAX_BOOKS - count || next_id > 1000000000 - quantity)
            send_text(fd, "ERROR Library capacity reached\n");
        else {
            int old_count = count, old_id = next_id;
            for (int i = 0; i < quantity; i++) {
                Book *b = &books[count++]; memset(b, 0, sizeof(*b));
                b->id = next_id++;
                strcpy(b->title, a[1]); strcpy(b->author, a[2]);
            }
            if (save()) { count = old_count; next_id = old_id; send_text(fd, "ERROR Could not save stock\n"); }
            else { snprintf(out, sizeof(out), "OK %d copies added\n", quantity); send_text(fd, out); }
        }
    } else if (!strcmp(a[0], "STOCK_SET") && argc == 3) {
        Book *b = NULL;
        for (int i = 0; i < count; i++) if (books[i].id == number(a[1])) b = &books[i];
        int new_state = !strcmp(a[2], "ACTIVE") ? 0 : !strcmp(a[2], "DAMAGED") ? 1 : !strcmp(a[2], "LOST") ? 2 : !strcmp(a[2], "REMOVED") ? 3 : -1;
        if (!b || new_state < 0) send_text(fd, "ERROR Select a copy and status ACTIVE, DAMAGED, LOST or REMOVED\n");
        else if (*b->borrower || first_hold(b->id)) send_text(fd, "ERROR Return the copy and clear reservations before changing stock status\n");
        else {
            int old_state = b->stock_state; b->stock_state = new_state;
            if (save()) { b->stock_state = old_state; send_text(fd, "ERROR Could not save stock status\n"); }
            else send_text(fd, "OK Stock status updated\n");
        }
    } else if (!strcmp(a[0], "MEMBERS") && argc == 1) {
        for (int i = 0; i < member_count; i++) {
            snprintf(out, sizeof(out), "%d | %s | %s\n", members[i].id, members[i].name, members[i].email); send_text(fd, out);
        }
    } else if (!strcmp(a[0], "MEMBER_ADD") && argc == 3 && field_ok(a[1]) && field_ok(a[2]) && strchr(a[2], '@')) {
        for (int i = 0; i < member_count; i++) if (!strcmp(members[i].email, a[2])) { send_text(fd, "ERROR Email already registered\n"); return 1; }
        if (member_count == 1000) { send_text(fd, "ERROR Member capacity reached\n"); return 1; }
        Member *m = &members[member_count]; m->id = member_count + 1;
        strcpy(m->name, a[1]); strcpy(m->email, a[2]); member_count++;
        if (save()) { member_count--; send_text(fd, "ERROR Could not save member\n"); }
        else send_text(fd, "OK Member registered\n");
    } else if (!strcmp(a[0], "LOANS") && argc == 1) {
        for (int i = loan_count - 1; i >= 0; i--) {
            Loan *l = &loans[i];
            snprintf(out, sizeof(out), "%d | %d | %d | %ld | %ld | %ld | %d\n", l->id, l->book, l->member, l->issued, l->due, l->returned, l->renewals); send_text(fd, out);
        }
    } else if (!strcmp(a[0], "HOLDS") && argc == 1) {
        for (int i = 0; i < hold_count; i++) {
            Hold *h = &holds[i];
            snprintf(out, sizeof(out), "%d | %d | %d | %ld | %d\n", h->id, h->book, h->member, h->placed, h->state);
            send_text(fd, out);
        }
    } else if (!strcmp(a[0], "HOLD") && argc == 3) {
        int bid = number(a[1]), mid = number(a[2]), found_book = 0, found_member = 0;
        for (int i = 0; i < count; i++) if (books[i].id == bid && !books[i].stock_state) found_book = 1;
        for (int i = 0; i < member_count; i++) if (members[i].id == mid) found_member = 1;
        if (!found_book || !found_member) send_text(fd, "ERROR Select an existing book and member\n");
        else if (hold_count == 10000) send_text(fd, "ERROR Hold capacity reached\n");
        else {
            int duplicate = 0;
            for (int i = 0; i < hold_count; i++) if (holds[i].book == bid && holds[i].member == mid && !holds[i].state) duplicate = 1;
            if (duplicate) send_text(fd, "ERROR Member already has a hold on this copy\n");
            else {
                holds[hold_count] = (Hold){hold_count + 1, bid, mid, (long)time(NULL), 0}; hold_count++;
                if (save()) { hold_count--; send_text(fd, "ERROR Could not save hold\n"); }
                else send_text(fd, "OK Hold placed\n");
            }
        }
    } else if (!strcmp(a[0], "CANCEL_HOLD") && argc == 2) {
        Hold *h = NULL;
        for (int i = 0; i < hold_count; i++) if (holds[i].id == number(a[1])) h = &holds[i];
        if (!h || h->state) send_text(fd, "ERROR Active hold not found\n");
        else { h->state = 2;
            if (save()) { h->state = 0; send_text(fd, "ERROR Could not cancel hold\n"); }
            else send_text(fd, "OK Hold cancelled\n");
        }
    } else if (!strcmp(a[0], "RENEW") && argc == 3) {
        Loan *l = NULL; int days = number(a[2]);
        for (int i = 0; i < loan_count; i++) if (loans[i].id == number(a[1])) l = &loans[i];
        if (!l || l->returned) send_text(fd, "ERROR Active loan not found\n");
        else if (days < 1 || days > 30) send_text(fd, "ERROR Renewal must be 1–30 days\n");
        else if (!l->due || l->renewals >= 2) send_text(fd, "ERROR Renewal limit reached or legacy loan has no due date\n");
        else if (first_hold(l->book)) send_text(fd, "ERROR Cannot renew a copy with a pending hold\n");
        else {
            long old_due = l->due, base = (long)time(NULL);
            if (old_due > base) base = old_due;
            l->due = base + days * 86400L; l->renewals++;
            if (save()) { l->due = old_due; l->renewals--; send_text(fd, "ERROR Could not save renewal\n"); }
            else send_text(fd, "OK Loan renewed\n");
        }
    } else if (!strcmp(a[0], "CHECKOUT") && argc == 4) {
        int bid = number(a[1]), mid = number(a[2]), days = number(a[3]); Book *b = NULL; Member *m = NULL; int active = 0;
        for (int i = 0; i < count; i++) if (books[i].id == bid) b = &books[i];
        for (int i = 0; i < member_count; i++) if (members[i].id == mid) m = &members[i];
        for (int i = 0; i < loan_count; i++) if (loans[i].member == mid && !loans[i].returned) active++;
        if (!b || !m || days < 1 || days > 60) send_text(fd, "ERROR Select a registered member, valid book, and 1–60 loan days\n");
        else if (b->stock_state) send_text(fd, "ERROR Copy is not available for checkout\n");
        else if (*b->borrower) send_text(fd, "ERROR Book already borrowed\n");
        else if (first_hold(bid) && first_hold(bid)->member != mid) send_text(fd, "ERROR Copy reserved for another member\n");
        else if (active >= 5 || loan_count == 10000) send_text(fd, "ERROR Loan limit reached (5 active loans per member)\n");
        else {
            Hold *h = first_hold(bid);
            long now = (long)time(NULL); Loan l = {loan_count + 1, bid, mid, now, now + days * 86400L, 0, 0};
            loans[loan_count++] = l; strcpy(b->borrower, m->name);
            if (h) h->state = 1;
            if (save()) { loan_count--; b->borrower[0] = 0; if (h) h->state = 0; send_text(fd, "ERROR Could not save checkout\n"); }
            else send_text(fd, "OK Checkout recorded\n");
        }
    } else if (!strcmp(a[0], "CHECKIN") && argc == 2) {
        Loan *l = NULL; Book *b = NULL;
        for (int i = 0; i < loan_count; i++) if (loans[i].id == number(a[1])) l = &loans[i];
        if (l) for (int i = 0; i < count; i++) if (books[i].id == l->book) b = &books[i];
        if (!l || !b || l->returned) send_text(fd, "ERROR Active loan not found\n");
        else {
            Book old = *b; l->returned = (long)time(NULL); b->borrower[0] = 0;
            if (save()) { *b = old; l->returned = 0; send_text(fd, "ERROR Could not save return\n"); }
            else send_text(fd, "OK Return recorded; loan retained in history\n");
        }
    } else if (!strcmp(a[0], "EDIT") && argc == 4 && field_ok(a[2]) && field_ok(a[3])) {
        Book *b = NULL;
        for (int i = 0; i < count; i++) if (books[i].id == number(a[1])) b = &books[i];
        if (!b) send_text(fd, "ERROR Book not found\n");
        else { Book old = *b; strcpy(b->title, a[2]); strcpy(b->author, a[3]);
            if (save()) { *b = old; send_text(fd, "ERROR Could not save changes\n"); }
            else send_text(fd, "OK Book updated\n"); }
    } else return 0;
    return 1;
}
static int tracked_book(int id) {
    for (int i = 0; i < loan_count; i++) if (loans[i].book == id && !loans[i].returned) return 1;
    return 0;
}
static void handle(int fd, char *line) {
    char *args[5]; int argc = 0;
    args[argc++] = line;
    for (char *p = line; *p; p++) if (*p == '\t') {
        *p = 0; if (argc == 5) { send_text(fd, "ERROR Too many fields\nEND\n"); return; }
        args[argc++] = p + 1;
    }
    pthread_mutex_lock(&lock);
    if (circulation(fd, argc, args)) { /* completed by circulation service */ }
    else if ((!strcmp(args[0], "LIST") && argc == 1) || (!strcmp(args[0], "SEARCH") && argc == 2)) {
        int found = 0;
        for (int i = 0; i < count; i++) if (argc == 1 || strstr(books[i].title, args[1]) || strstr(books[i].author, args[1])) { row(fd, &books[i]); found++; }
        if (!found) send_text(fd, "No books found.\n");
    } else if (!strcmp(args[0], "ADD") && argc == 3 && field_ok(args[1]) && field_ok(args[2])) {
        if (count == MAX_BOOKS || next_id >= 1000000000) send_text(fd, "ERROR Library capacity reached\n");
        else {
            Book *b = &books[count++]; memset(b, 0, sizeof(*b)); b->id = next_id++;
            strcpy(b->title, args[1]); strcpy(b->author, args[2]);
            if (save()) { count--; next_id--; send_text(fd, "ERROR Could not save book\n"); }
            else { send_text(fd, "OK Book added\n"); row(fd, b); }
        }
    } else if ((!strcmp(args[0], "BORROW") || !strcmp(args[0], "RETURN")) && argc == 3 && number(args[1]) > 0 && field_ok(args[2]) && strcmp(args[2], "-")) {
        Book *b = NULL;
        for (int i = 0; i < count; i++) if (books[i].id == number(args[1])) b = &books[i];
        int borrowing = !strcmp(args[0], "BORROW");
        if (!b) send_text(fd, "ERROR Book not found\n");
        else if (borrowing && *b->borrower) send_text(fd, "ERROR Book already borrowed\n");
        else if (borrowing && b->stock_state) send_text(fd, "ERROR Copy is not available for borrowing\n");
        else if (borrowing && first_hold(b->id)) send_text(fd, "ERROR Copy reserved; use CHECKOUT for the first waiting member\n");
        else if (!borrowing && tracked_book(b->id)) {
            Loan *legacy = NULL;
            for (int i = 0; i < loan_count; i++)
                if (loans[i].book == b->id && !loans[i].returned && !loans[i].issued)
                    legacy = &loans[i];
            if (!legacy || strcmp(b->borrower, args[2]))
                send_text(fd, "ERROR Use CHECKIN with the loan ID for tracked loans\n");
            else {
                Book old = *b;
                legacy->returned = (long)time(NULL); b->borrower[0] = 0;
                if (save()) { *b = old; legacy->returned = 0; send_text(fd, "ERROR Could not save return\n"); }
                else send_text(fd, "OK Book returned\n");
            }
        }
        else if (!borrowing && strcmp(b->borrower, args[2])) send_text(fd, "ERROR Borrower does not match or book is available\n");
        else {
            Book old = *b;
            strcpy(b->borrower, borrowing ? args[2] : "");
            if (save()) { *b = old; send_text(fd, "ERROR Could not save changes\n"); }
            else send_text(fd, borrowing ? "OK Book borrowed\n" : "OK Book returned\n");
        }
    } else send_text(fd, "ERROR Invalid command or fields (maximum 159 bytes per field)\n");
    pthread_mutex_unlock(&lock);
    send_text(fd, "END\n");
}
static void *session(void *arg) {
    int fd = *(int *)arg; free(arg);
    struct timeval timeout = {60, 0};
    setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
    setsockopt(fd, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));
    char line[LINE_SIZE];
    while (!read_line(fd, line, sizeof(line))) {
        if (!strncmp(line, "GET ", 4) || !strncmp(line, "POST ", 5)) { http_serve(fd, line, handle); break; }
        if (!strcmp(line, "QUIT")) break;
        handle(fd, line);
    }
    close(fd); return NULL;
}
int main(int argc, char **argv) {
    int port = argc > 1 ? number(argv[1]) : 5050;
    const char *host = argc > 2 ? argv[2] : "127.0.0.1";
    if (argc > 3) database = argv[3];
    if (argc > 4 || port < 1 || port > 65535) { fprintf(stderr, "Usage: %s [port] [bind_ipv4] [database]\n", argv[0]); return 1; }
    if (load()) { fprintf(stderr, "Cannot read database or invalid records: %s\n", database); return 1; }
    signal(SIGPIPE, SIG_IGN);
    int fd = socket(AF_INET, SOCK_STREAM, 0), yes = 1;
    if (fd < 0) { perror("socket"); return 1; }
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
    struct sockaddr_in addr = {0}; addr.sin_family = AF_INET; addr.sin_port = htons((unsigned short)port);
    if (inet_pton(AF_INET, host, &addr.sin_addr) != 1) { fprintf(stderr, "Invalid bind IPv4\n"); close(fd); return 1; }
    if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) || listen(fd, 16)) { perror("server"); close(fd); return 1; }
    printf("Library server on %s:%d; database: %s\n", host, port, database); fflush(stdout);
    for (;;) {
        int peer = accept(fd, NULL, NULL);
        if (peer < 0) { if (errno == EINTR) continue; perror("accept"); break; }
        int *p = malloc(sizeof(*p));
        if (!p) { close(peer); continue; }
        *p = peer; pthread_t thread;
        if (pthread_create(&thread, NULL, session, p)) { close(peer); free(p); }
        else pthread_detach(thread);
    }
    close(fd); return 1;
}
