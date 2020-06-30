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

    auto b = a * k;

//    std::cout << a.toString() << std::endl;
//    std::cout << b.toString() << std::endl;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            ASSERT_EQ(b(i, j), a(i, j) * k);
        }
    }
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
    int n = 2;
    int m = 2;
    Theo::CTheoMat a(n, m);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            a(i, j) = (double) i + j;
        }
    }

    auto b = a * a;

    std::cout << a.toString() << std::endl;
    std::cout << b.toString() << std::endl;

    ASSERT_TRUE(a == b);
}