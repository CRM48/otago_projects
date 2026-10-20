# Where in the World is CS

A Java project developed as an individual assignment at the University of Otago in 2023. The program accepts geographical coordinates in different formats, converts them into decimal degrees and displays the locations on an interactive map.

The project demonstrates string processing, coordinate conversion, input validation, JSON data generation and geographical visualisation.

## Requirements

- Java JDK (with `javac` and `java` available)
- Internet connection to view the generated map using [geojson.io](https://geojson.io/)

## Build and Run

Compile the Java source files using `javac`, then run the application's main class using `java`.

The program prompts the user to enter geographical coordinates and an optional location name.

Once the coordinates have been processed, the application generates a GeoJSON file and opens the results in the default browser using geojson.io.

## Features

- **Coordinate formats:** Supports degrees/minutes/seconds (DMS), decimal minutes (DegMin) and decimal degrees (DegDec).
- **Input parsing:** Handles different coordinate representations, separators and directional indicators (N, S, E, W).
- **Coordinate conversion:** Converts supported coordinate formats into a consistent decimal-degree representation.
- **Map visualisation:** Generates GeoJSON features and displays the locations on an interactive map.

## Implementation

The program processes geographical coordinates in four main stages:

1. **Input parsing:** Separates the latitude, longitude and optional location name, accounting for different input formats.
2. **Format identification:** Determines whether the coordinates use DMS, DegMin or DegDec notation.
3. **Coordinate conversion:** Converts the coordinates into decimal degrees, accounting for directional indicators.
4. **GeoJSON generation:** Creates a GeoJSON FeatureCollection containing the locations and opens it using geojson.io.

## Example Inputs

The program supports several coordinate formats, including:

```text
40:26:46.302N 079:58:55.903W
40°26′46″N 079°58′56″W
40.446195N 79.982195W
40.446195, -79.982195
40° 26.7717, -79° 58.93172
```

These represent approximately the same geographical location, expressed using different coordinate formats.