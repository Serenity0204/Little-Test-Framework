#ifndef TEST_TEMPLATE_H
#define TEST_TEMPLATE_H

#pragma once

#include "../little_test_framework/little_test_framework.h"
#include "../test_case/test_case.h"
#include "../test_suite/test_suite.h"

namespace LTF
{
    namespace LTFDebug
    {
        const bool debug = false;
    };

// TEST SUITE Associate to test function
// if suite does not exist, create one and add the function into that suite and add it to the static manager
// else get the existed suite, add the function, and then add it back to the static manager
#define LTF_TEST(suite_name, test_case_name, test_function)                                                                                    \
                                                                                                                                               \
    struct TestRegistration_##suite_name##_##test_case_name                                                                                    \
    {                                                                                                                                          \
        TestRegistration_##suite_name##_##test_case_name()                                                                                     \
        {                                                                                                                                      \
            if (LTF::LittleTestFramework::suite_exists(#suite_name))                                                                           \
            {                                                                                                                                  \
                LTF::TestSuite suite = LTF::LittleTestFramework::get_suite(#suite_name).add(LTF::TestCase(#test_case_name, test_function));    \
                LTF::LittleTestFramework::add(suite);                                                                                          \
                if (LTF::LTFDebug::debug) std::cout << #suite_name << " exists and created " << #test_case_name << std::endl;                  \
            }                                                                                                                                  \
            else                                                                                                                               \
            {                                                                                                                                  \
                LTF::TestSuite suite(#suite_name);                                                                                             \
                suite.add(LTF::TestCase(#test_case_name, test_function));                                                                      \
                LTF::LittleTestFramework::add(suite);                                                                                          \
                if (LTF::LTFDebug::debug) std::cout << #suite_name << " does not exist and created self and " << #test_case_name << std::endl; \
            }                                                                                                                                  \
        }                                                                                                                                      \
    } g_TestRegistration_##suite_name##_##test_case_name;

    // Run All
    inline void LTF_RUN_ALL(bool debug = false)
    {
        LTF::LittleTestFramework::run_all(debug);
        LTF::LittleTestFramework::clean();
    }

};

#endif // TEST_TEMPLATE_H
