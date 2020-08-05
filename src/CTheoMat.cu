#include "CTheoMat.cuh"
#include <iostream>
#include <random>
#include <cublas_v2.h>


void Theo::CTheoMat::hello() {
    std::cout << "Hello I am the theo's custom matrix library, WIP" << std::endl;
}

double* Theo::CTheoMat::initMat() const {
    auto matTemp = new double[rows * columns];
    for (int i = 0; i < rows * columns ; i++){
            matTemp[i] = 0;
    }
    return matTemp;
}

Theo::CTheoMat::CTheoMat(): rows(0), columns(0), mat(initMat()) {}

Theo::CTheoMat::CTheoMat(int rows_, int columns_): rows(rows_), columns(columns_), mat(initMat()) {}

Theo::CTheoMat::CTheoMat(const Theo::CTheoMat& matrix): rows(matrix.getN()), columns(matrix.getM()), mat(initMat()) {
    // deep copy, maybe not the best way to do it
    for(int i = 0; i < rows * columns; i++){
        mat[i] = matrix[i];
    }
}

Theo::CTheoMat::CTheoMat(std::initializer_list<std::initializer_list<double>> initList) {
    rows = initList.size();
    columns = initList.begin()->size();
    mat = initMat();
    int i = 0, j = 0;
    for(auto & row : initList) {
        if(row.size() != columns) {
            throw std::out_of_range("invalid initialisation list size");
        }
        for(auto & value : row){
            mat[i * columns + j] = value;
            j++;
        }
        j = 0;
        i++;
    }
}

Theo::CTheoMat::CTheoMat(std::vector<std::vector<double>> initVec) {
    rows = initVec.size();
    columns = initVec.begin()->size();
    mat = initMat();
    int i = 0, j = 0;
    for(auto & row : initVec) {
        if(row.size() != columns) {
            throw std::out_of_range("invalid initialisation vector size");
        }
        for(auto & value : row){
            mat[i * columns + j] = value;
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
    rows = 1;
    columns = initVect.size();
    mat = initMat();
    int i = 0;
    for(auto & value : initVect){
        mat[i] = value;
        i++;
    }
}

/**
 * Creates a matrix with just one line using the given values
 * @param values
 * @param size
 */
Theo::CTheoMat::CTheoMat(double *values, int size): rows(1), columns(size), mat(initMat()){
    for(int i = 0; i < columns; i++){
        mat[i] = values[i];
    }
}


void Theo::CTheoMat::freeMat() {
    delete [] mat;
}

Theo::CTheoMat::~CTheoMat() {
    freeMat();
}

double Theo::CTheoMat::getValue(int i, int j) const {
    if(i >= 0 && i < rows && j >= 0 && j < columns) {
        return (double) mat[i * columns + j];
    }
    throw std::out_of_range("i and/or j out of matrix range");
}

void Theo::CTheoMat::setValue(double value, int i, int j) {
    if(i >= 0 && i < rows && j >= 0 && j < columns){
        mat[i * columns + j] = value;
    }
}

void Theo::CTheoMat::random() {
    std::random_device r;
    std::default_random_engine e1(r());
    std::uniform_real_distribution<double> uniformDist(0,1);
    for(int i = 0; i < rows * columns; i++){
        mat[i] = uniformDist(e1);
    }
}

int Theo::CTheoMat::getN() const {return rows;}

int Theo::CTheoMat::getM() const {return columns;}

std::string Theo::CTheoMat::toString() {
    std::string s = "[";
    for(int i = 0; i < rows; i++){
        s += "[";
        for(int j = 0; j < columns - 1; j++){
            s += std::to_string(mat[i * columns + j]); s += ", ";
        }
        s += std::to_string(mat[i * columns + columns - 1]);
        s += "]";
        if(i != rows - 1){ s += "\n";}
    }
    s += "]";
    return s;
}

bool Theo::CTheoMat::checkDim(const Theo::CTheoMat &matrix) const {
    return rows == matrix.getN() && columns == matrix.getM();
}

Theo::CTheoMat & Theo::CTheoMat::operator=(const Theo::CTheoMat &matrix) {
    if(this != &matrix){
        freeMat();
        rows = matrix.getN();
        columns = matrix.getM();
        mat = new double[rows * columns];
        for (int i = 0; i < rows * columns; i++){
            mat[i] = matrix[i];
        }
    }
    return *this;
}

Theo::CTheoMat Theo::CTheoMat::operator+(const Theo::CTheoMat& matrix) {
    if(checkDim(matrix)){
        CTheoMat result(rows, columns);
        for(int i = 0; i < rows * columns; i++){
            result[i] = mat[i] + matrix[i];
        }
        return result;
    }
    std::string errorMessage = "cannot add matrices of different sizes (" + std::to_string(rows) + ", "
                               + std::to_string(columns) + ") and (" + std::to_string(matrix.getN()) + ", "
                               + std::to_string(matrix.getM()) + ")\n";
    throw std::out_of_range(errorMessage);
}

Theo::CTheoMat & Theo::CTheoMat::operator+=(const Theo::CTheoMat &matrix) {
    *this = *this + matrix;
    return *this;
}

Theo::CTheoMat Theo::CTheoMat::operator-(const Theo::CTheoMat& matrix) {
    if(checkDim(matrix)) {
        CTheoMat result(rows, columns);
        for (int i = 0; i < rows * columns; i++) {
            result[i] = mat[i] - matrix[i];
        }
        return result;
    }
    std::string errorMessage = "cannot subtract matrices of different sizes (" + std::to_string(rows) + ", "
                               + std::to_string(columns) + ") and (" + std::to_string(matrix.getN()) + ", "
                               + std::to_string(matrix.getM()) + ")\n";
    throw std::out_of_range(errorMessage);
}

Theo::CTheoMat Theo::CTheoMat::operator*(const Theo::CTheoMat &matrix) const {
    // very slow implementation ...
    if(columns == matrix.getN()) {
        CTheoMat result(rows, matrix.getM());
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < matrix.getM(); j++) {
                auto s = 0;
                for(int k = 0; k < columns; k++){
                    s += mat[i * columns + k] * matrix(k, j);
                }
                result(i, j) = s;
            }
        }
        return result;
    }
    std::string errorMessage = "cannot multiply incompatible matrices. first one has " + std::to_string(columns) +
                               " columns while second one has " + std::to_string(matrix.getN()) + " rows \n";
    throw std::out_of_range(errorMessage);

}

Theo::CTheoMat Theo::CTheoMat::operator*(double k) const {
    CTheoMat result(rows, columns);
    for(int i = 0; i < rows * columns; i++){
            result[i] = mat[i] * k;
    }
    return result;
}

Theo::CTheoMat Theo::CTheoMat::operator/(double k) const {
    CTheoMat result(rows, columns);
    for(int i = 0; i < rows * columns; i++){
        result[i] = mat[i] / k;
    }
    return result;
}

double& Theo::CTheoMat::operator[](int i) {
    if(i >= rows * columns){
        throw std::out_of_range("out of matrix range");
    }
    return mat[i];
}

double& Theo::CTheoMat::operator[](int& i) const {
    if(i >= rows * columns){
        throw std::out_of_range("out of matrix range");
    }
    return mat[i];
}

double &Theo::CTheoMat::operator()(int i, int j) {
    if(i >= 0 && i < rows && j >= 0 && j < columns) {
        return mat[i * columns + j];
    }
    throw std::out_of_range("i or j is out of the matrix range");
}

double &Theo::CTheoMat::operator()(int &i, int &j) const {
    if(i >= 0 && i < rows && j >= 0 && j < columns) {
        return mat[i * columns + j];
    }
    throw std::out_of_range("i or j is out of the matrix range");
}

bool Theo::CTheoMat::operator==(const Theo::CTheoMat &matrix) const {
    if(rows != matrix.getN() || columns != matrix.getM()){
        return false;
    }
    for(int i = 0; i < rows * columns; i++){
        if(mat[i] != matrix[i]){
            return false;
        }
    }
    return true;
}

Theo::CTheoMat Theo::CTheoMat::transpose() {
    CTheoMat transpose(columns, rows);
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            transpose(j, i) = mat[i * columns + j];
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
