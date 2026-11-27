












#include <cmath>
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
    int    dir;
    double base_x;
    double base_y;
    double start;
    double end;
    double cen_x;
    double cen_y;
    double dir_x;
    double dir_y;
    double radius;
    double parm;
};


double ARC_SPLINE_ask_dist_pt_to_line_seg_2d(const UGS::Math::Point2* pt,
                                             const UGS::Math::Point2* origin,
                                             const UGS::Math::Point2* end, double tol,
                                             int clamp, UGS::Math::Point2* closest,
                                             double* t_out, int* pos, int* side);
void ARC_SPLINE_evaluate_arc_seg_2d(const ARC_SPLINE_1_seg_2d_s* seg, int within, double t,
                                    UGS::Math::Point2* pt, UGS::Math::Vector2* tan_out,
                                    int* status);
void ARC_SPLINE_ask_parm_at_a_point_2d(const ARC_SPLINE_1_seg_2d_s* seg,
                                       const UGS::Math::Point2* pt, const double* tol,
                                       UGS::Math::Point2* pt_on_seg, double* parm_out,
                                       int* pos, int* status);


static const double UBARC_K_DEG2RAD = 0.01745329251994328;

double ARC_SPLINE_ask_dist_pt_to_1_seg_2d(
    ARC_SPLINE_1_seg_2d_s* seg,
    UGS::Math::Point2* pt,
    int within,
    double* tol,
    UGS::Math::Point2* closest,
    double* parm,
    int* pos,
    int* status)
{
    UGS::Math::Point2  origin;
    UGS::Math::Point2  endpt;
    UGS::Math::Point2  onseg;
    UGS::Math::Vector2 tangent;
    double arclen   = 0.0;
    double unit_x   = 0.0;
    double unit_y   = 0.0;
    double base_x;
    double base_y;
    double start;
    double end;
    int    dir;
    int    st;
    double tparm;

    closest->x = 0.0;
    closest->y = 0.0;
    *parm      = 0.0;
    *pos       = -1;
    *status    = 0;
    origin.x = 0.0;
    origin.y = 0.0;
    endpt.x  = 0.0;
    endpt.y  = 0.0;
    onseg.x  = 0.0;
    onseg.y  = 0.0;

    if (seg != nullptr)
    {
        dir   = seg->dir;
        end   = seg->end;
        start = seg->start;
        int type = seg->type;
        double span = (end - start) * (double)dir;
        if (span < 0.0)
        {
            span += 360.0;
            end = (double)dir * span + start;
        }
        base_x = seg->base_x;
        base_y = seg->base_y;
        origin.x = base_x;
        origin.y = base_y;
        if (type == 0)
        {
            arclen = seg->radius;
            unit_x = seg->dir_x;
            unit_y = seg->dir_y;
            endpt.x = unit_x * arclen + base_x;
            endpt.y = unit_y * arclen + base_y;
        }
        else
        {
            if (type != 1)
                goto call_line;
            double radius = seg->radius;
            if (radius < 1.0e-10)
                goto call_line;
            {
                double ang  = start * UBARC_K_DEG2RAD;
                arclen      = radius * UBARC_K_DEG2RAD;
                double invr = 1.0 / radius;
                arclen *= span;
                unit_x = cos(ang);
                unit_y = sin(ang);
                ARC_SPLINE_evaluate_arc_seg_2d(seg, 1, end, &endpt, &tangent, &st);
                if (invr < 1.0e-10)
                    goto call_line;
                ARC_SPLINE_ask_parm_at_a_point_2d(seg, pt, tol, &onseg, &tparm, pos, &st);
                if (st > 0)
                {
                    *status = 1;
                    return 0.0;
                }
                if (*pos == 1 && within != 0)
                {
                    if (dir > 0)
                    {
                        if (start > tparm)
                        {
                            *parm = start;
                            closest->x = base_x;
                            closest->y = base_y;
                        }
                        else if (tparm > end)
                        {
                            *parm = end;
                            *closest = endpt;
                        }
                    }
                    else if (dir < 0)
                    {
                        if (end > tparm)
                        {
                            *parm = end;
                            *closest = endpt;
                        }
                        else if (tparm > start)
                        {
                            *parm = start;
                            closest->x = base_x;
                            closest->y = base_y;
                        }
                    }
                }
                else
                {
                    *parm = tparm;
                    closest->x = onseg.x;
                    closest->y = onseg.y;
                }
                double dy = closest->y - pt->y;
                double dx = closest->x - pt->x;
                return sqrt(dx * dx + dy * dy);
            }
        }
    }

call_line:
    double t = *tol;
    if (t >= arclen)
    {

        __m128d orgv = _mm_loadu_pd(&origin.x);
        __m128d dirv = _mm_set_pd(unit_y, unit_x);
        __m128d sumv = _mm_add_pd(orgv, dirv);
        _mm_store_sd(&endpt.x, sumv);
        _mm_store_sd(&endpt.y, _mm_unpackhi_pd(sumv, sumv));
    }
    return ARC_SPLINE_ask_dist_pt_to_line_seg_2d(pt, &origin, &endpt, t, within, closest,
                                                parm, pos, &st);
}
