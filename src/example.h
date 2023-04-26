
/*
In the C and C++ programming languages, #pragma once is a non-standard 
but widely supported preprocessor directive designed to cause the current 
source file to be included only once in a single compilation.
*/
#pragma once
#include <bits/stdc++.h>
#include <vector>
using namespace std;

#define MISSING_PARAM_ERR -1
#define WRONG_SENTENCE_ID_ERR -2
#define DEFAULT_VAL_NUM 0   // if numeric field is missing store this value in the struct field
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




// structure for storing parameters contained in ZDA type packet
typedef struct {
    int day; // day of month (1-31)
    int month; // month of year (1-12)
    int year; // year (4 digits)
    int hour; // hours (0-23)
    int minute; // minutes (0-59)
    int second; // seconds (0-59)
    int millisecond; // milliseconds (0-999)
    int local_hour_offset; // local hour offset from UTC (hours)
    int local_minute_offset; // local minute offset from UTC (minutes)
} ZDA_data;


// structure for storing parameters contained in GST type packet
typedef struct {
    std::string utc_time;    // UTC time in hhmmss format
    double rms_deviation;     // root-mean-square deviation of range residuals (m)
    double semi_major_err;    // semi-major axis error estimate (m)
    double semi_minor_err;    // semi-minor axis error estimate (m)
    double orientation_err;   // orientation of semi-major axis error estimate (deg)
    double lat_err;           // latitude error estimate (m)
    double lon_err;           // longitude error estimate (m)
    double alt_err;           // altitude error estimate (m)
} GST_data;


// structure for storing parameters contained in HDT type sentence
typedef struct {
    float heading; // heading in degrees (true)
} HDT_data;

typedef struct {
    std::string utc_time; // UTC time in hhmmss format
    int mode; // receiver mode (0=no mode value yet, 1=autonomous, 2=DGPS, 3=estimated, 4=manual, 5=simulation)
    float residual1; // range residual 1 
    float residual2; // range residual 2 
    float residual3; // range residual 3 
    float residual4; // range residual 4 
    float residual5; // range residual 5 
    float residual6; // range residual 6 
    float residual7; // range residual 7 
    float residual8; // range residual 8 
    float residual9; // range residual 9 
    float residual10; // range residual 10
    float residual11; // range residual 11
    float residual12; // range residual 12
} GRS_data;


typedef struct {
    string sentence_code;
    union {
        GGA_data gga_data;

        // other sentence types
    } data;
} GPS_data;

void parse_nmea_sentence(string sentence);
string get_nmea_sentence_code(string sentence);

int parse_GGA_sentence(string sentence, GGA_data *gga_data);
int parse_GSA_sentence(string sentence, GSA_data *gsa_data);
int parse_GSV_sentence(string sentence, GSV_data *gsv_data);
int parse_RMC_sentence(string sentence, RMC_data *rmc_data);
int parse_VTG_sentence(string sentence, VTG_data *vtg_data);
int parse_GLL_sentence(string sentence, GLL_data *gll_data);
int parse_ZDA_sentence(string sentence, ZDA_data *zda_data);
int parse_GST_sentence(string sentence, GST_data *gst_data);
int parse_HDT_sentence(string sentence, HDT_data *hdt_data);
int parse_GRS_sentence(string sentence, GRS_data *grs_data);