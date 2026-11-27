



#pragma once


namespace UGS
{
namespace Math
{
struct Vector3
{
    double x, y, z;
};


struct Matrix3
{
    double m[9];
};
}
}


__declspec(dllimport) extern int MACH__checking_level;
extern "C"
{
    __declspec(dllimport) extern bool RDEBUG__enabled;
    __declspec(dllimport) int RDEBUG_ask_flag(const char *, bool);
}
__declspec(dllimport) int lprintf(const char *, ...);
__declspec(dllimport) void ERROR_raise(const char *, int, int, const char *,
                                       ...);



bool MTX3_is_ortho_normal(const UGS::Math::Matrix3 *m, double tolerance);

int MTX3_init_y_z(const UGS::Math::Vector3 *y, const UGS::Math::Vector3 *z,
                  UGS::Math::Matrix3 *m);

void MTX3_lprintf(int indent, const char *label, const UGS::Math::Matrix3 *m);

void MTX3_rpy_extract(const UGS::Math::Matrix3 *m, double *a2, double *a3,
                      double *a4, double *a5, double *a6, double *a7);

void MTX3_init_roll_pitch_yaw_impl(double cr, double sr, double cp, double sp,
                                   double cy, double sy,
                                   UGS::Math::Matrix3 *out);

int MTX3_massage_axes(UGS::Math::Matrix3 *m);

bool MTX3_ortho_normalize_reflection(UGS::Math::Matrix3 *m);

int MTX3_print_diff(const UGS::Math::Matrix3 *before, const UGS::Math::Matrix3 *after);


























#include <math.h>

static const char kSrcFile[] = "o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\mtx3.c";

bool MTX3_ortho_normalize(UGS::Math::Matrix3 *a1)
{
    bool first = true;
    int count = 0;
    bool result = false;

    double det = (a1->m[4] * a1->m[8] - a1->m[5] * a1->m[7]) * a1->m[0] -
                 (a1->m[1] * a1->m[8] - a1->m[2] * a1->m[7]) * a1->m[3] +
                 (a1->m[1] * a1->m[5] - a1->m[2] * a1->m[4]) * a1->m[6];
    if (det < 0.0)
    {
        result = MTX3_ortho_normalize_reflection(a1);
    }
    else
    {
        UGS::Math::Matrix3 before = *a1;
        if (!MTX3_is_ortho_normal(a1, 1.0e-14))
        {
            do
            {
                if (++count > 1000)
                {
                    lprintf("\n");
                    MTX3_lprintf(0, "Matrix:", a1);
                    ERROR_raise(kSrcFile, 1192, 4360000,
                                "Failed to orthonormalize matrix");
                }

                UGS::Math::Vector3 x = {a1->m[0], a1->m[1], a1->m[2]};
                UGS::Math::Vector3 z = {a1->m[6], a1->m[7], a1->m[8]};
                double xlen = sqrt(x.x * x.x + x.y * x.y + x.z * x.z);
                double zlen = sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
                double dotxz = x.x * z.x + x.y * z.y + x.z * z.z;

                if (xlen <= 1.0e-14 || zlen <= 1.0e-14 ||
                    !(fabs(dotxz) <= 1.0e-14))
                {
                    if (first && MTX3_massage_axes(a1) && RDEBUG__enabled &&
                        RDEBUG_ask_flag("UGMATH_mtx_debug", true) == 1)
                        lprintf("Matrix axes were massaged prior to reconstruct\n\n");
                    double cr, sr, cp, sp, cy, sy;
                    MTX3_rpy_extract(a1, &cr, &sr, &cp, &sp, &cy, &sy);
                    MTX3_init_roll_pitch_yaw_impl(cr, sr, cp, sp, cy, sy, a1);
                    if (first && MTX3_massage_axes(a1) && RDEBUG__enabled &&
                        RDEBUG_ask_flag("UGMATH_mtx_debug", true) == 1)
                        lprintf("Matrix axes were massaged after reconstruct\n\n");
                }
                else
                {
                    UGS::Math::Vector3 y;
                    y.x = z.y * x.z - z.z * x.y;
                    y.y = z.z * x.x - z.x * x.z;
                    y.z = z.x * x.y - z.y * x.x;
                    MTX3_init_y_z(&y, &z, a1);
                }
                first = false;
            } while (!MTX3_is_ortho_normal(a1, 1.0e-14));

            result = true;
            if (RDEBUG__enabled && RDEBUG_ask_flag("UGMATH_mtx_debug", true) == 1)
            {
                lprintf("\n\nMTX3_ortho_normalize\n");
                MTX3_lprintf(0, "Before:", &before);
                MTX3_lprintf(0, "After:", a1);
                MTX3_print_diff(&before, a1);
            }
        }
    }
    return result;
}
