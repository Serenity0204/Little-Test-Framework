#include "test_case.h"

namespace LTF
{
    TestCase::TestCase()
    {
        this->m_function = nullptr;
        this->m_test_name = "";
    }

    TestCase::TestCase(const std::string& name, LTFStatus (*function)(bool debug))
    {
        this->m_test_name = name;
        this->m_function = function;
    }

    TestCase::~TestCase()
    {
    }

    void TestCase::set_test_name(const std::string& name)
    {
        this->m_test_name = name;
    }

    void TestCase::set_test_function(LTFStatus (*function)(bool debug))
    {
        this->m_function = function;
    }

    LTFStatus TestCase::run(bool debug, double& time)
    {
        if (this->m_function == nullptr) return LTFStatus();
        std::chrono::duration<double, std::milli> elapsed = this->m_time();
        time = elapsed.count();
        return this->m_function(debug);
    }
};
