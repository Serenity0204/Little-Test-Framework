#ifndef TEST_TEMPLATE_H
#define TEST_TEMPLATE_H

#pragma once

#include "../little_test_framework/little_test_framework.h"
#include "../test_case/test_case.h"
#include "../test_suite/test_suite.h"
#include <vector>

namespace LTF
{
    namespace LTFDebug
    {
        const bool debug = false;
    };

// the macro for commenting
#define LTF_COMMENT(message) LTF::Singleton<LTF::LittleTestFramework>::instance().comment(__FUNCTION__, message);

// time macro for timing in ns
#define LTF_TIME(time_ns) LTF::Singleton<LTF::LittleTestFramework>::instance().time(__FUNCTION__, time_ns);

// TEST SUITE Associate to test function
// if suite does not exist, create one and add the function into that suite and add it to the manager through singleton instance
// else get the existed suite, add the function, and then add it back to the manager through singleton instance
#define LTF_TEST(suite_name, test_case)                                                                                               \
                                                                                                                                      \
    struct TestRegistration_##suite_name##_##test_case                                                                                \
    {                                                                                                                                 \
        TestRegistration_##suite_name##_##test_case()                                                                                 \
        {                                                                                                                             \
            if (LTF::Singleton<LTF::LittleTestFramework>::instance().suite_exists(#suite_name))                                       \
            {                                                                                                                         \
                LTF::TestCase test = LTF::TestCase(#test_case, test_case);                                                            \
                LTF::TestSuite suite = LTF::Singleton<LTF::LittleTestFramework>::instance().get_suite(#suite_name).add(test);         \
                LTF::Singleton<LTF::LittleTestFramework>::instance().add(suite);                                                      \
                if (LTF::LTFDebug::debug) std::cout << #suite_name << " exists and created " << #test_case << std::endl;              \
                return;                                                                                                               \
            }                                                                                                                         \
                                                                                                                                      \
            LTF::TestSuite suite(#suite_name);                                                                                        \
            suite.add(LTF::TestCase(#test_case, test_case));                                                                          \
            LTF::Singleton<LTF::LittleTestFramework>::instance().add(suite);                                                          \
            if (LTF::LTFDebug::debug) std::cout << #suite_name << " does not exist and created self and " << #test_case << std::endl; \
        }                                                                                                                             \
    } g_TestRegistration_##suite_name##_##test_case;

    // Run All
    inline void LTF_RUN_ALL(bool debug = false, MODE mode = LTF::CONSOLE, const std::string& path = "")
    {
        LTF::Singleton<LTF::LittleTestFramework>::instance().run_all(debug, mode, path);
        LTF::Singleton<LTF::LittleTestFramework>::instance().clean();
    }

    // Ignore test suites
    inline void LTF_IGNORE_SUITES(const std::vector<std::string>& ignored_suites)
    {
        LTF::Singleton<LTF::LittleTestFramework>::instance().ignore_suites(ignored_suites);
    }

    // Ignore test cases by test suites
    inline void LTF_IGNORE_TEST_CASES(const std::string& suite_name, const std::vector<std::string>& ignored_tests)
    {
        LTF::Singleton<LTF::LittleTestFramework>::instance().ignore_tests(suite_name, ignored_tests);
    }
};

#endif // TEST_TEMPLATE_H
