





#include <cmath>


#pragma once



namespace UGS {
namespace Math {

struct Matrix3 {
    double m[9];
};

}
}


using UGS::Math::Matrix3;



bool MTX3_is_ortho_normal(const Matrix3* m, double tol);

bool MTX3_is_identity(const Matrix3* m, double tol)
{
    const Matrix3 identity = {
        1.0, 0.0, 0.0,
        0.0, 1.0, 0.0,
        0.0, 0.0, 1.0,
    };
    for (int i = 0; i < 9; ++i)
    {
        if (!(tol >= fabs(m->m[i] - identity.m[i])))
            return false;
    }
    bool first = MTX3_is_ortho_normal(m, 1.0e-14);
    return first == MTX3_is_ortho_normal(&identity, 1.0e-14);
}
