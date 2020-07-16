#ifndef THEOMAT_CTHEOMAT_H
#define THEOMAT_CTHEOMAT_H

#include <vector>
#include <string>


namespace Theo {

    class CTheoMat {
    public:
        CTheoMat();
        CTheoMat(int n, int m);
        CTheoMat(const CTheoMat& matrix);
        CTheoMat(std::initializer_list<std::initializer_list<double>> initList);
        CTheoMat(std::vector<std::vector<double>> initList);
        CTheoMat(std::vector<double> initVect);
        CTheoMat(double* values, int size);
        ~CTheoMat();

        static CTheoMat identity(int n);

        void hello();
        double getValue(int i, int j) const;
        void setValue(double value, int i, int j);
        int getN() const;
        int getM() const;
        std::string toString();
        CTheoMat transpose();
        bool checkDim(const CTheoMat& matrix) const;

        CTheoMat & operator=(const CTheoMat& matrix);
        CTheoMat operator+(const CTheoMat& matrix);
        CTheoMat & operator+=(const CTheoMat& matrix);
        CTheoMat operator-(const CTheoMat& matrix);
        CTheoMat operator*(const CTheoMat& matrix) const;
        CTheoMat operator*(double k) const;
        CTheoMat operator[](int i);
        friend CTheoMat operator*(const double k, const CTheoMat& matrix);
        double& operator()(int i, int j);
        double& operator()(int& i, int& j) const;
        bool operator==(const CTheoMat& matrix) const;


    private:
        int n, m;
        double** mat;

        double** initMat() const;
        void freeMat();
    };

}
#endif //THEOMAT_CTHEOMAT_H
