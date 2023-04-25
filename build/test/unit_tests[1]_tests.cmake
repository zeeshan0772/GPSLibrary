add_test( GGA_parser.Valid_data [==[/home/zeeshan/Desktop/GPS Library/build/bin/unit_tests]==] [==[--gtest_filter=GGA_parser.Valid_data]==] --gtest_also_run_disabled_tests)
set_tests_properties( GGA_parser.Valid_data PROPERTIES WORKING_DIRECTORY [==[/home/zeeshan/Desktop/GPS Library/build/test]==] SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==] LABELS unit)
add_test( GGA_parser.data_with_missing_params [==[/home/zeeshan/Desktop/GPS Library/build/bin/unit_tests]==] [==[--gtest_filter=GGA_parser.data_with_missing_params]==] --gtest_also_run_disabled_tests)
set_tests_properties( GGA_parser.data_with_missing_params PROPERTIES WORKING_DIRECTORY [==[/home/zeeshan/Desktop/GPS Library/build/test]==] SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==] LABELS unit)
add_test( GGA_parser.data_with_wrong_strings [==[/home/zeeshan/Desktop/GPS Library/build/bin/unit_tests]==] [==[--gtest_filter=GGA_parser.data_with_wrong_strings]==] --gtest_also_run_disabled_tests)
set_tests_properties( GGA_parser.data_with_wrong_strings PROPERTIES WORKING_DIRECTORY [==[/home/zeeshan/Desktop/GPS Library/build/test]==] SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==] LABELS unit)
set( unit_tests_TESTS GGA_parser.Valid_data GGA_parser.data_with_missing_params GGA_parser.data_with_wrong_strings)
