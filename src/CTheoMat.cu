#include "CTheoMat.cuh"
#include <iostream>
#include <random>
#include <cublas_v2.h>


void Theo::CTheoMat::hello() {
    std::cout << "Hello I am the theo's custom matrix library, WIP" << std::endl;
}

float* Theo::CTheoMat::initMat() const {
    auto matTemp = new float[rows * columns];
//    float* matTemp;
//    cudaMallocManaged(&matTemp, rows * columns * sizeof(float));
    for (int i = 0; i < rows * columns ; i++){
            matTemp[i] = 0;
    }
    return matTemp;
}

Theo::CTheoMat::CTheoMat(): rows(0), columns(0), mat(initMat()) {}

Theo::CTheoMat::CTheoMat(int rows_, int columns_): rows(rows_), columns(columns_), mat(initMat()) {}

Theo::CTheoMat::CTheoMat(const Theo::CTheoMat& matrix): rows(matrix.getRows()), columns(matrix.getColumns()), mat(initMat()) {
    // deep copy, maybe not the best way to do it
    for(int i = 0; i < rows * columns; i++){
        mat[i] = matrix[i];
    }
}

Theo::CTheoMat::CTheoMat(std::initializer_list<std::initializer_list<float>> initList) {
    columns = initList.size();
    rows = initList.begin()->size();
    mat = initMat();
    int i = 0, j = 0;
    for(auto & column : initList) {
        if(column.size() != rows) {
            throw std::out_of_range("invalid initialisation list size");
        }
        for(auto & value : column){
            mat[i * rows + j] = value;
            j++;
        }
        j = 0;
        i++;
    }
}

Theo::CTheoMat::CTheoMat(std::vector<std::vector<float>> initVec) {
    columns = initVec.size();
    rows = initVec.begin()->size();
    mat = initMat();
    int i = 0, j = 0;
    for(auto & column : initVec) {
        if(column.size() != rows) {
            throw std::out_of_range("invalid initialisation list size");
        }
        for(auto & value : column){
            mat[i * rows + j] = value;
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
Theo::CTheoMat::CTheoMat(std::vector<float> initVect) {
    columns = 1;
    rows = initVect.size();
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
Theo::CTheoMat::CTheoMat(float *values, int size): rows(size), columns(1), mat(initMat()){
    for(int i = 0; i < columns; i++){
        mat[i] = values[i];
    }
}


void Theo::CTheoMat::freeMat() {
    delete [] mat;
//    cudaFree(mat);
}

Theo::CTheoMat::~CTheoMat() {
    freeMat();
}

float Theo::CTheoMat::getValue(int i, int j) const {
    if(i >= 0 && i < columns && j >= 0 && j < rows) {
        return (float) mat[i * rows + j];
    }
    throw std::out_of_range("i and/or j out of matrix range");
}

void Theo::CTheoMat::setValue(float value, int i, int j) {
    if(i >= 0 && i < columns && j >= 0 && j < rows){
        mat[i * rows + j] = value;
    }
}

void Theo::CTheoMat::random() {
    //this could be done with curand
    std::random_device r;
    std::default_random_engine e1(r());
    std::uniform_real_distribution<float> uniformDist(0,1);
    for(int i = 0; i < rows * columns; i++){
        mat[i] = uniformDist(e1);
    }
}

int Theo::CTheoMat::getRows() const {return rows;}

int Theo::CTheoMat::getColumns() const {return columns;}

std::string Theo::CTheoMat::toString() {
    std::string s = "[";
    for (int j = 0; j < rows; j++){
        s += "[";
        for (int i = 0; i < columns - 1; i++){
            s += std::to_string(mat[i * rows + j]) + ", ";
        }
        s += std::to_string(mat[(columns - 1) * rows + j]);
        s += "]\n";
    }
    s.pop_back();
    s += "]\n";
    return s;
}

bool Theo::CTheoMat::checkDim(const Theo::CTheoMat &matrix) const {
    return rows == matrix.getRows() && columns == matrix.getColumns();
}

Theo::CTheoMat & Theo::CTheoMat::operator=(const Theo::CTheoMat &matrix) {
    if(this != &matrix){
        freeMat();
        rows = matrix.getRows();
        columns = matrix.getColumns();
        mat = new float[rows * columns];
//        cudaMallocManaged(&mat, rows * columns * sizeof(float));
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
                               + std::to_string(columns) + ") and (" + std::to_string(matrix.getRows()) + ", "
                               + std::to_string(matrix.getColumns()) + ")\n";
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
                               + std::to_string(columns) + ") and (" + std::to_string(matrix.getRows()) + ", "
                               + std::to_string(matrix.getColumns()) + ")\n";
    throw std::out_of_range(errorMessage);
}

Theo::CTheoMat Theo::CTheoMat::operator*(const Theo::CTheoMat &matrix) const {
    // very slow implementation ...
    int M = rows;
    int N = matrix.getColumns();
    int K = columns;
    if(columns == matrix.getRows()) {
        CTheoMat result(M, N);

        // Pre-calculate the size (in bytes) of our matrices
        const size_t bytes_a = M * K * sizeof(float);
        const size_t bytes_b = K * N * sizeof(float);
        const size_t bytes_c = M * N * sizeof(float);

        // Allocate device memory
        float *d_a, *d_b, *d_c;
        cudaMalloc(&d_a, bytes_a);
        cudaMalloc(&d_b, bytes_b);
        cudaMalloc(&d_c, bytes_c);

        cudaMemcpy(d_a, mat, bytes_a, cudaMemcpyHostToDevice);
        cudaMemcpy(d_b, matrix.mat, bytes_b, cudaMemcpyHostToDevice);
        cudaMemcpy(d_c, result.mat, bytes_c, cudaMemcpyHostToDevice);

        // cuBLAS handle
        cublasHandle_t handle;
        cublasCreate(&handle);

        // Scalaing factors
        float alpha = 1.0f;
        float beta = 0.0f;

        // Calculate: c = (alpha*a) * b + (beta*c)
        // MxN = MxK * KxN
        // Signature: handle, operation, operation, M, N, K, alpha, A, lda, B, ldb,
        // beta, C, ldc
        cublasSgemm(handle, CUBLAS_OP_N, CUBLAS_OP_N, M, N, K, &alpha, d_a, M, d_b, K,
                    &beta, d_c, M);

        cudaMemcpy(result.mat, d_c, bytes_c, cudaMemcpyDeviceToHost);

        cudaFree(d_a);
        cudaFree(d_b);
        cudaFree(d_c);

        return result;

    }
    std::string errorMessage = "cannot multiply incompatible matrices. first one has " + std::to_string(columns) +
                               " columns while second one has " + std::to_string(matrix.getRows()) + " rows \n";
    throw std::out_of_range(errorMessage);

}

Theo::CTheoMat Theo::CTheoMat::operator*(float k) const {
    CTheoMat result(rows, columns);
    for(int i = 0; i < rows * columns; i++){
            result[i] = mat[i] * k;
    }
    return result;
}

Theo::CTheoMat Theo::CTheoMat::operator/(float k) const {
    CTheoMat result(rows, columns);
    for(int i = 0; i < rows * columns; i++){
        result[i] = mat[i] / k;
    }
    return result;
}

float& Theo::CTheoMat::operator[](int i) {
    if(i >= rows * columns){
        throw std::out_of_range("out of matrix range");
    }
    return mat[i];
}

float& Theo::CTheoMat::operator[](int& i) const {
    if(i >= rows * columns){
        throw std::out_of_range("out of matrix range");
    }
    return mat[i];
}

float &Theo::CTheoMat::operator()(int i, int j) {
    if(i >= 0 && i < columns && j >= 0 && j < rows) {
        return mat[i * rows + j];
    }
    throw std::out_of_range("i or j is out of the matrix range");
}

float &Theo::CTheoMat::operator()(int &i, int &j) const {
    if(i >= 0 && i < columns && j >= 0 && j < rows) {
        return mat[i * rows + j];
    }
    throw std::out_of_range("i or j is out of the matrix range");
}

bool Theo::CTheoMat::operator==(const Theo::CTheoMat &matrix) const {
    if(rows != matrix.getRows() || columns != matrix.getColumns()){
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
    for(int i = 0; i < columns; i++){
        for(int j = 0; j < rows; j++){
            transpose(j, i) = mat[i * rows + j];
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

Theo::CTheoMat Theo::operator*(const float k, const Theo::CTheoMat &matrix) {
    return matrix * k;
}
