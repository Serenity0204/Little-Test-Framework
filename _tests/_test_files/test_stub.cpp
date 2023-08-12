#include "gtest/gtest.h"
#include <iomanip>
#include <iostream>

//------------------------------------------------------------------------------
// Files we are testing:
#include "../../includes/stub/stub.h"

//------------------------------------------------------------------------------

using namespace std;

bool test_stub(bool debug = false)
{
    return stub();
}

// Lord help me!
const bool debug = false;

TEST(TEST_STUB, TestStub)
{
    bool success = test_stub(debug);
    EXPECT_EQ(success, true);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    std::cout << "\n\n----------running test_stub.cpp---------\n\n"
              << std::endl;
    return RUN_ALL_TESTS();
}
