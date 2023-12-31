#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#pragma once
#include "../../includes/LTF.h"
#include <cstdio> // For std::remove

inline LTF::LTFStatus test_utils1(bool debug = false)
{
    return LTF::LTFStatus(LTF::SUCCESS, __LINE__);
}

inline LTF::LTFStatus test_utils2(bool debug = false)
{
    return LTF::LTFStatus(LTF::FAIL, __LINE__);
}

inline LTF::LTFStatus test_utils3(bool debug = false)
{
    int a = 1 + 1;
    if (a == 2) return LTF::LTFStatus(LTF::SUCCESS, __LINE__);
    return LTF::LTFStatus(LTF::FAIL, __LINE__);
}

inline void delete_file(const std::string& path)
{
    std::remove(path.c_str());
}
#endif