#include "gtest/gtest.h"
#include "../src/CTheoMat.h"

TEST(General, hello)
{
    Theo::CTheoMat a(2, 2);
    a.hello();
}