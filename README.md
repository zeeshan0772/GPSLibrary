# GPA NMEA Parsing Library
The GPS NMEA Library is a C++ library for parsing and handling NMEA sentences. It only works with the following NMEA sentence types:

`GGA` - Global Positioning System Fix Data  
`GSA` - GPS DOP and Active Satellites  
`GSV` - GPS Satellites in View  
`RMC` - Recommended Minimum Specific GNSS Data  
`VTG` - Course Over Ground and Ground Speed  
`GLL` - Geographic Position, Latitude/Longitude  
`ZDA` - Time and Date  
`GST` - GNSS Pseudorange Noise Statistics  
`HDT` - Heading - True  
`GRS` - GNSS Range Residuals  

The library provides error codes for invalid NMEA sentences. These are:

`MISSING_PARAM_ERR`: Indicates that one or more parameters are missing from the NMEA sentence.  
`WRONG_SENTENCE_ID_ERR`: Indicates that the sentence ID in the NMEA sentence is incorrect.  
`INCORRECT_SENTENCE_CODE_ERR`: Indicates that the NMEA sentence code is incorrect.  
`CHECKSUM_ERR`: Indicates that the checksum in the NMEA sentence is incorrect.  

## Usage

To use the library, simply include the `gps_lib.h` header file in your project. The library provides the following structures for storing parameters contained in NMEA sentences:
```
GGA_data
GSA_data
GSV_data
RMC_data
VTG_data
GLL_data
ZDA_data
GST_data
HDT_data
GRS_data
```

You can use these structures to extract data from NMEA sentences of the respective type.

The `GPS_data` struct is used to store data that has been parsed from NMEA sentences in GPS devices. It has two fields:

`sentence_type (string)`: This field indicates the type of NMEA sentence that the data was parsed from. NMEA sentences are standardized messages used in GPS systems to convey information about location, speed, and other parameters. The sentence_type field can have values like "GGA" (Global Positioning System Fix Data), "RMC" (Recommended Minimum Navigation Information), "VTG" (Course Over Ground and Ground Speed), and others.

`data (void pointer)`: This field is a pointer to a structure containing the parsed data. The type of the structure depends on the value of sentence_type. For example, if sentence_type is "GGA", data points to a structure with fields for latitude, longitude, altitude, and other GPS data. If sentence_type is "RMC", data points to a structure with fields for time, date, speed, and other navigation data.

 ## Error Handling

The library provides error codes for invalid NMEA sentences. These error codes can be used to identify and handle invalid NMEA sentences.

## How to build this library

```bash
cmake -S. -Bbuild 
cmake --build build
```


## Running the tests

Using `unit_tests`:
```
$ cd build 
$ ./bin/unit_tests

[==========] Running 2 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 2 tests from parse_nmea_sentence
[ RUN      ] parse_nmea_sentence.Checksum_error
[       OK ] parse_nmea_sentence.Checksum_error (0 ms)
[ RUN      ] parse_nmea_sentence.No_checksum_error
[       OK ] parse_nmea_sentence.No_checksum_error (0 ms)
[----------] 2 tests from parse_nmea_sentence (0 ms total)

[----------] Global test environment tear-down
[==========] 2 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 2 tests.

```