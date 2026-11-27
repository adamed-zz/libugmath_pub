




















#include <math.h>
#include <intrin.h>

namespace UGS
{
namespace Math
{
struct Point2
{
    double x;
    double y;
};
struct Vector2
{
    double x;
    double y;
};
}
}

using UGS::Math::Point2;
using UGS::Math::Vector2;



#ifdef ARC_ANGLE_SELFTEST
void ERROR_internal(const char* file, int line, const char* msg, ...);
#else
__declspec(dllimport) void ERROR_internal(const char* file, int line, const char* msg, ...);
#endif


int VEC2_unitize(const Vector2* u, double tol, double* len_out, Vector2* out);
void h053(const double* a1, const double* a2, double* a3);

double ARC_SPLINE_ask_interior_angle_of_triangle_2d(Point2* a1, Point2* a2,
                                                    Point2* a3, double* a4,
                                                    int a5, int* a6)
{
    double answer = 0.0;
    *a6 = 0;
    Vector2 d1 = {0.0, 0.0};
    Vector2 d2 = {0.0, 0.0};
    double y1, y2, x1, x2, y3, x3, tol;

    if (a5 == 1)
    {
        y1 = a1->y;
        y2 = a2->y;
        x1 = a1->x;
        x2 = a2->x;
    }
    else if (a5 == 2)
    {
        y1 = a2->y;
        y2 = a1->y;
        x1 = a2->x;
        x2 = a1->x;
    }
    else if (a5 == 3)
    {
        y3 = a3->y;
        x3 = a3->x;
        y1 = a1->y;
        x1 = a1->x;
        y2 = a2->y;
        x2 = a2->x;
        tol = *a4;
        if (tol > sqrt((x3 - x1) * (x3 - x1) + (y3 - y1) * (y3 - y1)) ||
            tol > sqrt((x3 - x2) * (x3 - x2) + (y3 - y2) * (y3 - y2)))
        {
            *a6 = 1;
            return answer;
        }
        d1.x = x1 - x3;
        d1.y = y1 - y3;
        d2.x = x2 - x3;
        d2.y = y2 - y3;
        goto compute_angle;
    }
    else
    {
        ERROR_internal(
            "o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\arc_spline_apollonian_constructions.c",
            14749, "Unrecognizable input value for which_angle.");
        __debugbreak();
        __assume(0);
    }

    y3 = a3->y;
    x3 = a3->x;
    tol = *a4;
    if (tol > sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)) ||
        tol > sqrt((x1 - x3) * (x1 - x3) + (y1 - y3) * (y1 - y3)))
    {
        *a6 = 1;
    }
    else
    {
        d2.y = y3 - y1;
        d2.x = x3 - x1;
        d1.y = y2 - y1;
        d1.x = x2 - x1;
    }
    if (*a6)
        return answer;

compute_angle:
    {
        Vector2 uu = {0.0, 0.0};
        Vector2 vv = {0.0, 0.0};
        VEC2_unitize(&d1, 1.0e-10, (double*)&a6, &uu);
        VEC2_unitize(&d2, 1.0e-10, (double*)&a6, &vv);
        double dot = vv.y * uu.y + vv.x * uu.x;
        double cross = vv.y * uu.x - vv.x * uu.y;
        double angle;
        h053(&cross, &dot, &angle);
        double deg = angle * 57.29577951308235;
        if (*a4 >= fabs(deg - 180.0))
            answer = 180.0;
        else if (deg > 180.0)
            answer = 360.0 - deg;
        else
            answer = deg;
        return answer;
    }
}
