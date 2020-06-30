#include "CTheoMat.h"

#include <iostream>

void Theo::CTheoMat::hello() {
    std::cout << "Hello I am the theo's custom matrix library" << std::endl;
}

double** Theo::CTheoMat::initMat() {
    auto matTemp = new double*[n];
    for (int i = 0; i < n; i++){
        matTemp[i] = new double[m];
    }
    return matTemp;
}

Theo::CTheoMat::CTheoMat(int _n, int _m): n(_n), m(_m), mat(initMat()) {}

Theo::CTheoMat::CTheoMat(const Theo::CTheoMat& matrix): n(matrix.getN()), m(matrix.getM()), mat(initMat()) {
    // deep copy, maybe not the best way to do it
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            mat[i][j] = matrix.getValue(i, j);
        }
    }
}


Theo::CTheoMat::~CTheoMat() {
    for (int i = 0; i < n; i++){
        delete[] mat[i];
    }
    delete [] mat;
}

double Theo::CTheoMat::getValue(int i, int j) const {
    return (double) mat[i][j];
}

void Theo::CTheoMat::setValue(double value, int i, int j) {
    if(i >= 0 && i < n && j >= 0 && j < m){
        mat[i][j] = value;
    }
}

int Theo::CTheoMat::getN() const {return n;}

int Theo::CTheoMat::getM() const {return m;}

std::string Theo::CTheoMat::toString() {
    std::string s = "[";
    for(int i = 0; i < n; i++){
        s += "[";
        for(int j = 0; j < m-1; j++){
            s += std::to_string(mat[i][j]); s += ", ";
        }
        s += std::to_string(mat[i][m-1]);
        s += "]";
        if(i != n-1){s += "\n";}
    }
    s += "]";
    return s;
}

bool Theo::CTheoMat::checkDim(const Theo::CTheoMat &matrix) {
    return n == matrix.getN() && m == matrix.getM();
}

Theo::CTheoMat Theo::CTheoMat::operator+(const Theo::CTheoMat& matrix) {
    if(checkDim(matrix)){
        CTheoMat result(n, m);
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                result.setValue(matrix.getValue(i, j) + mat[i][j], i,j);
            }
        }
        return result;
    }
    std::cerr << "dimensions don't match" << std::endl;
//    TODO make this throw an exception, same goes for minus op
    return matrix;
}

Theo::CTheoMat Theo::CTheoMat::operator-(const Theo::CTheoMat& matrix) {
    CTheoMat result(n, m);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            result.setValue(matrix.getValue(i, j) - mat[i][j], i,j);
        }
    }
    return result;
}

Theo::CTheoMat Theo::CTheoMat::transpose() {
    CTheoMat transpose(m, n);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            transpose.setValue(mat[i][j], j, i);
        }
    }
    return transpose;
}
