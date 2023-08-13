#ifndef TEST_SUITE_H
#define TEST_SUITE_H

#pragma once

#include "../test_case/test_case.h"
#include <iostream>
#include <map>
#include <string>

namespace LTF
{
    class TestSuite
    {
    private:
        std::string _suite_name;
        std::map<std::string, TestCase> _test_cases;
        std::map<std::string, LTF::LTFCode> _passed_flags;

    public:
        TestSuite();
        TestSuite(const std::string& name);
        ~TestSuite();

        TestSuite& add(const TestCase& test_case);
        std::map<std::string, LTF::LTFCode>& run_all();
        inline const std::string& get_suite_name() const { return this->_suite_name; }
        inline std::size_t get_num_tests() const { return this->_test_cases.size(); }
    };

};

#endif // TEST_SUITE_H
