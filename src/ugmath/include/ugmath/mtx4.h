#pragma once

#include "ugmath/matrix3.h"





















namespace UGS {
namespace Math {



struct TransformMatrix {
    double m[16];
};

}
}

bool __cdecl MTX4_is_ortho_normal(const UGS::Math::TransformMatrix* m);



bool __cdecl MTX3_is_ortho_normal(const UGS::Math::Matrix3* matrix);























bool __cdecl MTX4_is_equal_transform(UGS::Math::TransformMatrix* a1,
                                     UGS::Math::TransformMatrix* a2);



bool __cdecl MTX4_is_equal_transform(const UGS::Math::TransformMatrix* a1,
                                     const UGS::Math::TransformMatrix* a2, double a3,
                                     double a4, double a5);
