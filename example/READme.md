# Example

This code parses a GPS NMEA sentence and stores the extracted data in a structure. It then prints out the parsed data.

## Building

To build this code, you will need to run the following commands:

```bash
cmake -S. -Bbuild
cmake --build build
```

## Usage

To run the code, simply execute the compiled binary located in `build/MyProject`. The code will parse the predefined NMEA sentence and print out the parsed data.

## Dependencies

This code has a dependency on a `gps_lib.h` header file that defines the `parse_nmea_sentence` function used in the code. Make sure to include this header file in your build environment.