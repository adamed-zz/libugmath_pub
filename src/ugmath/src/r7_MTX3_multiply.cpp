









#include "b36_math.h"

void MTX3_multiply(const UGS::Math::Matrix3* a1, const UGS::Math::Matrix3* a2,
                   UGS::Math::Matrix3* a3) {
    const double* m1 = a1->m;
    const double* m2 = a2->m;
    UGS::Math::Matrix3 r;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            r.m[i * 3 + j] = m2[i * 3 + 0] * m1[0 * 3 + j] + m2[i * 3 + 1] * m1[1 * 3 + j] +
                             m2[i * 3 + 2] * m1[2 * 3 + j];
        }
    }
    if (MTX3_is_ortho_normal(a1, 1.0e-14) && MTX3_is_ortho_normal(a2, 1.0e-14))
        MTX3_ortho_normalize(&r);
    *a3 = r;
}
