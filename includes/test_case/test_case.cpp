#include "test_case.h"

namespace LTF
{
    TestCase::TestCase()
    {
        this->_function = nullptr;
        this->_test_name = "";
    }

    TestCase::TestCase(const std::string& name, LTFStatus (*function)(bool debug))
    {
        this->_test_name = name;
        this->_function = function;
    }

    TestCase::~TestCase()
    {
    }

    void TestCase::set_test_name(const std::string& name)
    {
        this->_test_name = name;
    }

    void TestCase::set_test_function(LTFStatus (*function)(bool debug))
    {
        this->_function = function;
    }

    LTFStatus TestCase::run(bool debug, double& time)
    {
        if (this->_function == nullptr) return LTFStatus();
        std::chrono::duration<double, std::milli> elapsed = this->_time();
        time = elapsed.count();
        return this->_function(debug);
    }
};
