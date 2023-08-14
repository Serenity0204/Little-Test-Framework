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

    struct LTFStatus
    {
    public:
        std::size_t line;
        LTFCode code;
        LTFStatus(LTFCode code = LTFCode::FAIL, std::size_t line = 0)
        {
            this->line = line;
            this->code = code;
        }
        ~LTFStatus() {}
    };

    class TestCase
    {
    private:
        std::string _test_name;
        LTFStatus (*_function)(bool debug);

    public:
        TestCase();
        TestCase(const std::string& name, LTFStatus (*function)(bool debug));
        ~TestCase();
        LTFStatus run(bool debug = false);
        void set_test_name(const std::string& name);
        void set_test_function(LTFStatus (*function)(bool debug));
        inline const std::string& get_test_name() const { return this->_test_name; }
    };
};
#endif // TEST_CASE_H
