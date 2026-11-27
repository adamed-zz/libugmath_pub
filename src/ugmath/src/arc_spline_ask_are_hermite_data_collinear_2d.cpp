














#pragma once


namespace UGS
{
namespace Math
{
struct Point2
{
    double x, y;
};

struct Vector2
{
    double x, y;
};
}
}




int __cdecl VEC2_unitize(const UGS::Math::Vector2* u, double tol, double* len_out,
                         UGS::Math::Vector2* out);
bool __cdecl VEC2_is_parallel(const UGS::Math::Vector2* u, const UGS::Math::Vector2* v,
                              double tolerance);

#include <math.h>

bool __cdecl ARC_SPLINE_ask_are_hermite_data_collinear_2d(
    UGS::Math::Point2* a1, UGS::Math::Vector2* a2, UGS::Math::Point2* a3,
    UGS::Math::Vector2* a4, double a5, double* a6, UGS::Math::Vector2* a7)
{
    bool collinear = false;
    double s = sin(a5 * 0.01745329251994328);
    *a7 = UGS::Math::Vector2{a3->x - a1->x, a3->y - a1->y};
    VEC2_unitize(a7, 1.0e-10, a6, a7);
    if (VEC2_is_parallel(a7, a2, s))
    {
        if (VEC2_is_parallel(a7, a4, s))
            collinear = true;
    }
    return collinear;
}
