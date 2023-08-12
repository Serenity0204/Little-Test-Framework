#ifndef LTF_H
#define LTF_H

#pragma once
#include "stub/stub.h"

#include <iostream>
#include <string>
#include <vector>

class TestFramework
{
public:
    struct TestResult
    {
        std::string test_name;
        bool passed;
    };

    void addTest(std::string name, void (*testFunction)())
    {
        tests.push_back({name, testFunction});
    }

    void runTests()
    {
        int numPassed = 0;
        int numFailed = 0;

        for (const auto& test : tests)
        {
            try
            {
                test.testFunction();
                std::cout << "[PASS] " << test.name << std::endl;
                numPassed++;
            }
            catch (const std::exception& e)
            {
                std::cout << "[FAIL] " << test.name << " - " << e.what() << std::endl;
                numFailed++;
            }
        }

        std::cout << "\n=== Test Summary ===\n";
        std::cout << "Total tests: " << tests.size() << std::endl;
        std::cout << "Passed: " << numPassed << std::endl;
        std::cout << "Failed: " << numFailed << std::endl;
    }

private:
    struct Test
    {
        std::string name;
        void (*testFunction)();
    };

    std::vector<Test> tests;
};

// Assertion Macros

#define ASSERT_TRUE(condition) \
    if (!(condition)) throw std::runtime_error("Condition is false: " #condition)

#define ASSERT_EQUAL(expected, actual) \
    if ((expected) != (actual)) throw std::runtime_error("Expected: " #expected " | Actual: " #actual)

// Example Test Cases

void testAddition()
{
    int result = 2 + 3;
    ASSERT_EQUAL(5, result);
}

void testSubtraction()
{
    int result = 8 - 4;
    ASSERT_EQUAL(4, result);
}


#endif // LTF_H
