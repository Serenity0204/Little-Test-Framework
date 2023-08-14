#ifndef TEST_ENTRY_H
#define TEST_ENTRY_H

#pragma once

#include "../test_case/test_case.h"
#include "../test_suite/test_suite.h"

namespace LTF
{
    class TestSuite;
    class TestCase;
    class TestManager;

    class TestManager
    {
    private:
        std::vector<TestSuite> _suites;

    public:
        TestManager();
        ~TestManager();
        void add_test_suite(const TestSuite& suite);
        inline std::size_t get_num_suites() { return this->_suites.size(); }
    };

    extern TestManager LittleTestFramework;
};
#endif // TEST_ENTRY_H
