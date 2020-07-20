#include "CTheoMat.h"
#include <iostream>
#include <random>

void Theo::CTheoMat::hello() {
    std::cout << "Hello I am the theo's custom matrix library, WIP" << std::endl;
}

double** Theo::CTheoMat::initMat() const {
    auto matTemp = new double*[n];
    for (int i = 0; i < n; i++){
        matTemp[i] = new double[m];
        for(int j = 0; j < m; j++){
            matTemp[i][j] = 0;
        }
    }
    return matTemp;
}

Theo::CTheoMat::CTheoMat(): n(0), m(0), mat(initMat()) {}

Theo::CTheoMat::CTheoMat(int _n, int _m): n(_n), m(_m), mat(initMat()) {}

Theo::CTheoMat::CTheoMat(const Theo::CTheoMat& matrix): n(matrix.getN()), m(matrix.getM()), mat(initMat()) {
    // deep copy, maybe not the best way to do it
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            mat[i][j] = matrix.getValue(i, j);
        }
    }
}

Theo::CTheoMat::CTheoMat(std::initializer_list<std::initializer_list<double>> initList) {
    n = initList.size();
    m = initList.begin()->size();
    mat = initMat();
    int i = 0, j = 0;
    for(auto & row : initList) {
        if(row.size() != m) {
            throw std::out_of_range("invalid initialisation list size");
        }
        for(auto & value : row){
            mat[i][j] = value;
            j++;
        }
        j = 0;
        i++;
    }
}

Theo::CTheoMat::CTheoMat(std::vector<std::vector<double>> initVec) {
    n = initVec.size();
    m = initVec.begin()->size();
    mat = initMat();
    int i = 0, j = 0;
    for(auto & row : initVec) {
        if(row.size() != m) {
            throw std::out_of_range("invalid initialisation vector size");
        }
        for(auto & value : row){
            mat[i][j] = value;
            j++;
        }
        j = 0;
        i++;
    }
}

/**
 * Creates a one line matrix with the given vector
 * @param initVect
 */
Theo::CTheoMat::CTheoMat(std::vector<double> initVect) {
    n = 1;
    m = initVect.size();
    mat = initMat();
    int i = 0;
    for(auto & value : initVect){
        mat[0][i] = value;
        i++;
    }
}

/**
 * Creates a matrix with just one line using the given values
 * @param values
 * @param size
 */
Theo::CTheoMat::CTheoMat(double *values, int size): n(1), m(size), mat(initMat()){
    for(int i = 0; i < m; i++){
        mat[0][i] = values[i];
    }
}


void Theo::CTheoMat::freeMat() {
    for (int i = 0; i < n; i++){
        delete[] mat[i];
    }
    delete [] mat;
}

Theo::CTheoMat::~CTheoMat() {
    freeMat();
}

double Theo::CTheoMat::getValue(int i, int j) const {
    if(i >= 0 && i < n && j >= 0 && j < m) {
        return (double) mat[i][j];
    }
    throw std::out_of_range("i and/or j out of matrix range");
}

void Theo::CTheoMat::setValue(double value, int i, int j) {
    if(i >= 0 && i < n && j >= 0 && j < m){
        mat[i][j] = value;
    }
}

void Theo::CTheoMat::random() {
    std::random_device r;
    std::default_random_engine e1(r());
    std::uniform_real_distribution<double> uniformDist(0,1);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            mat[i][j] = uniformDist(e1);
        }
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

bool Theo::CTheoMat::checkDim(const Theo::CTheoMat &matrix) const {
    return n == matrix.getN() && m == matrix.getM();
}

Theo::CTheoMat & Theo::CTheoMat::operator=(const Theo::CTheoMat &matrix) {
    if(this != &matrix){
        freeMat();
        n = matrix.getN();
        m = matrix.getM();
        mat = new double*[n];
        for (int i = 0; i < n; i++){
            mat[i] = new double[m];
            for(int j = 0; j < m; j++){
                mat[i][j] = matrix(i, j);
            }
        }
    }
    return *this;
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
    std::string errorMessage = "cannot add matrices of different sizes (" + std::to_string(n) + ", "
            + std::to_string(m) + ") and (" + std::to_string(matrix.getN()) + ", "
            + std::to_string(matrix.getM()) + ")\n";
    throw std::out_of_range(errorMessage);
}

Theo::CTheoMat & Theo::CTheoMat::operator+=(const Theo::CTheoMat &matrix) {
    *this = *this + matrix;
    return *this;
}

Theo::CTheoMat Theo::CTheoMat::operator-(const Theo::CTheoMat& matrix) {
    if(checkDim(matrix)) {
        CTheoMat result(n, m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                result.setValue(matrix.getValue(i, j) - mat[i][j], i, j);
            }
        }
        return result;
    }
    std::string errorMessage = "cannot subtract matrices of different sizes (" + std::to_string(n) + ", "
                               + std::to_string(m) + ") and (" + std::to_string(matrix.getN()) + ", "
                               + std::to_string(matrix.getM()) + ")\n";
    throw std::out_of_range(errorMessage);
}

Theo::CTheoMat Theo::CTheoMat::operator*(const Theo::CTheoMat &matrix) const {
    if(m == matrix.getN()) {
        CTheoMat result(n, matrix.getM());
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < matrix.getM(); j++) {
                for(int k = 0; k < m; k++){
                    result(i, j) += mat[i][k] * matrix.getValue(k, j);
                }
            }
        }
        return result;
    }
    std::string errorMessage = "cannot multiply incompatible matrices. first one has " + std::to_string(m) +
            " columns while second one has " + std::to_string(matrix.getN()) + " rows \n";
    throw std::out_of_range(errorMessage);

}

Theo::CTheoMat Theo::CTheoMat::operator*(double k) const {
    CTheoMat result(n, m);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            result(i,j) = mat[i][j] * k;
        }
    }
    return result;
}

Theo::CTheoMat Theo::CTheoMat::operator/(double k) const {
    CTheoMat result(n, m);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            result(i,j) = mat[i][j] / k;
        }
    }
    return result;
}

/*
 * returns a copy and not the actual line
 */
Theo::CTheoMat Theo::CTheoMat::operator[](int i) {
    if(i >= n){
        throw std::out_of_range("line out of matrix range");
    }
    return CTheoMat(mat[i], m);
}

double &Theo::CTheoMat::operator()(int i, int j) {
    if(i >= 0 && i < n && j >= 0 && j < m) {
        return mat[i][j];
    }
    throw std::out_of_range("i or j is out of the matrix range");
}

double &Theo::CTheoMat::operator()(int &i, int &j) const {
    if(i >= 0 && i < n && j >= 0 && j < m) {
        return mat[i][j];
    }
    throw std::out_of_range("i or j is out of the matrix range");
}

bool Theo::CTheoMat::operator==(const Theo::CTheoMat &matrix) const {
    if(n != matrix.getN() || m != matrix.getM()){
        return false;
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(mat[i][j] != matrix(i, j)){
                return false;
            }
        }
    }
    return true;
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

Theo::CTheoMat Theo::CTheoMat::identity(int size) {
    CTheoMat id(size, size);
    for(int i = 0; i < size; i++){
        id(i, i) = 1;
    }
    return id;
}

Theo::CTheoMat Theo::operator*(const double k, const Theo::CTheoMat &matrix) {
    return matrix * k;
}
