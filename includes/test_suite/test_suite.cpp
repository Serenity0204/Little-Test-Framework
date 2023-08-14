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
        this->_passed_flags = std::map<std::string, LTF::LTFStatus>();

        // adding this test suite to the global test entry
        LTF::LittleTestFramework.add_test_suite(*this);
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

    std::map<std::string, LTF::LTFStatus>& TestSuite::run_all(bool debug)
    {
        for (const auto& test : this->_test_cases)
        {
            std::string name = test.first;
            TestCase test_case = test.second;
            LTFStatus code = test_case.run(debug);
            this->_passed_flags[name] = code;
        }
        return this->_passed_flags;
    }
};