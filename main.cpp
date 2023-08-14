#include "includes/LTF.h"
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
    return LTF::LTFStatus(LTF::SUCCESS, __LINE__);
}

inline LTF::LTFStatus test_utils_main2(bool debug = false)
{
    return LTF::LTFStatus(LTF::FAIL, __LINE__);
}

inline LTF::LTFStatus test_utils_main3(bool debug = false)
{
    if (debug)
    {
        cout << "HI" << endl;
    }
    int a = 1 + 1;
    if (a == 2) return LTF::LTFStatus(LTF::SUCCESS, __LINE__);
    return LTF::LTFStatus(LTF::FAIL, __LINE__);
}

inline LTF::LTFStatus test_utils_main4(bool debug = false)
{
    if (debug)
    {
        cout << "should be 120" << endl;
    }
    long long f = factorial(5);
    if (f == 120) return LTF::LTFStatus(LTF::SUCCESS, __LINE__);
    return LTF::LTFStatus(LTF::FAIL, __LINE__);
}

inline LTF::LTFStatus test_ignore1(bool debug = false)
{
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

const bool debug = false;

int main()
{
    // ignore test cases by LTF::LTF_IGNORE_TEST_CASES(<suite name as string>, {<test 1 as string>, <test 2 as string>, ...})
    LTF::LTF_IGNORE_TEST_CASES("SUITE3", {"test_ignore2"});

    // ignore the entire suite by LTF::LTF_IGNORE_SUITES({<suite name 1 as tring>, <suite name 2 as string>, ...});
    // LTF::LTF_IGNORE_SUITES({"SUITE3", "SUITE2"});
    LTF::LTF_RUN_ALL(debug);
    return 0;
}
