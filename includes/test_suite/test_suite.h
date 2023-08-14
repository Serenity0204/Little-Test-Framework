#ifndef TEST_SUITE_H
#define TEST_SUITE_H

#pragma once

#include "../test_case/test_case.h"
#include "../test_manager/test_manager.h"
#include <iostream>
#include <map>
#include <string>

namespace LTF
{
    class TestSuite
    {
    private:
        // test name vs test case, test name vs pass or not
        std::string _suite_name;
        std::map<std::string, TestCase> _test_cases;
        std::map<std::string, LTF::LTFStatus> _passed_flags;

    public:
        // CTORS
        TestSuite();
        TestSuite(const std::string& name);
        ~TestSuite();
        TestSuite& operator=(const TestSuite& rhs);

        // add the case to the suite by case name vs case
        TestSuite& add(const TestCase& test_case);

        // run all that will return a map of case name vs status
        std::map<std::string, LTF::LTFStatus>& run_all(bool debug = false);

        // getters
        inline const std::string& get_suite_name() const { return this->_suite_name; }
        inline std::size_t get_num_tests() const { return this->_test_cases.size(); }

        // print all of the cases's name
        void print() const
        {
            std::cout << "test cases:" << std::endl;
            for (const auto& test : this->_test_cases) std::cout << "name:" << test.first << std::endl;
            std::cout << std::endl;
        }
    };

};

#endif // TEST_SUITE_H
