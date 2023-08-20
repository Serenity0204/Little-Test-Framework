
# Little Test Framework (LTF)
Little Test Framework(LTF), is a hassle-free C++ unit testing framework. Designed to make your testing experience efficient and effective, this framework provides a minimalistic approach while maintaining powerful testing capabilities.


## Operations
See the Example Usage for more comprehensive examples.
* Make Your Utility Functions Like 
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
* Log Your Messages By
```
LTF_LOG(<Your Message>);
```
* Time Your Test By
```
LTF_TIME(<expected time in nanoseconds>);
```


## Features
- 🧪 Simplicity: We understand the importance of clean and straightforward testing. "Little Test Framework" lets you define and execute tests with just a few lines of code, without overwhelming you with unnecessary complexities.

- 🛠️ Macro-powered: Harness the power of macros to effortlessly define and manage your test cases. Using the "LTF_TEST" macro, you can easily create, organize, and run your tests, ensuring a smooth development process.

- 📜 Test Discovery: The framework automates test discovery, saving you time and effort. It automatically locates and runs all registered tests, providing a comprehensive overview of your code's health.

- 🚀 Efficient Execution: "Little Test Framework" optimizes the execution of your test suite, enabling rapid feedback loops during development. Spend less time waiting for tests to run and more time coding.

- 📊 Clear Reporting: With minimalistic design principles in mind, the framework provides concise and informative test execution reports. Identify issues quickly and make informed decisions based on test results.

- ⏸️ Flexible Test Skipping: The "Little Test Framework" allows you to ignore specific test cases or even entire test suites. This is particularly useful when certain tests are not applicable under certain conditions or during specific phases of development. By using the built-in skipping mechanism, you can focus on the relevant tests, ensuring efficient testing workflows without the need to comment out or remove test code.

- 📝 Insightful Logging: The framework features a comprehensive log message system, the macro "LTF_LOG" that provides detailed insights into the execution of each test case. During test runs, you can generate custom log messages using the provided logging functions. This allows you to trace the flow of test execution, inspect variable values, and diagnose potential issues more effectively.

- 🕒 Accurate Execution Timing: When a test case is executed with the "LTF_TIME" macro, the framework records the start and end times of the test's execution. The difference between these timestamps provides an accurate measurement of how long the test took to complete. 


## Installation Using CMake
```
cmake_minimum_required(VERSION 3.12)
project(YourProjectName) # Replace "YourProjectName" with the actual name of your project

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


## Demo
- Debug == False
```
LTF RUNNING ALL 4 TEST SUITES:
---------------------------------------------------------------------------------------------------------

1.SUITE1:
         RUNNING 3 TESTS FROM SUITE1
---------------------------------------------------------------------------------------------------------
         RUNNING...
                  1.TEST NAME:test_utils_main1 ----> [SUCCESS], TIME:0.000200 NANOSECONDS
         RUNNING...
                  2.TEST NAME:test_utils_main2 ----> [FAIL]
                           TIME LIMIT EXCEEDED: EXPECTED LESS THAN 180.000000 NANOSECONDS, TIME:200.475600 NANOSECONDS
         RUNNING...
                  3.TEST NAME:test_utils_main4 ----> [SUCCESS], TIME:0.000300 NANOSECONDS

TOTAL:
         (2) TESTS SUCCESS
         (1) TEST FAIL

---------------------------------------------------------------------------------------------------------
2.SUITE2:
         RUNNING 2 TESTS FROM SUITE2
---------------------------------------------------------------------------------------------------------
         RUNNING...
                  1.TEST NAME:test_utils_main3 ----> [SUCCESS], TIME:0.000100 NANOSECONDS
         RUNNING...
                  2.TEST NAME:test_utils_main4 ----> [SUCCESS], TIME:0.000100 NANOSECONDS

TOTAL:
         (2) TESTS SUCCESS

---------------------------------------------------------------------------------------------------------
3.SUITE3:
         RUNNING 1 TEST FROM SUITE3
---------------------------------------------------------------------------------------------------------
         RUNNING...
                  1.TEST NAME:test_ignore1 ----> [SUCCESS], TIME:0.000100 NANOSECONDS

TOTAL:
         (1) TEST SUCCESS

---------------------------------------------------------------------------------------------------------
4.SUITE_HELLO:
         RUNNING 1 TEST FROM SUITE_HELLO
---------------------------------------------------------------------------------------------------------
         RUNNING...
                  1.TEST NAME:test_ignore2 ----> [FAIL], TIME:0.000100 NANOSECONDS

TOTAL:
         (1) TEST FAIL

---------------------------------------------------------------------------------------------------------

SUMMARY:
         (7) TOTAL TESTS RUN
         (5) TOTAL TESTS SUCCESS
         (2) TOTAL TESTS FAIL


---------------------------------------------THE END OF TEST---------------------------------------------


```


- Debug == True
```
LTF RUNNING ALL 4 TEST SUITES:
---------------------------------------------------------------------------------------------------------

1.SUITE1:
         RUNNING 3 TESTS FROM SUITE1
---------------------------------------------------------------------------------------------------------
         RUNNING...
                  1.TEST NAME:test_utils_main1 ----> [SUCCESS], TIME:0.000400 NANOSECONDS

                  LOG MESSAGES FROM:test_utils_main1:
                  1:hello this is a message 1
                  2:hello this is a message 2
         RUNNING...
                  2.TEST NAME:test_utils_main2 ----> [FAIL] AT LINE [36]
                           TIME LIMIT EXCEEDED: EXPECTED LESS THAN 180.000000 NANOSECONDS, TIME:200.639800 NANOSECONDS
         RUNNING...
                  3.TEST NAME:test_utils_main4 ----> [SUCCESS], TIME:0.000300 NANOSECONDS

                  LOG MESSAGE FROM:test_utils_main4:
                  1:should be 120

TOTAL:
         (2) TESTS SUCCESS
         (1) TEST FAIL

---------------------------------------------------------------------------------------------------------
2.SUITE2:
         RUNNING 2 TESTS FROM SUITE2
---------------------------------------------------------------------------------------------------------
         RUNNING...
                  1.TEST NAME:test_utils_main3 ----> [SUCCESS], TIME:0.000000 NANOSECONDS

                  LOG MESSAGE FROM:test_utils_main3:
                  1:HI
         RUNNING...
                  2.TEST NAME:test_utils_main4 ----> [SUCCESS], TIME:0.000000 NANOSECONDS

                  LOG MESSAGE FROM:test_utils_main4:
                  1:should be 120

TOTAL:
         (2) TESTS SUCCESS

---------------------------------------------------------------------------------------------------------
3.SUITE3:
         RUNNING 1 TEST FROM SUITE3
---------------------------------------------------------------------------------------------------------
         RUNNING...
                  1.TEST NAME:test_ignore1 ----> [SUCCESS], TIME:0.000100 NANOSECONDS

TOTAL:
         (1) TEST SUCCESS

---------------------------------------------------------------------------------------------------------
4.SUITE_HELLO:
         RUNNING 1 TEST FROM SUITE_HELLO
---------------------------------------------------------------------------------------------------------
         RUNNING...
                  1.TEST NAME:test_ignore2 ----> [FAIL] AT LINE [64], TIME:0.000100 NANOSECONDS

TOTAL:
         (1) TEST FAIL

---------------------------------------------------------------------------------------------------------

SUMMARY:
         (7) TOTAL TESTS RUN
         (5) TOTAL TESTS SUCCESS
         (2) TOTAL TESTS FAIL


---------------------------------------------THE END OF TEST---------------------------------------------


```



## Example Usage
```
#include <LTF.h>
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
        LTF_LOG("hello this is a message 1");
        LTF_LOG("hello this is a message 2");
    }
    return LTF::LTFStatus(LTF::SUCCESS, __LINE__);
}

inline LTF::LTFStatus test_utils_main2(bool debug = false)
{
    LTF_TIME(180);
    double result = 0.0;
    for (int i = 0; i < 100000000; ++i) result += (true ? 1.0 : -1.0) * i;
    return LTF::LTFStatus(LTF::FAIL, __LINE__);
}

inline LTF::LTFStatus test_utils_main3(bool debug = false)
{
    if (debug) LTF_LOG("HI");

    int a = 1 + 1;
    if (a == 2) return LTF::LTFStatus(LTF::SUCCESS, __LINE__);
    return LTF::LTFStatus(LTF::FAIL, __LINE__);
}

inline LTF::LTFStatus test_utils_main4(bool debug = false)
{
    if (debug) LTF_LOG("should be 120");

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

const bool debug = true;

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




