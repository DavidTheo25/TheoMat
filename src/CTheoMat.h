#ifndef THEOMAT_CTHEOMAT_H
#define THEOMAT_CTHEOMAT_H

#include <vector>
#include <string>


namespace Theo {

    class CTheoMat {
    public:
        CTheoMat() = delete;
        CTheoMat(int n, int m);
        CTheoMat(const CTheoMat& matrix);
        ~CTheoMat();

        void hello();
        double getValue(int i, int j) const;
        void setValue(double value, int i, int j);
        int getN() const;
        int getM() const;
        std::string toString();
        CTheoMat transpose();

        bool checkDim(const CTheoMat& matrix);

        CTheoMat operator+(const CTheoMat& matrix);
        CTheoMat operator-(const CTheoMat& matrix);


    private:
        int n, m;
        double** mat;

        double** initMat();
    };

}
#endif //THEOMAT_CTHEOMAT_H
