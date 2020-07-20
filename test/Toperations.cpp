#include "gtest/gtest.h"
#include "../include/CTheoMat.h"

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

    auto c = a + b;

//    std::cout << a.toString() << std::endl;
//    std::cout << b.toString() << std::endl;
//    std::cout << c.toString() << std::endl;

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

    auto c = b - a;

//    std::cout << a.toString() << std::endl;
//    std::cout << b.toString() << std::endl;
//    std::cout << c.toString() << std::endl;

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
            a(i, j) = (double) i + j;
        }
    }

    auto b = a.transpose();

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            ASSERT_EQ(a(i, j), b(j, i));
        }
    }

//    std::cout << a.toString() << std::endl;
//    std::cout << b.toString() << std::endl;
}

TEST(Operations, multKOperator){
    int n = 2;
    int m = 3;
    Theo::CTheoMat a(n, m);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            a(i, j) = (double) i + j;
        }
    }

    double k = 2.8;

    auto b =  k * a * k;

//    std::cout << a.toString() << std::endl;
//    std::cout << b.toString() << std::endl;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            ASSERT_EQ(b(i, j), a(i, j) * k * k);
        }
    }
}

TEST(Operations, divideOperator){
    int n = 2;
    int m = 3;
    Theo::CTheoMat a(n, m);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            a(i, j) = (double) i + j;
        }
    }

    double k = 2.8;

    auto b =  a / k;


    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            ASSERT_EQ(b(i, j), a(i, j) / k);
        }
    }
    std::cout << a.toString() << std::endl;
    a = a / 1.0;
    std::cout << a.toString() << std::endl;
}

TEST(Operations, multMatOperator_id){
    int n = 2;
    int m = 3;
    Theo::CTheoMat a(n, m);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            a(i, j) = (double) i + j;
        }
    }

    auto idMat = Theo::CTheoMat::identity(m);

    auto b = a * idMat;

//    std::cout << idMat.toString() << std::endl;
//    std::cout << a.toString() << std::endl;
//    std::cout << b.toString() << std::endl;

    ASSERT_TRUE(a == b);
}

TEST(Operations, multMatOperator){
    Theo::CTheoMat a({{0, -1, 2}, {1, -2, 3}});
    Theo::CTheoMat b({{1,2},{0,-1}, {-2,3}});

    auto c = a * b;

    ASSERT_TRUE(c == Theo::CTheoMat({{-4, 7}, {-5, 13}}));
}

TEST(Operations, idx){
    Theo::CTheoMat a({{0, -1, 2}, {1, -2, 3}});
//    std::cout << a.toString() << std::endl;
//    std::cout << a.getM() << std::endl;
//    std::cout << a[1].toString() << std::endl;
    ASSERT_TRUE(a[1] == Theo::CTheoMat({{1, -2, 3}}));
}

TEST(Operations, random){
    Theo::CTheoMat a(4,5);
    a.random();
    auto b = a;
    a.random();
    ASSERT_FALSE(a == b);
}