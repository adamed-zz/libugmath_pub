#pragma once

#include "ugmath/matrix3.h"
#include "ugmath/vector3.h"

























void __cdecl MTX3_ask_roll_pitch_yaw(const UGS::Math::Matrix3* m, double* roll, double* pitch,
                                     double* yaw);























void __cdecl MTX3_init_roll_pitch_yaw(double roll, double pitch, double yaw,
                                      UGS::Math::Matrix3* out);



void __cdecl MTX3_init_roll_pitch_yaw_impl(double cr, double sr, double cp, double sp,
                                           double cy, double sy, UGS::Math::Matrix3* out);


























bool __cdecl MTX3_init_tol(const UGS::Math::Vector3* a1, const UGS::Math::Vector3* a2,
                           UGS::Math::Matrix3* a3);



int __cdecl mtx3_init_common(const UGS::Math::Vector3* a1, const UGS::Math::Vector3* a2,
                             UGS::Math::Matrix3* a3, char tol);



















bool __cdecl MTX3_is_ortho_normal(const UGS::Math::Matrix3* m);


bool __cdecl MTX3_is_ortho_normal(const UGS::Math::Matrix3* m, double tolerance);
