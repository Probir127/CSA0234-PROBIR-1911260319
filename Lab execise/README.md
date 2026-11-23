# Lab Exercises - CSA0234 C Programming

**PROBIR SAHA SHOHOM - 1911260319**

Completed implementations of all **120 numbered experiments** in the supplied
[List of Lab Experiments](List%20of%20Lab%20Experiments.pdf). Each experiment has
its own C source, sample input, and observed output. Programs are educational
examples; the small management exercises are local, in-memory demonstrations.

- [Experiment index: all 120 source files](EXPERIMENT_INDEX.md)
- [Lab record: input contracts, run commands, and actual outputs](LAB_RECORD.md)
- [Build and test evidence](VERIFICATION.md)
- [Machine-readable catalogue](experiments.json) and [sample results](sample-results.json)

## Build and run

Requirements: a C11 compiler and Make. Python 3 is required only for tests.
The verified environment is macOS ARM64 with Apple Clang 21.0.0. Experiment 117
and one file-copy test use POSIX file metadata/symlinks; macOS and Linux provide
these interfaces. No third-party C or Python packages are required to run tests.

From the repository root:

```sh
cd 'Lab execise'
make -j4
./build/009_temperature_conversion_celsius_to_fahrenheit_and_back < inputs/009.txt
make test
```

Expected temperature-conversion result:

```text
Fahrenheit: 212.00
```

Each executable reads standard input. You can redirect a sample file, pipe
values, or enter them yourself. The shared input check waits for EOF after the
required fields: press Ctrl+D on macOS/Linux when entering data interactively.
For example, the reverse conversion is:

```sh
printf 'F 32\n' | ./build/009_temperature_conversion_celsius_to_fahrenheit_and_back
```

Expected result: `Celsius: 0.00`.

To compile one exercise directly (keep `lab.h` beside the C files):

```sh
cc -std=c11 -Wall -Wextra -Wpedantic -Werror \
  src/009_temperature_conversion_celsius_to_fahrenheit_and_back.c \
  -o temperature -lm
```

The numbered files contain the algorithms; [src/lab.h](src/lab.h) provides
bounded input conversion, common record types, and small shared helpers.
No other numbered source file needs to be linked into an executable.

## Coverage

| Numbers | Areas |
| --- | --- |
| 001-024 | Structured layout, types/ranges, arithmetic formulas, constants, macros, enums, storage classes |
| 025-048 | Operators, decisions, calculator, grades, roots, loops, number algorithms, patterns, menus |
| 049-072 | Arrays, searching, sorting, merging, matrices, string algorithms |
| 073-096 | Structures, nested records, management menus, unions, bit fields, polynomial addition |
| 097-120 | Functions, recursion, pointers, dynamic allocation, linked lists, text/binary files, random access |

## Input and interpretation choices

The source list gives program names, not complete input/output specifications.
[LAB_RECORD.md](LAB_RECORD.md) states the chosen format and limits for every
exercise. These make the programs reproducible without inventing a hidden rubric.

- Integer and real inputs are range-checked. Non-numeric, missing, excessive,
  non-finite, and unexpected extra inputs produce an `Error:` message on standard
  error and exit status 1. Earlier output may already have been printed.
- Valid runs exit 0. Semantic menu failures such as unavailable books,
  insufficient funds, and occupied seats are reported without changing the
  affected record; the menu can continue.
- Text input uses a full line of at most 255 bytes. Put a newline after numeric
  fields when the next field is a name or text line. Strings use byte-oriented
  comparisons; their examples use ASCII. Anagrams ignore letter case and
  whitespace and reject other characters.
- Array sizes are at most 100, matrices at most 10 by 10. Other limits appear
  in the record and source comments. Search indices are zero-based; `-1` means
  absent. Binary search validates sorted order and may return any duplicate match.
- Grades use A >= 90, B >= 80, C >= 70, D >= 60, else F. Compound interest uses
  annual compounding. Year/week conversion uses fixed 365-day years. Time
  difference means an absolute difference within one day.
- Exercise 005 uses unsigned XOR swapping. Exercise 022 demonstrates defined
  unsigned wrap and detects the signed boundary instead of executing signed
  overflow, which is undefined in C. Macro examples use arguments without side
  effects. Primitive type sizes, pointer addresses, padding, and bit-field
  layout depend on the compiler/platform.
- C passes arguments by value, including pointer values. Exercises whose
  source-list titles say "reference" demonstrate modification through a pointer.
- Management programs 083, 084, 086, and 095 use bounded menu-driven records in
  memory; they are separate experiments, not the full capstone application.

## File exercises

Run these in a scratch working directory if you want to preserve existing files.
The included [input.txt](input.txt) contains the text used by examples 117/118.

| Exercise | File behavior |
| --- | --- |
| 116 | Overwrites `notes.txt`, closes it, reopens it, and displays its text |
| 117 | Reads source/destination paths from two lines; overwrites destination; rejects paths naming the same inode |
| 118 | Counts bytes, whitespace-delimited words, and lines; an unterminated final line is counted |
| 119 | Overwrites `students.dat` with a native count and raw student records, then retrieves them |
| 120 | Uses `ftell` and `fseek` to locate, update, and re-read an existing student record in that file |

Run 119 before 120 in the same working directory:

```sh
./build/119_store_and_retrieve_structure_records_using_a_binary_file < inputs/119.txt
./build/120_update_a_record_using_fseek_and_ftell_random_access < inputs/120.txt
```

The binary format intentionally demonstrates raw structure I/O. It is only for
the same compiler, structure layout, and platform; it is not an interchange
format. The random-access exercise updates in place and is not a transactional
database. File creation, conversion, read/write, positioning, and close errors
are checked where they occur.

## Verification

```sh
make -j4 test
make -j4 sanitize
```

The sanitizer target builds into `build-sanitize/` with AddressSanitizer and
UndefinedBehaviorSanitizer. Test runs use temporary directories and verify
actual executable outputs, menu state changes, file bytes, and random-access
record updates. [VERIFICATION.md](VERIFICATION.md) records the results.

`make clean` removes both build directories. Generated executables and runtime
data files are excluded from Git.
