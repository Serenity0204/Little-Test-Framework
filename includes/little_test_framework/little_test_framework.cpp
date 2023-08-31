#include "little_test_framework.h"

LTF::LittleTestFramework::LittleTestFramework()
{
    this->m_suites = std::map<std::string, LTF::TestSuite>();
    this->m_messages = std::map<std::string, std::vector<std::string>>();
    this->m_times = std::map<std::string, double>();
}

LTF::LittleTestFramework::~LittleTestFramework()
{
    this->clean();
}

void LTF::LittleTestFramework::add(const LTF::TestSuite& suite)
{
    this->m_suites[suite.get_suite_name()] = suite;
}

bool LTF::LittleTestFramework::suite_exists(const std::string& suite_name)
{
    return this->m_suites.count(suite_name) > 0;
}

LTF::TestSuite& LTF::LittleTestFramework::get_suite(const std::string& suite_name)
{
    assert(this->suite_exists(suite_name));
    return this->m_suites[suite_name];
}

void LTF::LittleTestFramework::ignore_suites(const std::vector<std::string>& suites)
{
    for (const std::string& suite : suites) this->m_suites.erase(suite);
}

void LTF::LittleTestFramework::ignore_tests(const std::string& suite_name, const std::vector<std::string>& tests)
{
    // if suite doesn't exist then do early return
    if (!this->suite_exists(suite_name)) return;
    // get the suite, remove the tests, then add it back
    LTF::TestSuite suite = this->get_suite(suite_name);
    suite.ignore_tests(tests);
    this->add(suite);
}

void LTF::LittleTestFramework::run_all(bool debug, MODE mode, const std::string& path)
{
    std::ofstream outs;
    if (mode == LTF::MODE::FILE) outs.open(path);

    // no suites
    if (this->get_num_suites() == 0)
    {
        LTF::LittleTestFramework::output("\nLTF: NO SUITES ADDED\n", outs, mode);
        LTF::LittleTestFramework::output("EXIT LTF...\n", outs, mode);

        if (mode == LTF::MODE::FILE) outs.close();
        return;
    }

    // constants
    const std::string SPACE = "         ";
    const std::string LINE = "---------------------------------------------------------------------------------------------------------";

    // count the number of tests and suites
    std::vector<std::size_t> tests_count;
    std::size_t suites_count = 0;
    for (auto& suite : this->m_suites)
    {
        tests_count.push_back(suite.second.get_num_tests());
        ++suites_count;
    }

    LTF::LittleTestFramework::output("\nLTF RUNNING ALL " + std::to_string(suites_count) + " TEST SUITE" + (suites_count != 1 ? "S" : "") + ":\n", outs, mode);
    LTF::LittleTestFramework::output(LINE + "\n\n", outs, mode);

    int i = 0;
    int success_total = 0, fail_total = 0;
    for (auto& suite : this->m_suites)
    {
        LTF::LittleTestFramework::output(std::to_string(i + 1) + "." + suite.first + ":\n", outs, mode);

        LTF::LittleTestFramework::output(SPACE + "RUNNING " + std::to_string(tests_count[i]) + " TEST" + (tests_count[i] != 1 ? "S" : "") + " FROM " + suite.first + "\n", outs, mode);
        LTF::LittleTestFramework::output(LINE + "\n", outs, mode);

        // run all and get the tests and times
        int num_test = 0;
        std::map<std::string, double> times;
        auto pass_map = suite.second.run_all(debug, num_test, times);

        // success and fail count
        int count = 1, success_count = 0, fail_count = 0;
        for (const auto& flag : pass_map)
        {
            LTF::LittleTestFramework::output(SPACE + "RUNNING...\n", outs, mode);
            std::string result = SPACE + SPACE + std::to_string(count) + ".TEST NAME:" + flag.first + " ----> ";

            // check timeout first, if timeout then automatically fail
            bool timed = false;
            // make sure the function exists
            assert(times.count(flag.first) > 0);

            // if timed
            if (this->m_times.count(flag.first) > 0)
            {
                // if actual is greater than or equal to expected
                if (this->m_times[flag.first] <= times[flag.first])
                {
                    ++fail_count;
                    result += "[FAIL]";
                    if (debug) result += " AT LINE [" + std::to_string(flag.second.line) + "]";
                    result += "\n" + SPACE + SPACE + SPACE + "TIME LIMIT EXCEEDED: EXPECTED LESS THAN " + std::to_string(m_times[flag.first]) + " NANOSECONDS";
                    timed = true;
                }
            }

            // if not timed, then compare success code
            if (!timed)
            {
                // check success or fail
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
            }

            // output result
            LTF::LittleTestFramework::output(result, outs, mode);

            // output the time
            std::string time_output = "";
            double nanoseconds = times[flag.first];
            LTF::LittleTestFramework::output(std::string(", TIME:") + std::to_string(nanoseconds) + " NANOSECONDS\n", outs, mode);

            // if there's log message then start outputting them
            if (this->m_messages.count(flag.first))
            {
                std::vector<std::string> messages = this->m_messages[flag.first];
                std::string messages_output = "";
                // concat messages
                for (int i = 0; i < messages.size(); ++i) messages_output += SPACE + SPACE + std::to_string(i + 1) + ":" + messages[i] + "\n";
                std::string output_str = "\n" + SPACE + SPACE + std::string("MESSAGE") + (messages.size() != 1 ? "S" : "") + std::string(" FROM:") + flag.first + ":\n" + messages_output;
                LTF::LittleTestFramework::output(output_str, outs, mode);
            }
            ++count;
        }

        // showing total test success and fail
        LTF::LittleTestFramework::output("\nTOTAL:\n", outs, mode);
        if (success_count != 0) LTF::LittleTestFramework::output(SPACE + "(" + std::to_string(success_count) + ") TEST" + (success_count != 1 ? "S" : "") + " SUCCESS\n", outs, mode);
        if (fail_count != 0) LTF::LittleTestFramework::output(SPACE + "(" + std::to_string(fail_count) + ") TEST" + (fail_count != 1 ? "S" : "") + " FAIL\n", outs, mode);

        success_total += success_count;
        fail_total += fail_count;

        LTF::LittleTestFramework::output("\n" + LINE + "\n", outs, mode);
        ++i;
    }

    // showing summary
    LTF::LittleTestFramework::output("\nSUMMARY:\n", outs, mode);
    int total_num_of_test = success_total + fail_total;
    LTF::LittleTestFramework::output(SPACE + "(" + std::to_string(total_num_of_test) + ") TOTAL TEST" + (success_total != 1 ? "S" : "") + " RUN\n", outs, mode);

    if (success_total != 0) LTF::LittleTestFramework::output(SPACE + "(" + std::to_string(success_total) + ") TOTAL TEST" + (success_total != 1 ? "S" : "") + " SUCCESS\n", outs, mode);

    if (fail_total != 0) LTF::LittleTestFramework::output(SPACE + "(" + std::to_string(fail_total) + ") TOTAL TEST" + (fail_total != 1 ? "S" : "") + " FAIL\n", outs, mode);

    LTF::LittleTestFramework::output("\n\n---------------------------------------------THE END OF TEST---------------------------------------------\n\n", outs, mode);

    if (mode == LTF::MODE::FILE) outs.close();
}

void LTF::LittleTestFramework::message(const std::string& function, const std::string& message)
{
    // if the key exists, then get the vector
    if (this->m_messages.count(function) > 0)
    {
        // check if message already exists, same message should not be output twice anyways
        bool exist = std::find(this->m_messages[function].begin(), this->m_messages[function].end(), message) != this->m_messages[function].end();
        if (exist) return;
        // insert if does not exist
        this->m_messages[function].push_back(message);
        return;
    }
    std::vector<std::string> newMessage = {message};
    this->m_messages[function] = newMessage;
}

void LTF::LittleTestFramework::time(const std::string& function, double time_ns)
{
    // if exists, then don't add
    if (this->m_times.count(function) > 0) return;
    // else add
    this->m_times[function] = time_ns;
}