#include "gtest/gtest.h"
#include "../include/CTheoMat.cuh"

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

TEST(General, initializerListCtor){
    Theo::CTheoMat a({{1,2,3},{3,4,5}});
    Theo::CTheoMat b(2,3);
    b(0,0) = 1; b(0, 1) = 2; b(0, 2) = 3;
    b(1,0) = 3; b(1, 1) = 4; b(1, 2) = 5;
    ASSERT_TRUE(a == b);
}

TEST(General, vecCtor){
    std::vector<double> foo = {0, 1, 2};
    ASSERT_TRUE(Theo::CTheoMat({0,1,2}) == Theo::CTheoMat({0,1,2}));
}