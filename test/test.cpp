#include <gtest/gtest.h>

#include "example.h"

/*
TEST(get_nmea_sentence_code, get_code_from_sentence) {
        auto nmea_sentence = "$GPGGA,170834,4124.8963,N,08151.6838,W,1,05,1.5,280.2,M,-34.0,M,,,*59 ";
        auto nmea_code = "GPGGA";
        ASSERT_EQ(nmea_code, get_nmea_sentence_code(nmea_sentence));
}

// check when invalid nmea format
TEST(get_nmea_sentence_code, handle_invalid_nmea_format) {
        auto nmea_sentence = "#GPGGA,170-34.0,M,,,*59 ";
        auto returned_error = "NMEA_CODE_ERR";
        ASSERT_EQ(returned_error, get_nmea_sentence_code(nmea_sentence));
}
*/

/*
TEST(GGA_parser, parsing_test_for_GGA) {
        auto sentence = "$GPGGA,170834,4124.8963,N,08151.6838,W,1,05,1.5,280.2,M,-34.0,M,,,*59";

        GGA_data *gga_data = new GGA_data;
        parse_GGA_sentence(sentence, gga_data);

        ASSERT_EQ("170834", gga_data->time);
        ASSERT_EQ("4124.8963", gga_data->latitude);
        ASSERT_EQ('N', gga_data->lat_direction);
        ASSERT_EQ("08151.6838", gga_data->longitude);
        ASSERT_EQ('W', gga_data->lon_direction);
        ASSERT_EQ(1, gga_data->gps_quality);
        ASSERT_EQ(05, gga_data->num_satellites);
        ASSERT_DOUBLE_EQ(1.5, gga_data->hdop);
        ASSERT_DOUBLE_EQ(280.2, gga_data->altitude);
        ASSERT_EQ('M', gga_data->unit_of_altitude);
        ASSERT_DOUBLE_EQ(-34.0, gga_data->geoidal_sep);
        ASSERT_EQ('M', gga_data->geoidal_unit);
        ASSERT_EQ(0, gga_data->age_diff_corr);
        ASSERT_EQ("", gga_data->diff_ref_station_id);
}

TEST(GSA_parser, parsing_test_for_GSA) {
    auto sentence = "$GPGSA,A,3,19,28,14,18,27,22,31,39,,,,,1.7,1.0,1.3*34";
    GSA_data *gsa_data = new GSA_data;
    parse_GSA_sentence(sentence, gsa_data);

    ASSERT_EQ('A', gsa_data->mode1);
    ASSERT_EQ(3, gsa_data->mode2);
    ASSERT_EQ(19, gsa_data->prn[0]);
    ASSERT_EQ(28, gsa_data->prn[1]);
    ASSERT_EQ(14, gsa_data->prn[2]);
    ASSERT_EQ(18, gsa_data->prn[3]);
    ASSERT_EQ(27, gsa_data->prn[4]);
    ASSERT_EQ(22, gsa_data->prn[5]);
    ASSERT_EQ(31, gsa_data->prn[6]);
    ASSERT_EQ(39, gsa_data->prn[7]);
    ASSERT_EQ(0, gsa_data->prn[8]);
    ASSERT_EQ(0, gsa_data->prn[9]);
    ASSERT_EQ(0, gsa_data->prn[10]);
    ASSERT_EQ(0, gsa_data->prn[11]);
    ASSERT_DOUBLE_EQ(1.7, gsa_data->pdop);
    ASSERT_DOUBLE_EQ(1.0, gsa_data->hdop);
    ASSERT_DOUBLE_EQ(1.3, gsa_data->vdop);
}

TEST(parse_GSV_sentence_test, valid_sentence) {
  // create a sample GSV sentence
  std::string sentence = "$GPGSV,3,1,11,03,03,111,00,04,15,270,00,06,01,010,00,13,06,292,00*74";

  // create a GSV_data object to store the parsed fields
  GSV_data *gsv_data = new GSV_data;

  // call the function to parse the sentence
  parse_GSV_sentence(sentence, gsv_data);

  // check if the parsed fields match the expected values
  ASSERT_EQ(gsv_data->num_msgs, 3);
  ASSERT_EQ(gsv_data->msg_num, 1);
  ASSERT_EQ(gsv_data->num_sats, 11);

  ASSERT_EQ(gsv_data->prn[0], 3);
  ASSERT_EQ(gsv_data->elev[0], 3);
  ASSERT_EQ(gsv_data->azim[0], 111);
  ASSERT_EQ(gsv_data->snr[0], 0);

  ASSERT_EQ(gsv_data->prn[1], 4);
  ASSERT_EQ(gsv_data->elev[1], 15);
  ASSERT_EQ(gsv_data->azim[1], 270);
  ASSERT_EQ(gsv_data->snr[1], 0);

  ASSERT_EQ(gsv_data->prn[2], 6);
  ASSERT_EQ(gsv_data->elev[2], 1);
  ASSERT_EQ(gsv_data->azim[2], 10);
  ASSERT_EQ(gsv_data->snr[2], 0);

  ASSERT_EQ(gsv_data->prn[3], 13);
  ASSERT_EQ(gsv_data->elev[3], 6);
  ASSERT_EQ(gsv_data->azim[3], 292);
  ASSERT_EQ(gsv_data->snr[3], 0);
}

TEST(parse_RMC_sentence, valid_sentence) {
    // Construct a valid RMC sentence
    std::string sentence = "$GPRMC,220516,A,5133.82,N,00042.24,W,173.8,231.8,130694,004.2,W*70";

    // Call parse_RMC_sentence to parse the sentence
    RMC_data *rmc_data = new RMC_data;
    parse_RMC_sentence(sentence, rmc_data);

    // Check that the parsed values match the expected values
    ASSERT_EQ(rmc_data->utc_time, "220516");
    ASSERT_EQ(rmc_data->status, 'A');
    ASSERT_EQ(rmc_data->latitude, "5133.82");
    ASSERT_EQ(rmc_data->latitude_dir, 'N');
    ASSERT_EQ(rmc_data->longitude, "00042.24");
    ASSERT_EQ(rmc_data->longitude_dir, 'W');
    ASSERT_DOUBLE_EQ(rmc_data->speed_knots, 173.8);
    ASSERT_DOUBLE_EQ(rmc_data->true_course, 231.8);
    ASSERT_EQ(rmc_data->date, "130694");
    ASSERT_DOUBLE_EQ(rmc_data->variation, 4.2);
    ASSERT_EQ(rmc_data->variation_dir, 'W');
}


TEST(ParseVTGSentenceTest, ValidSentence) {
  // Arrange
  std::string sentence = "$GPVTG,054.7,T,034.4,M,005.5,N,010.2,K,A*25";
  VTG_data vtg_data;
  parse_VTG_sentence(sentence, &vtg_data);

  // Assert
  ASSERT_EQ(vtg_data.true_track_degrees, 54.7);
  ASSERT_EQ(vtg_data.true_track_indicator, 'T');
  ASSERT_EQ(vtg_data.magnetic_track_degrees, 34.4);
  ASSERT_EQ(vtg_data.magnetic_track_indicator, 'M');
  ASSERT_EQ(vtg_data.ground_speed_knots, 5.5);
  ASSERT_EQ(vtg_data.ground_speed_knots_indicator, 'N');
  ASSERT_EQ(vtg_data.ground_speed_kph, 10.2);
  ASSERT_EQ(vtg_data.ground_speed_kph_indicator, 'K');
  ASSERT_EQ(vtg_data.mode, 'A');
}
*/

TEST(ParseGLLSentenceTest, ValidGLL) {
  // Create a valid GLL sentence
  std::string sentence = "$GPGLL,4916.45,N,12311.12,W,225444.00,A,A*58";

  // Create a GLL_data struct and call parse_GLL_sentence
  GLL_data gll_data;
  parse_GLL_sentence(sentence, &gll_data);

  // Check if the values in the struct match the expected values
  ASSERT_EQ(gll_data.latitude, "4916.45");
  ASSERT_EQ(gll_data.latitude_direction, 'N');
  ASSERT_EQ(gll_data.longitude, "12311.12");
  ASSERT_EQ(gll_data.longitude_direction, 'W');
  ASSERT_EQ(gll_data.utc_time, "225444.00");
  ASSERT_EQ(gll_data.status, 'A');
  ASSERT_EQ(gll_data.mode, 'A');
}

/*
TEST(ParseGLLSentenceTest, InvalidGLL) {
  // Create an invalid GLL sentence
  std::string sentence = "$GPGLL,4916.45,N,12311.12,W,225444.00,V,N*5C";

  // Create a GLL_data struct and call parse_GLL_sentence
  GLL_data gll_data;
  parse_GLL_sentence(sentence, &gll_data);

  // Check if the struct has default values (empty strings and 0 values)
  ASSERT_EQ(gll_data.latitude, "");
  ASSERT_EQ(gll_data.latitude_direction, 0);
  ASSERT_EQ(gll_data.longitude, "");
  ASSERT_EQ(gll_data.longitude_direction, 0);
  ASSERT_EQ(gll_data.utc_time, "");
  ASSERT_EQ(gll_data.status, 0);
  ASSERT_EQ(gll_data.mode, 0);
}
*/
