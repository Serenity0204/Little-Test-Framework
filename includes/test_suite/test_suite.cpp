#include "test_suite.h"

namespace LTF
{
    TestSuite::TestSuite()
    {
    }

    TestSuite::TestSuite(const std::string& name)
    {
        this->_suite_name = name;
        this->_test_cases = std::map<std::string, TestCase>();
        this->_passed_flags = std::map<std::string, LTF::LTFCode>();
    }

    TestSuite::~TestSuite()
    {
    }

    TestSuite& TestSuite::add(const TestCase& test_case)
    {
        std::string name = test_case.get_test_name();
        this->_test_cases[name] = test_case;
        return *this;
    }

    std::map<std::string, LTF::LTFCode>& TestSuite::run_all()
    {
        for (const auto& test : this->_test_cases)
        {
            std::string name = test.first;
            TestCase test_case = test.second;
            LTFCode code = test_case.run();
            this->_passed_flags[name] = code;
        }
        return this->_passed_flags;
    }
};