#include <gtest/gtest.h>

#include "example.h"


/*
TEST(calculateChecksum, GPGGA_sentence) {
  std::string sentence = "$GPGGA,170834,4124.8963,N,08151.6838,W,1,05,1.5,280.2,M,-34.0,M,,,*59";
  int result = calculateChecksum(sentence);
  ASSERT_EQ(result, 0);
}
*/

TEST(parse_nmea_sentence, Checksum_error) {
        auto nmea_sentence = "$GPGGA,170834,4124.8963,N,08151.6838,W,1,05,1.5,280.2,M,-34.0,M,,,*59";
        GPS_data gps_data;
        int err_code = parse_nmea_sentence(nmea_sentence, &gps_data);
        ASSERT_EQ(err_code, CHECKSUM_ERR);
}

/*
TEST(parse_nmea_sentence, GPGGA_sentence) {
        auto nmea_sentence = "$GPGGA,170834,4124.8963,N,08151.6838,W,1,05,1.5,280.2,M,-34.0,M,,,*59 ";
        auto nmea_code = "GGA";
        GPS_data gps_data;
        parse_nmea_sentence(nmea_sentence, &gps_data);
        ASSERT_EQ(nmea_code, gps_data.sentence_type);

        GGA_data& gga_data = *static_cast<GGA_data*>(gps_data.data);

        ASSERT_EQ("170834", gga_data.time);
        ASSERT_EQ("4124.8963", gga_data.latitude);
        ASSERT_EQ('N', gga_data.lat_direction);
        ASSERT_EQ("08151.6838", gga_data.longitude);
        ASSERT_EQ('W', gga_data.lon_direction);
        ASSERT_EQ(1, gga_data.gps_quality);
        ASSERT_EQ(05, gga_data.num_satellites);
        ASSERT_DOUBLE_EQ(1.5, gga_data.hdop);
        ASSERT_DOUBLE_EQ(280.2, gga_data.altitude);
        ASSERT_EQ('M', gga_data.unit_of_altitude);
        ASSERT_DOUBLE_EQ(-34.0, gga_data.geoidal_sep);
        ASSERT_EQ('M', gga_data.geoidal_unit);
        ASSERT_EQ(0, gga_data.age_diff_corr);
        ASSERT_EQ("", gga_data.diff_ref_station_id);
}
*/


/*
TEST(get_nmea_sentence_code, get_code_from_sentence) {
        auto nmea_sentence = "$GPGGA,170834,4124.8963,N,08151.6838,W,1,05,1.5,280.2,M,-34.0,M,,,*59 ";
        auto nmea_code = "GPGGA";
        ASSERT_EQ(nmea_code, get_nmea_sentence_code(nmea_sentence));
}

// invalid nmea format
TEST(get_nmea_sentence_code, invalid_nmea_format) {
        auto nmea_sentence = "#GPGGA,170-34.0,M,,,*59 ";
        auto returned_error = "NMEA_CODE_ERR";
        ASSERT_EQ(returned_error, get_nmea_sentence_code(nmea_sentence));
}
*/

/*
TEST(GGA_parser, Valid_data) {
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

TEST(GGA_parser, data_with_missing_params) {
        auto sentence = "$GPGGA,170834,1.5,280.2,M,-34.0,M,,,*59";

        GGA_data *gga_data = new GGA_data;
        int err_code = parse_GGA_sentence(sentence, gga_data);
        ASSERT_EQ(err_code, MISSING_PARAM_ERR);
        ASSERT_EQ("", gga_data->time);
        ASSERT_EQ("", gga_data->latitude);
        ASSERT_EQ('\0', gga_data->lat_direction);
        ASSERT_EQ("", gga_data->longitude);
        ASSERT_EQ('\0', gga_data->lon_direction);
        ASSERT_EQ(DEFAULT_VAL_NUM, gga_data->gps_quality);
        ASSERT_EQ(DEFAULT_VAL_NUM, gga_data->num_satellites);
        ASSERT_DOUBLE_EQ(DEFAULT_VAL_NUM, gga_data->hdop);
        ASSERT_DOUBLE_EQ(DEFAULT_VAL_NUM, gga_data->altitude);
        ASSERT_EQ('\0', gga_data->unit_of_altitude);
        ASSERT_DOUBLE_EQ(DEFAULT_VAL_NUM, gga_data->geoidal_sep);
        ASSERT_EQ('\0', gga_data->geoidal_unit);
        ASSERT_EQ(DEFAULT_VAL_NUM, gga_data->age_diff_corr);
        ASSERT_EQ("", gga_data->diff_ref_station_id);
}

TEST(GGA_parser, data_with_wrong_strings) {
        auto sentence = "$GPGGA,170834,4124.8963,N,08151.6838,W,*1,*05,*1.5,/280.2,M,%-34.0,M,,,*59";

        GGA_data *gga_data = new GGA_data;
        parse_GGA_sentence(sentence, gga_data);

        ASSERT_EQ("170834", gga_data->time);
        ASSERT_EQ("4124.8963", gga_data->latitude);
        ASSERT_EQ('N', gga_data->lat_direction);
        ASSERT_EQ("08151.6838", gga_data->longitude);
        ASSERT_EQ('W', gga_data->lon_direction);
        ASSERT_EQ(0, gga_data->gps_quality);
        ASSERT_EQ(0, gga_data->num_satellites);
        ASSERT_DOUBLE_EQ(0, gga_data->hdop);
        ASSERT_DOUBLE_EQ(0, gga_data->altitude);
        ASSERT_EQ('M', gga_data->unit_of_altitude);
        ASSERT_DOUBLE_EQ(0, gga_data->geoidal_sep);
        ASSERT_EQ('M', gga_data->geoidal_unit);
        ASSERT_EQ(0, gga_data->age_diff_corr);
        ASSERT_EQ("", gga_data->diff_ref_station_id);
}
*/

/*
TEST(GSA_parser, Valid_data) {
    auto sentence = "$GPGSA,A,3,19,28,14,18,27,22,31,39,,,,,1.7,1.0,1.3,*34";
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

TEST(GSA_parser, data_with_missing_params) {
    auto sentence = "$GPGSA,A,3,19,28,14,,,,,,1.7,1.0,1.3,*34";
    GSA_data *gsa_data = new GSA_data;
    int err_code = parse_GSA_sentence(sentence, gsa_data);
    ASSERT_EQ(err_code, MISSING_PARAM_ERR);
    ASSERT_EQ('\0', gsa_data->mode1);
    ASSERT_EQ(DEFAULT_VAL_NUM, gsa_data->mode2);
    ASSERT_EQ(DEFAULT_VAL_NUM, gsa_data->prn[0]);
    ASSERT_EQ(DEFAULT_VAL_NUM, gsa_data->prn[1]);
    ASSERT_EQ(DEFAULT_VAL_NUM, gsa_data->prn[2]);
    ASSERT_EQ(DEFAULT_VAL_NUM, gsa_data->prn[3]);
    ASSERT_EQ(DEFAULT_VAL_NUM, gsa_data->prn[4]);
    ASSERT_EQ(DEFAULT_VAL_NUM, gsa_data->prn[5]);
    ASSERT_EQ(DEFAULT_VAL_NUM, gsa_data->prn[6]);
    ASSERT_EQ(DEFAULT_VAL_NUM, gsa_data->prn[7]);
    ASSERT_EQ(DEFAULT_VAL_NUM, gsa_data->prn[8]);
    ASSERT_EQ(DEFAULT_VAL_NUM, gsa_data->prn[9]);
    ASSERT_EQ(DEFAULT_VAL_NUM, gsa_data->prn[10]);
    ASSERT_EQ(DEFAULT_VAL_NUM, gsa_data->prn[11]);
    ASSERT_DOUBLE_EQ(DEFAULT_VAL_NUM, gsa_data->pdop);
    ASSERT_DOUBLE_EQ(DEFAULT_VAL_NUM, gsa_data->hdop);
    ASSERT_DOUBLE_EQ(DEFAULT_VAL_NUM, gsa_data->vdop);
}


TEST(GSA_parser, Invalid_data) {
    auto sentence = "$GPGSA,A,3,19,28,14,18,&%2#7,22,31,/*39,,,,,1.7,1.0,1.3,*34";
    GSA_data *gsa_data = new GSA_data;
    parse_GSA_sentence(sentence, gsa_data);

    ASSERT_EQ('A', gsa_data->mode1);
    ASSERT_EQ(3, gsa_data->mode2);
    ASSERT_EQ(19, gsa_data->prn[0]);
    ASSERT_EQ(28, gsa_data->prn[1]);
    ASSERT_EQ(14, gsa_data->prn[2]);
    ASSERT_EQ(18, gsa_data->prn[3]);
    ASSERT_EQ(DEFAULT_VAL_NUM, gsa_data->prn[4]);
    ASSERT_EQ(22, gsa_data->prn[5]);
    ASSERT_EQ(31, gsa_data->prn[6]);
    ASSERT_EQ(DEFAULT_VAL_NUM, gsa_data->prn[7]);
    ASSERT_EQ(0, gsa_data->prn[8]);
    ASSERT_EQ(0, gsa_data->prn[9]);
    ASSERT_EQ(0, gsa_data->prn[10]);
    ASSERT_EQ(0, gsa_data->prn[11]);
    ASSERT_DOUBLE_EQ(1.7, gsa_data->pdop);
    ASSERT_DOUBLE_EQ(1.0, gsa_data->hdop);
    ASSERT_DOUBLE_EQ(1.3, gsa_data->vdop);
}
*/

/*
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


TEST(parse_GSV_sentence_test, missing_params) {
  // create a sample GSV sentence
  std::string sentence = "$GPGSV,3,1,11,03,03,111,00,04,15,01,010,00,13,06,292,00*74";

  // create a GSV_data object to store the parsed fields
  GSV_data *gsv_data = new GSV_data;

  // call the function to parse the sentence
  int err_code = parse_GSV_sentence(sentence, gsv_data);

  ASSERT_EQ(err_code, MISSING_PARAM_ERR);
  // check if the parsed fields match the expected values
  ASSERT_EQ(gsv_data->num_msgs, DEFAULT_VAL_NUM);
  ASSERT_EQ(gsv_data->msg_num, DEFAULT_VAL_NUM);
  ASSERT_EQ(gsv_data->num_sats, DEFAULT_VAL_NUM);

  ASSERT_EQ(gsv_data->prn[0], DEFAULT_VAL_NUM);
  ASSERT_EQ(gsv_data->elev[0], DEFAULT_VAL_NUM);
  ASSERT_EQ(gsv_data->azim[0], DEFAULT_VAL_NUM);
  ASSERT_EQ(gsv_data->snr[0], DEFAULT_VAL_NUM);

  ASSERT_EQ(gsv_data->prn[1], DEFAULT_VAL_NUM);
  ASSERT_EQ(gsv_data->elev[1], DEFAULT_VAL_NUM);
  ASSERT_EQ(gsv_data->azim[1], DEFAULT_VAL_NUM);
  ASSERT_EQ(gsv_data->snr[1], DEFAULT_VAL_NUM);

  ASSERT_EQ(gsv_data->prn[2], DEFAULT_VAL_NUM);
  ASSERT_EQ(gsv_data->elev[2], DEFAULT_VAL_NUM);
  ASSERT_EQ(gsv_data->azim[2], DEFAULT_VAL_NUM);
  ASSERT_EQ(gsv_data->snr[2], DEFAULT_VAL_NUM);

  ASSERT_EQ(gsv_data->prn[3], DEFAULT_VAL_NUM);
  ASSERT_EQ(gsv_data->elev[3], DEFAULT_VAL_NUM);
  ASSERT_EQ(gsv_data->azim[3], DEFAULT_VAL_NUM);
  ASSERT_EQ(gsv_data->snr[3], DEFAULT_VAL_NUM);
}


TEST(parse_GSV_sentence_test, Invalid_sentence) {
  // create a sample GSV sentence
  std::string sentence = "$GPGSV,*3,&1,11,03,03,111,00,04,15,270,00,06,01,010,00,13,06,292,00*74";

  // create a GSV_data object to store the parsed fields
  GSV_data *gsv_data = new GSV_data;

  // call the function to parse the sentence
  parse_GSV_sentence(sentence, gsv_data);

  // check if the parsed fields match the expected values
  ASSERT_EQ(gsv_data->num_msgs, DEFAULT_VAL_NUM);
  ASSERT_EQ(gsv_data->msg_num, DEFAULT_VAL_NUM);
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
*/



/*
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

TEST(parse_RMC_sentence, missing_param) {
    // Construct a valid RMC sentence
    std::string sentence = "$GPRMC,220516,A,,231.8,130694,004.2,W*70";

    // Call parse_RMC_sentence to parse the sentence
    RMC_data *rmc_data = new RMC_data;
    int err_code = parse_RMC_sentence(sentence, rmc_data);

    ASSERT_EQ(err_code, MISSING_PARAM_ERR);
    // Check that the parsed values match the expected values
    ASSERT_EQ(rmc_data->utc_time, "");
    ASSERT_EQ(rmc_data->status, '\0');
    ASSERT_EQ(rmc_data->latitude, "");
    ASSERT_EQ(rmc_data->latitude_dir, '\0');
    ASSERT_EQ(rmc_data->longitude, "");
    ASSERT_EQ(rmc_data->longitude_dir, '\0');
    ASSERT_DOUBLE_EQ(rmc_data->speed_knots, DEFAULT_VAL_NUM);
    ASSERT_DOUBLE_EQ(rmc_data->true_course, DEFAULT_VAL_NUM);
    ASSERT_EQ(rmc_data->date, "");
    ASSERT_DOUBLE_EQ(rmc_data->variation, DEFAULT_VAL_NUM);
    ASSERT_EQ(rmc_data->variation_dir, '\0');
}

TEST(parse_RMC_sentence, Invalid_sentence) {
    // Construct a valid RMC sentence
    std::string sentence = "$GPRMC,220516,A,5133.82,N,00042.24,W,/173.8,**231.8,130694,004.2,W*70";

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
    ASSERT_DOUBLE_EQ(rmc_data->speed_knots, 0);
    ASSERT_DOUBLE_EQ(rmc_data->true_course, 0);
    ASSERT_EQ(rmc_data->date, "130694");
    ASSERT_DOUBLE_EQ(rmc_data->variation, 4.2);
    ASSERT_EQ(rmc_data->variation_dir, 'W');
}
*/

/*
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

TEST(ParseVTGSentenceTest, Missing_params) {
  // Arrange
  std::string sentence = "$GPVTG,054.7,T,,N,010.2,K,A*25";
  VTG_data vtg_data;
  parse_VTG_sentence(sentence, &vtg_data);

  // Assert
  ASSERT_EQ(vtg_data.true_track_degrees, DEFAULT_VAL_NUM);
  ASSERT_EQ(vtg_data.true_track_indicator, '\0');
  ASSERT_EQ(vtg_data.magnetic_track_degrees, DEFAULT_VAL_NUM);
  ASSERT_EQ(vtg_data.magnetic_track_indicator, '\0');
  ASSERT_EQ(vtg_data.ground_speed_knots, DEFAULT_VAL_NUM);
  ASSERT_EQ(vtg_data.ground_speed_knots_indicator, '\0');
  ASSERT_EQ(vtg_data.ground_speed_kph, DEFAULT_VAL_NUM);
  ASSERT_EQ(vtg_data.ground_speed_kph_indicator, '\0');
  ASSERT_EQ(vtg_data.mode, '\0');
}

TEST(ParseVTGSentenceTest, Invalid_data) {
  // Arrange
  std::string sentence = "$GPVTG,054.7,T,034.4,M,*0,N,010.2,K,A*25";
  VTG_data vtg_data;
  parse_VTG_sentence(sentence, &vtg_data);

  // Assert
  ASSERT_EQ(vtg_data.true_track_degrees, 54.7);
  ASSERT_EQ(vtg_data.true_track_indicator, 'T');
  ASSERT_EQ(vtg_data.magnetic_track_degrees, 34.4);
  ASSERT_EQ(vtg_data.magnetic_track_indicator, 'M');
  ASSERT_EQ(vtg_data.ground_speed_knots, DEFAULT_VAL_NUM);
  ASSERT_EQ(vtg_data.ground_speed_knots_indicator, 'N');
  ASSERT_EQ(vtg_data.ground_speed_kph, 10.2);
  ASSERT_EQ(vtg_data.ground_speed_kph_indicator, 'K');
  ASSERT_EQ(vtg_data.mode, 'A');
}
*/

/*
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
*/
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


/*
TEST(ParseZDASentenceTest, ValidZDA) {
  // Create a valid ZDA sentence
  std::string sentence = "$GPZDA,024611.08,25,03,2002,00,00*6A ";

  // Create a ZDA_data struct and call parse_ZDA_sentence
  ZDA_data zda_data;
  parse_ZDA_sentence(sentence, &zda_data);

  // Check if the values in the struct match the expected values
  ASSERT_EQ(2, zda_data.hour);
  ASSERT_EQ(46, zda_data.minute);
  ASSERT_EQ(11, zda_data.second);
  ASSERT_EQ(8, zda_data.millisecond);
  ASSERT_EQ(25, zda_data.day);
  ASSERT_EQ(3, zda_data.month);
  ASSERT_EQ(2002, zda_data.year);
  ASSERT_EQ(0, zda_data.local_hour_offset);
  ASSERT_EQ(0, zda_data.local_minute_offset);
}


TEST(ParseZDASentenceTest, MissingParam) {
  // Create a valid ZDA sentence
  std::string sentence = "$GPZDA,25,03,2002,00*6A ";

  // Create a ZDA_data struct and call parse_ZDA_sentence
  ZDA_data zda_data;
  int err_code = parse_ZDA_sentence(sentence, &zda_data);
  
  ASSERT_EQ(err_code, MISSING_PARAM_ERR);
  // Check if the values in the struct match the expected values
  ASSERT_EQ(DEFAULT_VAL_NUM, zda_data.hour);
  ASSERT_EQ(DEFAULT_VAL_NUM, zda_data.minute);
  ASSERT_EQ(DEFAULT_VAL_NUM, zda_data.second);
  ASSERT_EQ(DEFAULT_VAL_NUM, zda_data.millisecond);
  ASSERT_EQ(DEFAULT_VAL_NUM, zda_data.day);
  ASSERT_EQ(DEFAULT_VAL_NUM, zda_data.month);
  ASSERT_EQ(DEFAULT_VAL_NUM, zda_data.year);
  ASSERT_EQ(DEFAULT_VAL_NUM, zda_data.local_hour_offset);
  ASSERT_EQ(DEFAULT_VAL_NUM, zda_data.local_minute_offset);
}

TEST(ParseZDASentenceTest, Invalid_data) {
  // Create a valid ZDA sentence
  std::string sentence = "$GPZDA,024611.08,/,03,*,00,00*6A ";

  // Create a ZDA_data struct and call parse_ZDA_sentence
  ZDA_data zda_data;
  parse_ZDA_sentence(sentence, &zda_data);

  // Check if the values in the struct match the expected values
  ASSERT_EQ(2, zda_data.hour);
  ASSERT_EQ(46, zda_data.minute);
  ASSERT_EQ(11, zda_data.second);
  ASSERT_EQ(8, zda_data.millisecond);
  ASSERT_EQ(DEFAULT_VAL_NUM, zda_data.day);
  ASSERT_EQ(3, zda_data.month);
  ASSERT_EQ(DEFAULT_VAL_NUM, zda_data.year);
  ASSERT_EQ(0, zda_data.local_hour_offset);
  ASSERT_EQ(0, zda_data.local_minute_offset);
}
*/

/*
TEST(GSTParsingTest, ValidSentence) {
  std::string sentence = "$GPGST,024603.00,3.2,6.6,4.7,47.3,5.8,5.6,22.0*58";

  GST_data parsed_data;
  parse_GST_sentence(sentence, &parsed_data);

  ASSERT_EQ(parsed_data.utc_time, "024603.00");
  ASSERT_DOUBLE_EQ(parsed_data.rms_deviation, 3.2);
  ASSERT_DOUBLE_EQ(parsed_data.semi_major_err, 6.6);
  ASSERT_DOUBLE_EQ(parsed_data.semi_minor_err, 4.7);
  ASSERT_DOUBLE_EQ(parsed_data.orientation_err, 47.3);
  ASSERT_DOUBLE_EQ(parsed_data.lat_err, 5.8);
  ASSERT_DOUBLE_EQ(parsed_data.lon_err, 5.6);
  ASSERT_DOUBLE_EQ(parsed_data.alt_err, 22.0);
}

TEST(GSTParsingTest, Missing_param) {
  std::string sentence = "$GPGST,6.6,4.7,47.3,5.8,5.6,22.0*58";

  GST_data parsed_data;
  int err_code = parse_GST_sentence(sentence, &parsed_data);
  ASSERT_EQ(err_code, MISSING_PARAM_ERR);
  ASSERT_EQ(parsed_data.utc_time, "");
  ASSERT_DOUBLE_EQ(parsed_data.rms_deviation, DEFAULT_VAL_NUM);
  ASSERT_DOUBLE_EQ(parsed_data.semi_major_err, DEFAULT_VAL_NUM);
  ASSERT_DOUBLE_EQ(parsed_data.semi_minor_err, DEFAULT_VAL_NUM);
  ASSERT_DOUBLE_EQ(parsed_data.orientation_err, DEFAULT_VAL_NUM);
  ASSERT_DOUBLE_EQ(parsed_data.lat_err, DEFAULT_VAL_NUM);
  ASSERT_DOUBLE_EQ(parsed_data.lon_err, DEFAULT_VAL_NUM);
  ASSERT_DOUBLE_EQ(parsed_data.alt_err, DEFAULT_VAL_NUM);
}

TEST(GSTParsingTest, InvalidSentence) {
  std::string sentence = "$GPGST,024603.00,3.2,6.6,SI,47.3,TR,5.6,22.0*58";

  GST_data parsed_data;
  parse_GST_sentence(sentence, &parsed_data);

  ASSERT_EQ(parsed_data.utc_time, "024603.00");
  ASSERT_DOUBLE_EQ(parsed_data.rms_deviation, 3.2);
  ASSERT_DOUBLE_EQ(parsed_data.semi_major_err, 6.6);
  ASSERT_DOUBLE_EQ(parsed_data.semi_minor_err, DEFAULT_VAL_NUM);
  ASSERT_DOUBLE_EQ(parsed_data.orientation_err, 47.3);
  ASSERT_DOUBLE_EQ(parsed_data.lat_err, DEFAULT_VAL_NUM);
  ASSERT_DOUBLE_EQ(parsed_data.lon_err, 5.6);
  ASSERT_DOUBLE_EQ(parsed_data.alt_err, 22.0);
}
*/

/*
TEST(ParseHDT, ValidSentence) {
  // Example valid HDT sentence: "$GPHDT,123.456,T*23\r\n"
  std::string sentence = "$GPHDT,123.456,T*23\r\n";
  HDT_data hdt_data;
  parse_HDT_sentence(sentence, &hdt_data);
  ASSERT_FLOAT_EQ(hdt_data.heading, 123.456);
}


TEST(ParseHDT, InvalidSentence) {
  // Example invalid HDT sentence: "$GPVTG,1.2,T,3.4,M,5.6,N,10.4,K*4E\r\n"
  std::string sentence = "$GPVTG,1.2,T,3.4,M,5.6,N,10.4,K*4E\r\n";
  HDT_data hdt_data;
  int err_code = parse_HDT_sentence(sentence, &hdt_data);
  ASSERT_EQ(err_code, WRONG_SENTENCE_ID_ERR);
}
*/

/*
TEST(ParseGRS, ValidSentence) {
  // Example valid GRS sentence: "$GPGRS,024603.00,1,-1.8,-2.7,0.3,,,,,,,,,*6C"
  std::string sentence = "$GPGRS,220320.0,0,-0.8,-0.2,-0.1,-0.2,0.8,0.6,,,,,,1,*55"; 

  GRS_data grs_data;
  parse_GRS_sentence(sentence, &grs_data);
  ASSERT_EQ(grs_data.utc_time, "220320.0");
  ASSERT_EQ(grs_data.mode, 0);
  ASSERT_FLOAT_EQ(grs_data.residual1, -0.8);
  ASSERT_FLOAT_EQ(grs_data.residual2, -0.2);
  ASSERT_FLOAT_EQ(grs_data.residual3, -0.1);
  ASSERT_FLOAT_EQ(grs_data.residual4, -0.2);
  ASSERT_FLOAT_EQ(grs_data.residual5, 0.8);
  ASSERT_FLOAT_EQ(grs_data.residual6, 0.6);
  ASSERT_FLOAT_EQ(grs_data.residual7, 0.0);
  ASSERT_FLOAT_EQ(grs_data.residual8, 0.0);
  ASSERT_FLOAT_EQ(grs_data.residual9, 0.0);
  ASSERT_FLOAT_EQ(grs_data.residual11, 0.0);
  ASSERT_FLOAT_EQ(grs_data.residual12, 1);
}
*/