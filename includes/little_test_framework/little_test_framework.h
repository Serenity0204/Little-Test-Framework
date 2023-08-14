#ifndef LITTLE_TEST_FRAMEWORK_H
#define LITTLE_TEST_FRAMEWORK_H

#pragma once

#include "../test_case/test_case.h"
#include "../test_suite/test_suite.h"
#include <iostream>
#include <map>
#include <string>

namespace LTF
{
    class TestSuite;
    class TestCase;
    class LittleTestFramework;

    // All static member
    class LittleTestFramework
    {
    private:
        // suite name vs suite
        static std::map<std::string, TestSuite> _suites;

    public:
        // CTORS
        LittleTestFramework();
        ~LittleTestFramework();

        // add suite by suite name vs suite
        static void add(const TestSuite& suite);

        // getters
        static bool suite_exists(const std::string& suite_name);
        static TestSuite& get_suite(const std::string& suite_name);
        static inline std::size_t get_num_suites() { return LittleTestFramework::_suites.size(); }

        // for testing
        static std::map<std::string, TestSuite>& get() { return LittleTestFramework::_suites; }

        // main method to call to run all tests
        static void run_all(bool debug = false, std::ostream& outs = std::cout);
        static inline void clean() { LittleTestFramework::_suites.clear(); }
    };
};
#endif // LITTLE_TEST_FRAMEWORK_H
