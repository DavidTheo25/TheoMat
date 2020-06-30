#include "gtest/gtest.h"
#include "../src/CTheoMat.h"

TEST(General, hello)
{
    Theo::CTheoMat a(2, 2);
    a.hello();
}

TEST(General, set_and_get_values){
    int n = 2;
    int m = 3;
    Theo::CTheoMat a(n, m);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            a.setValue((double) i+j, i, j);
        }
    }

    std::cout << a.toString() << std::endl;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            ASSERT_EQ(a.getValue(i, j), i+j);
        }
    }
}

TEST(General, copy_ctor){
    int n = 2;
    int m = 3;
    Theo::CTheoMat a(n, m);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            a.setValue((double) i+j, i, j);
        }
    }

    Theo::CTheoMat b(a);

    std::cout << b.toString() << std::endl;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            ASSERT_EQ(a.getValue(i, j), b.getValue(i, j));
        }
    }
}