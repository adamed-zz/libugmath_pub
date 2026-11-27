


















#include <emmintrin.h>

struct ARC_SPLINE_1_seg_2d_s
{
    int    type;
    int    sense;
    double x;
    double y;
    double parm0;
    double parm1;
    double cx;
    double cy;
    double dirx;
    double diry;
    double radius;
    double radius2;
};

namespace UGS {
namespace Math {
struct Point2 { double x, y; };
struct Vector2 { double x, y; };
}
}


#ifndef ARC_OFFSET_SELFTEST
#define ARC_IMPORT __declspec(dllimport)
#else
#define ARC_IMPORT
#endif
ARC_IMPORT extern int MACH__checking_level;
ARC_IMPORT void ERROR_assertion_failed(const char* file_name, int line,
                                        const char* message, ...);


int VEC2_unitize(const UGS::Math::Vector2* u, double tol, double* len,
                 UGS::Math::Vector2* out);
void ARC_SPLINE_evaluate_arc_seg_2d(const struct ARC_SPLINE_1_seg_2d_s* seg, int flag,
                                    double parm, UGS::Math::Point2* pt,
                                    UGS::Math::Vector2* tan, int* status);

void ARC_SPLINE_cre_offset_circle_2d(struct ARC_SPLINE_1_seg_2d_s* a1, double a2,
                                     double a3, struct ARC_SPLINE_1_seg_2d_s* a4)
{
    int    v5  = 0;
    double v10 = 0.0;
    double v7  = 0.0;
    double v12;
    double v13;
    const double tol = 1.0E-10;
    double v9  = 0.0;
    int    v8  = -1;
    int    v11 = 0;
    __m128d v19 = _mm_setzero_pd();
    __m128d v20 = _mm_setzero_pd();
    __m128d v21;
    __m128d v22;
    __m128d v23;
    int    v24;
    double v25;

    if (!a1)
    {
        v12 = *(volatile const double*)&v19.m128d_f64[1];
        v11 = 1;
        v13 = *(volatile const double*)&v19.m128d_f64[0];
    }
    else
    {
        v8  = a1->type;
        v13 = a1->cx;
        v12 = a1->cy;
        v19.m128d_f64[0] = v13;
        v19.m128d_f64[1] = v12;
        if (!v8)
        {
            v10 = 1.0E+19;
        }
        else
        {
            if (v8 == 1)
            {
                v10 = a1->radius;
                if (v10 < tol)
                    v8 = -1;
            }
            else
            {
                v11 = 2;
            }
        }
    }
    if (MACH__checking_level > 0 && !(v11 == 0 && v8 == 1))
        ERROR_assertion_failed(
            "o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\arc_spline_apollonian_constructions.c",
            13367, "%s", "( local_status_flag == 0 && type == 1 )");

    v10 = v10 + a2;
    if (MACH__checking_level > 0 && !(v10 >= a3))
        ERROR_assertion_failed(
            "o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\arc_spline_apollonian_constructions.c",
            13376, "%s", "( new_radius >= dist_tol )");

    v24 = 0;
    if (!a1)
    {
        v5 = 1;
    }
    else
    {
        v7 = a1->x;
        v9 = a1->y;
        if (!a1->type)
        {
            const double v15 = a1->radius;
            const double v16 = v15 * a1->diry + v9;
            const double v17 = v15 * a1->dirx + v7;
            v20.m128d_f64[1] = v16;
            v20.m128d_f64[0] = v17;
        }
        else
        {
            if (a1->type == 1)
            {
                if (a1->radius < tol)
                {
                    v5 = 2;
                }
                else
                {
                    ARC_SPLINE_evaluate_arc_seg_2d(
                        a1, 1, a1->parm1, (UGS::Math::Point2*)&v20,
                        (UGS::Math::Vector2*)&v23, &v24);
                    v5 = v24;
                }
            }
            else
            {
                v5 = 3;
            }
        }
    }
    if (MACH__checking_level > 0 && !(v5 == 0))
        ERROR_assertion_failed(
            "o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\arc_spline_apollonian_constructions.c",
            13389, "%s", "( local_status_flag == 0 )");

    v21.m128d_f64[0] = v7 - v13;
    v21.m128d_f64[1] = v9 - v12;
    VEC2_unitize((const UGS::Math::Vector2*)&v21, tol, &v25,
                 (UGS::Math::Vector2*)&v21);




    const __m128d v18 = _mm_add_pd(
        _mm_mul_pd(_mm_set1_pd(v10), _mm_loadu_pd(&v21.m128d_f64[0])),
        _mm_loadu_pd(&v19.m128d_f64[0]));
    v22.m128d_f64[0] = v20.m128d_f64[0] - v13;
    v22.m128d_f64[1] = v20.m128d_f64[1] - v12;
    VEC2_unitize((const UGS::Math::Vector2*)&v22, tol, &v25,
                 (UGS::Math::Vector2*)&v22);

    a4->type  = a1->type;
    a4->sense = a1->sense;
    ((double*)a4)[1] = v18.m128d_f64[0];
    ((double*)a4)[2] = _mm_unpackhi_pd(v18, v18).m128d_f64[0];
    ((double*)a4)[3] = ((const double*)a1)[3];
    ((double*)a4)[4] = ((const double*)a1)[4];
    ((double*)a4)[5] = ((const double*)a1)[5];
    ((double*)a4)[6] = ((const double*)a1)[6];
    ((double*)a4)[7] = ((const double*)a1)[7];
    ((double*)a4)[8] = ((const double*)a1)[8];
    ((double*)a4)[9]  = v10;
    ((double*)a4)[10] = v10;
}
