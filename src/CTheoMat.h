#ifndef THEOMAT_CTHEOMAT_H
#define THEOMAT_CTHEOMAT_H

#include <vector>

namespace Theo {

    class CTheoMat {
    public:
        CTheoMat() = delete;
        CTheoMat(int n, int m);
        CTheoMat(CTheoMat& matrix);
        void hello();
        ~CTheoMat();


    private:
        int n, m;
        double** mat;
//        std::vector<std::vector<double>> mat;
    };

}
#endif //THEOMAT_CTHEOMAT_H
