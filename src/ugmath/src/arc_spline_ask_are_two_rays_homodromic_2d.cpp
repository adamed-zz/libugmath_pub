







#include <cmath>

namespace UGS {
namespace Math {
struct Point2 { double x, y; };
struct Vector2 { double x, y; };
}
}

using UGS::Math::Point2;
using UGS::Math::Vector2;


extern "C" void ARC_SPLINE_inter_line_line_2d(
    const double* a1,
    const Point2* a2,
    const Point2* a3,
    int a4,
    const Vector2* a5,
    const Vector2* a6,
    Point2* a7,
    double* a8,
    double* a9,
    const int* a10);

int ARC_SPLINE_ask_are_two_rays_homodromic_2d(
    double* a1,
    Point2* a2,
    Vector2* a3,
    Point2* a4,
    Vector2* a5,
    int a6,
    Point2* a7,
    double* a8,
    int* a9)
{
    int* v9 = a9;
    int v10 = 1;
    if (a6 == 1)
        ARC_SPLINE_inter_line_line_2d(a1, a2, a4, 1, a3, a5, a7, a8,
                                      reinterpret_cast<double*>(&a9), a9);
    if (*v9 > 0)
    {
        const double* p3 = reinterpret_cast<const double*>(a3);
        const double* p5 = reinterpret_cast<const double*>(a5);
        v10 = p3[1] * p5[1] + p3[0] * p5[0] > 0.0;
    }
    else
    {
        if (*a1 >= fabs(a8[0]) && *a1 >= fabs(a8[1]))
            return -1;
        if (fabs(a8[0]) >= *a1 && fabs(a8[1]) >= *a1)
            v10 = !(a8[1] * *a8 < 0.0);
    }
    return v10;
}
