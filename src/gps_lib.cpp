// write code for handling missing fields
// write code for handling incomplete packets

#include "gps_lib.h"

/**
    @brief Parse an NMEA sentence and store the parsed data in the provided GPS_data structure.
    @param sentence The NMEA sentence to be parsed.
    @param gps_data A pointer to a GPS_data structure to store the parsed data.
    @return int An error code indicating if there was an issue with the provided sentence.
*/
int parse_nmea_sentence(string sentence, GPS_data *gps_data)
{
    string sentence_type = get_nmea_sentence_code(sentence);
    if (sentence_type == "NMEA_CODE_ERR")
    {
        return INCORRECT_SENTENCE_CODE_ERR;
    }
    
    int ret = calculateChecksum(sentence);
    
    if (ret == -1)
    {
        return CHECKSUM_ERR;
    }

    // If the sentence type is GPGGA, parse the sentence and store data in GPS_data structure
    if (sentence_type == "GPGGA")
    {
        gps_data->sentence_type = "GGA";
        GGA_data* ptr = new GGA_data;
        int err_code = parse_GGA_sentence(sentence, ptr);
        gps_data->data = ptr;
        return err_code;
    }
    else if (sentence_type == "GPGSA")
    {
        gps_data->sentence_type = "GSA";
        GSA_data* ptr = new GSA_data;
        int err_code = parse_GSA_sentence(sentence, ptr);
        gps_data->data = ptr;
        return err_code;
    }
    else if (sentence_type == "GPGSV")
    {
        gps_data->sentence_type = "GSV";
        GSV_data* ptr = new GSV_data;
        int err_code = parse_GSV_sentence(sentence, ptr);
        gps_data->data = ptr;
        return err_code;
    }
    else if (sentence_type == "GPRMC")
    {
        gps_data->sentence_type = "RMC";
        RMC_data* ptr = new RMC_data;
        int err_code = parse_RMC_sentence(sentence, ptr);
        gps_data->data = ptr;
        return err_code;
    }
    else if (sentence_type == "GPVTG")
    {
        gps_data->sentence_type = "VTG";
        VTG_data* ptr = new VTG_data;
        int err_code = parse_VTG_sentence(sentence, ptr);
        gps_data->data = ptr;
        return err_code;
    }
    else if (sentence_type == "GPGLL")
    {
        gps_data->sentence_type = "GLL";
        GLL_data* ptr = new GLL_data;
        int err_code = parse_GLL_sentence(sentence, ptr);
        gps_data->data = ptr;
        return err_code;
    }
    else if (sentence_type == "GPZDA")
    {
        gps_data->sentence_type = "ZDA";
        ZDA_data* ptr = new ZDA_data;
        int err_code = parse_ZDA_sentence(sentence, ptr);
        gps_data->data = ptr;
        return err_code;
    }
    else if (sentence_type == "GPGST")
    {
        gps_data->sentence_type = "GST";
        GST_data* ptr = new GST_data;
        int err_code = parse_GST_sentence(sentence, ptr);
        gps_data->data = ptr;
        return err_code;
    }
    else if (sentence_type == "GPHDT")
    {
        gps_data->sentence_type = "HDT";
        HDT_data* ptr = new HDT_data;
        int err_code = parse_HDT_sentence(sentence, ptr);
        gps_data->data = ptr;
        return err_code;
    }
    else if (sentence_type == "GPGRS")
    {
        gps_data->sentence_type = "GRS";
        GRS_data* ptr = new GRS_data;
        int err_code = parse_GRS_sentence(sentence, ptr);
        gps_data->data = ptr;
        return err_code;
    }
}


/**

    @brief Returns the NMEA code of an NMEA sentence.
    @param sentence The NMEA sentence string to extract the code from.
    @return The NMEA code as a string. If the sentence string doesn't start with '$', returns "NMEA_CODE_ERR". If the sentence string starts with '$' but doesn't contain a comma, returns an empty string.
*/
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

/**

    @brief Calculates the checksum of an NMEA sentence and compares it to the extracted checksum from the sentence. If they match, returns 0, otherwise returns -1.

    @param sentence a string representing an NMEA sentence

    @return an integer error code indicating whether the checksum is correct or not (-1 for incorrect, 0 for correct)
*/
int calculateChecksum(const std::string& sentence) {
    int checksum = 0;
    for (char c : sentence) 
    {
        if (c == '$') {
            checksum = 0;
        } else if (c == '*') {
            break;
        } else {
            checksum ^= c;
        }
    }

        std::stringstream ss;
        ss << std::hex << checksum; // convert decimal to hexadecimal
        string checksum_hex = ss.str();

        std::string extracted_checksum;
        size_t star_pos = sentence.find('*');
        if (star_pos != std::string::npos && star_pos < sentence.length() - 1)
        {
                extracted_checksum = sentence.substr(star_pos + 1); // extract the substring after the star character
        }
        else
        {
                return -1;
        }

        if (checksum_hex != extracted_checksum)
        {
                return -1;
        }
        else
        {
                return 0;
        }
}


// Returns true if the input string contains numeric data, false otherwise
bool is_numeric(const std::string& input) {
    if (input.empty()) {
        // Empty strings are not considered numeric
        return false;
    }

    // Loop through each character in the string
    for (char c : input) {
        if (!isdigit(c) && c != '.' && c != '-') {
            // If a non-numeric character is found, return false
            return false;
        }
    }

    // All characters are numeric, return true
    return true;
}

/**

    @brief Parse a GGA NMEA sentence and store the parsed data in the provided GGA_data structure.
    @param sentence The GGA NMEA sentence to be parsed.
    @param gga_data A pointer to a GGA_data structure to store the parsed data.
    @return int An error code indicating if there was an issue with the provided sentence.
*/

int parse_GGA_sentence(std::string sentence, GGA_data *gga_data) {
    // split the sentence into comma-separated fields
    std::istringstream ss(sentence);
    std::vector<std::string> fields;
    std::string field;
    while (std::getline(ss, field, ',')) {
        fields.push_back(field);
    }

    if (fields.size() == 16)  // No field is missing
    {
        // extract the fields and store them in the gga_data structure
        gga_data->time = fields[1];
        gga_data->latitude = fields[2];
        gga_data->lat_direction = fields[3][0];
        gga_data->longitude = fields[4];
        gga_data->lon_direction = fields[5][0];

        // handle exception
        if (!fields[6].empty() && is_numeric(fields[6]))
            gga_data->gps_quality = std::stoi(fields[6]);
        else
            gga_data->gps_quality = DEFAULT_VAL_NUM;

        if (!fields[7].empty() && is_numeric(fields[7]))
            gga_data->num_satellites = std::stoi(fields[7]);
        else
            gga_data->num_satellites = DEFAULT_VAL_NUM;

        if (!fields[8].empty() && is_numeric(fields[8]))
            gga_data->hdop = std::stod(fields[8]);
        else
            gga_data->hdop = DEFAULT_VAL_NUM;

        if (!fields[9].empty() && is_numeric(fields[9]))
            gga_data->altitude = std::stod(fields[9]);
        else
            gga_data->altitude = DEFAULT_VAL_NUM;

        gga_data->unit_of_altitude = fields[10][0];
        
        if (!fields[11].empty() && is_numeric(fields[11]))
            gga_data->geoidal_sep = std::stod(fields[11]);
        else
            gga_data->geoidal_sep = DEFAULT_VAL_NUM;

        gga_data->geoidal_unit = fields[12][0];
        
        if (!fields[13].empty() && is_numeric(fields[13])) {
            gga_data->age_diff_corr = std::stod(fields[13]);
        }
        else
            gga_data->age_diff_corr = DEFAULT_VAL_NUM;

        gga_data->diff_ref_station_id = fields[14];
    }
    else    // if some field(s) are missing
    {
        gga_data->time = "";
        gga_data->latitude = "";
        gga_data->lat_direction = '\0'; // store null terminator indicating this field is empty
        gga_data->longitude = "";
        gga_data->lon_direction = '\0';
        gga_data->gps_quality = DEFAULT_VAL_NUM;
        gga_data->num_satellites = DEFAULT_VAL_NUM;
        gga_data->hdop = DEFAULT_VAL_NUM;
        gga_data->altitude = DEFAULT_VAL_NUM;
        gga_data->unit_of_altitude = '\0';
        gga_data->geoidal_sep = DEFAULT_VAL_NUM;
        gga_data->geoidal_unit = '\0';
        gga_data->age_diff_corr = DEFAULT_VAL_NUM;
        gga_data->diff_ref_station_id = fields[14];
        return MISSING_PARAM_ERR;
    }

    return 0;
}

/**

    Parses the given GSA NMEA sentence and fills in the given GSA_data struct with the parsed values.
    @param sentence The GSA NMEA sentence to be parsed.
    @param gsa_data Pointer to a GSA_data struct where the parsed values will be stored.
    @return 0 if the sentence was successfully parsed, otherwise an error code:
    MISSING_PARAM_ERR if a required parameter is missing,

    INCORRECT_SENTENCE_CODE_ERR if the sentence does not match the expected format for a GSA sentence,
    
    CHECKSUM_ERR if the checksum of the sentence is incorrect.
*/

int parse_GSA_sentence(string sentence, GSA_data *gsa_data) {
    // check if the sentence is a valid GSA sentence
    if (sentence.substr(0, 6) != "$GPGSA") {
        return WRONG_SENTENCE_ID_ERR; // not a valid GSA sentence, so return
    }

    // split the sentence into comma-separated fields
    std::istringstream ss(sentence);
    std::vector<std::string> fields;
    std::string field;
    while (std::getline(ss, field, ',')) {
        fields.push_back(field);
    }

    if (fields.size() == 19)  // No field is missing
    {
        gsa_data->mode1 = fields[1][0];

        if (!fields[2].empty() && is_numeric(fields[2])) {
            gsa_data->mode2 = stoi(fields[2]);
        }
        else {
            gsa_data->mode2 = DEFAULT_VAL_NUM;
        }

        for (int i = 0; i < 12; i++) {
            if (!fields[i+3].empty() && is_numeric(fields[i+3])) {
                gsa_data->prn[i] = stoi(fields[i+3]);
            } else {
                gsa_data->prn[i] = DEFAULT_VAL_NUM;
            }
        }

        if (!fields[15].empty() && is_numeric(fields[15]))
            gsa_data->pdop = stod(fields[15]);
        else
            gsa_data->pdop = DEFAULT_VAL_NUM;

        if (!fields[16].empty() && is_numeric(fields[16]))
            gsa_data->hdop = stod(fields[16]);
        else
            gsa_data->hdop = DEFAULT_VAL_NUM;

        if (!fields[17].empty() && is_numeric(fields[17]))
            gsa_data->vdop = stod(fields[17]);
        else
            gsa_data->vdop = DEFAULT_VAL_NUM;
    }
    else
    {
        gsa_data->mode1 = '\0';
        gsa_data->mode2 = DEFAULT_VAL_NUM;
        for (int i = 0; i < 12; i++) {
            gsa_data->prn[i] = DEFAULT_VAL_NUM;
        }
        gsa_data->pdop = DEFAULT_VAL_NUM;
        gsa_data->hdop = DEFAULT_VAL_NUM;
        gsa_data->vdop = DEFAULT_VAL_NUM;  
        return MISSING_PARAM_ERR;      
    }
    return 0;
}

int parse_GSV_sentence(string sentence, GSV_data *gsv_data) {
    // check if the sentence is a valid GSV sentence
    if (sentence.substr(0, 6) != "$GPGSV") {
        return WRONG_SENTENCE_ID_ERR; // not a valid GSV sentence, so return
    }

    // split the sentence into comma-separated fields
    std::istringstream ss(sentence);
    std::vector<std::string> fields;
    std::string field;
    while (std::getline(ss, field, ',')) {
        fields.push_back(field);
    }

    if (fields.size() == 20)  // No field is missing
    {
        // extract the fields from the sentence
        if (!fields[1].empty() && is_numeric(fields[1]))
            gsv_data->num_msgs = std::stoi(fields[1]);
        else
            gsv_data->num_msgs = DEFAULT_VAL_NUM;

        if (!fields[2].empty() && is_numeric(fields[2]))
            gsv_data->msg_num = std::stoi(fields[2]);
        else
            gsv_data->msg_num = DEFAULT_VAL_NUM;

        if (!fields[3].empty() && is_numeric(fields[3]))
            gsv_data->num_sats = std::stoi(fields[3]);
        else
            gsv_data->num_sats = DEFAULT_VAL_NUM;

        // extract the satellite data from the sentence
        int num_sats = (fields.size() - 4) / 4;
        gsv_data->prn.resize(num_sats);
        gsv_data->elev.resize(num_sats);
        gsv_data->azim.resize(num_sats);
        gsv_data->snr.resize(num_sats);

        for (int i = 0; i < num_sats; i++) {
            int field_index = i * 4 + 4;
            if (!fields[field_index].empty() && is_numeric(fields[field_index]))
                gsv_data->prn[i] = std::stoi(fields[field_index]);
            else
                gsv_data->prn[i] = DEFAULT_VAL_NUM;

            if (!fields[field_index + 1].empty() && is_numeric(fields[field_index + 1]))
                gsv_data->elev[i] = std::stoi(fields[field_index + 1]);
            else
                gsv_data->elev[i] = DEFAULT_VAL_NUM;

            if (!fields[field_index + 2].empty() && is_numeric(fields[field_index + 2]))
                gsv_data->azim[i] = std::stoi(fields[field_index + 2]);
            else
                gsv_data->azim[i] = DEFAULT_VAL_NUM;

            if (!fields[field_index + 3].empty() && is_numeric(fields[field_index + 3]))
                gsv_data->snr[i] = std::stoi(fields[field_index + 3]);
            else
                gsv_data->snr[i] = DEFAULT_VAL_NUM;
        }
    }

    else 
    {
        gsv_data->num_msgs = DEFAULT_VAL_NUM;
        gsv_data->msg_num = DEFAULT_VAL_NUM;
        gsv_data->num_sats = DEFAULT_VAL_NUM;

        int num_sats = (fields.size() - 4) / 4;
        gsv_data->prn.resize(num_sats);
        gsv_data->elev.resize(num_sats);
        gsv_data->azim.resize(num_sats);
        gsv_data->snr.resize(num_sats);

        for (int i = 0; i < num_sats; i++) {
            int field_index = i * 4 + 4;
            gsv_data->prn[i] = DEFAULT_VAL_NUM;
            gsv_data->elev[i] = DEFAULT_VAL_NUM;
            gsv_data->azim[i] = DEFAULT_VAL_NUM;
            gsv_data->snr[i] = DEFAULT_VAL_NUM;
        }

        return MISSING_PARAM_ERR;
    }

    return 0;
}

int parse_RMC_sentence(string sentence, RMC_data *rmc_data)
{
    // check if the sentence is a valid RMC sentence
    if (sentence.substr(0, 6) != "$GPRMC") {
        return WRONG_SENTENCE_ID_ERR; // not a valid RMC sentence, so return
    }

    // split the sentence into comma-separated fields
    std::istringstream ss(sentence);
    std::vector<std::string> fields;
    std::string field;
    while (std::getline(ss, field, ',')) {
        fields.push_back(field);
    }
    
    
    if (fields.size() == 12)  // No field is missing
    {
        // extract all the parameters from nmea packet and store them
        // in their respective fields in rmc_data structure
        rmc_data->utc_time = fields[1];
        rmc_data->status = fields[2][0];
        rmc_data->latitude = fields[3];
        rmc_data->latitude_dir = fields[4][0];
        rmc_data->longitude = fields[5];
        rmc_data->longitude_dir = fields[6][0];

        if (!fields[7].empty() && is_numeric(fields[7]))
            rmc_data->speed_knots = stod(fields[7]);
        else
            rmc_data->speed_knots = DEFAULT_VAL_NUM;
    
        if (!fields[8].empty() && is_numeric(fields[8]))
            rmc_data->true_course = stod(fields[8]);
        else
            rmc_data->true_course = DEFAULT_VAL_NUM;

        rmc_data->date = fields[9];

        if (!fields[10].empty() && is_numeric(fields[10]))    
            rmc_data->variation = stod(fields[10]);
        else
            rmc_data->variation = DEFAULT_VAL_NUM;

        rmc_data->variation_dir = fields[11][0];
    }
    else
    {
        rmc_data->utc_time = "";
        rmc_data->status = '\0';
        rmc_data->latitude = "";
        rmc_data->latitude_dir = '\0';
        rmc_data->longitude = "";
        rmc_data->longitude_dir = '\0';
        rmc_data->speed_knots = DEFAULT_VAL_NUM;
        rmc_data->true_course = DEFAULT_VAL_NUM;
        rmc_data->date = "";
        rmc_data->variation = DEFAULT_VAL_NUM;
        rmc_data->variation_dir = '\0';
        return MISSING_PARAM_ERR;
    }
    return 0;
}


int parse_VTG_sentence(string sentence, VTG_data *vtg_data)
{
    // check if the sentence is a valid VTG sentence
    if (sentence.substr(0, 6) != "$GPVTG") {
        return WRONG_SENTENCE_ID_ERR; // not a valid VTG sentence, so return
    }

    // split the sentence into comma-separated fields
    std::istringstream ss(sentence);
    std::vector<std::string> fields;
    std::string field;
    while (std::getline(ss, field, ',')) {
        fields.push_back(field);
    }

    if (fields.size() == 10)  // No field is missing
    {
        // extract all the parameters from nmea packet and store them
        // in their respective fields in vtg_data structure
        if (!fields[1].empty() && is_numeric(fields[1]))
            vtg_data->true_track_degrees = stod(fields[1]);
        else
            vtg_data->true_track_degrees = DEFAULT_VAL_NUM;

        vtg_data->true_track_indicator = fields[2][0];
    
        if (!fields[3].empty() && is_numeric(fields[3]))
            vtg_data->magnetic_track_degrees = stod(fields[3]);
        else
            vtg_data->magnetic_track_degrees = DEFAULT_VAL_NUM;

        vtg_data->magnetic_track_indicator = fields[4][0];
    
        if (!fields[5].empty() && is_numeric(fields[5]))
            vtg_data->ground_speed_knots = stod(fields[5]);
        else
            vtg_data->ground_speed_knots = DEFAULT_VAL_NUM;

        vtg_data->ground_speed_knots_indicator = fields[6][0];
    
        if (!fields[7].empty() && is_numeric(fields[7]))
            vtg_data->ground_speed_kph = stod(fields[7]);
        else
            vtg_data->ground_speed_kph = DEFAULT_VAL_NUM;
    
        vtg_data->ground_speed_kph_indicator = fields[8][0];
        vtg_data->mode = fields[9][0];
    }    
    else 
    {
        vtg_data->true_track_degrees = DEFAULT_VAL_NUM;
        vtg_data->true_track_indicator = '\0';
        vtg_data->magnetic_track_degrees = DEFAULT_VAL_NUM;
        vtg_data->magnetic_track_indicator = '\0';
        vtg_data->ground_speed_knots = DEFAULT_VAL_NUM;
        vtg_data->ground_speed_knots_indicator = '\0';
        vtg_data->ground_speed_kph = DEFAULT_VAL_NUM;
        vtg_data->ground_speed_kph_indicator = '\0';
        vtg_data->mode = '\0';
        return MISSING_PARAM_ERR;
    }

    return 0;
}

int parse_GLL_sentence(string sentence, GLL_data *gll_data)
{
    // check if the sentence is a valid GLL sentence
    if (sentence.substr(0, 6) != "$GPGLL") {
        return WRONG_SENTENCE_ID_ERR; // not a valid GLL sentence, so return
    }

    // split the sentence into comma-separated fields
    std::istringstream ss(sentence);
    std::vector<std::string> fields;
    std::string field;
    while (std::getline(ss, field, ',')) {
        fields.push_back(field);
    }

    if (fields.size() == 8)  // No field is missing
    {
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
    else
    {
        gll_data->latitude = "";
        gll_data->latitude_direction = '\0';
        gll_data->longitude = "";
        gll_data->longitude_direction = '\0';
        gll_data->utc_time = "";
        gll_data->status = '\0';
        gll_data->mode = '\0';
        return MISSING_PARAM_ERR;
    }

    return 0;
}



int parse_ZDA_sentence(string sentence, ZDA_data *zda_data)
{
    // check if the sentence is a valid ZDA sentence
    if (sentence.substr(0, 6) != "$GPZDA") {
        return WRONG_SENTENCE_ID_ERR; // not a valid ZDA sentence, so return
    }

    // split the sentence into comma-separated fields
    std::istringstream ss(sentence);
    std::vector<std::string> fields;
    std::string field;
    while (std::getline(ss, field, ',')) {
        fields.push_back(field);
    }

    if (fields.size() == 7)  // No field is missing
    {
        // extract all the parameters from nmea packet and store them
        // in their respective fields in zda_data structure
        if (!fields[1].substr(0,2).empty() && is_numeric(fields[1].substr(0,2)))
            zda_data->hour = std::stoi(fields[1].substr(0, 2));
        else
            zda_data->hour = DEFAULT_VAL_NUM;

        if (!fields[1].substr(2, 2).empty() && is_numeric(fields[1].substr(2, 2)))
            zda_data->minute = std::stoi(fields[1].substr(2, 2));
        else
            zda_data->minute = DEFAULT_VAL_NUM;

        if (!fields[1].substr(4, 2).empty() && is_numeric(fields[1].substr(4, 2)))
            zda_data->second = std::stoi(fields[1].substr(4, 2));
        else
            zda_data->second = DEFAULT_VAL_NUM;

        if (!fields[1].substr(7, 3).empty() && is_numeric(fields[1].substr(7, 3)))
            zda_data->millisecond = std::stoi(fields[1].substr(7, 3));
        else
            zda_data->millisecond = DEFAULT_VAL_NUM;

        if (!fields[2].empty() && is_numeric(fields[2]))
            zda_data->day = std::stoi(fields[2]);
        else
            zda_data->day = DEFAULT_VAL_NUM;


        if (!fields[3].empty() && is_numeric(fields[3]))
            zda_data->month = std::stoi(fields[3]);
        else
            zda_data->month = DEFAULT_VAL_NUM;

        if (!fields[4].empty() && is_numeric(fields[4]))
            zda_data->year = std::stoi(fields[4]);
        else
            zda_data->year = DEFAULT_VAL_NUM;

        if (!fields[5].empty() && is_numeric(fields[5]))
            zda_data->local_hour_offset = std::stoi(fields[5]);
        else
            zda_data->local_hour_offset = DEFAULT_VAL_NUM;

        if (!fields[6].empty() && is_numeric(fields[6]))
            zda_data->local_minute_offset = std::stoi(fields[6]);        
        else
            zda_data->local_minute_offset = DEFAULT_VAL_NUM;
    }
    else
    {
        zda_data->hour = DEFAULT_VAL_NUM;
        zda_data->minute = DEFAULT_VAL_NUM;
        zda_data->second = DEFAULT_VAL_NUM;
        zda_data->millisecond = DEFAULT_VAL_NUM;
        zda_data->day = DEFAULT_VAL_NUM;
        zda_data->month = DEFAULT_VAL_NUM;
        zda_data->year = DEFAULT_VAL_NUM;
        zda_data->local_hour_offset = DEFAULT_VAL_NUM;
        zda_data->local_minute_offset = DEFAULT_VAL_NUM;
        return MISSING_PARAM_ERR;
    }

    return 0;
}




int parse_GST_sentence(string sentence, GST_data *gst_data)
{
    // check if the sentence is a valid GST sentence
    if (sentence.substr(0, 6) != "$GPGST") {
        return WRONG_SENTENCE_ID_ERR; // not a valid GST sentence, so return
    }

    // split the sentence into comma-separated fields
    std::istringstream ss(sentence);
    std::vector<std::string> fields;
    std::string field;
    while (std::getline(ss, field, ',')) {
        fields.push_back(field);
    }

    if (fields.size() == 9)  // No field is missing
    {    
        // extract all the parameters from nmea sentence and store them
        // in their respective fields in gst_data structure
        gst_data->utc_time = fields[1];

        if (!fields[2].empty() && is_numeric(fields[2]))
            gst_data->rms_deviation = std::stod(fields[2]);
        else
            gst_data->rms_deviation = DEFAULT_VAL_NUM;

        if (!fields[3].empty() && is_numeric(fields[3]))
            gst_data->semi_major_err = std::stod(fields[3]);
        else
            gst_data->semi_major_err = DEFAULT_VAL_NUM;

        if (!fields[4].empty() && is_numeric(fields[4]))      
           gst_data->semi_minor_err = std::stod(fields[4]);
        else
            gst_data->semi_minor_err = DEFAULT_VAL_NUM;

        if (!fields[5].empty() && is_numeric(fields[5]))
            gst_data->orientation_err = std::stod(fields[5]);
        else
            gst_data->orientation_err = DEFAULT_VAL_NUM;

        if (!fields[6].empty() && is_numeric(fields[6]))
            gst_data->lat_err = std::stod(fields[6]);
        else
            gst_data->lat_err = DEFAULT_VAL_NUM;
        
        if (!fields[7].empty() && is_numeric(fields[7]))
            gst_data->lon_err = std::stod(fields[7]);
        else
            gst_data->lon_err = DEFAULT_VAL_NUM;

        if (!fields[8].empty())
        {
            // Find the position of the '*' character
            std::size_t pos = fields[8].find('*');

            // Extract the substring before the '*' character
            std::string numStr = fields[8].substr(0, pos);

            // Convert the substring to a double
            gst_data->alt_err = std::stod(numStr);
        }
        else
            gst_data->alt_err = DEFAULT_VAL_NUM;
    }
    else
    {
        gst_data->utc_time = "";
        gst_data->rms_deviation = DEFAULT_VAL_NUM;
        gst_data->semi_major_err = DEFAULT_VAL_NUM;
        gst_data->semi_minor_err = DEFAULT_VAL_NUM;
        gst_data->orientation_err = DEFAULT_VAL_NUM;
        gst_data->lat_err = DEFAULT_VAL_NUM;
        gst_data->lon_err = DEFAULT_VAL_NUM;
        gst_data->alt_err = DEFAULT_VAL_NUM;
        return MISSING_PARAM_ERR;
    }

    return 0;
}

int parse_HDT_sentence(string sentence, HDT_data *hdt_data)
{
    // check if the sentence is a valid HDT sentence
    if (sentence.substr(0, 6) != "$GPHDT") {
        return WRONG_SENTENCE_ID_ERR; // not a valid HDT sentence, so return
    }

    // split the sentence into comma-separated fields
    std::istringstream ss(sentence);
    std::vector<std::string> fields;
    std::string field;
    while (std::getline(ss, field, ',')) {
        fields.push_back(field);
    }

    if (fields.size() == 3)  // No field is missing
    {
        // extract the parameters from nmea sentence and store them
        // in their respective fields in hdt_data structure
        if (!fields[1].empty() && is_numeric(fields[1]))
            hdt_data->heading = std::stof(fields[1]);
        else
            hdt_data->heading = DEFAULT_VAL_NUM;
    }
    else
    {
        hdt_data->heading = DEFAULT_VAL_NUM;
        return MISSING_PARAM_ERR;
    }

    return 0;
}

int parse_GRS_sentence(string sentence, GRS_data *grs_data)
{
    // check if the sentence is a valid GRS sentence
    if (sentence.substr(0, 6) != "$GPGRS") {
        return WRONG_SENTENCE_ID_ERR; // not a valid GRS sentence, so return
    }

    // split the sentence into comma-separated fields
    std::istringstream ss(sentence);
    std::vector<std::string> fields;
    std::string field;
    while (std::getline(ss, field, ',')) {
        fields.push_back(field);
    }


    if (fields.size() == 16)  // No field is missing
    {
        // extract all the parameters from nmea sentence and store them
        // in their respective fields in gst_data structure
        if (!fields[1].empty() && is_numeric(fields[1]))
            grs_data->utc_time = fields[1];
        else
            grs_data->utc_time = "";

        if (!fields[2].empty() && is_numeric(fields[2]))
            grs_data->mode = std::stoi(fields[2]);
        else
            grs_data->mode = 0;

        if (!fields[3].empty() && is_numeric(fields[3]))
            grs_data->residual1 = std::stof(fields[3]);
        else
            grs_data->residual1 = 0;
        
        if (!fields[4].empty() && is_numeric(fields[4]))
            grs_data->residual2 = std::stof(fields[4]);
        else
            grs_data->residual2 = 0;

        if (!fields[5].empty() && is_numeric(fields[5]))
            grs_data->residual3 = std::stof(fields[5]);
        else
            grs_data->residual3 = 0;

        if (!fields[6].empty() && is_numeric(fields[6]))
            grs_data->residual4 = std::stof(fields[6]);
        else
            grs_data->residual4 = 0;

        if (!fields[7].empty() && is_numeric(fields[7]))
            grs_data->residual5 = std::stof(fields[7]);
        else
            grs_data->residual5 = 0;

        if (!fields[8].empty() && is_numeric(fields[8]))
            grs_data->residual6 = std::stof(fields[8]);
        else
            grs_data->residual6 = 0;

        if (!fields[9].empty() && is_numeric(fields[9]))
            grs_data->residual7 = std::stof(fields[9]);
        else
            grs_data->residual7 = 0;

        if (!fields[10].empty() && is_numeric(fields[10]))
            grs_data->residual8 = std::stof(fields[10]);
        else
            grs_data->residual8 = 0;

        if (!fields[11].empty() && is_numeric(fields[11]))
            grs_data->residual9 = std::stof(fields[11]);
        else
            grs_data->residual9 = 0;

        if (!fields[12].empty() && is_numeric(fields[12]))
            grs_data->residual10 = std::stof(fields[12]);
        else
            grs_data->residual10 = 0;

        if (!fields[13].empty() && is_numeric(fields[13]))
            grs_data->residual11 = std::stof(fields[13]);
        else
            grs_data->residual11 = 0;

        if (!fields[14].empty() && is_numeric(fields[14]))
            grs_data->residual12 = std::stof(fields[14]);
        else
            grs_data->residual12 = 0;
    }
    else
    {
        grs_data->utc_time = "";
        grs_data->mode = DEFAULT_VAL_NUM;
        grs_data->residual1 = DEFAULT_VAL_NUM;
        grs_data->residual2 = DEFAULT_VAL_NUM;
        grs_data->residual3 = DEFAULT_VAL_NUM;
        grs_data->residual4 = DEFAULT_VAL_NUM;
        grs_data->residual5 = DEFAULT_VAL_NUM;
        grs_data->residual6 = DEFAULT_VAL_NUM;
        grs_data->residual7 = DEFAULT_VAL_NUM;
        grs_data->residual8 = DEFAULT_VAL_NUM;
        grs_data->residual9 = DEFAULT_VAL_NUM;
        grs_data->residual10 = DEFAULT_VAL_NUM;
        grs_data->residual11 = DEFAULT_VAL_NUM;
        grs_data->residual12 = DEFAULT_VAL_NUM;    

        return MISSING_PARAM_ERR;    
    }

    return 0;
}