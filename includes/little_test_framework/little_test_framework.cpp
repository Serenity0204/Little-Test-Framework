#include "little_test_framework.h"

namespace LTF
{
    // LittleTestFramework LittleTestFramework = LittleTestFramework();

    std::map<std::string, TestSuite> LittleTestFramework::_suites;

    LittleTestFramework::LittleTestFramework()
    {
        this->_suites = std::map<std::string, TestSuite>();
    }
    LittleTestFramework::~LittleTestFramework()
    {
    }

    void LittleTestFramework::add(const TestSuite& suite)
    {
        LittleTestFramework::_suites[suite.get_suite_name()] = suite;
    }
    bool LittleTestFramework::suite_exists(const std::string& suite_name)
    {
        return LittleTestFramework::_suites.count(suite_name) > 0;
    }
    TestSuite& LittleTestFramework::get_suite(const std::string& suite_name)
    {
        return LittleTestFramework::_suites[suite_name];
    }

    void LittleTestFramework::run_all(bool debug, std::ostream& outs)
    {
        const std::string space = "         ";
        outs << "\nLTF RUNNING ALL TEST SUITES:\n";
        outs << "----------------------------------------------------------------------\n\n";
        int i = 1;
        for (auto& suite : LittleTestFramework::_suites)
        {
            outs << i << ":SUITE:" << suite.first << "\n";
            outs << "----------------------------------------------------------------------\n";
            auto pass_map = suite.second.run_all(debug);
            int count = 1;
            for (const auto& flag : pass_map)
            {
                outs << space << "RUNNING...\n";
                outs << space << space << count << ":TEST NAME:" << flag.first << " ----> ";
                if (flag.second.code == LTF::SUCCESS) outs << "[SUCCESS]";
                if (flag.second.code == LTF::FAIL) outs << "[FAIL]";
                if (debug && flag.second.code == LTF::FAIL) outs << " AT LINE:[" << flag.second.line << "]";
                outs << "\n";
                ++count;
            }
            outs << "\n----------------------------------------------------------------------\n";
            ++i;
        }
        outs << "--------------------------THE END OF TEST-----------------------------\n\n";
    }
};