#include <stdio.h>
#include "gps_lib.h"

int main()
{
        auto GGA_nmea_sentence = "$GPGGA,170834,4124.8963,N,08151.6838,W,1,05,1.5,280.2,M,-34.0,M,,,*59";
        GPS_data gps_data;      // structure for storing the parsed data

        // Parse the sentence and store data in the gps_data structure
        int err_code = parse_nmea_sentence(GGA_nmea_sentence, &gps_data);
        if (err_code == CHECKSUM_ERR)
        {
                printf("Checksum Error\n");
                return -1;
        }
        else if (err_code == MISSING_PARAM_ERR)
        {
                printf("error: parameters missing from nmea sentence\n");
                return -1;
        } 
        else if(err_code == INCORRECT_SENTENCE_CODE_ERR)
        {
                printf("error: incorrect nmea sentence ID\n");
                return -1;
        }
        else if(err_code == 0)
        {
                GGA_data& gga_data = *static_cast<GGA_data*>(gps_data.data);
                printf("GGA Data\n");
                printf("Time: %s\n", gga_data.time.c_str());
                printf("Latitude: %s\n", gga_data.latitude.c_str());
                printf("Latituude Direction: %c\n", gga_data.lat_direction);
                printf("Longitude: %s\n", gga_data.longitude.c_str());
                printf("Longitude Direction: %c\n", gga_data.lon_direction);
                printf("GPS Quality: %d\n", gga_data.gps_quality);
                printf("Num. Statellites: %d\n", gga_data.num_satellites);
                printf("HDOP: %f\n", gga_data.hdop);
                printf("Altitude: %f\n", gga_data.altitude);
                printf("Altitude unit: %c\n", gga_data.unit_of_altitude);
                printf("Geoidl Separation: %f\n", gga_data.geoidal_sep);
                printf("Geoidl unit: %c\n", gga_data.geoidal_unit);
                printf("Age of differential GPS data: %f\n", gga_data.age_diff_corr);
                printf("Differential reference station ID number: %s\n", gga_data.diff_ref_station_id.c_str());
                return 0;
        }
}