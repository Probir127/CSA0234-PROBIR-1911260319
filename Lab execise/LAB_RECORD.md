# Completed Lab Experiments

**PROBIR SAHA SHOHOM - 1911260319 - CSA0234 C Programming**

Numbering follows the supplied experiment list. Each source contains the C implementation; the input contract below makes unspecified details explicit. The outputs were captured from actual successful runs on the verified platform.

For each example, run its executable from this folder and redirect the matching file in `inputs/`. Experiment 120 uses the binary file produced by 119; run 119 first in the same working directory. The included `input.txt` supports 117 and 118.

## 001. Hello World Program with Structured Layout

**Topic:** Introduction / CO1

**Input contract:** No input.

[C source](src/001_hello_world_program_with_structured_layout.c) - [Sample input](inputs/001.txt)

```sh
./build/001_hello_world_program_with_structured_layout < inputs/001.txt
```

**Sample input**

```text
(none)
```

**Observed output**

```text
Hello, World!
```

## 002. Display Size and Range of All Primitive Data Types

**Topic:** Introduction / CO1

**Input contract:** No input.

[C source](src/002_display_size_and_range_of_all_primitive_data_types.c) - [Sample input](inputs/002.txt)

```sh
./build/002_display_size_and_range_of_all_primitive_data_types < inputs/002.txt
```

**Sample input**

```text
(none)
```

**Observed output**

```text
char: size=1 range=-128..127
signed char: size=1 range=-128..127
unsigned char: size=1 range=0..255
short: size=2 range=-32768..32767
unsigned short: size=2 range=0..65535
int: size=4 range=-2147483648..2147483647
unsigned int: size=4 range=0..4294967295
long: size=8 range=-9223372036854775808..9223372036854775807
unsigned long: size=8 range=0..18446744073709551615
long long: size=8 range=-9223372036854775808..9223372036854775807
unsigned long long: size=8 range=0..18446744073709551615
float: size=4 lowest=-3.40282e+38 min-positive-normal=1.17549e-38 max=3.40282e+38
double: size=8 lowest=-1.79769e+308 min-positive-normal=2.22507e-308 max=1.79769e+308
long double: size=8 lowest=-1.79769e+308 min-positive-normal=2.22507e-308 max=1.79769e+308
_Bool: size=1 range=0..1
void has no object size or value range. Floating ranges include negative values and zero; minimum shown is positive and normal.
```

## 003. Add Two Integers Read from the User

**Topic:** Introduction / CO1

**Input contract:** Two integers, each -1000000..1000000.

[C source](src/003_add_two_integers_read_from_the_user.c) - [Sample input](inputs/003.txt)

```sh
./build/003_add_two_integers_read_from_the_user < inputs/003.txt
```

**Sample input**

```text
12 -5
```

**Observed output**

```text
Sum: 7
```

## 004. Swap Two Numbers Using a Temporary Variable

**Topic:** Introduction / CO1

**Input contract:** Two integers, each -1000000..1000000.

[C source](src/004_swap_two_numbers_using_a_temporary_variable.c) - [Sample input](inputs/004.txt)

```sh
./build/004_swap_two_numbers_using_a_temporary_variable < inputs/004.txt
```

**Sample input**

```text
10 20
```

**Observed output**

```text
20 10
```

## 005. Swap Two Numbers Without a Temporary Variable

**Topic:** Introduction / CO1

**Input contract:** Two unsigned integers, 0..UINT_MAX; XOR swap.

[C source](src/005_swap_two_numbers_without_a_temporary_variable.c) - [Sample input](inputs/005.txt)

```sh
./build/005_swap_two_numbers_without_a_temporary_variable < inputs/005.txt
```

**Sample input**

```text
10 20
```

**Observed output**

```text
20 10
```

## 006. Area and Circumference of a Circle Using define

**Topic:** Introduction / CO1

**Input contract:** Radius, 0..1000000.

[C source](src/006_area_and_circumference_of_a_circle_using_define.c) - [Sample input](inputs/006.txt)

```sh
./build/006_area_and_circumference_of_a_circle_using_define < inputs/006.txt
```

**Sample input**

```text
2
```

**Observed output**

```text
Area: 12.57
Circumference: 12.57
```

## 007. Simple Interest Calculation

**Topic:** Introduction / CO1

**Input contract:** Principal, annual percentage rate, years; each 0..1000000.

[C source](src/007_simple_interest_calculation.c) - [Sample input](inputs/007.txt)

```sh
./build/007_simple_interest_calculation < inputs/007.txt
```

**Sample input**

```text
1000 5 2
```

**Observed output**

```text
Interest: 100.00
Amount: 1100.00
```

## 008. Compound Interest Calculation

**Topic:** Introduction / CO1

**Input contract:** Principal 0..1000000, annual percentage 0..100, whole years 0..100; annual compounding.

[C source](src/008_compound_interest_calculation.c) - [Sample input](inputs/008.txt)

```sh
./build/008_compound_interest_calculation < inputs/008.txt
```

**Sample input**

```text
1000 10 2
```

**Observed output**

```text
Interest: 210.00
Amount: 1210.00
```

## 009. Temperature Conversion Celsius to Fahrenheit and Back

**Topic:** Introduction / CO1

**Input contract:** Direction C or F, then temperature -1000000..1000000.

[C source](src/009_temperature_conversion_celsius_to_fahrenheit_and_back.c) - [Sample input](inputs/009.txt)

```sh
./build/009_temperature_conversion_celsius_to_fahrenheit_and_back < inputs/009.txt
```

**Sample input**

```text
C 100
```

**Observed output**

```text
Fahrenheit: 212.00
```

## 010. Convert Days into Years Weeks and Days

**Topic:** Introduction / CO1

**Input contract:** Days 0..1000000000; use fixed 365-day years and 7-day weeks.

[C source](src/010_convert_days_into_years_weeks_and_days.c) - [Sample input](inputs/010.txt)

```sh
./build/010_convert_days_into_years_weeks_and_days < inputs/010.txt
```

**Sample input**

```text
400
```

**Observed output**

```text
Years: 1
Weeks: 5
Days: 0
```

## 011. Print the ASCII Value of a Character

**Topic:** Introduction / CO1

**Input contract:** One non-whitespace ASCII character.

[C source](src/011_print_the_ascii_value_of_a_character.c) - [Sample input](inputs/011.txt)

```sh
./build/011_print_the_ascii_value_of_a_character < inputs/011.txt
```

**Sample input**

```text
A
```

**Observed output**

```text
ASCII: 65
```

## 012. Implicit and Explicit Type Casting

**Topic:** Introduction / CO1

**Input contract:** Integer -1000000..1000000, real -1000000..1000000.

[C source](src/012_implicit_and_explicit_type_casting.c) - [Sample input](inputs/012.txt)

```sh
./build/012_implicit_and_explicit_type_casting < inputs/012.txt
```

**Sample input**

```text
7 3.75
```

**Observed output**

```text
Implicit double: 7.00
Explicit integer: 3
Integer division: 3
Floating division: 3.50
```

## 013. Constants Using const and define

**Topic:** Introduction / CO1

**Input contract:** Radius 0..1000000.

[C source](src/013_constants_using_const_and_define.c) - [Sample input](inputs/013.txt)

```sh
./build/013_constants_using_const_and_define < inputs/013.txt
```

**Sample input**

```text
2
```

**Observed output**

```text
PI: 3.141593
Radius: 2.00
Area: 12.57
```

## 014. Macros with Arguments Square and Maximum

**Topic:** Introduction / CO1

**Input contract:** Two integers -1000000..1000000; pass side-effect-free arguments.

[C source](src/014_macros_with_arguments_square_and_maximum.c) - [Sample input](inputs/014.txt)

```sh
./build/014_macros_with_arguments_square_and_maximum < inputs/014.txt
```

**Sample input**

```text
4 7
```

**Observed output**

```text
Square: 16
Maximum: 7
```

## 015. Conditional Compilation Using ifdef and ifndef

**Topic:** Introduction / CO1

**Input contract:** No input. Define LAB_FEATURE=0 at compilation to disable the feature.

[C source](src/015_conditional_compilation_using_ifdef_and_ifndef.c) - [Sample input](inputs/015.txt)

```sh
./build/015_conditional_compilation_using_ifdef_and_ifndef < inputs/015.txt
```

**Sample input**

```text
(none)
```

**Observed output**

```text
Feature enabled
Fallback constant: 42
```

## 016. Area of a Triangle Using Heron Formula

**Topic:** Introduction / CO1

**Input contract:** Three positive side lengths, at most 1000000, satisfying the strict triangle inequality.

[C source](src/016_area_of_a_triangle_using_heron_formula.c) - [Sample input](inputs/016.txt)

```sh
./build/016_area_of_a_triangle_using_heron_formula < inputs/016.txt
```

**Sample input**

```text
3 4 5
```

**Observed output**

```text
Area: 6.00
```

## 017. Total and Average Marks of Five Subjects

**Topic:** Introduction / CO1

**Input contract:** Five marks, each 0..100.

[C source](src/017_total_and_average_marks_of_five_subjects.c) - [Sample input](inputs/017.txt)

```sh
./build/017_total_and_average_marks_of_five_subjects < inputs/017.txt
```

**Sample input**

```text
80 90 70 60 100
```

**Observed output**

```text
Total: 400.00
Average: 80.00
```

## 018. Convert Seconds to HH MM SS

**Topic:** Introduction / CO1

**Input contract:** Seconds 0..1000000000; hours may exceed 23.

[C source](src/018_convert_seconds_to_hh_mm_ss.c) - [Sample input](inputs/018.txt)

```sh
./build/018_convert_seconds_to_hh_mm_ss < inputs/018.txt
```

**Sample input**

```text
3661
```

**Observed output**

```text
01:01:01
```

## 019. Extract the Digits of a Three Digit Number

**Topic:** Introduction / CO1

**Input contract:** Integer 100..999.

[C source](src/019_extract_the_digits_of_a_three_digit_number.c) - [Sample input](inputs/019.txt)

```sh
./build/019_extract_the_digits_of_a_three_digit_number < inputs/019.txt
```

**Sample input**

```text
472
```

**Observed output**

```text
Hundreds: 4
Tens: 7
Units: 2
```

## 020. Distance Between Two Points

**Topic:** Introduction / CO1

**Input contract:** x1 y1 x2 y2, each -1000000..1000000.

[C source](src/020_distance_between_two_points.c) - [Sample input](inputs/020.txt)

```sh
./build/020_distance_between_two_points < inputs/020.txt
```

**Sample input**

```text
0 0 3 4
```

**Observed output**

```text
Distance: 5.00
```

## 021. Formatted Output Using printf Width and Precision

**Topic:** Introduction / CO1

**Input contract:** One real -1000000..1000000.

[C source](src/021_formatted_output_using_printf_width_and_precision.c) - [Sample input](inputs/021.txt)

```sh
./build/021_formatted_output_using_printf_width_and_precision < inputs/021.txt
```

**Sample input**

```text
12.3456
```

**Observed output**

```text
Right: [     12.35]
Left:  [12.35     ]
Precise: 12.3456
```

## 022. Integer Overflow and Underflow Demonstration

**Topic:** Introduction / CO1

**Input contract:** No input; unsigned wrap is defined, signed overflow is prevented.

[C source](src/022_integer_overflow_and_underflow_demonstration.c) - [Sample input](inputs/022.txt)

```sh
./build/022_integer_overflow_and_underflow_demonstration < inputs/022.txt
```

**Sample input**

```text
(none)
```

**Observed output**

```text
Unsigned overflow: 0
Unsigned underflow: 4294967295
Signed overflow/underflow avoided: adding to INT_MAX or subtracting from INT_MIN is undefined.
```

## 023. Days of the Week Using enum

**Topic:** Introduction / CO1

**Input contract:** Day 1..7, Monday=1.

[C source](src/023_days_of_the_week_using_enum.c) - [Sample input](inputs/023.txt)

```sh
./build/023_days_of_the_week_using_enum < inputs/023.txt
```

**Sample input**

```text
3
```

**Observed output**

```text
Wednesday
```

## 024. Storage Classes auto static extern register

**Topic:** Introduction / CO1

**Input contract:** No input.

[C source](src/024_storage_classes_auto_static_extern_register.c) - [Sample input](inputs/024.txt)

```sh
./build/024_storage_classes_auto_static_extern_register < inputs/024.txt
```

**Sample input**

```text
(none)
```

**Observed output**

```text
auto=3 register=5 extern=10
static calls: 1 2
```

## 025. Arithmetic Operators Demonstration

**Topic:** Operators / CO2

**Input contract:** Two integers -1000000..1000000; second must be nonzero.

[C source](src/025_arithmetic_operators_demonstration.c) - [Sample input](inputs/025.txt)

```sh
./build/025_arithmetic_operators_demonstration < inputs/025.txt
```

**Sample input**

```text
17 5
```

**Observed output**

```text
Add: 22
Subtract: 12
Multiply: 85
Divide: 3
Remainder: 2
```

## 026. Relational and Logical Operators Demonstration

**Topic:** Operators / CO2

**Input contract:** Two integers -1000000..1000000.

[C source](src/026_relational_and_logical_operators_demonstration.c) - [Sample input](inputs/026.txt)

```sh
./build/026_relational_and_logical_operators_demonstration < inputs/026.txt
```

**Sample input**

```text
3 5
```

**Observed output**

```text
Equal: 0
Not equal: 1
Less: 1
Greater: 0
Less or equal: 1
Greater or equal: 0
AND: 1
OR: 1
NOT first: 0
```

## 027. Bitwise Operators Demonstration

**Topic:** Operators / CO2

**Input contract:** Two unsigned values 0..65535 and shift 0..15; NOT is explicitly masked to 16 bits.

[C source](src/027_bitwise_operators_demonstration.c) - [Sample input](inputs/027.txt)

```sh
./build/027_bitwise_operators_demonstration < inputs/027.txt
```

**Sample input**

```text
12 10 1
```

**Observed output**

```text
AND: 8
OR: 14
XOR: 6
NOT16: 65523
Left: 24
Right: 6
```

## 028. Even or Odd Using Modulus and Bitwise AND

**Topic:** Operators / CO2

**Input contract:** Integer -1000000..1000000.

[C source](src/028_even_or_odd_using_modulus_and_bitwise_and.c) - [Sample input](inputs/028.txt)

```sh
./build/028_even_or_odd_using_modulus_and_bitwise_and < inputs/028.txt
```

**Sample input**

```text
7
```

**Observed output**

```text
Modulus: Odd
Bitwise: Odd
```

## 029. Largest of Three Numbers Using if else

**Topic:** Decision Making / CO2

**Input contract:** Three integers -1000000..1000000.

[C source](src/029_largest_of_three_numbers_using_if_else.c) - [Sample input](inputs/029.txt)

```sh
./build/029_largest_of_three_numbers_using_if_else < inputs/029.txt
```

**Sample input**

```text
8 3 12
```

**Observed output**

```text
Largest: 12
```

## 030. Leap Year Check

**Topic:** Decision Making / CO2

**Input contract:** Gregorian year 1..9999.

[C source](src/030_leap_year_check.c) - [Sample input](inputs/030.txt)

```sh
./build/030_leap_year_check < inputs/030.txt
```

**Sample input**

```text
2000
```

**Observed output**

```text
Leap year
```

## 031. Simple Calculator Using switch

**Topic:** Decision Making / CO2

**Input contract:** Number, operator (+ - * /), number; magnitudes <=1000000; divisor nonzero.

[C source](src/031_simple_calculator_using_switch.c) - [Sample input](inputs/031.txt)

```sh
./build/031_simple_calculator_using_switch < inputs/031.txt
```

**Sample input**

```text
12 / 4
```

**Observed output**

```text
Result: 3.00
```

## 032. Grade Assignment Using else if Ladder

**Topic:** Decision Making / CO2

**Input contract:** Mark 0..100; A>=90, B>=80, C>=70, D>=60, otherwise F.

[C source](src/032_grade_assignment_using_else_if_ladder.c) - [Sample input](inputs/032.txt)

```sh
./build/032_grade_assignment_using_else_if_ladder < inputs/032.txt
```

**Sample input**

```text
85
```

**Observed output**

```text
Grade: B
```

## 033. Roots of a Quadratic Equation

**Topic:** Decision Making / CO2

**Input contract:** a b c each -1000000..1000000; a must be nonzero; supports complex roots.

[C source](src/033_roots_of_a_quadratic_equation.c) - [Sample input](inputs/033.txt)

```sh
./build/033_roots_of_a_quadratic_equation < inputs/033.txt
```

**Sample input**

```text
1 -5 6
```

**Observed output**

```text
Roots: 3.00 2.00
```

## 034. Vowel or Consonant Using switch

**Topic:** Decision Making / CO2

**Input contract:** One ASCII alphabetic character; case-insensitive.

[C source](src/034_vowel_or_consonant_using_switch.c) - [Sample input](inputs/034.txt)

```sh
./build/034_vowel_or_consonant_using_switch < inputs/034.txt
```

**Sample input**

```text
E
```

**Observed output**

```text
Vowel
```

## 035. Largest and Smallest Using the Ternary Operator

**Topic:** Decision Making / CO2

**Input contract:** Three integers -1000000..1000000.

[C source](src/035_largest_and_smallest_using_the_ternary_operator.c) - [Sample input](inputs/035.txt)

```sh
./build/035_largest_and_smallest_using_the_ternary_operator < inputs/035.txt
```

**Sample input**

```text
8 -3 12
```

**Observed output**

```text
Largest: 12
Smallest: -3
```

## 036. Sum of the First N Natural Numbers

**Topic:** Looping / CO2

**Input contract:** N 0..1000000.

[C source](src/036_sum_of_the_first_n_natural_numbers.c) - [Sample input](inputs/036.txt)

```sh
./build/036_sum_of_the_first_n_natural_numbers < inputs/036.txt
```

**Sample input**

```text
10
```

**Observed output**

```text
Sum: 55
```

## 037. Factorial of a Number Using Loops

**Topic:** Looping / CO2

**Input contract:** N 0..20.

[C source](src/037_factorial_of_a_number_using_loops.c) - [Sample input](inputs/037.txt)

```sh
./build/037_factorial_of_a_number_using_loops < inputs/037.txt
```

**Sample input**

```text
5
```

**Observed output**

```text
Factorial: 120
```

## 038. Fibonacci Series

**Topic:** Looping / CO2

**Input contract:** Term count 0..93, starting 0 1.

[C source](src/038_fibonacci_series.c) - [Sample input](inputs/038.txt)

```sh
./build/038_fibonacci_series < inputs/038.txt
```

**Sample input**

```text
7
```

**Observed output**

```text
0 1 1 2 3 5 8
```

## 039. Prime Number Check

**Topic:** Looping / CO2

**Input contract:** Integer -1000000000..1000000000.

[C source](src/039_prime_number_check.c) - [Sample input](inputs/039.txt)

```sh
./build/039_prime_number_check < inputs/039.txt
```

**Sample input**

```text
97
```

**Observed output**

```text
Prime
```

## 040. Prime Numbers in a Given Range

**Topic:** Looping / CO2

**Input contract:** Inclusive lower and upper endpoints, 0..100000; lower<=upper.

[C source](src/040_prime_numbers_in_a_given_range.c) - [Sample input](inputs/040.txt)

```sh
./build/040_prime_numbers_in_a_given_range < inputs/040.txt
```

**Sample input**

```text
10 20
```

**Observed output**

```text
11 13 17 19
```

## 041. Armstrong Number

**Topic:** Looping / CO2

**Input contract:** Nonnegative integer 0..1000000000; sum each digit raised to the digit count.

[C source](src/041_armstrong_number.c) - [Sample input](inputs/041.txt)

```sh
./build/041_armstrong_number < inputs/041.txt
```

**Sample input**

```text
153
```

**Observed output**

```text
Armstrong
```

## 042. Palindrome Number

**Topic:** Looping / CO2

**Input contract:** Integer 0..1000000000.

[C source](src/042_palindrome_number.c) - [Sample input](inputs/042.txt)

```sh
./build/042_palindrome_number < inputs/042.txt
```

**Sample input**

```text
12321
```

**Observed output**

```text
Palindrome
```

## 043. Reverse a Number

**Topic:** Looping / CO2

**Input contract:** Integer -1000000000..1000000000; preserve its sign.

[C source](src/043_reverse_a_number.c) - [Sample input](inputs/043.txt)

```sh
./build/043_reverse_a_number < inputs/043.txt
```

**Sample input**

```text
-120
```

**Observed output**

```text
Reversed: -21
```

## 044. GCD and LCM of Two Numbers

**Topic:** Looping / CO2

**Input contract:** Two integers 0..1000000000; gcd(0,0)=0 and lcm with zero is 0.

[C source](src/044_gcd_and_lcm_of_two_numbers.c) - [Sample input](inputs/044.txt)

```sh
./build/044_gcd_and_lcm_of_two_numbers < inputs/044.txt
```

**Sample input**

```text
12 18
```

**Observed output**

```text
GCD: 6
LCM: 36
```

## 045. Perfect Number Check

**Topic:** Looping / CO2

**Input contract:** Integer 1..1000000000; compare with the sum of proper positive divisors.

[C source](src/045_perfect_number_check.c) - [Sample input](inputs/045.txt)

```sh
./build/045_perfect_number_check < inputs/045.txt
```

**Sample input**

```text
28
```

**Observed output**

```text
Perfect
```

## 046. Star Pyramid and Diamond Patterns

**Topic:** Looping / CO2

**Input contract:** Row count 1..10.

[C source](src/046_star_pyramid_and_diamond_patterns.c) - [Sample input](inputs/046.txt)

```sh
./build/046_star_pyramid_and_diamond_patterns < inputs/046.txt
```

**Sample input**

```text
2
```

**Observed output**

```text
Pyramid:
 *
***
Diamond:
 *
***
 *
```

## 047. Floyd Triangle and Pascal Triangle

**Topic:** Looping / CO2

**Input contract:** Row count 1..10.

[C source](src/047_floyd_triangle_and_pascal_triangle.c) - [Sample input](inputs/047.txt)

```sh
./build/047_floyd_triangle_and_pascal_triangle < inputs/047.txt
```

**Sample input**

```text
3
```

**Observed output**

```text
Floyd:
1
2 3
4 5 6
Pascal:
1
1 1
1 2 1
```

## 048. Menu Driven Program Using do while break and continue

**Topic:** Looping / CO2

**Input contract:** Commands: 1 a b (add), 2 n (square), 3 (skip), 0 (exit); numbers +/-1000000; at most 1000 commands.

[C source](src/048_menu_driven_program_using_do_while_break_and_continue.c) - [Sample input](inputs/048.txt)

```sh
./build/048_menu_driven_program_using_do_while_break_and_continue < inputs/048.txt
```

**Sample input**

```text
1 2 3 3 2 4 0
```

**Observed output**

```text
Sum: 5
Skipped
Square: 16
```

## 049. Read and Display a One Dimensional Array

**Topic:** Arrays and Searching / CO3

**Input contract:** Count 0..100, then that many integers -1000000..1000000.

[C source](src/049_read_and_display_a_one_dimensional_array.c) - [Sample input](inputs/049.txt)

```sh
./build/049_read_and_display_a_one_dimensional_array < inputs/049.txt
```

**Sample input**

```text
4 9 -2 7 0
```

**Observed output**

```text
9 -2 7 0
```

## 050. Find the Largest and Smallest Element in an Array

**Topic:** Arrays and Searching / CO3

**Input contract:** Count 1..100, then that many integers -1000001..1000000.

[C source](src/050_find_the_largest_and_smallest_element_in_an_array.c) - [Sample input](inputs/050.txt)

```sh
./build/050_find_the_largest_and_smallest_element_in_an_array < inputs/050.txt
```

**Sample input**

```text
4 9 -2 7 0
```

**Observed output**

```text
Largest: 9
Smallest: -2
```

## 051. Reverse an Array

**Topic:** Arrays and Searching / CO3

**Input contract:** Count 0..100, then that many integers -1000000..1000000.

[C source](src/051_reverse_an_array.c) - [Sample input](inputs/051.txt)

```sh
./build/051_reverse_an_array < inputs/051.txt
```

**Sample input**

```text
4 1 2 3 4
```

**Observed output**

```text
4 3 2 1
```

## 052. Linear Search

**Topic:** Arrays and Searching / CO3

**Input contract:** Count 0..100, then that many integers -1000000..1000000. Then target; returns first zero-based index or -1.

[C source](src/052_linear_search.c) - [Sample input](inputs/052.txt)

```sh
./build/052_linear_search < inputs/052.txt
```

**Sample input**

```text
5 7 2 9 2 1 2
```

**Observed output**

```text
Index: 1
```

## 053. Binary Search

**Topic:** Arrays and Searching / CO3

**Input contract:** Count 0..100, then that many integers -1000000..1000000. Nondecreasing order required; then target; returns any matching zero-based index or -1.

[C source](src/053_binary_search.c) - [Sample input](inputs/053.txt)

```sh
./build/053_binary_search < inputs/053.txt
```

**Sample input**

```text
5 2 4 6 8 10 8
```

**Observed output**

```text
Index: 3
```

## 054. Bubble Sort

**Topic:** Sorting and Merging / CO3

**Input contract:** Count 0..100, then that many integers -1000000..1000000.

[C source](src/054_bubble_sort.c) - [Sample input](inputs/054.txt)

```sh
./build/054_bubble_sort < inputs/054.txt
```

**Sample input**

```text
5 4 -1 3 3 0
```

**Observed output**

```text
-1 0 3 3 4
```

## 055. Selection Sort

**Topic:** Sorting and Merging / CO3

**Input contract:** Count 0..100, then that many integers -1000000..1000000.

[C source](src/055_selection_sort.c) - [Sample input](inputs/055.txt)

```sh
./build/055_selection_sort < inputs/055.txt
```

**Sample input**

```text
5 4 -1 3 3 0
```

**Observed output**

```text
-1 0 3 3 4
```

## 056. Insertion Sort

**Topic:** Sorting and Merging / CO3

**Input contract:** Count 0..100, then that many integers -1000000..1000000.

[C source](src/056_insertion_sort.c) - [Sample input](inputs/056.txt)

```sh
./build/056_insertion_sort < inputs/056.txt
```

**Sample input**

```text
5 4 -1 3 3 0
```

**Observed output**

```text
-1 0 3 3 4
```

## 057. Merge Two Sorted Arrays

**Topic:** Sorting and Merging / CO3

**Input contract:** First count and sorted array, then second count and sorted array; each count 0..100, values +/-1000000.

[C source](src/057_merge_two_sorted_arrays.c) - [Sample input](inputs/057.txt)

```sh
./build/057_merge_two_sorted_arrays < inputs/057.txt
```

**Sample input**

```text
3 1 3 5 3 2 4 6
```

**Observed output**

```text
1 2 3 4 5 6
```

## 058. Remove Duplicate Elements from an Array

**Topic:** Sorting and Merging / CO3

**Input contract:** Count 0..100, then that many integers -1000000..1000000. Preserve first-occurrence order.

[C source](src/058_remove_duplicate_elements_from_an_array.c) - [Sample input](inputs/058.txt)

```sh
./build/058_remove_duplicate_elements_from_an_array < inputs/058.txt
```

**Sample input**

```text
6 3 1 3 2 1 2
```

**Observed output**

```text
3 1 2
```

## 059. Matrix Addition and Subtraction

**Topic:** Two-Dimensional Arrays / CO3

**Input contract:** Rows and columns 1..10, then two matrices of that shape in row-major order; entries +/-10000.

[C source](src/059_matrix_addition_and_subtraction.c) - [Sample input](inputs/059.txt)

```sh
./build/059_matrix_addition_and_subtraction < inputs/059.txt
```

**Sample input**

```text
2 2 1 2 3 4 5 6 7 8
```

**Observed output**

```text
Addition:
6 8
10 12
Subtraction:
-4 -4
-4 -4
```

## 060. Matrix Multiplication

**Topic:** Two-Dimensional Arrays / CO3

**Input contract:** r k c (1..10), then A (r by k), B (k by c); entries +/-10000.

[C source](src/060_matrix_multiplication.c) - [Sample input](inputs/060.txt)

```sh
./build/060_matrix_multiplication < inputs/060.txt
```

**Sample input**

```text
2 2 2 1 2 3 4 5 6 7 8
```

**Observed output**

```text
19 22
43 50
```

## 061. Transpose of a Matrix

**Topic:** Two-Dimensional Arrays / CO3

**Input contract:** Rows and columns 1..10, then the matrix row-major; entries +/-10000.

[C source](src/061_transpose_of_a_matrix.c) - [Sample input](inputs/061.txt)

```sh
./build/061_transpose_of_a_matrix < inputs/061.txt
```

**Sample input**

```text
2 3 1 2 3 4 5 6
```

**Observed output**

```text
1 4
2 5
3 6
```

## 062. Row wise and Column wise Sum of a Matrix

**Topic:** Two-Dimensional Arrays / CO3

**Input contract:** Rows and columns 1..10, then matrix row-major; entries +/-10000.

[C source](src/062_row_wise_and_column_wise_sum_of_a_matrix.c) - [Sample input](inputs/062.txt)

```sh
./build/062_row_wise_and_column_wise_sum_of_a_matrix < inputs/062.txt
```

**Sample input**

```text
2 3 1 2 3 4 5 6
```

**Observed output**

```text
Rows: 6 15
Columns: 5 7 9
```

## 063. Diagonal Sums and Symmetric Matrix Check

**Topic:** Two-Dimensional Arrays / CO3

**Input contract:** Square size 1..10, then matrix row-major; entries +/-10000. Both diagonals include their centre.

[C source](src/063_diagonal_sums_and_symmetric_matrix_check.c) - [Sample input](inputs/063.txt)

```sh
./build/063_diagonal_sums_and_symmetric_matrix_check < inputs/063.txt
```

**Sample input**

```text
2 1 2 2 4
```

**Observed output**

```text
Main diagonal: 5
Secondary diagonal: 4
Symmetric
```

## 064. String Length Without strlen

**Topic:** Strings / CO3

**Input contract:** One text line, up to 255 bytes; operations are byte-based and case-sensitive unless stated otherwise.

[C source](src/064_string_length_without_strlen.c) - [Sample input](inputs/064.txt)

```sh
./build/064_string_length_without_strlen < inputs/064.txt
```

**Sample input**

```text
Hello world
```

**Observed output**

```text
Length: 11
```

## 065. Reverse a String

**Topic:** Strings / CO3

**Input contract:** One text line, up to 255 bytes; operations are byte-based and case-sensitive unless stated otherwise.

[C source](src/065_reverse_a_string.c) - [Sample input](inputs/065.txt)

```sh
./build/065_reverse_a_string < inputs/065.txt
```

**Sample input**

```text
hello
```

**Observed output**

```text
olleh
```

## 066. Palindrome String Check

**Topic:** Strings / CO3

**Input contract:** One text line, up to 255 bytes; operations are byte-based and case-sensitive unless stated otherwise.

[C source](src/066_palindrome_string_check.c) - [Sample input](inputs/066.txt)

```sh
./build/066_palindrome_string_check < inputs/066.txt
```

**Sample input**

```text
level
```

**Observed output**

```text
Palindrome
```

## 067. Count Vowels Consonants Digits and Spaces

**Topic:** Strings / CO3

**Input contract:** One text line, up to 255 bytes; operations are byte-based and case-sensitive unless stated otherwise. Spaces means ASCII space, not every whitespace character.

[C source](src/067_count_vowels_consonants_digits_and_spaces.c) - [Sample input](inputs/067.txt)

```sh
./build/067_count_vowels_consonants_digits_and_spaces < inputs/067.txt
```

**Sample input**

```text
Hello 123
```

**Observed output**

```text
Vowels: 2
Consonants: 3
Digits: 3
Spaces: 1
```

## 068. String Concatenation and Comparison Without Library Functions

**Topic:** Strings / CO3

**Input contract:** Two text lines, each up to 255 bytes; lexicographic byte comparison returns -1, 0 or 1.

[C source](src/068_string_concatenation_and_comparison_without_library_functions.c) - [Sample input](inputs/068.txt)

```sh
./build/068_string_concatenation_and_comparison_without_library_functions < inputs/068.txt
```

**Sample input**

```text
cat
dog
```

**Observed output**

```text
Concatenated: catdog
Comparison: -1
```

## 069. Anagram Check

**Topic:** Strings / CO3

**Input contract:** Two lines containing ASCII letters and whitespace; ignore case and whitespace.

[C source](src/069_anagram_check.c) - [Sample input](inputs/069.txt)

```sh
./build/069_anagram_check < inputs/069.txt
```

**Sample input**

```text
Listen
Silent
```

**Observed output**

```text
Anagrams
```

## 070. Sort Strings in Alphabetical Order

**Topic:** Strings / CO3

**Input contract:** Count 0..20 on its own line, followed by one string per line; case-sensitive lexicographic order.

[C source](src/070_sort_strings_in_alphabetical_order.c) - [Sample input](inputs/070.txt)

```sh
./build/070_sort_strings_in_alphabetical_order < inputs/070.txt
```

**Sample input**

```text
3
pear
apple
banana
```

**Observed output**

```text
apple
banana
pear
```

## 071. Character Frequency in a String

**Topic:** Strings / CO3

**Input contract:** One text line, up to 255 bytes; operations are byte-based and case-sensitive unless stated otherwise. Output byte-code:count pairs in ascending byte order.

[C source](src/071_character_frequency_in_a_string.c) - [Sample input](inputs/071.txt)

```sh
./build/071_character_frequency_in_a_string < inputs/071.txt
```

**Sample input**

```text
banana
```

**Observed output**

```text
97:3
98:1
110:2
```

## 072. Substring Pattern Search in a String

**Topic:** Strings / CO3

**Input contract:** Text line then pattern line; return first zero-based index or -1; empty pattern matches at 0.

[C source](src/072_substring_pattern_search_in_a_string.c) - [Sample input](inputs/072.txt)

```sh
./build/072_substring_pattern_search_in_a_string < inputs/072.txt
```

**Sample input**

```text
abracadabra
cad
```

**Observed output**

```text
Index: 4
```

## 073. Student Record Using a Structure

**Topic:** Structures / CO4

**Input contract:** Roll number 1..1000000 on its own line, name line, mark 0..100 on its own line.

[C source](src/073_student_record_using_a_structure.c) - [Sample input](inputs/073.txt)

```sh
./build/073_student_record_using_a_structure < inputs/073.txt
```

**Sample input**

```text
7
Mira
92
```

**Observed output**

```text
7 | Mira | 92.00
```

## 074. Employee Details Using an Array of Structures

**Topic:** Structures / CO4

**Input contract:** Count 1..100; for each employee: unique positive ID line, name line, salary 0..1000000000 line.

[C source](src/074_employee_details_using_an_array_of_structures.c) - [Sample input](inputs/074.txt)

```sh
./build/074_employee_details_using_an_array_of_structures < inputs/074.txt
```

**Sample input**

```text
2
1
Mira
5000
2
Arun
6000
```

**Observed output**

```text
1 | Mira | 5000.00
2 | Arun | 6000.00
```

## 075. Complex Number Addition and Multiplication

**Topic:** Structures / CO4

**Input contract:** Real and imaginary parts of two complex numbers, each +/-1000000.

[C source](src/075_complex_number_addition_and_multiplication.c) - [Sample input](inputs/075.txt)

```sh
./build/075_complex_number_addition_and_multiplication < inputs/075.txt
```

**Sample input**

```text
1 2 3 4
```

**Observed output**

```text
Sum: 4.00 6.00i
Product: -5.00 10.00i
```

## 076. Distance Between Two Points Using Structures

**Topic:** Structures / CO4

**Input contract:** x1 y1 x2 y2, each +/-1000000.

[C source](src/076_distance_between_two_points_using_structures.c) - [Sample input](inputs/076.txt)

```sh
./build/076_distance_between_two_points_using_structures < inputs/076.txt
```

**Sample input**

```text
0 0 3 4
```

**Observed output**

```text
Distance: 5.00
```

## 077. Time Difference Using Structures

**Topic:** Structures / CO4

**Input contract:** Two same-day times as hour minute second; 0..23,0..59,0..59. Output the absolute difference.

[C source](src/077_time_difference_using_structures.c) - [Sample input](inputs/077.txt)

```sh
./build/077_time_difference_using_structures < inputs/077.txt
```

**Sample input**

```text
10 20 30 12 30 45
```

**Observed output**

```text
02:10:15
```

## 078. Date Validation and Comparison

**Topic:** Structures / CO4

**Input contract:** Two Gregorian dates as day month year; years 1..9999; invalid calendar dates are errors.

[C source](src/078_date_validation_and_comparison.c) - [Sample input](inputs/078.txt)

```sh
./build/078_date_validation_and_comparison < inputs/078.txt
```

**Sample input**

```text
29 2 2024 1 3 2024
```

**Observed output**

```text
First date is earlier
```

## 079. Sort Students by Marks

**Topic:** Structures / CO4

**Input contract:** Count 1..100, then student records (roll line, name line, mark line); descending marks, stable ties.

[C source](src/079_sort_students_by_marks.c) - [Sample input](inputs/079.txt)

```sh
./build/079_sort_students_by_marks < inputs/079.txt
```

**Sample input**

```text
2
1
Mira
80
2
Arun
95
```

**Observed output**

```text
2 | Arun | 95.00
1 | Mira | 80.00
```

## 080. Search a Record by Roll Number

**Topic:** Structures / CO4

**Input contract:** Count 1..100, student records (roll/name/mark lines), then target roll.

[C source](src/080_search_a_record_by_roll_number.c) - [Sample input](inputs/080.txt)

```sh
./build/080_search_a_record_by_roll_number < inputs/080.txt
```

**Sample input**

```text
2
1
Mira
80
2
Arun
95
2
```

**Observed output**

```text
2 | Arun | 95.00
```

## 081. Employee with Address and Date of Birth

**Topic:** Nested Structures / CO4

**Input contract:** ID line, name line, street line, city line, then DOB day month year.

[C source](src/081_employee_with_address_and_date_of_birth.c) - [Sample input](inputs/081.txt)

```sh
./build/081_employee_with_address_and_date_of_birth < inputs/081.txt
```

**Sample input**

```text
7
Mira
12 Lake Road
Chennai
4 5 2000
```

**Observed output**

```text
7 | Mira
12 Lake Road, Chennai
DOB: 2000-05-04
```

## 082. Student Report Card with Nested Subject Marks

**Topic:** Nested Structures / CO4

**Input contract:** Roll line, name line, then five marks 0..100; grade based on average (90/80/70/60 thresholds).

[C source](src/082_student_report_card_with_nested_subject_marks.c) - [Sample input](inputs/082.txt)

```sh
./build/082_student_report_card_with_nested_subject_marks < inputs/082.txt
```

**Sample input**

```text
1
Mira
80 90 70 60 100
```

**Observed output**

```text
1 | Mira
Total: 400.00
Average: 80.00
Grade: B
```

## 083. Library Management Using Structures

**Topic:** Nested Structures / CO4

**Input contract:** Up to 1000 commands: 1 ID newline title newline author newline (add); 2 ID (borrow); 3 ID (return); 4 (list); 0 (exit). Capacity 100 books.

[C source](src/083_library_management_using_structures.c) - [Sample input](inputs/083.txt)

```sh
./build/083_library_management_using_structures < inputs/083.txt
```

**Sample input**

```text
1 1
C Primer
Demo Author
2 1 4 3 1 4 0
```

**Observed output**

```text
Added
Borrowed
1 | C Primer | Demo Author | Borrowed
Returned
1 | C Primer | Demo Author | Available
```

## 084. Bank Account Management Using Structures

**Topic:** Nested Structures / CO4

**Input contract:** Account ID line, owner line, starting balance cents 0..1000000000000; commands 1 positive-cents deposit, 2 positive-cents withdraw, 3 show, 0 exit. At most 1000 commands.

[C source](src/084_bank_account_management_using_structures.c) - [Sample input](inputs/084.txt)

```sh
./build/084_bank_account_management_using_structures < inputs/084.txt
```

**Sample input**

```text
1
Alex
10000
1 5000 2 2500 3 0
```

**Observed output**

```text
Balance cents: 15000
Balance cents: 12500
1 | Alex | 12500 cents
```

## 085. Employee Payroll Processing

**Topic:** Nested Structures / CO4

**Input contract:** Employee count 1..100; each: ID line, name line, basic pay 0..1e9, HRA percent 0..100, DA percent 0..100, deductions 0..1e9. Deductions cannot exceed gross pay.

[C source](src/085_employee_payroll_processing.c) - [Sample input](inputs/085.txt)

```sh
./build/085_employee_payroll_processing < inputs/085.txt
```

**Sample input**

```text
1
7
Mira
10000 20 10 500
```

**Observed output**

```text
7 | Mira | Gross: 13000.00 | Net: 12500.00
```

## 086. Inventory Management System

**Topic:** Nested Structures / CO4

**Input contract:** Commands: 1 ID newline name newline quantity price-cents (add), 2 ID quantity (set), 3 ID quantity (sell), 4 list, 0 exit. Capacity 100; qty 0..1e6, cents 0..1e9; at most 1000 commands.

[C source](src/086_inventory_management_system.c) - [Sample input](inputs/086.txt)

```sh
./build/086_inventory_management_system < inputs/086.txt
```

**Sample input**

```text
1 7
Pen
10 25
3 7 3 2 7 5 4 0
```

**Observed output**

```text
Added
Sold
Updated
7 | Pen | 5 | 25 cents
Stock value cents: 125
```

## 087. Pass a Structure to a Function by Value

**Topic:** Structures / CO4

**Input contract:** Roll number 1..1000000 on its own line, name line, mark 0..100 on its own line. The copied mark is raised by five, capped at 100.

[C source](src/087_pass_a_structure_to_a_function_by_value.c) - [Sample input](inputs/087.txt)

```sh
./build/087_pass_a_structure_to_a_function_by_value < inputs/087.txt
```

**Sample input**

```text
1
Mira
80
```

**Observed output**

```text
Inside copy: 85.00
Caller: 80.00
```

## 088. Pass a Structure to a Function by Reference

**Topic:** Structures / CO4

**Input contract:** Roll number 1..1000000 on its own line, name line, mark 0..100 on its own line. A pointer is passed by value to modify the original mark, capped at 100.

[C source](src/088_pass_a_structure_to_a_function_by_reference.c) - [Sample input](inputs/088.txt)

```sh
./build/088_pass_a_structure_to_a_function_by_reference < inputs/088.txt
```

**Sample input**

```text
1
Mira
80
```

**Observed output**

```text
Caller: 85.00
```

## 089. Pointer to a Structure and the Arrow Operator

**Topic:** Structures / CO4

**Input contract:** Roll number 1..1000000 on its own line, name line, mark 0..100 on its own line.

[C source](src/089_pointer_to_a_structure_and_the_arrow_operator.c) - [Sample input](inputs/089.txt)

```sh
./build/089_pointer_to_a_structure_and_the_arrow_operator < inputs/089.txt
```

**Sample input**

```text
1
Mira
80
```

**Observed output**

```text
1 | Mira | 80.00
```

## 090. Union Demonstration

**Topic:** Unions / CO4

**Input contract:** Integer +/-1000000, real +/-1000000, then a text line. Assign and read one active member at a time.

[C source](src/090_union_demonstration.c) - [Sample input](inputs/090.txt)

```sh
./build/090_union_demonstration < inputs/090.txt
```

**Sample input**

```text
42 3.5
C union
```

**Observed output**

```text
Integer: 42
Real: 3.50
Text: C union
```

## 091. Memory Size Comparison of Structure and Union

**Topic:** Unions / CO4

**Input contract:** No input; sizes depend on platform alignment and padding.

[C source](src/091_memory_size_comparison_of_structure_and_union.c) - [Sample input](inputs/091.txt)

```sh
./build/091_memory_size_comparison_of_structure_and_union < inputs/091.txt
```

**Sample input**

```text
(none)
```

**Observed output**

```text
Structure size: 32
Union size: 16
Union covers every member: yes
```

## 092. Variant Data Type Using a Union

**Topic:** Unions / CO4

**Input contract:** Tag 1=int, 2=real, 3=text, followed by that value; text starts on next line. Magnitudes <=1000000.

[C source](src/092_variant_data_type_using_a_union.c) - [Sample input](inputs/092.txt)

```sh
./build/092_variant_data_type_using_a_union < inputs/092.txt
```

**Sample input**

```text
2 3.75
```

**Observed output**

```text
Real: 3.75
```

## 093. Structure with Bit Fields

**Topic:** Structures / CO4

**Input contract:** Ready 0..1, mode 0..3, count 0..31; bit allocation and layout are implementation-defined.

[C source](src/093_structure_with_bit_fields.c) - [Sample input](inputs/093.txt)

```sh
./build/093_structure_with_bit_fields < inputs/093.txt
```

**Sample input**

```text
1 2 17
```

**Observed output**

```text
Ready: 1
Mode: 2
Count: 17
```

## 094. typedef with Structures and Unions

**Topic:** Structures / CO4

**Input contract:** Item code, price 0..1e6, then quantity kind 1=count 0..1e6 or 2=weight 0..1e6, then quantity.

[C source](src/094_typedef_with_structures_and_unions.c) - [Sample input](inputs/094.txt)

```sh
./build/094_typedef_with_structures_and_unions < inputs/094.txt
```

**Sample input**

```text
7 12.5 1 3
```

**Observed output**

```text
Item: 7 | 12.50
Count: 3
```

## 095. Railway Ticket Reservation System

**Topic:** Nested Structures / CO4

**Input contract:** Capacity 1..20; commands 1 seat newline passenger-name newline (book), 2 seat (cancel), 3 list, 0 exit. At most 1000 commands.

[C source](src/095_railway_ticket_reservation_system.c) - [Sample input](inputs/095.txt)

```sh
./build/095_railway_ticket_reservation_system < inputs/095.txt
```

**Sample input**

```text
2 1 1
Alex
3 2 1 3 0
```

**Observed output**

```text
Booked: 1
1 | Alex
2 | Available
Cancelled: 1
1 | Available
2 | Available
```

## 096. Polynomial Addition Using Structures

**Topic:** Structures / CO4

**Input contract:** First term count 0..20 and coefficient/exponent pairs, then second polynomial; coefficient +/-1e6, exponent 0..100. Output nonzero coefficient/exponent pairs descending.

[C source](src/096_polynomial_addition_using_structures.c) - [Sample input](inputs/096.txt)

```sh
./build/096_polynomial_addition_using_structures < inputs/096.txt
```

**Sample input**

```text
2 3 2 2 0 2 4 1 -2 0
```

**Observed output**

```text
3 2
4 1
```

## 097. User Defined Functions All Four Types

**Topic:** Functions / CO5

**Input contract:** Two integers +/-1000000. Demonstrates argument/return combinations.

[C source](src/097_user_defined_functions_all_four_types.c) - [Sample input](inputs/097.txt)

```sh
./build/097_user_defined_functions_all_four_types < inputs/097.txt
```

**Sample input**

```text
3 4
```

**Observed output**

```text
No args/no return
Args/no return: 3
No args/return: 5
Args/return: 7
```

## 098. Call by Value vs Call by Reference Swap

**Topic:** Functions / CO5

**Input contract:** Two integers +/-1000000. C always passes values; copied pointers can identify caller objects.

[C source](src/098_call_by_value_vs_call_by_reference_swap.c) - [Sample input](inputs/098.txt)

```sh
./build/098_call_by_value_vs_call_by_reference_swap < inputs/098.txt
```

**Sample input**

```text
10 20
```

**Observed output**

```text
Inside value call: 20 10
After value call: 10 20
After pointer call: 20 10
```

## 099. Return Multiple Values from a Function Using Pointers

**Topic:** Functions / CO5

**Input contract:** Two integers +/-1000000.

[C source](src/099_return_multiple_values_from_a_function_using_pointers.c) - [Sample input](inputs/099.txt)

```sh
./build/099_return_multiple_values_from_a_function_using_pointers < inputs/099.txt
```

**Sample input**

```text
7 3
```

**Observed output**

```text
Sum: 10
Difference: 4
Product: 21
```

## 100. Modular Prime Number Program Using Functions

**Topic:** Functions / CO5

**Input contract:** Integer +/-1000000000.

[C source](src/100_modular_prime_number_program_using_functions.c) - [Sample input](inputs/100.txt)

```sh
./build/100_modular_prime_number_program_using_functions < inputs/100.txt
```

**Sample input**

```text
97
```

**Observed output**

```text
Prime
```

## 101. Pass Arrays to Functions

**Topic:** Functions / CO5

**Input contract:** Count 1..100 and integers +/-1000000.

[C source](src/101_pass_arrays_to_functions.c) - [Sample input](inputs/101.txt)

```sh
./build/101_pass_arrays_to_functions < inputs/101.txt
```

**Sample input**

```text
4 1 2 3 4
```

**Observed output**

```text
Sum: 10
Mean: 2.50
```

## 102. Factorial Using Recursion

**Topic:** Recursion / CO5

**Input contract:** N 0..20.

[C source](src/102_factorial_using_recursion.c) - [Sample input](inputs/102.txt)

```sh
./build/102_factorial_using_recursion < inputs/102.txt
```

**Sample input**

```text
5
```

**Observed output**

```text
Factorial: 120
```

## 103. Fibonacci Series Using Recursion

**Topic:** Recursion / CO5

**Input contract:** Term count 0..93, starting 0 1. Recursive memoization avoids exponential work.

[C source](src/103_fibonacci_series_using_recursion.c) - [Sample input](inputs/103.txt)

```sh
./build/103_fibonacci_series_using_recursion < inputs/103.txt
```

**Sample input**

```text
7
```

**Observed output**

```text
0 1 1 2 3 5 8
```

## 104. GCD Using Recursion

**Topic:** Recursion / CO5

**Input contract:** Two integers 0..1000000000; gcd(0,0)=0.

[C source](src/104_gcd_using_recursion.c) - [Sample input](inputs/104.txt)

```sh
./build/104_gcd_using_recursion < inputs/104.txt
```

**Sample input**

```text
48 18
```

**Observed output**

```text
GCD: 6
```

## 105. Tower of Hanoi

**Topic:** Recursion / CO5

**Input contract:** Disk count 1..10; move from A to C using B.

[C source](src/105_tower_of_hanoi.c) - [Sample input](inputs/105.txt)

```sh
./build/105_tower_of_hanoi < inputs/105.txt
```

**Sample input**

```text
2
```

**Observed output**

```text
A -> B
A -> C
B -> C
```

## 106. Power of a Number Using Recursion

**Topic:** Recursion / CO5

**Input contract:** Base -100..100, integer exponent -100..100. Zero to a negative power is invalid; 0^0 is defined as 1 in this exercise.

[C source](src/106_power_of_a_number_using_recursion.c) - [Sample input](inputs/106.txt)

```sh
./build/106_power_of_a_number_using_recursion < inputs/106.txt
```

**Sample input**

```text
2 -3
```

**Observed output**

```text
Power: 0.125000
```

## 107. Binary Search Using Recursion

**Topic:** Recursion / CO5

**Input contract:** Count 0..100, nondecreasing integers +/-1000000, then target; any matching zero-based index or -1.

[C source](src/107_binary_search_using_recursion.c) - [Sample input](inputs/107.txt)

```sh
./build/107_binary_search_using_recursion < inputs/107.txt
```

**Sample input**

```text
5 2 4 6 8 10 8
```

**Observed output**

```text
Index: 3
```

## 108. Sum of Digits and String Reversal Using Recursion

**Topic:** Recursion / CO5

**Input contract:** Nonnegative integer 0..1000000000000 on its own line, then a text line up to 255 bytes.

[C source](src/108_sum_of_digits_and_string_reversal_using_recursion.c) - [Sample input](inputs/108.txt)

```sh
./build/108_sum_of_digits_and_string_reversal_using_recursion < inputs/108.txt
```

**Sample input**

```text
12345
hello
```

**Observed output**

```text
Digit sum: 15
Reversed: olleh
```

## 109. Pointer Basics Address and Dereference Operators

**Topic:** Pointers / CO5

**Input contract:** Integer +/-1000000; the printed address varies between executions.

[C source](src/109_pointer_basics_address_and_dereference_operators.c) - [Sample input](inputs/109.txt)

```sh
./build/109_pointer_basics_address_and_dereference_operators < inputs/109.txt
```

**Sample input**

```text
42
```

**Observed output**

```text
Value: 42
Address: 0x16fa2e078
Dereferenced: 42
Updated: 43
```

## 110. Array Traversal Using Pointer Arithmetic

**Topic:** Pointers / CO5

**Input contract:** Count 0..100 and integers +/-1000000.

[C source](src/110_array_traversal_using_pointer_arithmetic.c) - [Sample input](inputs/110.txt)

```sh
./build/110_array_traversal_using_pointer_arithmetic < inputs/110.txt
```

**Sample input**

```text
4 1 2 3 4
```

**Observed output**

```text
1 2 3 4
```

## 111. Dynamic Memory Allocation malloc calloc realloc free

**Topic:** Pointers / CO5

**Input contract:** Initial count 1..100 and integers +/-1000000, then added count 0..100 and added integers.

[C source](src/111_dynamic_memory_allocation_malloc_calloc_realloc_free.c) - [Sample input](inputs/111.txt)

```sh
./build/111_dynamic_memory_allocation_malloc_calloc_realloc_free < inputs/111.txt
```

**Sample input**

```text
3 1 2 3 2 4 5
```

**Observed output**

```text
malloc: 1 2 3
calloc first: 0
realloc: 1 2 3 4 5
```

## 112. Dynamic Two Dimensional Array

**Topic:** Pointers / CO5

**Input contract:** Rows and columns 1..10, then row-major integers +/-1000000.

[C source](src/112_dynamic_two_dimensional_array.c) - [Sample input](inputs/112.txt)

```sh
./build/112_dynamic_two_dimensional_array < inputs/112.txt
```

**Sample input**

```text
2 3 1 2 3 4 5 6
```

**Observed output**

```text
1 2 3
4 5 6
```

## 113. Array of Pointers to Strings

**Topic:** Pointers / CO5

**Input contract:** Count 1..20 on its own line, then text lines; sort strings by exchanging their pointers.

[C source](src/113_array_of_pointers_to_strings.c) - [Sample input](inputs/113.txt)

```sh
./build/113_array_of_pointers_to_strings < inputs/113.txt
```

**Sample input**

```text
3
pear
apple
banana
```

**Observed output**

```text
apple
banana
pear
```

## 114. Menu Driven Calculator Using Function Pointers

**Topic:** Pointers / CO5

**Input contract:** Commands 1=add, 2=subtract, 3=multiply, 4=divide, each followed by two reals +/-1e6; 0 exits. Divisor nonzero; at most 1000 commands.

[C source](src/114_menu_driven_calculator_using_function_pointers.c) - [Sample input](inputs/114.txt)

```sh
./build/114_menu_driven_calculator_using_function_pointers < inputs/114.txt
```

**Sample input**

```text
1 2 3 3 4 5 4 9 3 0
```

**Observed output**

```text
Result: 5.00
Result: 20.00
Result: 3.00
```

## 115. Singly Linked List Insertion Deletion and Traversal

**Topic:** Pointers / CO5

**Input contract:** Commands 1 integer (append), 2 integer (delete first match), 3 (display), 0 (exit). Integers +/-1e6; capacity 100 nodes; at most 1000 commands.

[C source](src/115_singly_linked_list_insertion_deletion_and_traversal.c) - [Sample input](inputs/115.txt)

```sh
./build/115_singly_linked_list_insertion_deletion_and_traversal < inputs/115.txt
```

**Sample input**

```text
1 10 1 20 1 10 3 2 10 3 0
```

**Observed output**

```text
Inserted
Inserted
Inserted
10 20 10
Deleted
20 10
```

## 116. Write and Read a Text File

**Topic:** File Handling / CO5

**Input contract:** One text line (up to 255 bytes); overwrites notes.txt in the current directory and reads it back.

[C source](src/116_write_and_read_a_text_file.c) - [Sample input](inputs/116.txt)

```sh
./build/116_write_and_read_a_text_file < inputs/116.txt
```

**Sample input**

```text
Hello file
```

**Observed output**

```text
Read: Hello file
```

## 117. Copy the Contents of One File to Another

**Topic:** File Handling / CO5

**Input contract:** Source path line then destination path line; distinct files. Overwrites destination. POSIX stat prevents copying onto the same inode.

[C source](src/117_copy_the_contents_of_one_file_to_another.c) - [Sample input](inputs/117.txt)

```sh
./build/117_copy_the_contents_of_one_file_to_another < inputs/117.txt
```

**Sample input**

```text
input.txt
copy.txt
```

**Observed output**

```text
Copied
```

## 118. Count Characters Words and Lines in a File

**Topic:** File Handling / CO5

**Input contract:** File path line. Characters are bytes; words are whitespace-delimited; a nonempty unterminated final line counts as a line.

[C source](src/118_count_characters_words_and_lines_in_a_file.c) - [Sample input](inputs/118.txt)

```sh
./build/118_count_characters_words_and_lines_in_a_file < inputs/118.txt
```

**Sample input**

```text
input.txt
```

**Observed output**

```text
Characters: 24
Words: 4
Lines: 2
```

## 119. Store and Retrieve Structure Records Using a Binary File

**Topic:** File Handling / CO5

**Input contract:** Count 0..100, then unique student records (roll/name/mark lines). Overwrites students.dat; raw struct format is for the same compiler/platform only.

[C source](src/119_store_and_retrieve_structure_records_using_a_binary_file.c) - [Sample input](inputs/119.txt)

```sh
./build/119_store_and_retrieve_structure_records_using_a_binary_file < inputs/119.txt
```

**Sample input**

```text
2
1
Mira
80
2
Arun
90
```

**Observed output**

```text
1 | Mira | 80.00
2 | Arun | 90.00
```

## 120. Update a Record Using fseek and ftell Random Access

**Topic:** File Handling / CO5

**Input contract:** Run experiment 119 first in the same directory. Input: target roll and replacement mark 0..100. Updates students.dat in place; format is compiler/platform-specific.

[C source](src/120_update_a_record_using_fseek_and_ftell_random_access.c) - [Sample input](inputs/120.txt)

```sh
./build/120_update_a_record_using_fseek_and_ftell_random_access < inputs/120.txt
```

**Sample input**

```text
2 95
```

**Observed output**

```text
Updated at byte: 276
2 | Arun | 95.00
```
