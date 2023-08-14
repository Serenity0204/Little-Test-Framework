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
    if (f != 5) return LTF::LTFStatus(LTF::SUCCESS, __LINE__);
    return LTF::LTFStatus(LTF::FAIL, __LINE__);
}

LTF_TEST(SUITE1, test1, test_utils_main1);

LTF_TEST(SUITE2, test3, test_utils_main3);

LTF_TEST(SUITE1, test2, test_utils_main2);

LTF_TEST(SUITE1, test4, test_utils_main4);

LTF_TEST(SUITE2, test1, test_utils_main4);

int main()
{
    bool debug = true;
    auto m = LTF::LittleTestFramework.get();
    for (auto& x : m)
    {
        cout << "-----------------------------------" << endl;
        cout << x.first << endl;
        // x.second.print();
        auto pass = x.second.run_all(debug);
        for (auto flag : pass)
        {
            cout << flag.first << ":";
            if (flag.second.code == LTF::SUCCESS) cout << "success";
            if (flag.second.code == LTF::FAIL) cout << "fail";
            if (debug)
                cout << " at line:" << flag.second.line << endl;
            else
                cout << endl;
        }
        cout << "-----------------------------------" << endl;
    }
    return 0;
}
