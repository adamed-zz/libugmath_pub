#pragma once
















#include "ugmath/point3.h"

void __cdecl PNT3_cylindrical_to_cartesian(UGS::Math::Point3* in, UGS::Math::Point3* out);




























struct PLN3_s {
    double origin[3];
    double normal[3];
};

bool __cdecl PNT3_proj_to_plane(const UGS::Math::Point3* point, const PLN3_s* plane,
                                UGS::Math::Point3* out);
