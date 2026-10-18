# Rational Arithmetic

A C++ project implementing arbitrary-precision integer and rational number arithmetic, developed for COSC326 at the University of Otago.

## Overview

The project implements two custom numeric classes:

- **Integer:** Represents integers using strings, allowing calculations with numbers larger than standard C++ integer types can hold.
- **Rational:** Represents fractions using the custom Integer class, supporting rational arithmetic and simplification.

Both classes overload standard C++ operators to support addition, subtraction, multiplication, division, and comparisons.

## Key Features

- Object-oriented programming in C++
- Operator overloading
- Arbitrary-precision arithmetic
- Fraction representation and simplification
- Handling negative numbers and large integers

## Compile and Run

Requires a C++17-compatible compiler (such as g++).

Write or adapt the main program and compile it using:

```bash
g++ -std=c++17 main.cpp Integer.cpp Rational.cpp -o rationals
./rationals
```

## Testing

A separate `tests.cpp` file checks integer and rational arithmetic, comparisons, large numbers, negative values, and fraction simplification.

Compile and run the tests:

```bash
g++ -std=c++17 tests.cpp Integer.cpp Rational.cpp -o tests
./tests
```

The tests report individual PASS/FAIL results and a final summary.