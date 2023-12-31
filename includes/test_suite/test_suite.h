#ifndef TEST_SUITE_H
#define TEST_SUITE_H

#pragma once

#include "../test_case/test_case.h"
#include <iostream>
#include <map>
#include <string>
#include <vector>

namespace LTF
{
    class TestSuite
    {
    private:
        // test name vs test case, test name vs pass or not
        std::string m_suite_name;
        std::map<std::string, TestCase> m_test_cases;
        std::map<std::string, LTF::LTFStatus> m_passed_flags;

    public:
        // CTORS
        TestSuite();
        TestSuite(const std::string& name);
        ~TestSuite();
        TestSuite& operator=(const TestSuite& rhs);

        // add the case to the suite by case name vs case
        TestSuite& add(const TestCase& test_case);

        // run all that will return a map of case name vs status
        std::map<std::string, LTF::LTFStatus>& run_all(bool debug, int& test_count, std::map<std::string, double>& times);

        // getters
        inline const std::string& get_suite_name() const { return this->m_suite_name; }
        inline std::size_t get_num_tests() const { return this->m_test_cases.size(); }

        // print all of the cases's name
        void print() const
        {
            std::cout << "test cases:" << std::endl;
            for (const auto& test : this->m_test_cases) std::cout << "name:" << test.first << std::endl;
            std::cout << std::endl;
        }

        // remove test cases
        inline void ignore_tests(const std::vector<std::string>& tests)
        {
            for (const std::string& test : tests) this->m_test_cases.erase(test);
        }
    };

};

#endif // TEST_SUITE_H
