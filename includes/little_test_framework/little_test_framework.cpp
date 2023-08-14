#include "little_test_framework.h"

std::map<std::string, LTF::TestSuite> LTF::LittleTestFramework::_suites;

LTF::LittleTestFramework::LittleTestFramework()
{
    this->_suites = std::map<std::string, LTF::TestSuite>();
}
LTF::LittleTestFramework::~LittleTestFramework()
{
}

void LTF::LittleTestFramework::add(const LTF::TestSuite& suite)
{
    LTF::LittleTestFramework::_suites[suite.get_suite_name()] = suite;
}
bool LTF::LittleTestFramework::suite_exists(const std::string& suite_name)
{
    return LTF::LittleTestFramework::_suites.count(suite_name) > 0;
}
LTF::TestSuite& LTF::LittleTestFramework::get_suite(const std::string& suite_name)
{
    return LTF::LittleTestFramework::_suites[suite_name];
}

void LTF::LittleTestFramework::run_all(bool debug, std::ostream& outs)
{
    const std::string space = "         ";
    outs << "\nLTF RUNNING ALL TEST SUITES:\n";
    outs << "----------------------------------------------------------------------\n\n";
    int i = 1;
    for (auto& suite : LTF::LittleTestFramework::_suites)
    {
        outs << i << ":SUITE:" << suite.first << "\n";
        outs << "----------------------------------------------------------------------\n";
        int num_test = 0;
        auto pass_map = suite.second.run_all(debug, num_test);

        int count = 1;
        for (const auto& flag : pass_map)
        {
            outs << space << "RUNNING...\n";
            outs << space << space << count << ":TEST NAME:" << flag.first << " ----> ";
            if (flag.second.code == LTF::SUCCESS) outs << "[SUCCESS]";
            if (flag.second.code == LTF::FAIL) outs << "[FAIL]";
            if (debug && flag.second.code == LTF::FAIL) outs << " AT LINE [" << flag.second.line << "]";
            outs << "\n";
            ++count;
        }
        outs << "\n----------------------------------------------------------------------\n";
        ++i;
    }
    outs << "--------------------------THE END OF TEST-----------------------------\n\n";
}
