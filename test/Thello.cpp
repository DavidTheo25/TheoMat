#include "gtest/gtest.h"
#include "../include/CTheoMat.cuh"

TEST(General, hello)
{
    Theo::CTheoMat a(2, 2);
    a.hello();
}

TEST(General, set_and_get_values){
    int rows = 2;
    int columns = 3;
    Theo::CTheoMat a(rows, columns);
    for(int i = 0; i < columns; i++){
        for(int j = 0; j < rows; j++){
            a.setValue((float) i+j, i, j);
        }
    }

    std::cout << a.toString() << std::endl;

    for(int i = 0; i < columns; i++){
        for(int j = 0; j < rows; j++){
            ASSERT_EQ(a.getValue(i, j), i+j);
        }
    }
}

TEST(General, copy_ctor){
    int n = 2;
    int m = 3;
    Theo::CTheoMat a(n, m);
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            a.setValue((float) i+j, i, j);
        }
    }

    Theo::CTheoMat b(a);

    std::cout << b.toString() << std::endl;

    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            ASSERT_EQ(a.getValue(i, j), b.getValue(i, j));
        }
    }
}

TEST(General, initializerListCtor){
    Theo::CTheoMat a({{1,2,3},{3,4,5}});
    Theo::CTheoMat b(3,2);
    std::cout << a.toString() << std::endl;
    b(0,0) = 1; b(0, 1) = 2; b(0, 2) = 3;
    b(1,0) = 3; b(1, 1) = 4; b(1, 2) = 5;
    ASSERT_TRUE(a == b);
}

TEST(General, vecCtor){
    std::vector<float> foo = {0, 1, 2};
    ASSERT_TRUE(Theo::CTheoMat({0,1,2}) == Theo::CTheoMat({0,1,2}));
}