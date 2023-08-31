#include "gtest/gtest.h"
#include <iomanip>
#include <iostream>

//------------------------------------------------------------------------------
// Files we are testing:
#include "../../includes/logger/logger.h"
#include "../../includes/logger_template/logger_template.h"
#include "../../includes/singleton/singleton.h"
#include "../_test_utils/test_utils.h"
//------------------------------------------------------------------------------

using namespace std;

bool test_logger1(bool debug = false)
{
    // change this
    const int NUM = 3;

    // reset the state
    delete_file("../../log1.txt");

    LTF::Logger& log = LTF::Singleton<LTF::Logger>::instance();
    log.level(LTF::Logger::Level::WARNING);
    log.open("../../log1.txt");

    // log
    log.log(LTF::Logger::Level::DEBUG, "debug message", LTF::Logger::Info(__FILE__, __LINE__));
    log.log(LTF::Logger::Level::INFO, "info message", LTF::Logger::Info(__FILE__, __LINE__));
    log.log(LTF::Logger::Level::WARNING, "warning message", LTF::Logger::Info(__FILE__, __LINE__));
    log.log(LTF::Logger::Level::ERROR, "error message", LTF::Logger::Info(__FILE__, __LINE__));
    log.log(LTF::Logger::Level::FATAL, "fatal message", LTF::Logger::Info(__FILE__, __LINE__));

    EXPECT_EQ(log.count(), NUM);
    return true;
}

bool test_logger2(bool debug = false)
{
    // should be 3 + 2 = 5
    const int NUM = 5;

    // // reset the state
    delete_file("../../log2.txt");

    LTF_LOG_INIT("../../log2.txt");
    LTF_LOG_LEVEL(LTF::Logger::Level::INFO);

    // // log
    LTF_DEBUG("debug message");
    LTF_INFO("info message");
    LTF_WARNING("warning message");
    LTF_ERROR("error message");
    LTF_FATAL("fatal message");

    LTF::Logger& log = LTF::Singleton<LTF::Logger>::instance();
    EXPECT_EQ(log.count(), NUM);
    return true;
}

// Lord help me!
const bool debug = false;

TEST(TEST_LOGGER, TestLogger1)
{
    bool success = test_logger1(debug);
    EXPECT_EQ(success, true);
}

TEST(TEST_LOGGER, TestLogger2)
{
    bool success = test_logger2(debug);
    EXPECT_EQ(success, true);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    std::cout << "\n\n----------running test_log.cpp---------\n\n"
              << std::endl;
    return RUN_ALL_TESTS();
}
