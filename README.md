# University Portfolio
This repository contains selected projects from my Bachelors degree at Otago University:
- Bachelor of Science and Commerce majoring in Computer Science and Finance | University of Otago (2021-2024)

## Projects
- **ANDIE: A Non-Destructive Image Editor** - 2022 Group Project
- **Counting it Up** - 2023 Pair Project
- **Dates** - 2023 Individual Project
- **Snowflake** - 2023 Individual Project
- **Where in the World is CS** - 2023 Individual Project

## Project Details

### ANDIE: A Non-Destructive Image Editor (2022)
- An image editor that retains the files original state
- Allows operations such as colour adjustments, transformations, filtering, selections and more
- This was my first group project at Uni
- It was coded almost entirely in Java as that was the primary language we learnt and used in 2021-2022
- All details on how to build and run the application can be found in the ReadMe file in the ANDIE folder.

### Counting it Up (2023)
- A set of programs designed to find the binomial coefficient of two numbers
- That is, the number of sets of size k that can be derived from n instances (say k = 5 different cards from a pack of n = 52)
- The goal was to calculate these values for large numbers using only long (64 bit) variable types
- There are 8 iterations, the first six use the binomial coefficient formula
- Each iteration of the first six program are progressively more accurate and efficient, minimising the size of produced numbers by manipulating the formula
- The seventh iteration uses pascals triange to 'find' the result
- The final iteration adapts a formulaic approach to pascals triangle by finding the triangle number with the inputs being the rows/columns
- The ReadMe file for this project explains it better

### Dates (2023)
- This program has a much simpler purpose: to take a date input and check its validity
- It checks the input format is valid, and then checks the date itself is a valid date
- Finally it converts the date into a consistent format and outputs it (if valid)

### Snowflake (2023)
- The purpose of this project was to allow us to garner a basic understanding of Graphical User Interfaces (GUIs)
- The purpose was to create a program that produces an interactive GUI that allows users to display a Koch Snowflake of a chosen order
- A Koch snowflake starts as a triangle for order 1, adds a further triangle to each of its sides for order 2 (in the middle of each side)
- For order 3 it adds another triangle to each side, and so on
- Details are displayed in the Read Me file, it can be run through the FrameApp file

### Where in the World is CS (2023)
- This project took valid coordinate inputs from the user and showed each point on a map
- Valid coordinates were in the form Degrees/Minutes/Seconds (DMS), Degrees/Minutes (MinDec), or Degrees (DegDec)
- The first class took the users input and converted it into the same format
- The second class printed these coordinates into a JSON file and used geoJSON to show them on a map
- My design process is described in the ReadMe file

