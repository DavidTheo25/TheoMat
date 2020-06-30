#include "gtest/gtest.h"
#include "../src/CTheoMat.h"

TEST(Operations, add_operator){
    int n = 2;
    int m = 3;
    Theo::CTheoMat a(n, m);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            a(i, j) = (double) i + j;
        }
    }

    Theo::CTheoMat b(a);

    Theo::CTheoMat c(a + b);

    std::cout << a.toString() << std::endl;
    std::cout << b.toString() << std::endl;
    std::cout << c.toString() << std::endl;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            ASSERT_EQ(c(i, j), a(i, j) + b(i, j));
        }
    }
}

TEST(Operations, sub_operator){
    int n = 2;
    int m = 3;
    Theo::CTheoMat a(n, m);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            a(i, j) = (double) i + j;
        }
    }

    Theo::CTheoMat b(a);

    Theo::CTheoMat c(a - b);

    std::cout << a.toString() << std::endl;
    std::cout << b.toString() << std::endl;
    std::cout << c.toString() << std::endl;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            ASSERT_EQ(c(i, j), a(i, j) - b(i, j));
        }
    }
}

TEST(Operations, transpose){
    int n = 2;
    int m = 3;
    Theo::CTheoMat a(n, m);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            a.setValue((double) i+j, i, j);
        }
    }

    auto b = a.transpose();

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            ASSERT_EQ(a(i, j), b(j, i));
        }
    }

    std::cout << a.toString() << std::endl;
    std::cout << b.toString() << std::endl;

}