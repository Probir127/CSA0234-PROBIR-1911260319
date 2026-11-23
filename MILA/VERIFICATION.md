# Verification Record

Verified on **23 November 2026** with Apple Clang 21.0.0 on macOS ARM64
(`Darwin arm64`) and Python 3.15.2. This is technical execution evidence for the
included programs, not evidence of classroom participation or an official grade.

## Strict build and behavioral tests

From `MILA/`:

```sh
make test
```

All eight programs compiled with:

```text
-std=c11 -Wall -Wextra -Wpedantic -Werror -O2
```

The Python standard-library test runner reported:

```text
test_bounds ... ok
test_input_contracts ... ok
test_inventory ... ok
test_jigsaw ... ok
test_pogil ... ok
test_primes ... ok
test_quiz ... ok
test_search ... ok
test_swap ... ok
Ran 9 tests
OK
```

Each named test contains multiple cases. Checks exercise the actual executable
interfaces: exit codes, standard output, and standard error. Examples include:

| Area | Evidence checked |
| --- | --- |
| Arrays and statistics | Known sums and means; singleton, all-negative, mixed-sign, and maximum-size inputs |
| Numeric limits | Sums beyond 32-bit range; `INT_MIN`/`INT_MAX` on the verified platform; maximum permitted inventory value |
| Inventory | Exact cent arithmetic, zero stock, zero price, rejected negative and excessive fields |
| Primes | Values below two, smallest primes, square 49, prime 97, and large 32-bit values |
| Bounds correction | Empty array, one element, 100 elements, invalid count, missing element |
| Quiz | Full, zero, and partial scores; per-answer feedback counts; invalid choices |
| Swap | Caller unchanged after scalar-copy call; exchanged after pointer call; equal and extreme values |
| Search | First/middle/last matches, absent keys, empty/singleton arrays, negative and duplicate keys, rejected unsorted input |
| Shared parser | Empty input, malformed token, oversized token, out-of-range integer, incomplete data, and extra input |

## Memory and undefined-behavior checks

The eight programs were rebuilt and the same test suite was run with both
AddressSanitizer and UndefinedBehaviorSanitizer:

```sh
make clean
make test CFLAGS='-std=c11 -Wall -Wextra -Wpedantic -Werror -O1 -g -fsanitize=address,undefined -fno-omit-frame-pointer'
```

Result: **all nine test groups passed**, exit status 0. No sanitizer diagnostics
appeared during the tested runs.

## Limits and reproducibility

- The tests are selected examples and boundaries; they are not a proof for all
  inputs or a measurement of educational outcomes.
- C sources target C11. This run used a platform with 32-bit `int`; test cases
  containing its extreme integer values assume that range. Other platforms
  were not executed.
- Means are printed to two decimal places. Inventory values use integer cents
  and do not apply taxes, discounts, or currency-specific rounding rules.
- The intentionally faulty snippet in the report is discussion material; it is
  excluded from builds and was not executed.
- Markdown links within the new portfolio are checked against the source files.
  Mermaid source is included for GitHub rendering; no browser rendering check
  was performed because browser control was unavailable.
- Generated executables are excluded from Git. Rebuild with `make clean` and
  `make test` when changing compiler flags, since Make does not track flag changes.

## Local runner and usage demo

On 23 November 2026, `make test-runner` passed all four integration test groups.
The checks start a temporary loopback server and verify actual C results, invalid
input, program selection restrictions, request validation, origin handling, and
the served page. The browser usage scenarios in [demo/README.md](demo/README.md)
were also operated and checked through the visible interface. The 1:38 video
uses actual captured browser screens; the encoded MP4 decoded end to end without
FFmpeg errors.
