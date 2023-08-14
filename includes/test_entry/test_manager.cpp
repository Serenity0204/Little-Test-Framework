#include "test_manager.h"

namespace LTF
{
    TestManager LittleTestFramework = TestManager();

    TestManager::TestManager()
    {
        this->_suites = std::vector<TestSuite>();
    }
    TestManager::~TestManager()
    {
    }

    void TestManager::add_test_suite(const TestSuite& suite)
    {
        this->_suites.push_back(suite);
    }

};