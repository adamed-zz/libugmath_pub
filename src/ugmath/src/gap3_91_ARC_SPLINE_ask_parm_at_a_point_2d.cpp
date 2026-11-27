






#include <cmath>
#include <emmintrin.h>

struct ARC_SPLINE_1_seg_2d_s
{
    int    type;
    int    dir;
    double base_x;
    double base_y;
    double start_parm;
    double end_parm;
    double center_x;
    double center_y;
    double vec_x;
    double vec_y;
    double length_or_radius;
};

namespace UGS { namespace Math {
struct Point2  { double x; double y; };
struct Vector2 { double x; double y; };
}}

using UGS::Math::Point2;
using UGS::Math::Vector2;


double ARC_SPLINE_ask_dist_pt_to_line_2d(const Point2* pt, const Point2* origin,
                                         const Vector2* dir, double tol,
                                         Point2* closest, double* t, int* side);
double ARC_SPLINE_ask_dist_pt_to_line_seg_2d(const Point2* pt, const Point2* origin,
                                             const Point2* end, double tol, int clamp,
                                             Point2* closest, double* t_out,
                                             int* pos, int* side);
void ARC_SPLINE_evaluate_arc_seg_2d(const ARC_SPLINE_1_seg_2d_s* seg, int within,
                                    double t, Point2* pt, Vector2* tan_out, int* status);
int ARC_SPLINE_ask_is_parm_in_arc_domain(const ARC_SPLINE_1_seg_2d_s* seg, double tol,
                                         double* parm);

void h053(const double* y, const double* x, double* out);


static const double UBARC_K_DEG2RAD = 0.01745329251994328;

static const double UBARC_K_RAD2DEG = 57.29577951308235;

void ARC_SPLINE_ask_parm_at_a_point_2d(
    const ARC_SPLINE_1_seg_2d_s* seg,
    const Point2* pt,
    const double* const tol,
    Point2* closest,
    double* parm,
    int* status,
    int* flag)
{

    *flag = 0;
    *parm = 0.0;
    closest->x = 0.0;
    closest->y = 0.0;

    int status_local = 0;
    Vector2 vec = {0.0, 0.0};
    Point2 p_end = {0.0, 0.0};
    Point2 p_base = {0.0, 0.0};
    Point2 center = {0.0, 0.0};
    Point2 eval_pt;
    _mm_storeu_pd(&eval_pt.x, _mm_setzero_pd());
    Vector2 tangents;

    double len_param = 0.0;
    int dir = 0;
    double end_p = 0.0;
    double start_p = 0.0;
    double bx, by, cy, cx, radius;

    if (seg != 0)
    {
        dir = seg->dir;
        end_p = seg->end_parm;
        start_p = seg->start_parm;
        double sweep = (end_p - start_p) * (double)dir;
        if (sweep < 0.0)
        {
            sweep += 360.0;
            end_p = (double)dir * sweep + start_p;
        }
        cy = seg->center_y;
        bx = seg->base_x;
        by = seg->base_y;
        cx = seg->center_x;
        int type = seg->type;
        p_base.x = bx;
        p_base.y = by;
        center.x = cx;
        center.y = cy;

        if (type == 0)
        {

            double vx = seg->vec_x;
            double vy = seg->vec_y;
            len_param = seg->length_or_radius;
            vec.x = vx;
            vec.y = vy;
            p_end.x = vx * len_param + bx;
            p_end.y = vy * len_param + by;
            goto LINE_PATH;
        }
        if (type != 1)
            goto LINE_PATH;

        radius = seg->length_or_radius;
        if (1.0e-10 > radius)
            goto LINE_PATH;
        len_param = radius * UBARC_K_DEG2RAD * sweep;
        double inv_radius = 1.0 / radius;
        double ang0 = start_p * UBARC_K_DEG2RAD;
        vec.x = cos(ang0);
        vec.y = sin(ang0);
        ARC_SPLINE_evaluate_arc_seg_2d(seg, 1, end_p, &p_end, &tangents, &status_local);
        if (1.0e-10 > inv_radius)
            goto LINE_PATH;

        {
            double dy = pt->y - cy;
            double dx = pt->x - cx;
            p_base.y = dy;
            p_base.x = dx;
            double dist = std::sqrt(dx * dx + dy * dy);
            if (1.0e-10 > dist)
            {

                closest->x = bx;
                closest->y = by;
                *parm = start_p;
                *status = 0;
                return;
            }

            __m128d u = _mm_mul_pd(_mm_set1_pd(1.0 / dist), _mm_loadu_pd(&p_base.x));
            double ux = _mm_cvtsd_f64(u);
            double uy = _mm_cvtsd_f64(_mm_unpackhi_pd(u, u));
            __m128d cl = _mm_add_pd(
                _mm_mul_pd(_mm_set1_pd(1.0 / inv_radius),
                           _mm_set_pd(uy, ux)),
                _mm_loadu_pd(&center.x));
            _mm_storeu_pd(&closest->x, cl);


            double x_arg = -uy;
            double y_arg = ux;
            if (dir == -1)
            {
                x_arg = -x_arg;
                y_arg = -y_arg;
            }
            double angle;
            h053(&y_arg, &x_arg, &angle);

            double deg = angle * UBARC_K_RAD2DEG;
            *parm = deg;
            if (fabs(deg - start_p) <= 1.0e-10)
            {
                *parm = start_p;
                deg = start_p;
            }
            if (dir == 1)
            {
                double hi = start_p + 360.0;
                if (fabs(deg - hi) <= 1.0e-10)
                {
                    *parm = hi;
                    deg = hi;
                }
                if (start_p > deg)
                {
                    deg += 360.0;
                    *parm = deg;
                }
                else if (deg >= hi)
                {
                    deg -= 360.0;
                    *parm = deg;
                }
            }
            else if (dir == -1)
            {
                double lo = start_p - 360.0;
                if (fabs(deg - lo) <= 1.0e-10)
                {
                    *parm = lo;
                    deg = lo;
                }
                if (lo >= deg)
                {
                    deg += 360.0;
                    *parm = deg;
                }
                else if (deg > start_p)
                {
                    deg -= 360.0;
                    *parm = deg;
                }
            }

            int dom = ARC_SPLINE_ask_is_parm_in_arc_domain(seg, tol[1], parm);
            *status = dom;
            if (dom == 1)
            {
                if (dir == 1)
                {
                    double v40 = start_p + 360.0 - *parm;
                    double v41 = *parm - end_p;
                    if (v41 >= v40)
                        *parm = start_p - v40;
                    else
                        *parm = end_p + v41;
                }
                else if (dir == -1)
                {
                    double v43 = end_p - *parm;
                    double v44 = *parm - (start_p - 360.0);
                    if (v43 >= v44)
                        *parm = start_p + v44;
                    else
                        *parm = end_p - v43;
                }
            }

            ARC_SPLINE_evaluate_arc_seg_2d(seg, 1, *parm, &eval_pt, &tangents, &status_local);
            if (status_local > 0 ||
                std::sqrt((closest->x - eval_pt.x) * (closest->x - eval_pt.x) +
                          (closest->y - eval_pt.y) * (closest->y - eval_pt.y)) > tol[0])
            {
                *flag = 1;
            }
            return;
        }
    }

LINE_PATH:

    {
        if (tol[0] >= len_param)
        {
            ARC_SPLINE_ask_dist_pt_to_line_2d(pt, &p_base, &vec, tol[0],
                                              closest, parm, &status_local);
            if (tol[0] >= fabs(*parm - 0.0))
                *status = 0;
            else if (*parm < 0.0)
                *status = 1;
        }
        else
        {
            ARC_SPLINE_ask_dist_pt_to_line_seg_2d(pt, &p_base, &p_end, tol[0], 0,
                                                  closest, parm, status, &status_local);
        }
    }
}
