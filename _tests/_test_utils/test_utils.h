#ifndef TEST_UTILS_H
#define TEST_UTILS_H
#include "../../includes/LTF.h"

inline LTF::LTFStatus test_utils1()
{
    return LTF::LTFStatus(LTF::SUCCESS, __LINE__);
}

inline LTF::LTFStatus test_utils2()
{
    return LTF::LTFStatus(LTF::FAIL, __LINE__);
}

inline LTF::LTFStatus test_utils3()
{
    int a = 1 + 1;
    if (a == 2) return LTF::LTFStatus(LTF::SUCCESS, __LINE__);
    return LTF::FAIL;
}
#endif