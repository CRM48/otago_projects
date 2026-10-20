# Dates

A Java project developed as an individual assignment at the University of Otago in 2023. The program takes user-provided dates, checks their validity and converts them into a consistent output format.

The project focuses on string processing, input validation and handling different date formats.

## Requirements

- Java JDK (with `javac` and `java` available)
- No external dependencies

## Build and Run

Compile the Java source file using `javac`, then run the program using `java`.

The program reads dates from standard input (`stdin`) and outputs the formatted results to standard output (`stdout`).

## Features

- **Date parsing:** Accepts dates using different separators, including spaces, hyphens and slashes.
- **Format validation:** Checks day, month and year inputs, including numeric and written month representations.
- **Date validation:** Verifies valid days for each month, leap years and years within the supported range (1753–3000).
- **Error handling:** Identifies invalid dates, outputs the original input followed by `- INVALID` and prints error details to standard error (`stderr`).

## Implementation

The program processes dates in three main stages:

1. **Year:** Checks the year format and ensures it falls within the supported range.
2. **Month:** Converts numeric or written month inputs into a consistent representation.
3. **Day:** Validates the day against the month and year, including leap-year handling for February 29.

If all three components are valid, the date is formatted and printed. Otherwise, the program identifies the invalid input and reports an error.

## Testing

The program was manually tested with different date formats, invalid inputs, leap years and boundary cases.