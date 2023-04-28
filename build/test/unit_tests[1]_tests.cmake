add_test( parse_nmea_sentence.Checksum_error [==[/home/zeeshan/Desktop/GPS Library/build/bin/unit_tests]==] [==[--gtest_filter=parse_nmea_sentence.Checksum_error]==] --gtest_also_run_disabled_tests)
set_tests_properties( parse_nmea_sentence.Checksum_error PROPERTIES WORKING_DIRECTORY [==[/home/zeeshan/Desktop/GPS Library/build/test]==] SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==] LABELS unit)
set( unit_tests_TESTS parse_nmea_sentence.Checksum_error)
