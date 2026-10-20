# ANDIE: A Non-Destructive Image Editor

ANDIE is a Java-based image editor developed as a group project for COSC202 at the University of Otago in 2022. It allows users to edit images without permanently modifying the original, with support for undoing and redoing operations.

The project demonstrates object-oriented programming, GUI development, image processing and collaborative software development.

## Requirements

- Java JDK (with `javac` and `java` available)
- No external dependencies required to run the application

## Build and Run

From the project directory, compile the Java source files:

```bash
javac -d bin/ src/main/cosc202/andie/**/*.java src/main/cosc202/andie/*.java
```

Then launch the application:

```bash
java -cp bin cosc202.andie.Andie
```

Once running, open an image using the File menu. Editing operations are available through the menus, toolbar and keyboard shortcuts.

## Features

- **Image editing:** Non-destructive operations with undo, redo, image importing and exporting.
- **Filters:** Gaussian blur, median, sharpen, emboss and edge detection.
- **Colour adjustments:** Brightness, contrast, greyscale and posterisation.
- **Transformations:** Image resizing, rotation, flipping and zooming.
- **Selections:** Mouse-based selection, cropping, drawing shapes and adding text.
- **Macros:** Record and replay sequences of image editing operations.
- **Interface:** Toolbar, keyboard shortcuts and error handling for invalid operations.

## Testing

The application was tested with different image formats, including images with transparency and alpha channels. Tests covered filters, colour adjustments, transformations, selections and other editing operations.

JUnit tests are included in `src/test/`. To compile and run them on Windows:

```bash
javac -d bin/ -cp "bin;lib/junit-platform-console-standalone-1.8.2.jar" src/test/cosc202/andie/*.java

java -jar lib/junit-platform-console-standalone-1.8.2.jar -cp bin/ --scan-class-path
```

## Acknowledgements

Developed as a group project by Curtis Mellsop, Callum Cooper, Adam Aizal and Sam Merton.

My main contributions included posterisation, brightness and contrast adjustments, image rotation, cropping, drawing operations and the application toolbar.