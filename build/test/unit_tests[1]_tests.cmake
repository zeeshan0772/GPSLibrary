add_test( ParseGLLSentenceTest.ValidGLL [==[/home/zeeshan/Desktop/GPS Library/build/bin/unit_tests]==] [==[--gtest_filter=ParseGLLSentenceTest.ValidGLL]==] --gtest_also_run_disabled_tests)
set_tests_properties( ParseGLLSentenceTest.ValidGLL PROPERTIES WORKING_DIRECTORY [==[/home/zeeshan/Desktop/GPS Library/build/test]==] SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==] LABELS unit)
set( unit_tests_TESTS ParseGLLSentenceTest.ValidGLL)
