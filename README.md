
# Little Test Framework (LTF)
Project Description goes here

* operation 1
* operation 2


## Design
Can be found in https://github.com/Serenity0204/Little-Test-Framework/blob/master/design.txt


## Features
- feature 1
- feature 2



## Usage
```
#include <LTF.h>
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
// test utility functions implement your logic here
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


// test registration, format as (<Test Suite Name>, <Test Case Name>, <Test Case Utility Function>)
LTF_TEST(SUITE1, test1, test_utils_main1);

LTF_TEST(SUITE2, test3, test_utils_main3);

LTF_TEST(SUITE1, test2, test_utils_main2);

LTF_TEST(SUITE1, test4, test_utils_main4);

LTF_TEST(SUITE2, test1, test_utils_main4);

const bool debug = true;

int main()
{

    LTF::LTF_RUN_ALL(debug);
    return 0;
}
```


