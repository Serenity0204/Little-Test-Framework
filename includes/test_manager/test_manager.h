#ifndef TEST_MANAGER_H
#define TEST_MANAGER_H

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
    class TestManager;

    class TestManager
    {
    private:
        // suite name vs suite
        std::map<std::string, TestSuite> _suites;

    public:
        // CTORS
        TestManager();
        ~TestManager();

        // add suite by suite name vs suite
        void add(const TestSuite& suite);

        // getters
        bool suite_exists(const std::string& suite_name);
        TestSuite& get_suite(const std::string& suite_name);
        inline std::size_t get_num_suites() { return this->_suites.size(); }

        // for testing
        std::map<std::string, TestSuite>& get() { return this->_suites; }
    };

    extern TestManager LittleTestFramework;
};
#endif // TEST_MANAGER_H
