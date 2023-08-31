#include "includes/LTF.h"
// import your files here

#include <iostream>
using namespace std;

unsigned long long factorial(int n)
{
    if (n == 0 || n == 1)
    {
        return 1;
    }
    else
    {
        return n * factorial(n - 1);
    }
}

// utility functions like
// inline LTF::LTFStatus <your utility function name>(bool debug = false)
inline LTF::LTFStatus test_utils_main1(bool debug = false)
{
    if (debug)
    {
        LTF_COMMENT("hello this is a message 1");
        LTF_COMMENT("hello this is a message 2");
    }
    LTF_DEBUG("debug message");

    return LTF::LTFStatus(LTF::SUCCESS, __LINE__);
}

inline LTF::LTFStatus test_utils_main2(bool debug = false)
{
    LTF_TIME(180);
    double result = 0.0;
    for (int i = 0; i < 100000000; ++i) result += (true ? 1.0 : -1.0) * i;

    LTF_INFO("info message");

    return LTF::LTFStatus(LTF::FAIL, __LINE__);
}

inline LTF::LTFStatus test_utils_main3(bool debug = false)
{
    if (debug) LTF_COMMENT("HI");

    int a = 1 + 1;

    LTF_WARNING("warning message");
    if (a == 2) return LTF::LTFStatus(LTF::SUCCESS, __LINE__);
    return LTF::LTFStatus(LTF::FAIL, __LINE__);
}

inline LTF::LTFStatus test_utils_main4(bool debug = false)
{
    if (debug) LTF_COMMENT("should be 120");

    long long f = factorial(5);

    LTF_ERROR("error message");

    if (f == 120) return LTF::LTFStatus(LTF::SUCCESS, __LINE__);
    return LTF::LTFStatus(LTF::FAIL, __LINE__);
}

inline LTF::LTFStatus test_ignore1(bool debug = false)
{
    LTF_FATAL("fatal message");
    return LTF::LTFStatus(LTF::SUCCESS, __LINE__);
}

inline LTF::LTFStatus test_ignore2(bool debug = false)
{
    return LTF::LTFStatus(LTF::FAIL, __LINE__);
}

// test registration, format as (<Test Suite Name>, <Test Case Utility Function>)
LTF_TEST(SUITE1, test_utils_main1);

LTF_TEST(SUITE1, test_utils_main2);

LTF_TEST(SUITE1, test_utils_main4);

LTF_TEST(SUITE2, test_utils_main3);

LTF_TEST(SUITE2, test_utils_main4);

LTF_TEST(SUITE3, test_ignore1);

LTF_TEST(SUITE3, test_ignore2);

LTF_TEST(SUITE_HELLO, test_ignore2);

const bool debug = true;

int main()
{
    // logging init
    LTF_LOG_INIT("../../log_main.txt");
    LTF_LOG_LEVEL(LTF::Logger::Level::WARNING);

    // ignore test cases by LTF::LTF_IGNORE_TEST_CASES(<suite name as string>, {<test 1 as string>, <test 2 as string>, ...})
    LTF::LTF_IGNORE_TEST_CASES("SUITE3", {"test_ignore2"});

    // ignore the entire suite by LTF::LTF_IGNORE_SUITES({<suite name 1 as tring>, <suite name 2 as string>, ...});
    // LTF::LTF_IGNORE_SUITES({"SUITE3", "SUITE2"});

    // run all and output to file
    // LTF::LTF_RUN_ALL(debug, LTF::MODE::FILE, "../../output.txt");
    // run all and output to console
    LTF::LTF_RUN_ALL(debug, LTF::MODE::CONSOLE);
    LTF_DEBUG("debug message from main");
    return 0;
}
