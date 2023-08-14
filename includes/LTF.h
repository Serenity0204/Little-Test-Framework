#ifndef LTF_H
#define LTF_H

#pragma once

#include "test_entry/test_manager.h"
#include <iostream>
#include <string>
#include <vector>

// enum LTFCode
// {
//     FAIL = 0,
//     SUCCESS = 1,
// };

// class TestFramework
// {
// public:
//     struct TestResult
//     {
//         std::string test_name;
//         bool passed;
//     };

//     void addTest(std::string name, LTFCode (*testFunction)())
//     {
//         tests.push_back({name, testFunction});
//     }

//     void runTests()
//     {
//         int numPassed = 0;
//         int numFailed = 0;

//         for (const auto& test : tests)
//         {
//             try
//             {
//                 LTFCode code = test.testFunction();
//                 if (code == LTFCode::SUCCESS)
//                 {
//                     std::cout << "[PASS] " << test.name << std::endl;
//                     numPassed++;
//                 }
//                 if (code == LTFCode::FAIL)
//                 {
//                     std::cout << "[FAIL] " << test.name << std::endl;
//                     numFailed++;
//                 }
//             }
//             catch (const std::exception& e)
//             {
//                 std::cout << "[FAIL] " << test.name << " - " << e.what() << std::endl;
//                 numFailed++;
//             }
//         }

//         std::cout << "\n=== Test Summary ===\n";
//         std::cout << "Total tests: " << tests.size() << std::endl;
//         std::cout << "Passed: " << numPassed << std::endl;
//         std::cout << "Failed: " << numFailed << std::endl;
//     }

// private:
//     struct Test
//     {
//         std::string name;
//         LTFCode (*testFunction)();
//     };

//     std::vector<Test> tests;
// };

// // Assertion Macros

// #define ASSERT_TRUE(condition) \
//     if (!(condition)) throw std::runtime_error("Condition is false: " #condition)

// #define ASSERT_EQUAL(expected, actual) \
//     if ((expected) != (actual)) throw std::runtime_error("Expected: " #expected " | Actual: " #actual)

// // Example Test Cases

// LTFCode testAddition()
// {
//     int result = 2 + 3;
//     ASSERT_EQUAL(5, result);
//     return LTFCode::FAIL;
// }

// LTFCode testSubtraction()
// {
//     int result = 8 - 4;
//     ASSERT_EQUAL(4, result);
//     return LTFCode::SUCCESS;
// }

#endif // LTF_H
