#include "little_test_framework.h"

std::map<std::string, LTF::TestSuite> LTF::LittleTestFramework::_suites;
std::map<std::string, std::vector<std::string>> LTF::LittleTestFramework::_messages;

LTF::LittleTestFramework::LittleTestFramework()
{
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

void LTF::LittleTestFramework::ignore_suites(const std::vector<std::string>& suites)
{
    for (const std::string& suite : suites) LTF::LittleTestFramework::_suites.erase(suite);
}

void LTF::LittleTestFramework::ignore_tests(const std::string& suite_name, const std::vector<std::string>& tests)
{
    // if suite doesn't exist then do early return
    if (!LTF::LittleTestFramework::suite_exists(suite_name)) return;
    // get the suite, remove the tests, then add it back
    LTF::TestSuite suite = LTF::LittleTestFramework::get_suite(suite_name);
    suite.ignore_tests(tests);
    LTF::LittleTestFramework::add(suite);
}

void LTF::LittleTestFramework::run_all(bool debug, MODE mode, const std::string& path)
{
    std::ofstream outs;
    if (mode == LTF::MODE::FILE) outs.open(path);

    // no suites
    if (LTF::LittleTestFramework::get_num_suites() == 0)
    {
        LTF::LittleTestFramework::output("\nLTF: NO SUITES ADDED\n", outs, mode);
        LTF::LittleTestFramework::output("EXIT LTF...\n", outs, mode);

        if (mode == LTF::MODE::FILE) outs.close();
        return;
    }

    const std::string space = "         ";

    std::vector<std::size_t> tests_count;
    std::size_t suites_count = 0;
    for (auto& suite : LTF::LittleTestFramework::_suites)
    {
        tests_count.push_back(suite.second.get_num_tests());
        ++suites_count;
    }

    LTF::LittleTestFramework::output("\nLTF RUNNING ALL " + std::to_string(suites_count) + " TEST SUITE" + (suites_count != 1 ? "S" : "") + ":\n", outs, mode);
    LTF::LittleTestFramework::output("----------------------------------------------------------------------\n\n", outs, mode);

    int i = 0;
    int success_total = 0, fail_total = 0;
    for (auto& suite : LTF::LittleTestFramework::_suites)
    {
        LTF::LittleTestFramework::output(std::to_string(i + 1) + "." + suite.first + ":\n", outs, mode);

        LTF::LittleTestFramework::output(space + "RUNNING " + std::to_string(tests_count[i]) + " TEST" + (tests_count[i] != 1 ? "S" : "") + " FROM " + suite.first + "\n", outs, mode);
        LTF::LittleTestFramework::output("----------------------------------------------------------------------\n", outs, mode);

        int num_test = 0;
        auto pass_map = suite.second.run_all(debug, num_test);

        int count = 1, success_count = 0, fail_count = 0;
        for (const auto& flag : pass_map)
        {
            LTF::LittleTestFramework::output(space + "RUNNING...\n", outs, mode);
            std::string result = space + space + std::to_string(count) + ".TEST NAME:" + flag.first + " ----> ";
            if (flag.second.code == LTF::SUCCESS)
            {
                ++success_count;
                result += "[SUCCESS]";
            }
            if (flag.second.code == LTF::FAIL)
            {
                ++fail_count;
                result += "[FAIL]";
                if (debug) result += " AT LINE [" + std::to_string(flag.second.line) + "]";
            }
            LTF::LittleTestFramework::output(result + "\n", outs, mode);

            // if there's log message then start outputting them
            if (LTF::LittleTestFramework::_messages.count(flag.first))
            {
                std::vector<std::string> messages = LTF::LittleTestFramework::_messages[flag.first];
                std::string messages_output = "";
                // concat messages
                for (int i = 0; i < messages.size(); ++i) messages_output += space + space + std::to_string(i + 1) + ":" + messages[i] + "\n";
                std::string output_str = "\n" + space + space + std::string("LOG MESSAGE") + (messages.size() != 1 ? "S" : "") + std::string(" FROM:") + flag.first + ":\n" + messages_output;
                LTF::LittleTestFramework::output(output_str, outs, mode);
            }
            ++count;
        }

        LTF::LittleTestFramework::output("\nTOTAL:\n", outs, mode);
        if (success_count != 0) LTF::LittleTestFramework::output(space + "(" + std::to_string(success_count) + ") TEST" + (success_count != 1 ? "S" : "") + " SUCCESS\n", outs, mode);
        if (fail_count != 0) LTF::LittleTestFramework::output(space + "(" + std::to_string(fail_count) + ") TEST" + (fail_count != 1 ? "S" : "") + " FAIL\n", outs, mode);

        success_total += success_count;
        fail_total += fail_count;

        LTF::LittleTestFramework::output("\n----------------------------------------------------------------------\n", outs, mode);
        ++i;
    }

    LTF::LittleTestFramework::output("\nSUMMARY:\n", outs, mode);
    int total_num_of_test = success_total + fail_total;
    LTF::LittleTestFramework::output(space + "(" + std::to_string(total_num_of_test) + ") TOTAL TEST" + (success_total != 1 ? "S" : "") + " RUN\n", outs, mode);

    if (success_total != 0) LTF::LittleTestFramework::output(space + "(" + std::to_string(success_total) + ") TOTAL TEST" + (success_total != 1 ? "S" : "") + " SUCCESS\n", outs, mode);

    if (fail_total != 0) LTF::LittleTestFramework::output(space + "(" + std::to_string(fail_total) + ") TOTAL TEST" + (fail_total != 1 ? "S" : "") + " FAIL\n", outs, mode);

    LTF::LittleTestFramework::output("\n\n--------------------------THE END OF TEST-----------------------------\n\n", outs, mode);

    if (mode == LTF::MODE::FILE) outs.close();
}

void LTF::LittleTestFramework::log(const std::string& function, const std::string& message)
{
    // if the key exists, then get the vector
    if (LTF::LittleTestFramework::_messages.count(function) > 0)
    {
        // check if message already exists, same message should not be output twice anyways
        bool exist = std::find(LTF::LittleTestFramework::_messages[function].begin(), LTF::LittleTestFramework::_messages[function].end(), message) != LTF::LittleTestFramework::_messages[function].end();
        if (exist) return;
        // insert if does not exist
        LTF::LittleTestFramework::_messages[function].push_back(message);
        return;
    }
    std::vector<std::string> newMessage = {message};
    LTF::LittleTestFramework::_messages[function] = newMessage;
}