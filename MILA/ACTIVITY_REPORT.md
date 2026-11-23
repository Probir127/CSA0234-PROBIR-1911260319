# MILA Activity Report — C Programming

**Student:** PROBIR SAHA SHOHOM  
**Register number:** 1911260319  
**Course:** CSA0234 — C Programming

## Purpose and scope

Apply the nine MILA approaches in the supplied Classroom description to core C
concepts: arrays, functions, structures, control flow, pointers, searching, and
safe input handling. Each activity contains a learning objective, a worked
exercise, and an explanation of the result.

This is an individual portfolio prepared from the visible assignment description.
The C exercises were selected to illustrate those methods because no separate
worksheet was supplied. Team roles, peer instruction, and classroom timings below
are proposed facilitation plans. They are not records of sessions conducted,
peer scores, or instructor approval. Program execution is documented separately
in [VERIFICATION.md](VERIFICATION.md).

## 1. POGIL — Process Oriented Guided Inquiry Learning

**Objective:** Discover how array traversal and accumulation calculate a sum and
mean. **Artifact:** [01_pogil_arrays.c](src/01_pogil_arrays.c).

**Model:** An array contains `1, 2, 3, 4, 5`. The program starts with `sum = 0`
and visits indices from `0` while `i < n`.

| Iteration | Index `i` | Element | Sum before | Sum after |
| --- | --- | --- | --- | --- |
| 1 | 0 | 1 | 0 | 1 |
| 2 | 1 | 2 | 1 | 3 |
| 3 | 2 | 3 | 3 | 6 |
| 4 | 3 | 4 | 6 | 10 |
| 5 | 4 | 5 | 10 | 15 |

**Guided questions and worked answers**

1. **Why start at index zero?** C array indexing identifies offsets from the
   beginning. The first element has offset zero.
2. **What does `sum` represent before iteration `i`?** The sum of the first `i`
   elements. Initially no elements have been processed, so the sum is zero.
3. **Why use `i < n`?** The last valid index is `n - 1`; `n` is outside the array
   portion containing the input.
4. **Why convert before division?** `(double)sum / n` performs floating-point
   division. Integer division would discard the fractional part.
5. **Why reject `n = 0` here?** A mean needs at least one observation; division
   by zero must be prevented.

**Worked run:** Input `5 1 2 3 4 5` produces `Sum: 15` and `Mean: 3.00`.
Input `3 -5 0 2` produces sum `-3` and mean `-1.00`.

**Inference:** The loop invariant explains correctness: each step adds the next
element, and at termination all `n` elements have been included. The traversal
takes O(n) time. This implementation stores at most 100 integers; it could also
compute the same result using a running total without retaining the array.

**Facilitation plan:** A manager coordinates the questions, a recorder fills the
trace table, and a presenter explains the invariant. Rotate roles for a second
array. **Reflection:** Predicting state changes before execution makes a loop's
termination condition and accumulated result easier to justify.

## 2. Jigsaw — Expert Groups and Integration

**Objective:** Break a statistics program into independently explainable
functions, then combine them. **Artifact:**
[02_jigsaw_statistics.c](src/02_jigsaw_statistics.c).

**Problem:** For `12, 7, 19, 7, 5`, find the minimum, maximum, sum, and mean.

| Proposed expert role | Component | Contract / explanation |
| --- | --- | --- |
| Input expert | `read_values` | Fill exactly `n` integers; reject failed conversions and extra input |
| Extrema expert | `minimum`, `maximum` | For `n >= 1`, initialize from element zero and compare the rest |
| Aggregation expert | `total` | Return a `long long` sum of all values |
| Integration expert | `main` | Validate count, call components, and calculate a floating-point mean |

**Worked integration:** The minimum is `5`, maximum `19`, sum
`12 + 7 + 19 + 7 + 5 = 50`, and mean `50 / 5 = 10.00`.

```text
Min: 5
Max: 19
Sum: 50
Mean: 10.00
```

**Teach-back questions and answers:**

- Initializing the maximum to zero fails for an all-negative array; initializing
  from the first element makes the starting candidate a real observation.
- The calculation functions use `const int values[]` because they inspect the
  elements without modifying them.
- The caller establishes `1 <= n <= 100`, so extrema functions may safely read
  `values[0]` and the mean has a nonzero divisor.
- Each calculation is O(n); a fixed number of complete passes is still O(n).

**Facilitation plan:** Experts first explain their component to peers, then join
mixed groups to review the contracts and integrated output. **Reflection:** Clear
contracts allow components to fit together without relying on hidden assumptions.

## 3. SCALE-UP — Collaborative Problem Solving

**Objective:** Translate a realistic inventory problem into structures and exact
integer arithmetic. **Artifact:**
[03_scale_up_inventory.c](src/03_scale_up_inventory.c).

**Challenge:** A shop needs the value of its stock. Each item has a quantity and
a unit price. Use integer cents so decimal money values are represented exactly
within the stated bounds.

| Item | Quantity | Unit price in cents | Line value in cents |
| --- | --- | --- | --- |
| A | 2 | 1250 | 2500 |
| B | 3 | 499 | 1497 |
| C | 0 | 999 | 0 |
| **Total** | | | **3997** |

**Worked solution:** Define an `Item` structure with `quantity` and
`unit_price_cents`. For each item, multiply after converting the quantity to
`long long`, then add to a wide total. Input `3 2 1250 3 499 0 999` yields:

```text
Total cents: 3997
Total value: 39.97
```

**Discussion answers:**

- A zero quantity contributes zero and is valid. A negative quantity is outside
  this inventory model and is rejected.
- With 100 items, quantity at most 10000, and price at most 1000000 cents, the
  maximum total is `1000000000000` cents. Multiplication must widen before the
  product is formed, not after overflowing an `int`.
- Display uses quotient and remainder: cents divided by 100 gives whole units;
  the remainder is printed with two digits.
- Floating-point prices would require a rounding policy. Integer cents avoid
  that issue for this two-decimal-place model.

**Facilitation plan:** One learner models the data, another checks the arithmetic
and limits, and another challenges assumptions with zero-stock and maximum-value
cases. Compare results on a shared table before implementation.
**Reflection:** A useful model needs both a formula and an explicit domain.

## 4. PLTBL — Peer-Led Team-Based Learning

**Objective:** Explain prime checking, challenge edge cases, and justify an
efficient stopping condition. **Artifact:** [04_pltbl_prime.c](src/04_pltbl_prime.c).

**Problem:** Determine whether an integer is prime. A prime is an integer at
least two with no positive divisors other than one and itself.

**Worked algorithm:** Reject values below two. Try divisors starting at two.
If any divides evenly, return false. Stop when `divisor > n / divisor`.

| Input | Reason | Result |
| --- | --- | --- |
| -3, 0, 1 | All below two | Not prime |
| 2 | No candidate divisor is needed | Prime |
| 49 | Divisor 7 divides evenly | Not prime |
| 97 | No divisor from 2 through 9 divides evenly | Prime |

**Peer leader's questions and worked answers:**

1. **Why is checking up to the square root sufficient?** If `n = a * b` is
   composite, both factors cannot exceed the square root; at least one factor
   is small enough to be found.
2. **Why use `<=`, not `<`, in the stopping condition?** A perfect square such
   as 49 needs its square-root divisor checked.
3. **Why compare `divisor <= n / divisor`?** It expresses the square-root limit
   without risking overflow in `divisor * divisor`.
4. **What is the complexity?** O(sqrt(n)) trial divisions and O(1) extra space.

**Facilitation plan:** The peer leader elicits predictions, asks another learner
to trace 49, and has the team review 1 and 2. The faculty facilitator can prompt
an explanation when the team cannot justify the loop condition.
**Reflection:** Boundary examples expose mistakes that ordinary prime examples
may hide.

## 5. Concept Mapping

**Objective:** Explain relationships among C concepts, not merely list terms.
**Artifact:** [CONCEPT_MAP.md](CONCEPT_MAP.md), including a Mermaid diagram and
equivalent text propositions.

**Worked task:** Connect arrays to traversal, traversal to statistics, structures
to inventory, functions to decomposition, pointers to object mutation, and
ordered arrays to binary search. Add validation and tests as cross-cutting ideas.

**Relationship explanations:**

- Arrays and loops connect because an index-controlled traversal visits each
  valid element exactly once in the sum examples.
- Functions and pointers connect because a copied pointer can still identify
  an object owned by the caller.
- Data ordering and algorithms connect because binary search relies on sorted
  input to decide which half can be discarded.
- Types and safety connect because even correct arithmetic formulas can fail
  if intermediate values exceed the chosen representation.

**Review question:** Is C pass-by-reference? **Worked answer:** No. C passes
argument values, including pointer values. Modifying `*p` changes the object
identified by the copied address; reassigning local `p` alone does not change
the caller's pointer variable.

**Reflection:** Labelled relationships help transfer an idea such as a function
contract from one activity to a different algorithm.

## 6. Critical Pedagogy — Question, Diagnose, and Correct

**Objective:** Critique a plausible program by identifying assumptions and
testing alternative explanations. **Artifact:**
[05_critical_bounds.c](src/05_critical_bounds.c).

**Faulty fragment for discussion only; it is not executed:**

```c
int n, a[100], sum;
scanf("%d", &n);
for (int i = 0; i <= n; ++i) {
    scanf("%d", &a[i]);
    sum += a[i];
}
```

| Defect or assumption | Consequence | Correction in the runnable program |
| --- | --- | --- |
| `sum` is uninitialized | Reading an indeterminate value is invalid | Initialize a wide sum to zero |
| `i <= n` | Visits one too many elements; may write outside the array | Iterate while `i < n` |
| No bounds check on `n` | A large count exceeds capacity | Accept only 0–100 |
| Conversion results ignored | Malformed or missing input leaves invalid state | Require each bounded conversion to succeed |
| Narrow accumulator | Valid individual inputs can overflow the total | Use `long long` for the aggregate |
| Extra input silently ignored | Input does not match the advertised format | Require only whitespace after the expected fields |

**Worked correction:** Input `3 10 -2 5` yields `Count: 3` and `Sum: 13`.
Input `0` yields `Count: 0` and `Sum: 0`. Input `101` is rejected before any array
access. Input `2 1` is rejected because one element is missing.

**Alternative viewpoint:** Should an empty collection be an error? For a sum,
zero elements can consistently have a total of zero. For a mean, the same
choice would be undefined, which is why the POGIL program requires `n >= 1`.
Validation policy depends on the operation's contract.

**Reflection:** A program that prints a plausible answer once is insufficient
evidence. Question its preconditions, initialization, indexing, and conversions.

## 7. Game-Based Learning / Gamification

**Objective:** Reinforce C concepts through a short quiz with feedback and points.
**Artifact:** [06_quiz.c](src/06_quiz.c).

**Rules:** Five questions, three choices each. One point per correct response;
zero for an incorrect response; no negative marking. Supply five choices in
question order, then the program shows feedback and a score out of five.

| Question | Choices | Correct choice and explanation |
| --- | --- | --- |
| First index of a C array? | 1: 0; 2: 1; 3: -1 | **1.** The first element has index zero |
| Address-of operator? | 1: `*`; 2: `&`; 3: `%` | **2.** Unary `&` obtains an object's address |
| Integer remainder operator? | 1: `/`; 2: `+`; 3: `%` | **3.** `%` computes the integer remainder |
| Stops a loop immediately? | 1: `break`; 2: `continue`; 3: `sizeof` | **1.** `break` exits the innermost loop; `continue` proceeds to its next iteration |
| Binary search requires? | 1: unique keys; 2: sorted input; 3: positive keys | **2.** Ordering enables discarding half the range; duplicates and negative keys are allowed |

**Worked results:** `1 2 3 1 2` scores `5/5`; `2 1 1 2 1` scores `0/5`;
`1 1 3 2 2` scores `3/5`. Choices outside 1–3 are input errors, not wrong answers.

**Facilitation plan:** Learners predict answers before viewing the key, explain
one incorrect answer, then revisit a related code example. The code is a
demonstration quiz, so its answer key is intentionally available for learning.
**Reflection:** Explanations turn a score into useful feedback about a concept.

## 8. Role Play — Function Calls and Memory

**Objective:** Distinguish modifying local scalar copies from modifying objects
through pointers. **Artifact:** [07_role_play_swap.c](src/07_role_play_swap.c).

**Proposed roles:** A caller holds two value cards, a value-function actor holds
copied cards, a pointer-function actor receives address cards, and a memory actor
maintains the caller's original storage. Address cards are symbolic labels;
the program does not rely on a specific numeric memory address.

**Worked script for `a = 10`, `b = 20`:**

1. The caller displays `10 20`.
2. The value-function actor receives copies, exchanges those copies, and displays
   `20 10`. The caller's cards stay `10 20`.
3. After that call returns, the caller still displays `10 20`.
4. The pointer-function actor receives copies of the addresses of the caller's
   objects, reads the first value into a temporary, and writes through those
   addresses to exchange the original values.
5. The caller now displays `20 10`.

```text
Before: 10 20
Inside value function: 20 10
After value call: 10 20
After pointer call: 20 10
```

**Discussion answer:** Both calls pass values. The second passes address values,
so dereferencing them reaches the caller's objects. The temporary preserves the
first value before it is overwritten. This is clearer than an arithmetic swap,
which can overflow and obscures the memory operations being taught.

**Reflection:** Tracking which storage a name or pointer refers to resolves the
apparent contradiction between pass-by-value and caller-visible modification.

## 9. Flipped Classroom — Prepare, Apply, Explain

**Objective:** Use preparation about searching to solve and explain a binary
search problem. **Artifact:** [08_flipped_search.c](src/08_flipped_search.c).

**Preparation material:** Review zero-based arrays, `while` loops, integer
division, and sorted order. Predict why comparing against a middle element can
eliminate candidates. Linear search inspects up to every element; binary search
can repeatedly halve the search interval when the input is ordered.

**Preparation questions and worked answers:**

- **Can binary search be used directly on an unsorted array?** Its elimination
  rule is not valid there; this program rejects unsorted input.
- **How is the middle computed?** `low + (high - low) / 2` avoids forming the
  potentially overflowing sum `low + high` in a general implementation.
- **What represents failure?** Return index `-1`, which is outside valid
  nonnegative array indices.

**Applied challenge:** Find 8 in `[2, 4, 6, 8, 10]`.

| Step | Low | High | Middle | Value | Action |
| --- | --- | --- | --- | --- | --- |
| 1 | 0 | 4 | 2 | 6 | Target is larger; set low to 3 |
| 2 | 3 | 4 | 3 | 8 | Match; return 3 |

Input `5 2 4 6 8 10 8` therefore produces `Index: 3`.
For target 7, the candidate interval becomes empty and the result is `-1`.
For an empty array, `high` starts at `-1`, so no element is accessed.

**Invariant:** If the target exists and has not been found, a matching element
remains within the candidate interval. On each unsuccessful step the interval
shrinks. Duplicate keys are allowed; the returned match need not be the first.

**Complexity distinction:** The search function takes O(log n) time and O(1)
extra space. This complete command-line program also reads and validates all
`n` inputs, so its overall running time is O(n). Storage is bounded by 100
integers in this exercise.

**Facilitation plan:** Use preparation time for the concepts, then classroom time
to trace a missing key, debate preconditions, and test duplicate and boundary
cases. **Reflection:** Preparation is useful when application requires an
explanation of the invariant and preconditions, not just copying the algorithm.

## Technical evidence and learning outcomes

The runnable artifacts demonstrate traversal, modular design, structures, trial
division, bounds correction, feedback scoring, pointer-based mutation, and
binary search. The tests include ordinary examples, boundary sizes, signed
values, large totals, malformed tokens, incomplete input, and extra input.
See [VERIFICATION.md](VERIFICATION.md) for commands and actual results.

The portfolio illustrates how the same C concepts can be explored through
guided discovery, expert explanation, problem solving, peer questioning,
concept relationships, critique, quizzes, role scripts, and preparation followed
by application. It does not establish classroom participation or learning gains
from a conducted group session.
