#include "gtest/gtest.h"
#include <iomanip>
#include <iostream>

//------------------------------------------------------------------------------
// Files we are testing:
#include "../../includes/test_suite/test_suite.h"
#include "../_test_utils/test_utils.h"
//------------------------------------------------------------------------------

using namespace std;

bool test_suite1(bool debug = false)
{
    LTF::TestSuite suite("test1");
    suite.add({"test1", test_utils1}).add({"test2", test_utils2}).add({"test3", test_utils3});

    auto map = suite.run_all();
    int i = 0;
    for (auto x : map)
    {
        if (debug)
        {
            cout << x.first << ":";
            if (x.second.code == LTF::SUCCESS) cout << "success" << endl;
            if (x.second.code == LTF::FAIL) cout << "fail" << endl;
        }
        if (x.second.code == LTF::FAIL && i == 0) return false;
        if (x.second.code == LTF::SUCCESS && i == 1) return false;
        if (x.second.code == LTF::FAIL && i == 2) return false;
        i++;
    }
    return true;
}

// Lord help me!
const bool debug = false;

TEST(TEST_SUITE, TestSuite1)
{
    bool success = test_suite1(debug);
    EXPECT_EQ(success, true);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    std::cout << "\n\n----------running test_stub.cpp---------\n\n"
              << std::endl;
    return RUN_ALL_TESTS();
}
