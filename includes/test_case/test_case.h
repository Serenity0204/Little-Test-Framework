#ifndef TEST_CASE_H
#define TEST_CASE_H
#pragma once

#include <chrono>
#include <functional>
#include <string>

namespace LTF
{
    // success code
    enum LTFCode
    {
        FAIL = 0,
        SUCCESS = 1,
    };

    // status struct that will record the success code and line number
    struct LTFStatus
    {
    public:
        std::size_t line;
        LTFCode code;
        LTFStatus(LTFCode code = LTFCode::FAIL, std::size_t line = 0)
        {
            this->line = line;
            this->code = code;
        }
        ~LTFStatus() {}
    };

    class TestCase
    {
    private:
        std::string m_test_name;
        LTFStatus (*m_function)(bool debug);

        // Function to time other function, in unit of nanoseconds
        inline std::chrono::duration<double, std::nano> m_time()
        {
            // Start the timer
            auto start = std::chrono::high_resolution_clock::now();

            // Call the input function in debug = false
            m_function(false);

            // Stop the timer
            auto end = std::chrono::high_resolution_clock::now();

            // Calculate the elapsed time in milliseconds
            return end - start;
        }

    public:
        // CTORS
        TestCase();
        TestCase(const std::string& name, LTFStatus (*function)(bool debug));
        ~TestCase();

        // call the function
        LTFStatus run(bool debug, double& time);

        // getters and setters
        void set_test_name(const std::string& name);
        void set_test_function(LTFStatus (*function)(bool debug));
        inline const std::string& get_test_name() const { return this->m_test_name; }
    };
};
#endif // TEST_CASE_H
