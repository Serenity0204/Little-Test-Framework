#include "test_suite.h"

LTF::TestSuite::TestSuite()
{
}

LTF::TestSuite::TestSuite(const std::string& name)
{
    this->m_suite_name = name;
    this->m_test_cases = std::map<std::string, TestCase>();
    this->m_passed_flags = std::map<std::string, LTF::LTFStatus>();
}

LTF::TestSuite::~TestSuite()
{
}

LTF::TestSuite& LTF::TestSuite::operator=(const TestSuite& rhs)
{
    this->m_suite_name = rhs.m_suite_name;
    this->m_test_cases = rhs.m_test_cases;
    this->m_passed_flags = rhs.m_passed_flags;
    return *this;
}
LTF::TestSuite& LTF::TestSuite::add(const TestCase& test_case)
{
    std::string name = test_case.get_test_name();
    this->m_test_cases[name] = test_case;
    return *this;
}

std::map<std::string, LTF::LTFStatus>& LTF::TestSuite::run_all(bool debug, int& test_count, std::map<std::string, double>& times)
{
    this->m_passed_flags.clear();
    times.clear();
    for (const auto& test : this->m_test_cases)
    {
        std::string name = test.first;
        TestCase test_case = test.second;
        double time = 0;
        LTFStatus code = test_case.run(debug, time);
        times[name] = time;
        this->m_passed_flags[name] = code;
    }
    test_count = this->m_passed_flags.size();
    return this->m_passed_flags;
}
