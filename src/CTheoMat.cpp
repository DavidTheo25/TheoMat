#include "CTheoMat.h"

#include <iostream>

void Theo::CTheoMat::hello() {
    std::cout << "Hello I am the theo's custom matrix library" << std::endl;
}

Theo::CTheoMat::CTheoMat(int _n, int _m): n(_n), m(_m) {
    mat = new double*[n];
    for (int i = 0; i < n; i++){
        mat[i] = new double[m];
    }
}

Theo::CTheoMat::~CTheoMat() {
    for (int i = 0; i < n; i++){
        delete[] mat[i];
    }
    delete [] mat;
}

Theo::CTheoMat::CTheoMat(Theo::CTheoMat &matrix) {

    for(int i = 0; i < n; i++){
        for(int j = 0; j < 0; j++){

        }
    }
}
