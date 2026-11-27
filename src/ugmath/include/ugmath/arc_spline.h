#pragma once

#include "ugmath/matrix3.h"
#include "ugmath/vector3.h"


























void __cdecl ARC_SPLINE_cre_matrix_of_rotation_around_axis(UGS::Math::Vector3* axis,
                                                           double angle_deg,
                                                           UGS::Math::Matrix3* out);


void __cdecl MTX3_rot_about_axis(double angle_rad, const UGS::Math::Vector3* axis,
                                 UGS::Math::Matrix3* out);
