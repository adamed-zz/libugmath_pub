













#include "b36_math.h"

namespace {

void Embed3x3(const double* m, UGS::Math::TransformMatrix* out) {
    double* t = out->m;
    for (int r = 0; r < 3; ++r) {
        t[r * 4 + 0] = m[r * 3 + 0];
        t[r * 4 + 1] = m[r * 3 + 1];
        t[r * 4 + 2] = m[r * 3 + 2];
        t[r * 4 + 3] = 0.0;
    }
    t[12] = 0.0;
    t[13] = 0.0;
    t[14] = 0.0;
    t[15] = 1.0;
}

void Translation(const UGS::Math::Vector3* v, UGS::Math::TransformMatrix* out) {
    double* t = out->m;
    t[0] = 1.0;
    t[1] = 0.0;
    t[2] = 0.0;
    t[3] = v->x;
    t[4] = 0.0;
    t[5] = 1.0;
    t[6] = 0.0;
    t[7] = v->y;
    t[8] = 0.0;
    t[9] = 0.0;
    t[10] = 1.0;
    t[11] = v->z;
    t[12] = 0.0;
    t[13] = 0.0;
    t[14] = 0.0;
    t[15] = 1.0;
}

}

void sub_18009FBD0(const UGS::Math::Vector3* t1, const UGS::Math::Matrix3* a,
                   const UGS::Math::Vector3* t2, const UGS::Math::Matrix3* b,
                   UGS::Math::TransformMatrix* out) {
    UGS::Math::TransformMatrix mB;
    UGS::Math::TransformMatrix mA;
    UGS::Math::TransformMatrix mT1;
    UGS::Math::TransformMatrix mT2;
    UGS::Math::TransformMatrix tmp;
    Embed3x3(b->m, &mB);
    Embed3x3(a->m, &mA);
    UGS::Math::Vector3 neg = {-t1->x, -t1->y, -t1->z};
    Translation(&neg, &mT1);
    Translation(t2, &mT2);
    MTX4_invert(&mB, &mB);
    MTX4_multiply(&mT1, &mA, &tmp);
    MTX4_multiply(&tmp, &mB, &mT1);
    MTX4_multiply(&mT1, &mT2, out);
}
