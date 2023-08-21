#ifndef LITTLE_TEST_FRAMEWORK_H
#define LITTLE_TEST_FRAMEWORK_H

#pragma once

#include "../test_case/test_case.h"
#include "../test_suite/test_suite.h"
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

namespace LTF
{
    enum MODE
    {
        CONSOLE = 0,
        FILE = 1,
    };

    // All static member
    class LittleTestFramework
    {
    private:
        // suite name vs suite
        static std::map<std::string, TestSuite> _suites;
        // for messages, function name vs vector of message
        static std::map<std::string, std::vector<std::string>> _messages;
        // for timing, function name vs time in ms
        static std::map<std::string, double> _times;

        static inline void output(const std::string& message, std::ofstream& outs, LTF::MODE mode = LTF::MODE::CONSOLE)
        {
            if (mode == LTF::MODE::FILE) outs << message;
            if (mode == LTF::MODE::CONSOLE) std::cout << message;
        }

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
        static void run_all(bool debug = false, LTF::MODE mode = LTF::CONSOLE, const std::string& path = "");

        // remove
        static inline void clean()
        {
            LittleTestFramework::_suites.clear();
            LittleTestFramework::_messages.clear();
            LittleTestFramework::_times.clear();
        }

        static void ignore_suites(const std::vector<std::string>& suites);
        static void ignore_tests(const std::string& suite_name, const std::vector<std::string>& tests);

        // log
        static void log(const std::string& function, const std::string& message);

        // time
        static void time(const std::string& function, double time_ns);
    };
};
#endif // LITTLE_TEST_FRAMEWORK_H
