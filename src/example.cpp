// write code for handling missing fields
// write code for handling incomplete packets

#include "example.h"

void parse_nmea_sentence(string sentence)
{
    string sentence_type = get_nmea_sentence_code(sentence);
}

string get_nmea_sentence_code(string sentence)
{
    string code;

    // check if the sentence starts with "$"
    if (sentence[0] != '$') {
        code = "NMEA_CODE_ERR";
        return code; // return error string if it doesn't start with $
    }

    // find the first comma
    size_t comma_pos = sentence.find(',');

    // extract the code
    code = sentence.substr(1, comma_pos - 1);

    return code;
}

/*
void parse_GGA_sentence(string sentence, GGA_data *gga_data)
{
    // parse the string sentence

    // extract all the parameters from nmea packet and store them
    // in their respective fields in gga_data structure
    // example: $GPGGA,170834,4124.8963,N,08151.6838,W,1,05,1.5,280.2,M,-34.0,M,,,*59
}
*/


void parse_GGA_sentence(std::string sentence, GGA_data *gga_data) {
    // check if the sentence is a valid GGA sentence
    if (sentence.substr(0, 6) != "$GPGGA") {
        return; // not a valid GGA sentence, so return
    }

    // split the sentence into comma-separated fields
    std::istringstream ss(sentence);
    std::vector<std::string> fields;
    std::string field;
    while (std::getline(ss, field, ',')) {
        fields.push_back(field);
    }

    // extract the fields and store them in the gga_data structure
    gga_data->time = fields[1];
    gga_data->latitude = fields[2];
    gga_data->lat_direction = fields[3][0];
    gga_data->longitude = fields[4];
    gga_data->lon_direction = fields[5][0];
    gga_data->gps_quality = std::stoi(fields[6]);
    gga_data->num_satellites = std::stoi(fields[7]);
    gga_data->hdop = std::stod(fields[8]);
    gga_data->altitude = std::stod(fields[9]);
    gga_data->unit_of_altitude = fields[10][0];
    gga_data->geoidal_sep = std::stod(fields[11]);
    gga_data->geoidal_unit = fields[12][0];
    if (!fields[13].empty()) {
        gga_data->age_diff_corr = std::stod(fields[13]);
    }
    gga_data->diff_ref_station_id = fields[14];
}

void parse_GSA_sentence(string sentence, GSA_data *gsa_data) {
    // check if the sentence is a valid GSA sentence
    if (sentence.substr(0, 6) != "$GPGSA") {
        return; // not a valid GSA sentence, so return
    }

    // split the sentence into comma-separated fields
    std::istringstream ss(sentence);
    std::vector<std::string> fields;
    std::string field;
    while (std::getline(ss, field, ',')) {
        fields.push_back(field);
    }

    gsa_data->mode1 = fields[1][0];
    gsa_data->mode2 = stoi(fields[2]);
    for (int i = 0; i < 12; i++) {
        if (fields[i+3].empty()) {
            gsa_data->prn[i] = 0;
        } else {
            gsa_data->prn[i] = stoi(fields[i+3]);
        }
    }
    gsa_data->pdop = stod(fields[15]);
    gsa_data->hdop = stod(fields[16]);
    gsa_data->vdop = stod(fields[17]);
}

void parse_GSV_sentence(string sentence, GSV_data *gsv_data) {
    // check if the sentence is a valid GSV sentence
    if (sentence.substr(0, 6) != "$GPGSV") {
        return; // not a valid GSV sentence, so return
    }

    // split the sentence into comma-separated fields
    std::istringstream ss(sentence);
    std::vector<std::string> fields;
    std::string field;
    while (std::getline(ss, field, ',')) {
        fields.push_back(field);
    }

    // extract the fields from the sentence
    gsv_data->num_msgs = std::stoi(fields[1]);
    gsv_data->msg_num = std::stoi(fields[2]);
    gsv_data->num_sats = std::stoi(fields[3]);

    // extract the satellite data from the sentence
    int num_sats = (fields.size() - 4) / 4;
    gsv_data->prn.resize(num_sats);
    gsv_data->elev.resize(num_sats);
    gsv_data->azim.resize(num_sats);
    gsv_data->snr.resize(num_sats);

    for (int i = 0; i < num_sats; i++) {
        int field_index = i * 4 + 4;
        gsv_data->prn[i] = std::stoi(fields[field_index]);
        gsv_data->elev[i] = std::stoi(fields[field_index + 1]);
        gsv_data->azim[i] = std::stoi(fields[field_index + 2]);
        gsv_data->snr[i] = std::stoi(fields[field_index + 3]);
    }
}

void parse_RMC_sentence(string sentence, RMC_data *rmc_data)
{
    // check if the sentence is a valid RMC sentence
    if (sentence.substr(0, 6) != "$GPRMC") {
        return; // not a valid RMC sentence, so return
    }

    // split the sentence into comma-separated fields
    std::istringstream ss(sentence);
    std::vector<std::string> fields;
    std::string field;
    while (std::getline(ss, field, ',')) {
        fields.push_back(field);
    }

    // extract all the parameters from nmea packet and store them
    // in their respective fields in rmc_data structure
    rmc_data->utc_time = fields[1];
    rmc_data->status = fields[2][0];
    rmc_data->latitude = fields[3];
    rmc_data->latitude_dir = fields[4][0];
    rmc_data->longitude = fields[5];
    rmc_data->longitude_dir = fields[6][0];
    rmc_data->speed_knots = stod(fields[7]);
    rmc_data->true_course = stod(fields[8]);
    rmc_data->date = fields[9];
    rmc_data->variation = stod(fields[10]);
    rmc_data->variation_dir = fields[11][0];
}


void parse_VTG_sentence(string sentence, VTG_data *vtg_data)
{
    // check if the sentence is a valid VTG sentence
    if (sentence.substr(0, 6) != "$GPVTG") {
        return; // not a valid VTG sentence, so return
    }

    // split the sentence into comma-separated fields
    std::istringstream ss(sentence);
    std::vector<std::string> fields;
    std::string field;
    while (std::getline(ss, field, ',')) {
        fields.push_back(field);
    }

    // extract all the parameters from nmea packet and store them
    // in their respective fields in vtg_data structure
    vtg_data->true_track_degrees = stod(fields[1]);
    vtg_data->true_track_indicator = fields[2][0];
    vtg_data->magnetic_track_degrees = stod(fields[3]);
    vtg_data->magnetic_track_indicator = fields[4][0];
    vtg_data->ground_speed_knots = stod(fields[5]);
    vtg_data->ground_speed_knots_indicator = fields[6][0];
    vtg_data->ground_speed_kph = stod(fields[7]);
    vtg_data->ground_speed_kph_indicator = fields[8][0];
    vtg_data->mode = fields[9][0];
}

void parse_GLL_sentence(string sentence, GLL_data *gll_data)
{
    // check if the sentence is a valid GLL sentence
    if (sentence.substr(0, 6) != "$GPGLL") {
        return; // not a valid GLL sentence, so return
    }

    // split the sentence into comma-separated fields
    std::istringstream ss(sentence);
    std::vector<std::string> fields;
    std::string field;
    while (std::getline(ss, field, ',')) {
        fields.push_back(field);
    }

    // extract all the parameters from nmea packet and store them
    // in their respective fields in gll_data structure
    gll_data->latitude = fields[1];
    gll_data->latitude_direction = fields[2][0];
    gll_data->longitude = fields[3];
    gll_data->longitude_direction = fields[4][0];
    gll_data->utc_time = fields[5];
    gll_data->status = fields[6][0];
    gll_data->mode = fields[7][0];
}



void parse_ZDA_sentence(string sentence, ZDA_data *zda_data)
{
    // check if the sentence is a valid ZDA sentence
    if (sentence.substr(0, 6) != "$GPZDA") {
        return; // not a valid ZDA sentence, so return
    }

    // split the sentence into comma-separated fields
    std::istringstream ss(sentence);
    std::vector<std::string> fields;
    std::string field;
    while (std::getline(ss, field, ',')) {
        fields.push_back(field);
    }

    // extract all the parameters from nmea packet and store them
    // in their respective fields in zda_data structure
    zda_data->hour = std::stoi(fields[1].substr(0, 2));
    zda_data->minute = std::stoi(fields[1].substr(2, 2));
    zda_data->second = std::stoi(fields[1].substr(4, 2));
    zda_data->millisecond = std::stoi(fields[1].substr(7, 3));
    zda_data->day = std::stoi(fields[2]);
    zda_data->month = std::stoi(fields[3]);
    zda_data->year = std::stoi(fields[4]);
    zda_data->local_hour_offset = std::stoi(fields[5]);
    zda_data->local_minute_offset = std::stoi(fields[6]);
}




void parse_GST_sentence(string sentence, GST_data *gst_data)
{
    // check if the sentence is a valid GST sentence
    if (sentence.substr(0, 6) != "$GPGST") {
        return; // not a valid GST sentence, so return
    }

    // split the sentence into comma-separated fields
    std::istringstream ss(sentence);
    std::vector<std::string> fields;
    std::string field;
    while (std::getline(ss, field, ',')) {
        fields.push_back(field);
    }

    // extract all the parameters from nmea sentence and store them
    // in their respective fields in gst_data structure
    gst_data->utc_time = fields[1];
    gst_data->rms_deviation = std::stod(fields[2]);
    gst_data->semi_major_err = std::stod(fields[3]);
    gst_data->semi_minor_err = std::stod(fields[4]);
    if (!fields[5].empty())
        gst_data->orientation_err = std::stod(fields[5]);
    else
        gst_data->orientation_err = 0;

    if (!fields[6].empty())
        gst_data->lat_err = std::stod(fields[6]);
    else
        gst_data->lat_err = 0;
    
    if (!fields[7].empty())
        gst_data->lon_err = std::stod(fields[7]);
    else
        gst_data->lon_err = 0;

    if (!fields[8].empty())
        gst_data->alt_err = std::stod(fields[8]);
    else
        gst_data->lon_err = 0;
}