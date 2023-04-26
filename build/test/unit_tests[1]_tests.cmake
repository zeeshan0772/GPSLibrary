add_test( GSTParsingTest.ValidSentence [==[/home/zeeshan/Desktop/GPS Library/build/bin/unit_tests]==] [==[--gtest_filter=GSTParsingTest.ValidSentence]==] --gtest_also_run_disabled_tests)
set_tests_properties( GSTParsingTest.ValidSentence PROPERTIES WORKING_DIRECTORY [==[/home/zeeshan/Desktop/GPS Library/build/test]==] SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==] LABELS unit)
set( unit_tests_TESTS GSTParsingTest.ValidSentence)
