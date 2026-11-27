#pragma once

#include "ugmath/vector3.h"























int __cdecl VEC3_unitize(const UGS::Math::Vector3* u, double tol, double* len_out,
                         UGS::Math::Vector3* out);
























double __cdecl VEC3_find_acute_angle_between(const UGS::Math::Vector3* a1,
                                             const UGS::Math::Vector3* a2);


double __cdecl VEC3_find_angle_between(const UGS::Math::Vector3* a1,
                                       const UGS::Math::Vector3* a2);
