# Snowflake

A Java project developed as an individual assignment at the University of Otago in 2023. The application generates and displays Koch snowflakes, allowing users to interactively change the fractal's order through a graphical user interface (GUI).

The project demonstrates recursive geometric patterns, coordinate calculations, GUI development and Java graphics programming.

## Requirements

- Java JDK (with `javac` and `java` available)
- No external dependencies

## Build and Run

Compile the Java source files using `javac`, then run the `FrameApp` class to launch the application.

Once running, use the `+` and `-` buttons to increase or decrease the snowflake order, or enter an order directly into the text field.

## Features

- **Koch snowflake generation:** Generates fractal patterns by replacing each line segment with four smaller segments at each successive order.
- **Interactive controls:** Allows users to increase, decrease or directly enter the desired snowflake order.
- **Responsive GUI:** Automatically redraws and scales the snowflake when the window is resized, maximised or restored.
- **Graphics rendering:** Uses Java Graphics2D for precise coordinate calculations and drawing.

## Implementation

The application uses two main classes to generate and display the snowflake:

- **DimensionCreator:** Calculates the coordinates of new line segments using six possible directions based on a hexagonal structure.
- **KochSnowflake:** Manages the GUI, draws the snowflake and handles user input.
- **Coordinate storage:** Stores previously calculated snowflake orders in nested ArrayLists to avoid unnecessary recalculation.
- **Dynamic rendering:** Recalculates and redraws the snowflake to fit the available window space.

## Limitations

Performance decreases at higher orders (around 7–8) because the number of line segments increases exponentially. Each additional order requires four times as many line segments as the previous order.