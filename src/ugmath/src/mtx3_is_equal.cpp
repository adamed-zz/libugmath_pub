





#include <cmath>

namespace UGS {
namespace Math {

struct Matrix3 {
    double m[9];
};

}
}

using UGS::Math::Matrix3;


bool MTX3_is_ortho_normal(const Matrix3* m, double tol);

bool MTX3_is_equal(const Matrix3* m1, const Matrix3* m2, double tol)
{
    for (int i = 0; i < 9; ++i)
    {
        if (!(tol >= fabs(m1->m[i] - m2->m[i])))
            return false;
    }
    bool first = MTX3_is_ortho_normal(m1, 1.0e-14);
    return first == MTX3_is_ortho_normal(m2, 1.0e-14);
}
