#include "gtest/gtest.h"
#include <iomanip>
#include <iostream>

//------------------------------------------------------------------------------
// Files we are testing:
#include "../../includes/test_suite/test_suite.h"
#include "../../includes/test_template/test_template.h"
#include "../_test_utils/test_utils.h"
//------------------------------------------------------------------------------

using namespace std;

bool test_suite1(bool debug = false)
{
    LTF::TestSuite suite("test1");
    suite.add({"test1", test_utils1}).add({"test2", test_utils2}).add({"test3", test_utils3});
    LTF::Singleton<LTF::LittleTestFramework>::instance().add(suite);
    int size = 0;
    std::map<std::string, double> times;
    auto map = suite.run_all(false, size, times);
    int i = 0;
    for (auto x : map)
    {
        if (debug)
        {
            cout << x.first << ":";
            if (x.second.code == LTF::SUCCESS) cout << "success at line:" << x.second.line << endl;
            if (x.second.code == LTF::FAIL) cout << "fail at line:" << x.second.line << endl;
        }
        if (x.second.code == LTF::FAIL && i == 0) return false;
        if (x.second.code == LTF::SUCCESS && i == 1) return false;
        if (x.second.code == LTF::FAIL && i == 2) return false;
        i++;
    }
    return true;
}

bool test_manager(bool debug = false)
{
    LTF::TestSuite suite1("test2");
    LTF::Singleton<LTF::LittleTestFramework>::instance().add(suite1);
    if (LTF::Singleton<LTF::LittleTestFramework>::instance().get_num_suites() != 2) return false;
    LTF::TestSuite suite2("test2");
    LTF::Singleton<LTF::LittleTestFramework>::instance().add(suite1);
    if (LTF::Singleton<LTF::LittleTestFramework>::instance().get_num_suites() != 2) return false;
    LTF::TestSuite suite3("test3");
    LTF::Singleton<LTF::LittleTestFramework>::instance().add(suite3);
    if (LTF::Singleton<LTF::LittleTestFramework>::instance().get_num_suites() != 3) return false;
    return true;
}

bool test_template(bool debug = false)
{
    LTF_TEST(test4, test_utils1);
    if (LTF::Singleton<LTF::LittleTestFramework>::instance().get_num_suites() != 4) return false;
    LTF_TEST(test4, test_utils2);
    if (LTF::Singleton<LTF::LittleTestFramework>::instance().get_num_suites() != 4) return false;

    if (debug)
    {
        auto m = LTF::Singleton<LTF::LittleTestFramework>::instance().get();
        for (const auto& x : m)
        {
            cout << x.first << endl;
            x.second.print();
        }
    }
    if (LTF::Singleton<LTF::LittleTestFramework>::instance().get_suite("test4").get_num_tests() != 2) return false;
    return true;
}

// Lord help me!
const bool debug = false;

TEST(TEST_SUITE, TestSuite1)
{
    bool success = test_suite1(debug);
    EXPECT_EQ(success, true);
}

TEST(TEST_MANAGER, LittleTestFramework1)
{
    bool success = test_manager(debug);
    EXPECT_EQ(success, true);
}

TEST(TEST_TEMPLATE, TestTemplate1)
{
    bool success = test_template(debug);
    EXPECT_EQ(success, true);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    std::cout << "\n\n----------running test_ltf.cpp---------\n\n"
              << std::endl;
    return RUN_ALL_TESTS();
}
