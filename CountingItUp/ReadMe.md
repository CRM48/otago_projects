# Counting it Up

A Java project developed as a pair assignment at the University of Otago in 2023. The goal was to calculate large binomial coefficients while working within the limitations of 64-bit integer types.

The binomial coefficient calculates the number of ways to choose *k* items from a set of *n* items:

\[
\binom{n}{k} = \frac{n!}{k!(n-k)!}
\]

The project explores different approaches to this calculation, focusing on numerical accuracy, efficiency and avoiding integer overflow.

## Requirements

- Java JDK (with `javac` and `java` available)
- No external dependencies

## Build and Run

Compile the Java source files using `javac`, then run the desired implementation with `java`.

The project contains eight versions of the algorithm, each exploring a different approach to calculating binomial coefficients.

## Features

- **Binomial coefficients:** Calculates the number of possible combinations of *k* items chosen from *n*.
- **Multiple implementations:** Eight versions exploring different mathematical approaches and improvements.
- **Overflow reduction:** Simplifies calculations and reduces intermediate values to work within 64-bit integer limits.
- **Alternative algorithms:** Explores both factorial-based calculations and methods derived from Pascal's triangle.

## Implementation

The project was developed iteratively to overcome the limitations of the standard factorial formula.

- **Initial approach:** Directly calculates factorials, which quickly produces values too large for 64-bit integers.
- **Improved calculations:** Rearranges the formula and alternates multiplication and division to reduce intermediate values.
- **Pascal's triangle:** Uses the relationship between neighbouring binomial coefficients as an alternative to factorial calculations.
- **Final approach:** Uses a formula-based method derived from Pascal's triangle to calculate coefficients more efficiently.

Each implementation demonstrates a different way of approaching the same mathematical problem, highlighting the importance of algorithm design and numerical limitations.