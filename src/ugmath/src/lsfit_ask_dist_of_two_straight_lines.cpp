








#include <math.h>

namespace UGS
{
namespace Math
{
struct Point3 { double x, y, z; };
struct Vector3 { double x, y, z; };
}
}


bool VEC3_is_parallel(const UGS::Math::Vector3* u,
                      const UGS::Math::Vector3* v, double tolerance);
double LSFIT_ask_dist_pt_to_line_3d(UGS::Math::Point3* p, UGS::Math::Point3* base,
                                    UGS::Math::Vector3* dir, double tol,
                                    UGS::Math::Point3* proj, double* param);
int SOLVE_solve_3equations(double (*const a)[3], double* const b, double* const x);

double __cdecl LSFIT_ask_dist_of_two_straight_lines(
    UGS::Math::Point3* a1, UGS::Math::Vector3* a2,
    UGS::Math::Point3* a3, UGS::Math::Vector3* a4,
    double* a5, UGS::Math::Point3* a6, double* a7,
    UGS::Math::Point3* a8, double* a9, bool* a10, bool* a11)
{
    a6->x = a1->x;
    a6->y = a1->y;
    a6->z = a1->z;
    *a7 = 0.0;
    a8->x = a3->x;
    a8->y = a3->y;
    a8->z = a3->z;
    *a9 = 0.0;
    *a11 = false;
    *a10 = false;

    double dist = sqrt((a1->y - a3->y) * (a1->y - a3->y)
                     + (a1->x - a3->x) * (a1->x - a3->x)
                     + (a1->z - a3->z) * (a1->z - a3->z));
    if (*a5 > dist)
        *a11 = true;

    double sin_angle = sin(a5[1] * 0.01745329251994328);
    bool is_parallel;
    if (VEC3_is_parallel(a2, a4, sin_angle))
    {
        *a10 = true;
        is_parallel = true;
    }
    else
    {
        is_parallel = *a10;
    }

    if (*a11)
        return dist;
    if (is_parallel)
        return LSFIT_ask_dist_pt_to_line_3d(a1, a3, a4, *a5, a8, a9);

    double dy0 = a3->y - a1->y;
    double dx0 = a3->x - a1->x;
    double dz0 = a3->z - a1->z;
    double dot = a4->x * a2->x + a4->y * a2->y + a4->z * a2->z;

    double A[3][3];
    A[0][0] = 1.0;
    A[0][1] = -dot;
    A[0][2] = 0.0;
    A[1][0] = -dot;
    A[1][1] = 1.0;
    A[1][2] = 0.0;
    A[2][0] = 0.0;
    A[2][1] = 0.0;
    A[2][2] = 1.0;

    double b[3];
    b[0] = a2->y * dy0 + a2->x * dx0 + a2->z * dz0;
    b[1] = -(a4->y * dy0 + a4->x * dx0 + a4->z * dz0);
    b[2] = 0.0;

    double x[3];
    if (SOLVE_solve_3equations(A, b, x))
    {
        *a10 = true;
        return LSFIT_ask_dist_pt_to_line_3d(a1, a3, a4, *a5, a8, a9);
    }

    *a7 = x[0];
    a6->x = a1->x + x[0] * a2->x;
    a6->y = a1->y + x[0] * a2->y;
    a6->z = a1->z + x[0] * a2->z;
    *a9 = x[1];
    a8->x = a3->x + x[1] * a4->x;
    a8->y = a3->y + x[1] * a4->y;
    a8->z = a3->z + x[1] * a4->z;

    return sqrt((a6->y - a8->y) * (a6->y - a8->y)
              + (a6->x - a8->x) * (a6->x - a8->x)
              + (a6->z - a8->z) * (a6->z - a8->z));
}
