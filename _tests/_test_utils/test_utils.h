#ifndef TEST_UTILS_H
#define TEST_UTILS_H
#include "../../includes/LTF.h"

inline LTF::LTFCode test_utils1()
{
    return LTF::SUCCESS;
}

inline LTF::LTFCode test_utils2()
{
    return LTF::FAIL;
}

inline LTF::LTFCode test_utils3()
{
    int a = 1 + 1;
    if (a == 2) return LTF::SUCCESS;
    return LTF::FAIL;
}
#endif