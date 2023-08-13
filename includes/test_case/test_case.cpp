#include "test_case.h"

namespace LTF
{
    TestCase::TestCase()
    {
        this->_function = nullptr;
        this->_test_name = "";
    }

    TestCase::TestCase(const std::string& name, LTFCode (*function)())
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

    void TestCase::set_test_function(LTFCode (*function)())
    {
        this->_function = function;
    }

    LTFCode TestCase::run()
    {
        return this->_function();
    }
};
