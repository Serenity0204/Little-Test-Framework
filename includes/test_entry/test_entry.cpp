#include "test_entry.h"

namespace LTF
{
    TestEntry LTFEntry = TestEntry();

    TestEntry::TestEntry()
    {
        this->_suites = std::vector<TestSuite>();
    }
    TestEntry::~TestEntry()
    {
    }

    void TestEntry::add_test_suite(const TestSuite& suite)
    {
        this->_suites.push_back(suite);
    }

};