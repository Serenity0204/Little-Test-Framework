
# Little Test Framework (LTF)
Little Test Framework(LTF), is a hassle-free C++ unit testing. Designed to make your testing experience efficient and effective, this framework provides a minimalistic approach while maintaining powerful testing capabilities.


## Operations
See the Usage for more comprehensive examples.
* Make Your Ttility Functions Like 
```
inline LTF::LTFStatus <your utility function name>(bool debug = false)
// return value option
// LTF::LTFStatus(LTF::SUCCESS, __LINE__) // for success
// LTF::LTFStatus(LTF::FAIL, __LINE__) // for fail
// the __LINE__ is for when debug == true
```
* Register Your Test Case Like
```
LTF_TEST(<Test Suite Name>, <Related Utility Function>);
```
* Run All The Registered Tests By
```
// for debug flag
const bool debug = false;

int main()
{
    // run all and output to the file
    // LTF::LTF_RUN_ALL(debug, LTF::MODE::FILE, "../../output.txt");
    // run all and output to the console
    LTF::LTF_RUN_ALL(debug, LTF::MODE::CONSOLE);
    return 0;
}
```
* Ignore Test Suites By
```
LTF::LTF_IGNORE_TEST_CASES(<suite name as string>, {<test 1 as string>, <test 2 as string>, ...})
```

* Ignore Test Cases Of A Test Suite By
```
LTF::LTF_IGNORE_SUITES({<suite name 1 as tring>, <suite name 2 as string>, ...});
```



## Demo
- Debug == False
```

LTF RUNNING ALL 4 TEST SUITES:
----------------------------------------------------------------------

1.SUITE1:
         RUNNING 3 TESTS FROM SUITE1
----------------------------------------------------------------------
         RUNNING...
                  1.TEST NAME:test_utils_main1 ----> [SUCCESS]
         RUNNING...
                  2.TEST NAME:test_utils_main2 ----> [FAIL]
         RUNNING...
                  3.TEST NAME:test_utils_main4 ----> [SUCCESS]

 TOTAL:
         (2) TESTS SUCCESS
         (1) TEST FAIL

----------------------------------------------------------------------
2.SUITE2:
         RUNNING 2 TESTS FROM SUITE2
----------------------------------------------------------------------
         RUNNING...
                  1.TEST NAME:test_utils_main3 ----> [SUCCESS]
         RUNNING...
                  2.TEST NAME:test_utils_main4 ----> [SUCCESS]

 TOTAL:
         (2) TESTS SUCCESS

----------------------------------------------------------------------
3.SUITE3:
         RUNNING 1 TEST FROM SUITE3
----------------------------------------------------------------------
         RUNNING...
                  1.TEST NAME:test_ignore1 ----> [SUCCESS]

 TOTAL:
         (1) TEST SUCCESS

----------------------------------------------------------------------
4.SUITE_HELLO:
         RUNNING 1 TEST FROM SUITE_HELLO
----------------------------------------------------------------------
         RUNNING...
                  1.TEST NAME:test_ignore2 ----> [FAIL]

 TOTAL:
         (1) TEST FAIL

----------------------------------------------------------------------

SUMMARY:
         (5) TOTAL TESTS SUCCESS
         (2) TOTAL TESTS FAIL


--------------------------THE END OF TEST-----------------------------


```
- Debug == True
```

LTF RUNNING ALL 4 TEST SUITES:
----------------------------------------------------------------------  

1.SUITE1:
         RUNNING 3 TESTS FROM SUITE1
----------------------------------------------------------------------  
should be 120
         RUNNING...
                  1.TEST NAME:test_utils_main1 ----> [SUCCESS]
         RUNNING...
                  2.TEST NAME:test_utils_main2 ----> [FAIL] AT LINE [26]
         RUNNING...
                  3.TEST NAME:test_utils_main4 ----> [SUCCESS]

 TOTAL:
         (2) TESTS SUCCESS
         (1) TEST FAIL

----------------------------------------------------------------------  
2.SUITE2:
         RUNNING 2 TESTS FROM SUITE2
----------------------------------------------------------------------  
HI
should be 120
         RUNNING...
                  1.TEST NAME:test_utils_main3 ----> [SUCCESS]
         RUNNING...
                  2.TEST NAME:test_utils_main4 ----> [SUCCESS]

 TOTAL:
         (2) TESTS SUCCESS

----------------------------------------------------------------------  
3.SUITE3:
         RUNNING 1 TEST FROM SUITE3
----------------------------------------------------------------------  
         RUNNING...
                  1.TEST NAME:test_ignore1 ----> [SUCCESS]

 TOTAL:
         (1) TEST SUCCESS

----------------------------------------------------------------------
4.SUITE_HELLO:
         RUNNING 1 TEST FROM SUITE_HELLO
----------------------------------------------------------------------
         RUNNING...
                  1.TEST NAME:test_ignore2 ----> [FAIL] AT LINE [58]

 TOTAL:
         (1) TEST FAIL

----------------------------------------------------------------------

SUMMARY:
         (5) TOTAL TESTS SUCCESS
         (2) TOTAL TESTS FAIL


--------------------------THE END OF TEST-----------------------------

```



## Features
- 🧪 Simplicity: We understand the importance of clean and straightforward testing. "Little Test Framework" lets you define and execute tests with just a few lines of code, without overwhelming you with unnecessary complexities.

- 🛠️ Macro-powered: Harness the power of macros to effortlessly define and manage your test cases. Using the LTF_TEST macro, you can easily create, organize, and run your tests, ensuring a smooth development process.

- 📜 Test Discovery: The framework automates test discovery, saving you time and effort. It automatically locates and runs all registered tests, providing a comprehensive overview of your code's health.

- 🚀 Efficient Execution: "Little Test Framework" optimizes the execution of your test suite, enabling rapid feedback loops during development. Spend less time waiting for tests to run and more time coding.

- 📊 Clear Reporting: With minimalistic design principles in mind, the framework provides concise and informative test execution reports. Identify issues quickly and make informed decisions based on test results.




## Installation Using CMake
```
cmake_minimum_required(VERSION 3.12)
project(YourProjectName) # Replace "YourProjectName" with the actual name of your project

# Set CMP0002 policy to NEW to suppress the warning
cmake_policy(SET CMP0002 NEW)

if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
endif()

## Fetch the content
include(FetchContent)
FetchContent_Declare(
  LTF
  GIT_REPOSITORY https://github.com/Serenity0204/Little-Test-Framework.git
)
FetchContent_MakeAvailable(LTF)

## Linking
ADD_EXECUTABLE(main main.cpp)
TARGET_LINK_LIBRARIES(main PRIVATE LTF)
```



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

    // run all and output to file
    // LTF::LTF_RUN_ALL(debug, LTF::MODE::FILE, "../../output.txt");
    // run all and output to console
    LTF::LTF_RUN_ALL(debug, LTF::MODE::CONSOLE);
    return 0;
}


```


## Design
Can be found in https://github.com/Serenity0204/Little-Test-Framework/blob/master/design.txt




