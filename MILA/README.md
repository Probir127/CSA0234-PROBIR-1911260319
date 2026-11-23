# MILA Activity — C Programming

**Course:** CSA0234 · **Student:** PROBIR SAHA SHOHOM · **Register number:** 1911260319

This individual learning portfolio applies the nine MILA methods listed in the
provided Classroom assignment description to C programming. MILA means
**Multiple Interactive Learning Algorithm** in that description: short lecture
segments combined with interactive, student-centred activities.

The [activity report](ACTIVITY_REPORT.md) contains worked questions, explanations,
role scripts, and reflections. The [concept map](CONCEPT_MAP.md) connects the C
topics. Eight runnable programs demonstrate the technical activities; concept
mapping is the ninth activity. [Verification](VERIFICATION.md) records execution
evidence and the limits of the checks.

The supplied description lists teaching methods without a separate C worksheet
or required file format. The exercises here are selected applications of those
methods. Collaborative sections are facilitation plans and worked examples;
they do not claim that a group session or peer evaluation has taken place.

## Coverage

| MILA method | C activity | Deliverable |
| --- | --- | --- |
| POGIL | Discover array traversal and an accumulator invariant | [Array sum and mean](src/01_pogil_arrays.c) |
| Jigsaw | Integrate input, extrema, and statistics functions | [Modular statistics](src/02_jigsaw_statistics.c) |
| SCALE-UP | Model and solve an inventory valuation problem | [Struct-based inventory](src/03_scale_up_inventory.c) |
| PLTBL | Reason about and test a prime-checking algorithm | [Prime checker](src/04_pltbl_prime.c) |
| Concept Mapping | Connect syntax, data, control, and algorithms | [Concept map](CONCEPT_MAP.md) |
| Critical Pedagogy | Diagnose bounds, initialization, and input defects | [Corrected array program](src/05_critical_bounds.c) |
| Game-Based Learning | Answer five C questions with points and feedback | [Quiz](src/06_quiz.c) |
| Role Play | Model copies, addresses, and caller memory | [Swap demonstration](src/07_role_play_swap.c) |
| Flipped Classroom | Prepare search concepts, then apply binary search | [Binary search](src/08_flipped_search.c) |

## Build and run

Requirements: a C11 compiler, Make, and Python 3 for tests. No third-party packages.
From the repository root:

```sh
cd MILA
make
printf '5 1 2 3 4 5\n' | ./build/01_pogil_arrays
make test
```

Expected example output:

```text
Sum: 15
Mean: 3.00
```

Programs read whitespace-separated integer tokens from standard input. They are
batch examples: enter the complete input and signal EOF when running interactively.
Successful runs exit 0. Malformed, missing, extra, or out-of-range input exits 1
with `Invalid input` on standard error. [`input.h`](src/input.h) shares bounded
integer parsing so the activities can focus on their C concepts.

| Executable in `build/` | Input format and bounds | Example input |
| --- | --- | --- |
| `01_pogil_arrays` | `n` (1–100), then `n` signed integers | `5 1 2 3 4 5` |
| `02_jigsaw_statistics` | `n` (1–100), then `n` signed integers | `5 12 7 19 7 5` |
| `03_scale_up_inventory` | `n` (1–100), then `quantity price_in_cents` per item; quantity 0–10000, price 0–1000000 | `3 2 1250 3 499 0 999` |
| `04_pltbl_prime` | One signed integer | `97` |
| `05_critical_bounds` | `n` (0–100), then `n` signed integers | `3 10 -2 5` |
| `06_quiz` | Five choices, each 1–3; questions and answer key in the report | `1 2 3 1 2` |
| `07_role_play_swap` | Two signed integers | `10 20` |
| `08_flipped_search` | `n` (0–100), `n` integers in nondecreasing order, then target | `5 2 4 6 8 10 8` |

The verified platform has 32-bit `int`. Values must fit the compiler's `int` range
(`INT_MIN` to `INT_MAX`). Totals use `long long`; the stated bounds keep them
within range on the verified platform. Search returns a zero-based index, or
`-1` for no match; with duplicates it may return any matching index.

`make clean` removes generated executables. Only source, documentation, and tests
are stored in Git.
