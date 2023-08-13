#ifndef TEST_UTILS_H
#define TEST_UTILS_H
#include "../../includes/LTF.h"

inline LTF::LTFStatus test_utils1()
{
    return LTF::LTFStatus(LTF::SUCCESS, 7);
}

inline LTF::LTFStatus test_utils2()
{
    return LTF::LTFStatus(LTF::FAIL, 12);
}

inline LTF::LTFStatus test_utils3()
{
    int a = 1 + 1;
    if (a == 2) return LTF::LTFStatus(LTF::SUCCESS, 18);
    return LTF::FAIL;
}
#endif