

















#include <cmath>
#include <cstring>
#include <emmintrin.h>

namespace UGS { namespace Math {
struct Point2  { double x; double y; };
struct Vector2 { double x; double y; };

inline Vector2 operator+(const Vector2& a, const Vector2& b)
{ Vector2 r; r.x = a.x + b.x; r.y = a.y + b.y; return r; }
inline Point2 operator+(const Point2& a, const Vector2& b)
{ Point2 r; r.x = a.x + b.x; r.y = a.y + b.y; return r; }
inline Point2 operator-(const Point2& a, const Vector2& b)
{ Point2 r; r.x = a.x - b.x; r.y = a.y - b.y; return r; }
inline Vector2 operator-(const Vector2& a, const Vector2& b)
{ Vector2 r; r.x = a.x - b.x; r.y = a.y - b.y; return r; }
inline Vector2 operator*(const Vector2& v, double s)
{ Vector2 r; r.x = v.x * s; r.y = v.y * s; return r; }
inline Vector2 operator*(double s, const Vector2& v)
{ Vector2 r; r.x = s * v.x; r.y = s * v.y; return r; }



static inline Point2 p_add_mul(const Point2& p, const Vector2& v, double s)
{
    __m128d vp = _mm_loadu_pd(&p.x);
    __m128d vv = _mm_loadu_pd(&v.x);
    __m128d ss = _mm_set1_pd(s);
    __m128d rr = _mm_add_pd(_mm_mul_pd(ss, vv), vp);
    Point2 o;
    o.x = _mm_cvtsd_f64(rr);
    o.y = _mm_cvtsd_f64(_mm_unpackhi_pd(rr, rr));
    return o;
}
static inline Point2 p_sub_mul(const Point2& p, const Vector2& v, double s)
{
    __m128d vp = _mm_loadu_pd(&p.x);
    __m128d vv = _mm_loadu_pd(&v.x);
    __m128d ss = _mm_set1_pd(s);
    __m128d rr = _mm_add_pd(_mm_mul_pd(ss, vv), vp);
    Point2 o;
    o.x = _mm_cvtsd_f64(rr);
    o.y = _mm_cvtsd_f64(_mm_unpackhi_pd(rr, rr));
    return o;
}
}}

struct ARC_SPLINE_1_seg_2d_s
{
    int    type;
    int    dir;
    double base_x;
    double base_y;
    double start;
    double end;
    double center_x;
    double center_y;
    double line_dx;
    double line_dy;
    double radius;
    double radius2;
};
static_assert(sizeof(ARC_SPLINE_1_seg_2d_s) == 0x58, "seg size");
static_assert(offsetof(ARC_SPLINE_1_seg_2d_s, center_x) == 0x28, "center off");
static_assert(offsetof(ARC_SPLINE_1_seg_2d_s, radius) == 0x48, "radius off");

using UGS::Math::Point2;
using UGS::Math::Vector2;


void ARC_SPLINE_ask_parm_at_a_point_2d(
    const ARC_SPLINE_1_seg_2d_s* a1, const Point2* a2, const double* const a3,
    Point2* a4, double* a5, int* a6, int* a7);
void ARC_SPLINE_ask_tangents_thru_a_point_2d(
    const ARC_SPLINE_1_seg_2d_s* a1, const Point2* a2, int a3, const double* const a4,
    int* a5, Point2* a6, Point2* a7, double* a8, int* a9, int* a10);
void ARC_SPLINE_cre_strt_seg_2d(
    const Point2* a1, const Point2* a2, const Vector2* a3,
    ARC_SPLINE_1_seg_2d_s* a4);

void ARC_SPLINE_ask_tangents_exterior_to_circles_2d(
    ARC_SPLINE_1_seg_2d_s* a1,
    ARC_SPLINE_1_seg_2d_s* a2,
    int a3,
    int a4,
    double* a5,
    int* a6,
    ARC_SPLINE_1_seg_2d_s* a7,
    ARC_SPLINE_1_seg_2d_s* a8,
    double* a9,
    double* a10,
    int* a11)
{

    ARC_SPLINE_1_seg_2d_s* v12 = a7;
    ARC_SPLINE_1_seg_2d_s* v11 = a8;
    int* v13 = a6;
    int* v15 = a11;
    double* v18 = a9;
    double* v19 = a10;
    double* v81 = a10 + 1;

    Point2  v67 = { 0.0, 0.0 };
    Point2  v70 = { 0.0, 0.0 };
    Point2  v66 = { 0.0, 0.0 };
    Point2  v69 = { 0.0, 0.0 };
    Point2  v76 = { 0.0, 0.0 };
    Point2  v77 = { 0.0, 0.0 };
    Point2  v79 = { 0.0, 0.0 };
    Point2  v80 = { 0.0, 0.0 };
    Point2  v71 = { 0.0, 0.0 };
    Point2  v75 = { 0.0, 0.0 };
    Vector2 v74 = { 0.0, 0.0 };
    Vector2 v78 = { 0.0, 0.0 };
    Point2  v72 = { 0.0, 0.0 };
    double  v73 = 0.0;

    *v13 = 0;
    for (int i = 0; i < 11; ++i) ((unsigned long long*)v12)[i] = 0;
    for (int i = 0; i < 11; ++i) ((unsigned long long*)v11)[i] = 0;
    v18[0] = 0.0; v18[1] = 0.0;
    a8 = (ARC_SPLINE_1_seg_2d_s*)(a9 + 1);
    v19[0] = 0.0; v19[1] = 0.0;
    *v15 = 0;

    if (!a1 || a1->type != 1) { *v15 = 1; return; }
    v75.x = a1->center_x; v75.y = a1->center_y;
    double r1 = a1->radius;
    *(int*)&a6 = 0;
    if (!a2 || a2->type != 1) { *v15 = 2; return; }
    v71.x = a2->center_x; v71.y = a2->center_y;
    double r2 = a2->radius;

    double dx = v75.x - v71.x;
    double dy = v75.y - v71.y;
    double d = sqrt(dx * dx + dy * dy);
    double rdiff = fabs(r1 - r2);
    double tol = *a5;
    if (tol > d || rdiff - tol > d) { *v15 = 3; return; }

    Vector2 u;
    if (!(r1 >= r2)) { u.x = dx;          u.y = dy; }
    else             { u.x = v71.x - v75.x; u.y = v71.y - v75.y; }
    double invd = 1.0 / d;
    u = u * invd;
    v74.x = -u.y; v74.y = u.x;

    if (!(tol >= fabs(d - rdiff)))
    {

        v78.x = 0.0; v78.y = 0.0;
        if (tol >= rdiff)
        {

            v67 = p_add_mul(v75, v74, r1);
            v70 = p_sub_mul(v75, v74, -r1);
            v69 = p_sub_mul(v71, v74, -r2);
            v66 = p_add_mul(v71, v74, r2);
        }
        else
        {

            Point2 base;
            double t;
            if (r1 > r2) { t = r2 * d / rdiff; base = v71; }
            else         { t = r1 * d / rdiff; base = v75; }
            v72 = p_add_mul(base, u, t);

            ARC_SPLINE_ask_tangents_thru_a_point_2d(a1, &v72, a3, a5,
                (int*)&a7, &v67, &v70, &v74.x, (int*)&a11, (int*)&a6);
            if (*(int*)&a6 > 0 || (!a3 && *(int*)&a7 < 2)) { *v15 = 4; return; }
            if ((v67.x - v70.x) * (-u.y) + (v67.y - v70.y) * u.x < 0.0)
            {
                Point2 sw = v67; v67 = v70; v70 = sw;
            }

            ARC_SPLINE_ask_tangents_thru_a_point_2d(a2, &v72, a4, a5,
                (int*)&a7, &v66, &v69, &v74.x, (int*)&a11, (int*)&a6);
            if (*(int*)&a6 > 0 || (!a4 && *(int*)&a7 < 2)) { *v15 = 5; return; }
            if ((v66.x - v69.x) * (-u.y) + (v66.y - v69.y) * u.x < 0.0)
            {
                Point2 sw = v66; v66 = v69; v69 = sw;
            }
        }


        ARC_SPLINE_ask_parm_at_a_point_2d(a1, &v67, a5, &v76, v18,     (int*)&a7,     (int*)&a6);
        if (!a3) *(int*)&a7 = -1;
        ARC_SPLINE_ask_parm_at_a_point_2d(a2, &v66, a5, &v77, (double*)a8, (int*)&a7 + 1, (int*)&a6);
        int n2c = a4 ? *((int*)&a7 + 1) : -1;
        ARC_SPLINE_ask_parm_at_a_point_2d(a1, &v70, a5, &v79, v19,     (int*)&a8,     (int*)&a6);
        if (!a3) *(int*)&a8 = -1;
        ARC_SPLINE_ask_parm_at_a_point_2d(a2, &v69, a5, &v80, v81,     (int*)&a8 + 1, (int*)&a6);
        int n4v = *((int*)&a8 + 1);
        if (!a4) n4v = -1;

        if (*(int*)&a7 != 1 && n2c != 1)
        {
            ++*v13;
            ARC_SPLINE_cre_strt_seg_2d(&v67, &v66, &v78, v12);
        }
        if (*(int*)&a8 != 1 && n4v != 1)
        {
            ++*v13;
            ARC_SPLINE_cre_strt_seg_2d(&v70, &v69, &v78, v11);
        }
        return;
    }


    if (!(r1 >= r2)) { v66 = p_add_mul(v71, u, r2); }
    else             { v67 = p_add_mul(v75, u, r1); }

    ARC_SPLINE_ask_parm_at_a_point_2d(a1, &v67, a5, &v76, v18,     (int*)&a7,     (int*)&a6);
    if (!a3) *(int*)&a7 = -1;
    ARC_SPLINE_ask_parm_at_a_point_2d(a2, &v66, a5, &v77, (double*)a8, (int*)&a7 + 1, (int*)&a6);
    int n2c = a4 ? *((int*)&a7 + 1) : -1;

    if (*(int*)&a7 == -1 && n2c == -1)
    {

        v71.x = 0.5 * (v66.x + v67.x);
        v71.y = 0.5 * (v66.y + v67.y);
        *v13 = 1;
        ARC_SPLINE_cre_strt_seg_2d(&v71, &v71, &v74, v12);
    }
}
