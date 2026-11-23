# Verification - All 120 Lab Experiments

Verified on **23 November 2026**, on macOS ARM64 with Apple Clang 21.0.0 and
Python 3.15.2. Every number in the supplied PDF maps to one numbered C source,
executable, sample input, and successful sample result.

## Strict build and behavioral checks

```sh
make -j4 test
```

All 120 programs compiled with:

```text
-std=c11 -Wall -Wextra -Wpedantic -Werror -O2
```

The formatted final sources produced:

```text
Ran 130 tests in 5.254s
OK
Executed 422 program invocations across 120 experiments.
```

The suite checks every documented example and rejection of extra input.
Additional checks use known answers and independent properties:

- Numeric boundaries, leap centuries, grades, both temperature directions,
  complex roots, maximum factorial, zero values, and 93 Fibonacci terms.
- Seeded arrays compared with Python sorting/de-duplication; first, last,
  missing, and duplicate search targets; identity matrix multiplication,
  transpose, diagonal sums, and symmetry.
- Empty and maximum-length strings, case sensitivity, concatenation and
  comparison, anagram normalization, character frequencies, and substring search.
- Invalid dates and duplicate rolls; value/pointer mutation; library state,
  bank overdrafts, insufficient inventory, occupied seats, and linked-list
  insertion/deletion/traversal at head, tail, and empty states.
- Exact text and copied-file bytes, same-file/symlink rejection, empty files,
  unterminated lines, binary student records, random-access updates, preserved
  neighboring records, unknown rolls, and truncated files.
- Invalid numbers, missing text, non-finite values, division by zero, excessive
  sizes, unsorted input, invalid choices, and overlong strings.

## Address and undefined-behavior sanitizers

```sh
make -j4 sanitize
```

All 120 programs were independently rebuilt in `build-sanitize/` with:

```text
-std=c11 -Wall -Wextra -Wpedantic -Werror -O1 -g
-fsanitize=address,undefined -fno-omit-frame-pointer
```

Result:

```text
Ran 130 tests in 47.678s
OK
Executed 422 program invocations across 120 experiments.
```

The test runner treats AddressSanitizer, LeakSanitizer, and undefined-behavior
runtime diagnostics as failures. No such diagnostics occurred in these runs.
Selected-case testing is evidence, not proof for all possible inputs.

## Alternate conditional-compilation branch

Experiment 015 was also compiled with `-DLAB_FEATURE=0 -DLAB_FALLBACK=7`.
Actual output:

```text
Feature disabled
Fallback constant: 7
```

The default example exercises the enabled feature and default fallback.

## Sample record and limits

[LAB_RECORD.md](LAB_RECORD.md) and [sample-results.json](sample-results.json)
contain actual outputs from 120 fresh successful runs. Experiment 119 creates
the binary data used by 120. Pointer addresses and native layout values vary;
tests check meaningful phrases or properties rather than a hard-coded address.

The original five-page question PDF is included unchanged. All 120 PDF numbers
were cross-checked against the index and source/input files. Native binary
structures are not a portable interchange format. File tests use temporary
directories. The stated macOS platform was executed; Linux compatibility is
expected from the C11/POSIX interfaces but was not executed here.

No official grade, classroom participation, or instructor approval is claimed.
