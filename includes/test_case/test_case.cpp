#include "test_case.h"

LTF::TestCase::TestCase()
{
    this->m_function = nullptr;
    this->m_test_name = "";
}

LTF::TestCase::TestCase(const std::string& name, LTFStatus (*function)(bool debug))
{
    this->m_test_name = name;
    this->m_function = function;
}

LTF::TestCase::~TestCase()
{
}

void LTF::TestCase::set_test_name(const std::string& name)
{
    this->m_test_name = name;
}

void LTF::TestCase::set_test_function(LTFStatus (*function)(bool debug))
{
    this->m_function = function;
}

LTF::LTFStatus LTF::TestCase::run(bool debug, double& time)
{
    if (this->m_function == nullptr) return LTFStatus();
    std::chrono::duration<double, std::milli> elapsed = this->time();
    time = elapsed.count();
    return this->m_function(debug);
}
