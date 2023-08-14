#include "test_manager.h"

namespace LTF
{
    TestManager LittleTestFramework = TestManager();

    TestManager::TestManager()
    {
        this->_suites = std::map<std::string, TestSuite>();
    }
    TestManager::~TestManager()
    {
    }

    void TestManager::add(const TestSuite& suite)
    {
        this->_suites[suite.get_suite_name()] = suite;
    }
    bool TestManager::suite_exists(const std::string& suite_name)
    {
        return this->_suites.count(suite_name) > 0;
    }
    TestSuite& TestManager::get_suite(const std::string& suite_name)
    {
        return this->_suites[suite_name];
    }
};