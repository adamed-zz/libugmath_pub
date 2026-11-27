
















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

struct ARC_SPLINE_1_seg_2d_s
{
    int    kind;
    int    flags;
    double base_x;
    double base_y;
    double ang0;
    double ang1;
    double center_x;
    double center_y;
    double dir_x;
    double dir_y;
    double radius;
    double parm;
};

#include <emmintrin.h>



int ARC_SPLINE_ask_3pts_collinearity_2d(const UGS::Math::Point2* a1,
                                        const UGS::Math::Point2* a2,
                                        const UGS::Math::Point2* a3,
                                        const double* const a4, int a5, int* a6);

int VEC2_unitize(const UGS::Math::Vector2* u, double tol, double* len_out,
                 UGS::Math::Vector2* out);

void ARC_SPLINE_inter_line_line_2d(const double* const tol,
                                   const UGS::Math::Point2* p1,
                                   const UGS::Math::Point2* p2, int dirs_unitized,
                                   UGS::Math::Vector2* dir1,
                                   UGS::Math::Vector2* dir2,
                                   UGS::Math::Point2* out_pt, double* params,
                                   double* dot, int* status);

void ARC_SPLINE_cre_arc_seg_2d(const UGS::Math::Point2* start,
                               const UGS::Math::Vector2* dir, double sweep,
                               double radius, int direction,
                               ARC_SPLINE_1_seg_2d_s* seg,
                               UGS::Math::Point2* end_pt,
                               UGS::Math::Vector2* out_vec);

void ARC_SPLINE_cre_circle_thru_3_points_2d(
    const UGS::Math::Point2* a1, const UGS::Math::Point2* a2,
    const UGS::Math::Point2* a3, const double* const a4,
    ARC_SPLINE_1_seg_2d_s* a5, int* a6)
{


    ARC_SPLINE_1_seg_2d_s* const seg = a5;
    int* const st = a6;


    seg->kind = 0;
    seg->flags = 0;
    seg->base_x = 0.0;
    seg->base_y = 0.0;
    seg->ang0 = 0.0;
    seg->ang1 = 0.0;
    seg->center_x = 0.0;
    seg->center_y = 0.0;
    seg->dir_x = 0.0;
    seg->dir_y = 0.0;
    seg->radius = 0.0;
    seg->parm = 0.0;

    int orient = -1;
    UGS::Math::Vector2 perp13;
    UGS::Math::Vector2 urd = {};
    double radius;
    UGS::Math::Vector2 u13 = {};
    UGS::Math::Vector2 u12 = {};
    UGS::Math::Point2 ctr = {};
    UGS::Math::Vector2 t13, t12, perp12;
    UGS::Math::Point2 mid13, mid12;
    UGS::Math::Vector2 cd;
    UGS::Math::Vector2 par;

    *st = ARC_SPLINE_ask_3pts_collinearity_2d(a1, a2, a3, a4, 2, &orient);
    if (*st <= 0)
    {
        t13.x = a3->x - a1->x;
        t13.y = a3->y - a1->y;
        VEC2_unitize(&t13, 1.0e-10, (double*)&a5, &u13);
        {
            __m128d sums = _mm_setr_pd(a1->x + a3->x, a1->y + a3->y);
            __m128d m = _mm_mul_pd(_mm_set_pd(0.5, 0.5), sums);
            mid13.x = _mm_cvtsd_f64(m);
            mid13.y = _mm_cvtsd_f64(_mm_unpackhi_pd(m, m));
        }
        perp13.x = -u13.y;
        perp13.y = u13.x;
        t12.x = a2->x - a1->x;
        t12.y = a2->y - a1->y;
        VEC2_unitize(&t12, 1.0e-10, (double*)&a5, &u12);
        {
            __m128d sums = _mm_setr_pd(a1->x + a2->x, a1->y + a2->y);
            __m128d m = _mm_mul_pd(_mm_set_pd(0.5, 0.5), sums);
            mid12.x = _mm_cvtsd_f64(m);
            mid12.y = _mm_cvtsd_f64(_mm_unpackhi_pd(m, m));
        }
        perp12.x = -u12.y;
        perp12.y = u12.x;
        ARC_SPLINE_inter_line_line_2d(a4, &mid12, &mid13, 1, &perp12, &perp13,
                                      &ctr, (double*)&par, (double*)&a6, st);
        if (*st <= 0)
        {
            cd.x = a1->x - ctr.x;
            cd.y = a1->y - ctr.y;
            VEC2_unitize(&cd, 1.0e-10, &radius, &urd);
            int dir = -1;
            if (orient == 1)
            {
                perp13.x = urd.y;
                perp13.y = -urd.x;
            }
            else
            {
                dir = 1;
                perp13.x = -urd.y;
                perp13.y = urd.x;
            }
            ARC_SPLINE_cre_arc_seg_2d(a1, &perp13, 360.0, radius, dir, seg, &ctr,
                                      &par);
        }
    }
}
