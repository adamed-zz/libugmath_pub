















#include <math.h>
#include <emmintrin.h>

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
    int    type;
    int    nsegs;
    double strt_x;
    double strt_y;
    double start;
    double end;
    double center_x;
    double center_y;
    double dir_x;
    double dir_y;
    double parm;
    double radius;
};
static_assert(sizeof(ARC_SPLINE_1_seg_2d_s) == 0x58, "seg layout");


__declspec(dllimport) extern int MACH__checking_level;
__declspec(dllimport) void ERROR_assertion_failed(const char* file, int line,
                                                  const char* fmt, ...);


double ARC_SPLINE_ask_dist_pt_to_line_2d(const UGS::Math::Point2* pt,
                                         const UGS::Math::Point2* origin,
                                         const UGS::Math::Vector2* dir,
                                         double tol,
                                         UGS::Math::Point2* closest,
                                         double* t, int* side);
int VEC2_unitize(const UGS::Math::Vector2* u, double tol, double* len_out,
                 UGS::Math::Vector2* out);
bool VEC2_is_perpendicular(const UGS::Math::Vector2* u,
                           const UGS::Math::Vector2* v, double tol);
void ARC_SPLINE_cre_circle_from_point_tangent_radius_2d(
    const UGS::Math::Point2* point, const UGS::Math::Vector2* tangent,
    double radius, int sense, ARC_SPLINE_1_seg_2d_s* seg);
void ARC_SPLINE_cre_circle_thru_2_points_tangent_to_line(
    const UGS::Math::Point2* p1, const UGS::Math::Point2* p2,
    const UGS::Math::Point2* p3, UGS::Math::Vector2* dir,
    const double* const tol,
    int* side, UGS::Math::Point2* o1, UGS::Math::Point2* o2,
    ARC_SPLINE_1_seg_2d_s* s1, ARC_SPLINE_1_seg_2d_s* s2, int* n);
void ARC_SPLINE_cre_strt_seg_2d(const UGS::Math::Point2* a,
                                const UGS::Math::Point2* b,
                                const UGS::Math::Vector2* dir,
                                ARC_SPLINE_1_seg_2d_s* seg);



static bool sub_1800018E0(const UGS::Math::Point2* c, double radius,
                          const UGS::Math::Point2* cand, double otherRadius,
                          double tol, int* flag, UGS::Math::Point2* out)
{


    out->x = 0.0;
    out->y = 0.0;
    *flag = 1;
    double dx = cand->x - c->x;
    double dy = cand->y - c->y;
    double d = sqrt(dx * dx + dy * dy);
    double sumr = radius + otherRadius;
    if (tol >= fabs(d - sumr))
    {
        *flag = 0;

        double inv = 1.0 / d;
        double ux = inv * dx;
        double uy = inv * dy;
        out->x = c->x + radius * ux;
        out->y = c->y + radius * uy;
        return true;
    }
    if (d > sumr)
        return false;
    *flag = -1;
    double rdiff = radius - otherRadius;
    if (!(tol < fabs(rdiff)))
    {
        if (tol >= d)
            *flag = -6;
        return false;
    }
    if (otherRadius <= radius)
    {
        if (tol >= fabs(rdiff - d))
        {
            *flag = -2;
            double inv = 1.0 / d;
            double ux = inv * dx;
            double uy = inv * dy;
            out->x = c->x + radius * ux;
            out->y = c->y + radius * uy;
            return true;
        }
        int v = *flag;
        if (d > rdiff)
            v = -4;
        *flag = v;
        return false;
    }
    if (tol < fabs((otherRadius - radius) - d))
    {
        if (d > otherRadius - radius)
            *flag = -5;
        return false;
    }
    *flag = -3;
    double inv = 1.0 / d;
    double ux = inv * dx;
    double uy = inv * dy;
    out->x = c->x - radius * ux;
    out->y = c->y - radius * uy;
    return true;
}


static void clear_seg(ARC_SPLINE_1_seg_2d_s* s)
{
    s->type = 0;
    s->nsegs = 0;
    s->strt_x = 0.0;
    s->strt_y = 0.0;
    s->start = 0.0;
    s->end = 0.0;
    s->center_x = 0.0;
    s->center_y = 0.0;
    s->dir_x = 0.0;
    s->dir_y = 0.0;
    s->parm = 0.0;
    s->radius = 0.0;
}

void ARC_SPLINE_cre_circle_tangent_to_circle_and_line_at_pt_2d(
    UGS::Math::Point2* pt, UGS::Math::Vector2* dir,
    ARC_SPLINE_1_seg_2d_s* circle, double* tol, int a5, int* n,
    UGS::Math::Point2* p1, UGS::Math::Point2* p2,
    ARC_SPLINE_1_seg_2d_s* seg1, ARC_SPLINE_1_seg_2d_s* seg2, int* a11,
    int* err)
{
    int* n_ = n;
    int* err_ = err;
    ARC_SPLINE_1_seg_2d_s* circle_ = circle;
    *n_ = 0;
    p1->x = 0.0;
    p1->y = 0.0;
    UGS::Math::Point2 ctr = {0.0, 0.0};
    UGS::Math::Point2 wp = {0.0, 0.0};
    p2->x = 0.0;
    p2->y = 0.0;
    UGS::Math::Point2 v79 = {0.0, 0.0};
    UGS::Math::Point2 v80 = {0.0, 0.0};
    *a11 = 0;
    *err_ = 0;
    UGS::Math::Point2 v77 = {0.0, 0.0};
    UGS::Math::Point2 v76 = {0.0, 0.0};
    UGS::Math::Point2 mirror = {0.0, 0.0};
    UGS::Math::Point2 tangm = {0.0, 0.0};
    UGS::Math::Vector2 perp = {0.0, 0.0};
    ARC_SPLINE_1_seg_2d_s s1;
    ARC_SPLINE_1_seg_2d_s s2;
    double v75 = 0.0;
    const double utol = 1.0e-10;
    double v60, v67, rad2, rad3;
    int v70;
    bool v57 = false;

    if (MACH__checking_level > 0 && (!seg1 || !seg2))
        ERROR_assertion_failed(
            "o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\arc_spline_apollonian_constructions.c",
            10490, "%s", "seg_ptr_1 && seg_ptr_2");

    *reinterpret_cast<int*>(&n) = 0;
    if (!circle_)
    {
        *err_ = 1;
        return;
    }
    ctr.x = circle_->center_x;
    ctr.y = circle_->center_y;
    double cx = ctr.x;
    double cy = ctr.y;
    if (circle_->type != 1)
    {
        *err_ = 1;
        return;
    }
    double px = pt->x;
    double py = pt->y;
    double r = circle_->parm;
    double d1 = sqrt((cy - py) * (cy - py) + (cx - px) * (cx - px));
    double tv = *tol;
    if (tv >= fabs(d1 - r))
    {
        ARC_SPLINE_ask_dist_pt_to_line_2d(&ctr, pt, dir, tv, &wp,
                                          reinterpret_cast<double*>(&circle),
                                          reinterpret_cast<int*>(&err));
        wp.x = px - cx;
        wp.y = py - cy;
        VEC2_unitize(reinterpret_cast<UGS::Math::Vector2*>(&wp), utol, &v75,
                     reinterpret_cast<UGS::Math::Vector2*>(&wp));
        double sn = sin(0.26179938779914924);
        if (VEC2_is_perpendicular(dir,
                                  reinterpret_cast<UGS::Math::Vector2*>(&wp),
                                  sn))
        {
            *n_ = 3;
            seg1->type = circle_->type;
            seg1->nsegs = circle_->nsegs;
            seg1->strt_x = circle_->strt_x;
            seg1->strt_y = circle_->strt_y;
            seg1->start = circle_->start;
            seg1->end = circle_->end;
            seg1->center_x = circle_->center_x;
            seg1->center_y = circle_->center_y;
            seg1->dir_x = circle_->dir_x;
            seg1->dir_y = circle_->dir_y;
            seg1->parm = circle_->parm;
            seg1->radius = circle_->radius;
            seg2->type = circle_->type;
            seg2->nsegs = circle_->nsegs;
            seg2->strt_x = circle_->strt_x;
            seg2->strt_y = circle_->strt_y;
            seg2->start = circle_->start;
            seg2->end = circle_->end;
            seg2->center_x = circle_->center_x;
            seg2->center_y = circle_->center_y;
            seg2->dir_x = circle_->dir_x;
            seg2->dir_y = circle_->dir_y;
            seg2->parm = circle_->parm;
            seg2->radius = circle_->radius;
            p1->x = px;
            p1->y = py;
            p2->x = px;
            p2->y = py;
        }
        return;
    }
    double dist = ARC_SPLINE_ask_dist_pt_to_line_2d(
        &ctr, pt, dir, tv, &wp, reinterpret_cast<double*>(&circle),
        reinterpret_cast<int*>(&err));
    if (tv > dist)
    {
        double d2 = sqrt((py - cy) * (py - cy) + (px - cx) * (px - cx));
        double r2;
        if (*reinterpret_cast<int*>(&err) == -1)
        {
            *a11 = 2;
            r2 = r - d2 / r * d2;
        }
        else
        {
            r2 = d2 / r * d2 - r;
        }
        double half = r2 * 0.5;
        clear_seg(seg1);
        ARC_SPLINE_cre_circle_from_point_tangent_radius_2d(pt, dir, half, 1,
                                                           seg1);
        clear_seg(seg2);
        ARC_SPLINE_cre_circle_from_point_tangent_radius_2d(pt, dir, half, -1,
                                                           seg2);
        *n_ = 2;
        wp.x = seg1->center_x - cx;
        wp.y = seg1->center_y - cy;
        VEC2_unitize(reinterpret_cast<UGS::Math::Vector2*>(&wp), utol, &v75,
                     reinterpret_cast<UGS::Math::Vector2*>(&wp));
        __m128d rad = _mm_set1_pd(r);
        __m128d cv = _mm_loadu_pd(&ctr.x);
        __m128d uv = _mm_loadu_pd(&wp.x);
        _mm_storeu_pd(&p1->x, _mm_add_pd(_mm_mul_pd(uv, rad), cv));
        wp.x = seg2->center_x - cx;
        wp.y = seg2->center_y - cy;
        VEC2_unitize(reinterpret_cast<UGS::Math::Vector2*>(&wp), utol, &v75,
                     reinterpret_cast<UGS::Math::Vector2*>(&wp));
        __m128d uv2 = _mm_loadu_pd(&wp.x);
        _mm_storeu_pd(&p2->x, _mm_add_pd(_mm_mul_pd(rad, uv2), cv));
        return;
    }
    double wx = dir->x;
    double wy = -dir->y;
    if (*reinterpret_cast<int*>(&err) != -1)
    {
        wy = -wy;
        wx = -wx;
    }
    perp.x = wy;
    perp.y = wx;
    mirror.x = 0.0;
    mirror.y = 0.0;
    ARC_SPLINE_ask_dist_pt_to_line_2d(&ctr, pt, &perp, tv, &mirror,
                                      reinterpret_cast<double*>(&circle),
                                      reinterpret_cast<int*>(&err));
    {
        __m128d closest = _mm_loadu_pd(&mirror.x);
        __m128d off = _mm_set_pd(mirror.y - cy, mirror.x - cx);
        _mm_storeu_pd(&mirror.x, _mm_add_pd(closest, off));
    }
    int side = (r >= dist) ? -1 : 1;
    *reinterpret_cast<int*>(&circle) = side;
    {
        __m128d rad = _mm_set1_pd(r);
        __m128d nrad = _mm_set1_pd(-r);
        __m128d pv = _mm_loadu_pd(&pt->x);
        __m128d dv = _mm_loadu_pd(&perp.x);
        _mm_storeu_pd(&perp.x, _mm_add_pd(_mm_mul_pd(rad, dv), pv));
        _mm_storeu_pd(&tangm.x, _mm_add_pd(_mm_mul_pd(nrad, dv), pv));
    }
    if (tv >= fabs(dist - r))
        goto LABEL_31;
    ARC_SPLINE_cre_circle_thru_2_points_tangent_to_line(
        &ctr, &mirror, reinterpret_cast<UGS::Math::Point2*>(&perp), dir, tol,
        reinterpret_cast<int*>(&err), &v77, &v76, &s1, &s2,
        reinterpret_cast<int*>(&n));
    if (*reinterpret_cast<int*>(&n) > 0)
    {
        *err_ = 3;
        return;
    }
    if (*reinterpret_cast<int*>(&err) == 1)
    {
        if (s1.type == 0)
            goto LABEL_31;
    }
    else if (*reinterpret_cast<int*>(&err) <= 0)
    {
        v57 = false;
        goto LABEL_45;
    }

    *reinterpret_cast<int*>(&n) = 0;
    wp = *reinterpret_cast<UGS::Math::Point2*>(&s1.center_x);
    if (s1.type == 0)
        rad2 = 1.0e19;
    else if (s1.type == 1)
        rad2 = s1.parm;
    else
    {
        *err_ = 4;
        return;
    }
    v60 = fabs((double)*reinterpret_cast<int*>(&circle) * r + rad2);
    ARC_SPLINE_ask_dist_pt_to_line_2d(&wp, pt, dir, *tol, &v79,
                                      reinterpret_cast<double*>(&perp),
                                      reinterpret_cast<int*>(&circle));
    if (*reinterpret_cast<int*>(&circle) == -1)
        *reinterpret_cast<int*>(&circle) = 1;
    else
        *reinterpret_cast<int*>(&circle) = -1;
    if (sub_1800018E0(&ctr, r, &wp, v60, *tol, reinterpret_cast<int*>(&p1),
                      p1))
    {
        if (*reinterpret_cast<int*>(&p1))
            *a11 = 1;
        clear_seg(seg1);
        ARC_SPLINE_cre_circle_from_point_tangent_radius_2d(
            pt, dir, v60, *reinterpret_cast<int*>(&circle), seg1);
        ++*n_;
    }
    else
    {
        *err_ = 5;
        return;
    }
    v57 = false;
LABEL_45:
    if (a5 == 1 || v57)
        return;
    ARC_SPLINE_cre_circle_thru_2_points_tangent_to_line(
        &ctr, &mirror, &tangm, dir, tol, reinterpret_cast<int*>(&err), &v77,
        &v76, &s1, &s2, reinterpret_cast<int*>(&n));
    if (*reinterpret_cast<int*>(&n) > 0)
    {
        *err_ = 6;
        return;
    }
    if (*reinterpret_cast<int*>(&err) > 0)
    {
        mirror = *reinterpret_cast<UGS::Math::Point2*>(&s1.center_x);
        if (s1.type == 0)
            rad3 = 1.0e19;
        else if (s1.type == 1)
            rad3 = s1.parm;
        else
        {
            *err_ = 7;
            return;
        }
        v67 = fabs(rad3 - r * 1.0);
        ARC_SPLINE_ask_dist_pt_to_line_2d(&mirror, pt, dir, *tol, &v80,
                                          reinterpret_cast<double*>(&n),
                                          reinterpret_cast<int*>(&p1));
        v70 = (*reinterpret_cast<int*>(&p1) == -1) ? 1 : -1;
        if (sub_1800018E0(&ctr, r, &mirror, v67, *tol,
                          reinterpret_cast<int*>(&p1), p2))
        {
            if (*reinterpret_cast<int*>(&p1))
                ++*a11;
            clear_seg(seg2);
            ARC_SPLINE_cre_circle_from_point_tangent_radius_2d(pt, dir, v67,
                                                               v70, seg2);
            ++*n_;
        }
        else
        {
            *err_ = 8;
        }
    }
    return;

LABEL_31:
    ARC_SPLINE_cre_strt_seg_2d(pt, pt, dir, seg1);
    p1->x = wp.x;
    p1->y = wp.y;
    v57 = true;
    ++*n_;
    goto LABEL_45;
}
