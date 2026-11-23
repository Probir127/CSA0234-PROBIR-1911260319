# C Programming Concept Map

Arrows describe relationships rather than a required learning order.

```mermaid
flowchart TD
    C[C programming] --> Data[Data representation]
    C --> Control[Control flow]
    C --> Functions[Functions]
    C --> Safety[Validation and testing]
    Data --> Types[Integer and floating-point types]
    Data --> Arrays[Arrays: contiguous indexed elements]
    Data --> Structs[Structures: related fields]
    Data --> Pointers[Pointers: addresses of objects]
    Types --> Arithmetic[Arithmetic and range limits]
    Arithmetic --> Totals[Wide accumulators and exact money in cents]
    Arrays --> Traversal[Loops visit valid indices 0 through n minus 1]
    Control --> Selection[if / else decisions]
    Control --> Iteration[for / while repetition]
    Iteration --> Traversal
    Traversal --> Statistics[Sum, mean, minimum, maximum]
    Structs --> Inventory[Inventory valuation]
    Totals --> Inventory
    Functions --> Decomposition[Parameters, return values, contracts]
    Decomposition --> Statistics
    Functions --> Value[C passes argument values]
    Value --> Copies[Scalar parameter changes are local]
    Value --> Address[Pointer values can identify caller objects]
    Pointers --> Address
    Address --> Swap[Dereferencing permits caller-object mutation]
    Selection --> Prime[Primality checks]
    Iteration --> Prime
    Arrays --> Sorted[Nondecreasing ordering]
    Sorted --> Binary[Binary search halves a candidate interval]
    Safety --> Input[Check conversion, size, ordering, and EOF]
    Safety --> Bounds[Prevent out-of-bounds access]
    Safety --> Tests[Normal, boundary, and invalid-input cases]
    Input --> Bounds
    Tests --> Statistics
    Tests --> Prime
    Tests --> Binary
```

## Read the map as propositions

1. An array stores elements of one type; loops access them using valid indices.
2. An accumulator combines array values; its type must accommodate the total.
3. A structure groups fields such as quantity and price for one inventory item.
4. Functions split a problem into components with input and output contracts.
5. All C function arguments are passed by value. Passing an address copies a
   pointer value, through which a function can modify the pointed-to object.
6. Binary search needs ordered input and repeatedly reduces the candidate range.
7. Validation establishes preconditions; tests provide evidence for selected cases.

## Worked concept check

**Why do arrays, loops, functions, and testing connect in the statistics activity?**
The array holds the observations, loops inspect each observation, functions
encapsulate separate calculations, and tests check outcomes for positive,
negative, singleton, and extreme values. Each concept has a distinct role in
making the complete program understandable and dependable.
