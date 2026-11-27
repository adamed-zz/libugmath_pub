


















#include <cmath>
#include <emmintrin.h>

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

struct ARC_SPLINE_1_seg_2d_s
{
    int    type;
    int    dir;
    double base_x;
    double base_y;
    double parm0;
    double parm1;
    double center_x;
    double center_y;
    double line_dx;
    double line_dy;
    double radius;
    double radius2;
};
static_assert(sizeof(ARC_SPLINE_1_seg_2d_s) == 0x58, "seg layout");

using UGS::Math::Point2;
using UGS::Math::Vector2;


int VEC2_unitize(const Vector2* v, double tol, double* len, Vector2* out);
void ARC_SPLINE_inter_line_line_2d(const double* const tol, const Point2* p1,
                                   const Point2* p2, int dirs_unitized,
                                   Vector2* d1, Vector2* d2, Point2* out_pt,
                                   double* params, double* dot, int* status);
void ARC_SPLINE_cre_strt_seg_2d(const Point2* p1, const Point2* p2,
                                const Vector2* dir, ARC_SPLINE_1_seg_2d_s* seg);
double ARC_SPLINE_ask_dist_pt_to_line_2d(const Point2* pt, const Point2* origin,
                                         const Vector2* dir, double tol,
                                         Point2* closest, double* t, int* side);
void ARC_SPLINE_cre_circle_thru_3_points_2d(const Point2* p1, const Point2* p2,
                                            const Point2* p3,
                                            const double* const tol,
                                            ARC_SPLINE_1_seg_2d_s* seg, int* status);
double ARC_SPLINE_ask_dist_pt_to_line_seg_2d(const Point2* pt, const Point2* origin,
                                             const Point2* end, double tol, int clamp,
                                             Point2* closest, double* t, int* pos,
                                             int* side);
void ARC_SPLINE_cre_circle_thru_pt_and_tangent_to_line_at_pt_2d(
    const Point2* a1, const Vector2* a2, const Point2* a3, const double* const a4,
    ARC_SPLINE_1_seg_2d_s* a5, int* a6);

void __cdecl ARC_SPLINE_cre_circle_thru_2_points_tangent_to_line(
    const Point2* a1, const Point2* a2, const Point2* a3, Vector2* a4,
    const double* const a5, int* a6, Point2* a7, Point2* a8,
    ARC_SPLINE_1_seg_2d_s* a9, ARC_SPLINE_1_seg_2d_s* a10, int* a11)
{
    ARC_SPLINE_1_seg_2d_s* const  seg1 = a9;
    Point2* const                 tan1 = a7;
    int* const                    cnt  = a6;

    Point2 isect    = {0.0, 0.0};
    Point2 closest1 = {0.0, 0.0};

    *cnt = 0;
    tan1->x = 0.0;
    tan1->y = 0.0;
    {
        Point2* const tan2z = a8;
        tan2z->x = 0.0;
        tan2z->y = 0.0;
    }
    for (int i = 0; i < 11; ++i)
        ((long long*)seg1)[i] = 0;
    {
        long long* const z10 = (long long*)a10;
        for (int i = 0; i < 11; ++i)
            z10[i] = 0;
    }
    Point2 closest2 = {0.0, 0.0};
    *a11 = 0;

    Vector2 dir;
    dir.x = a2->x - a1->x;
    dir.y = a2->y - a1->y;
    VEC2_unitize(&dir, 1.0e-10, reinterpret_cast<double*>(&a11), &dir);

    double params[2];
    ARC_SPLINE_inter_line_line_2d(a5, a1, a3, 1, &dir, a4, &isect, params,
                                  reinterpret_cast<double*>(&a7),
                                  reinterpret_cast<int*>(&a6));

    const int code = *(const int*)&a6;
    if (code == 2)
    {
        *cnt = 1;
        ARC_SPLINE_cre_strt_seg_2d(a1, a2, &dir, seg1);
        tan1->x = a1->x;
        tan1->y = a1->y;
        Point2* const tan2 = a8;
        tan2->x = a2->x;
        tan2->y = a2->y;
        *cnt = 1;
    }
    else if (code == 1)
    {

        {
            const __m128d sums = _mm_unpacklo_pd(_mm_set_sd(a1->x + a2->x),
                                                 _mm_set_sd(a2->y + a1->y));
            const __m128d midv = _mm_mul_pd(_mm_set_pd(0.5, 0.5), sums);
            isect.x = _mm_cvtsd_f64(midv);
            isect.y = _mm_cvtsd_f64(_mm_unpackhi_pd(midv, midv));
        }
        ARC_SPLINE_ask_dist_pt_to_line_2d(&isect, a3, a4, a5[0], &closest1,
                                          reinterpret_cast<double*>(&a10),
                                          reinterpret_cast<int*>(&a8));
        ARC_SPLINE_cre_circle_thru_3_points_2d(a1, a2, &closest1, a5, seg1,
                                               reinterpret_cast<int*>(&a8));
        {
            const __m128d cv = _mm_loadu_pd(&closest1.x);
            tan1->x = _mm_cvtsd_f64(cv);
            tan1->y = _mm_cvtsd_f64(_mm_unpackhi_pd(cv, cv));
        }
        if (*(const int*)&a8 == 0)
            *cnt = 1;
    }
    else
    {
        const double tol = a5[0];
        ARC_SPLINE_ask_dist_pt_to_line_seg_2d(&isect, a1, a2, tol, 0, &closest2,
                                              reinterpret_cast<double*>(&a9),
                                              reinterpret_cast<int*>(&a6),
                                              reinterpret_cast<int*>(&a7));
        const int pos = *(const int*)&a6;
        if (pos == -1)
        {
            *cnt = 0;
        }
        else if (pos == 0)
        {
            if (a5[0] >= fabs(0.0 - *(const double*)&a9))
            {
                ARC_SPLINE_cre_circle_thru_pt_and_tangent_to_line_at_pt_2d(
                    a1, a4, a2, a5, seg1, reinterpret_cast<int*>(&a8));
                tan1->x = a1->x;
                tan1->y = a1->y;
            }
            else
            {
                ARC_SPLINE_cre_circle_thru_pt_and_tangent_to_line_at_pt_2d(
                    a2, a4, a1, a5, seg1, reinterpret_cast<int*>(&a8));
                tan1->x = a2->x;
                tan1->y = a2->y;
            }
            *cnt = 1;
        }
        else
        {
            const __m128d isectv = _mm_loadu_pd(&isect.x);
            const double iy   = isect.y;
            const double dy2  = iy - a2->y;
            const double dy1  = iy - a1->y;
            const double dx2  = isect.x - a2->x;
            const double dx1  = isect.x - a1->x;
            const double d2   = sqrt(dx2 * dx2 + dy2 * dy2);
            const double d1   = sqrt(dx1 * dx1 + dy1 * dy1);
            const double g    = sqrt(d2 * d1);
            _mm_storeu_pd(&tan1->x,
                          _mm_add_pd(_mm_mul_pd(_mm_set1_pd(g), _mm_loadu_pd(&dir.x)),
                                     isectv));
            ARC_SPLINE_cre_circle_thru_3_points_2d(a1, a2, tan1, a5, seg1,
                                                   reinterpret_cast<int*>(&a6));
            Point2* const tan2 = a8;
            const double ng = -g;
            _mm_storeu_pd(&tan2->x,
                          _mm_add_pd(_mm_mul_pd(_mm_set1_pd(ng), _mm_loadu_pd(&dir.x)),
                                     isectv));
            ARC_SPLINE_cre_circle_thru_3_points_2d(a1, a2, tan2, a5, a10,
                                                   reinterpret_cast<int*>(&a8));
            if (*(const int*)&a6 == 0 || *(const int*)&a8 == 0)
                *cnt = 2;
        }
    }
}
