#ifndef TEST_CASE_H
#define TEST_CASE_H
#pragma once

#include <string>
#include <vector>

namespace LTF
{
    enum LTFCode
    {
        FAIL = 0,
        SUCCESS = 1,
    };

    class TestCase
    {
    private:
        std::string _test_name;
        LTFCode (*_function)();

    public:
        TestCase();
        TestCase(const std::string& name, LTFCode (*function)());
        ~TestCase();
        LTFCode run();
        void set_test_name(const std::string& name);
        void set_test_function(LTFCode (*function)());
        inline const std::string& get_test_name() const { return this->_test_name; }
    };
};
#endif // TEST_CASE_H
