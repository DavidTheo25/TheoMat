#ifndef THEOMAT_CTHEOMAT_CUH
#define THEOMAT_CTHEOMAT_CUH

#include <vector>
#include <string>


namespace Theo {

    class CTheoMat {
    public:
        int rows, columns;
        float* mat;

        CTheoMat();
        CTheoMat(int rows_, int columns_);
        CTheoMat(const CTheoMat& matrix);
        CTheoMat(std::initializer_list<std::initializer_list<float>> initList);
        CTheoMat(std::vector<std::vector<float>> initList);
        CTheoMat(std::vector<float> initVect);
        CTheoMat(float* values, int size);
        ~CTheoMat();

        static CTheoMat identity(int n);

        void hello();
        float getValue(int i, int j) const;
        void setValue(float value, int i, int j);
        void random();
        int getRows() const;
        int getColumns() const;
        std::string toString();
        CTheoMat transpose();
        bool checkDim(const CTheoMat& matrix) const;

        CTheoMat & operator=(const CTheoMat& matrix);
        CTheoMat operator+(const CTheoMat& matrix);
        CTheoMat & operator+=(const CTheoMat& matrix);
        CTheoMat operator-(const CTheoMat& matrix);
        CTheoMat operator*(const CTheoMat& matrix) const;
        CTheoMat operator*(float k) const;
        CTheoMat operator/(float k) const;
        float& operator[](int i);
        float& operator[](int& i) const;
        friend CTheoMat operator*(const float k, const CTheoMat& matrix);
        float& operator()(int i, int j);
        float& operator()(int& i, int& j) const;
        bool operator==(const CTheoMat& matrix) const;


    private:


        float* initMat() const;
        void freeMat();
    };

}
#endif //THEOMAT_CTHEOMAT_CUH
