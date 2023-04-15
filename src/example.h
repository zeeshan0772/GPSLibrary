
/*
In the C and C++ programming languages, #pragma once is a non-standard 
but widely supported preprocessor directive designed to cause the current 
source file to be included only once in a single compilation.
*/
#pragma once
#include <bits/stdc++.h>
#include <vector>
using namespace std;



/*
    GGA - Global Positioning System Fix Data
    GSA - GPS DOP and Active Satellites
    GSV - GPS Satellites in View
    RMC - Recommended Minimum Specific GNSS Data
    VTG - Course Over Ground and Ground Speed
    GLL - Geographic Position, Latitude/Longitude
    ZDA - Time and Date
    GST - GNSS Pseudorange Noise Statistics
    HDT - Heading - True
    GRS - GNSS Range Residuals
*/

// structure for storing parameters contained in GGA type packet
typedef struct {      
        string time; // UTC time in hhmmss.ss format
        string latitude; // latitude in ddmm.mmm format
        char lat_direction; // latitude direction - 'N' (North) or 'S' (South)
        string longitude; // longitude in dddmm.mmm format
        char lon_direction; // longitude direction - 'E' (East) or 'W' (West)
        int gps_quality; // GPS quality indicator - 0 for invalid, 1 for GPS fix, 2 for differential GPS fix
        int num_satellites; // number of satellites in use
        double hdop; // horizontal dilution of precision (HDOP) - relative accuracy of horizontal position
        double altitude; // altitude above mean sea level in meters
        char unit_of_altitude;  // altitude unit, 'M' for meters
        double geoidal_sep; // geoidal separation - difference between the WGS84 earth ellipsoid and mean sea level, in meters
        char geoidal_unit;
        double age_diff_corr; // age of differential GPS data - in seconds (blank if not used)
        string diff_ref_station_id; // differential reference station ID (blank if not used)
} GGA_data;

// structure for storing parameters contained in GSA type packet
typedef struct {
    char mode1;  // selection mode
    int mode2;   // mode for fix type: 1 = no fix, 2 = 2D fix, 3 = 3D fix
    int prn[12]; // array of 12 integers representing satellite PRNs used in the fix
    double pdop; // position dilution of precision
    double hdop; // horizontal dilution of precision
    double vdop; // vertical dilution of precision
} GSA_data;

// structure for storing parameters contained in GSV type packet
typedef struct {
    int num_msgs; // total number of messages for this sentence
    int msg_num; // message number
    int num_sats; // total number of satellites in view
    std::vector<int> prn; // satellite PRN numbers
    std::vector<int> elev; // satellite elevation angles
    std::vector<int> azim; // satellite azimuth angles
    std::vector<int> snr; // satellite signal-to-noise ratio
} GSV_data;

// structure for storing parameters contained in RMC type packet
typedef struct {
    string utc_time; // UTC time
    char status; // status, A = data valid, V = data invalid
    string latitude;
    char latitude_dir; // latitude direction, N = north, S = south
    string longitude;
    char longitude_dir; // longitude direction, E = east, W = west
    double speed_knots; // speed over ground in knots
    double true_course; // true course made good in degrees
    string date; // date in ddmmyy format
    double variation; // magnetic variation in degrees
    char variation_dir; // magnetic variation direction, E = east, W = west
} RMC_data;

// structure for storing parameters contained in VTG type packet
typedef struct {
    double true_track_degrees; // true track made good in degrees
    char true_track_indicator; // T = true
    double magnetic_track_degrees; // magnetic track made good in degrees
    char magnetic_track_indicator; // M = magnetic
    double ground_speed_knots; // ground speed in knots
    char ground_speed_knots_indicator; // N = knots
    double ground_speed_kph; // ground speed in kilometers per hour
    char ground_speed_kph_indicator; // K = kilometers per hour
    char mode; // mode indicator, A = autonomous, D = differential, E = estimated, N = not valid
} VTG_data;



// structure for storing parameters contained in GLL type packet
typedef struct {
    string latitude; // latitude in degrees
    char latitude_direction; // N = North, S = South
    string longitude; // longitude in degrees
    char longitude_direction; // E = East, W = West
    string utc_time; // UTC time in hhmmss.ss format
    char status; // A = valid data, V = invalid data
    char mode; // mode indicator, A = autonomous, D = differential, E = estimated, N = not valid
} GLL_data;



/*
// structure for storing parameters contained in GSV type packet
typedef struct {
    // complete this code
    // declare the elements of this struct to store NMEA RMC packet fields
    // example: $GPVTG,054.7,T,034.4,M,005.5,N,010.2,K,A*25
} RMC_data;
*/


typedef struct {
    string sentence_code;
    union {
        GGA_data gga_data;

        // other sentence types
    } data;
} GPS_data;

void parse_nmea_sentence(string sentence);
string get_nmea_sentence_code(string sentence);
void parse_GGA_sentence(string sentence, GGA_data *gga_data);
void parse_GSA_sentence(string sentence, GSA_data *gsa_data);
void parse_GSV_sentence(string sentence, GSV_data *gsv_data);
void parse_RMC_sentence(string sentence, RMC_data *rmc_data);
void parse_VTG_sentence(string sentence, VTG_data *vtg_data);
void parse_GLL_sentence(string sentence, GLL_data *gll_data);