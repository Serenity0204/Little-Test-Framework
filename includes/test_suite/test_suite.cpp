#include "test_suite.h"

LTF::TestSuite::TestSuite()
{
}

LTF::TestSuite::TestSuite(const std::string& name)
{
    this->_suite_name = name;
    this->_test_cases = std::map<std::string, TestCase>();
    this->_passed_flags = std::map<std::string, LTF::LTFStatus>();
}

LTF::TestSuite::~TestSuite()
{
}

LTF::TestSuite& LTF::TestSuite::operator=(const TestSuite& rhs)
{
    this->_suite_name = rhs._suite_name;
    this->_test_cases = rhs._test_cases;
    this->_passed_flags = rhs._passed_flags;
    return *this;
}
LTF::TestSuite& LTF::TestSuite::add(const TestCase& test_case)
{
    std::string name = test_case.get_test_name();
    this->_test_cases[name] = test_case;
    return *this;
}

std::map<std::string, LTF::LTFStatus>& LTF::TestSuite::run_all(bool debug, int& test_count)
{
    for (const auto& test : this->_test_cases)
    {
        std::string name = test.first;
        TestCase test_case = test.second;
        LTFStatus code = test_case.run(debug);
        this->_passed_flags[name] = code;
    }
    test_count = this->_passed_flags.size();
    return this->_passed_flags;
}
