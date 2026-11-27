














#include <cmath>


#pragma once








namespace UGS {
namespace Math {

struct TransformMatrix {
    double m[16];
};

struct Matrix3 {
    double m[9];
};

}
}

using UGS::Math::Matrix3;
using UGS::Math::TransformMatrix;



bool MTX3_is_ortho_normal(const Matrix3* m);

bool MTX4_is_equal(const TransformMatrix* m1,
                   const TransformMatrix* m2,
                   double tolerance)
{
    for (int i = 0; i < 16; ++i)
    {

        if (!(tolerance >= fabs(m1->m[i] - m2->m[i])))
            return false;
    }



    Matrix3 r1 = {m1->m[0], m1->m[1], m1->m[2],
                  m1->m[4], m1->m[5], m1->m[6],
                  m1->m[8], m1->m[9], m1->m[10]};

    const bool o1 = MTX3_is_ortho_normal(&r1);


    Matrix3 r2 = {m2->m[0], m2->m[1], m2->m[2],
                  m2->m[4], m2->m[5], m2->m[6],
                  m2->m[8], m2->m[9], m2->m[10]};

    const bool o2 = MTX3_is_ortho_normal(&r2);

    return o1 == o2;
}
