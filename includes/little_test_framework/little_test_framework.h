#ifndef LITTLE_TEST_FRAMEWORK_H
#define LITTLE_TEST_FRAMEWORK_H

#pragma once

#include "../singleton/singleton.h"
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

    // implement Singleton design pattern
    class LittleTestFramework
    {
    private:
        friend class Singleton<LTF::LittleTestFramework>;

    private:
        // suite name vs suite
        std::map<std::string, TestSuite> m_suites;
        // for messages, function name vs vector of message
        std::map<std::string, std::vector<std::string>> m_messages;
        // for timing, function name vs time in ms
        std::map<std::string, double> m_times;

        inline static void output(const std::string& message, std::ofstream& outs, LTF::MODE mode = LTF::MODE::CONSOLE)
        {
            if (mode == LTF::MODE::FILE) outs << message;
            if (mode == LTF::MODE::CONSOLE) std::cout << message;
        }

    private:
        // CTORS
        LittleTestFramework();
        LittleTestFramework(const LittleTestFramework& rhs) = delete;
        LittleTestFramework& operator=(const LittleTestFramework& rhs) = delete;
        ~LittleTestFramework();

    public:
        // add suite by suite name vs suite
        void add(const TestSuite& suite);

        // getters
        bool suite_exists(const std::string& suite_name);
        TestSuite& get_suite(const std::string& suite_name);
        inline std::size_t get_num_suites() { return this->m_suites.size(); }

        // for testing
        std::map<std::string, TestSuite>& get() { return this->m_suites; }

        // main method to call to run all tests
        void run_all(bool debug = false, LTF::MODE mode = LTF::CONSOLE, const std::string& path = "");

        // remove
        inline void clean()
        {
            this->m_suites.clear();
            this->m_messages.clear();
            this->m_times.clear();
        }

        void ignore_suites(const std::vector<std::string>& suites);
        void ignore_tests(const std::string& suite_name, const std::vector<std::string>& tests);

        // message
        void comment(const std::string& function, const std::string& message);

        // time
        void time(const std::string& function, double time_ns);
    };
};
#endif // LITTLE_TEST_FRAMEWORK_H
