





#include <cmath>


struct ARC_SPLINE_1_seg_2d_s
{
    int    type;
    int    dir;
    double base_x;
    double base_y;
    double start;
    double end;
    unsigned char _pad_28[0x20];
    double radius;
};

namespace UGS { namespace Math {
struct Point2  { double x; double y; };
struct Vector2 { double x; double y; };
}}


static const double UBARC_K_DEG2RAD = 0.01745329251994328;

void ARC_SPLINE_evaluate_arc_seg_2d(
    const ARC_SPLINE_1_seg_2d_s* seg,
    int within,
    double t,
    UGS::Math::Point2* pt,
    UGS::Math::Vector2* tan_out,
    int* status)
{
    *status = 0;
    if (seg->type == 0)
    {
        *status = 1;
        return;
    }

    int    dir    = seg->dir;
    double start  = seg->start;
    double end    = seg->end;
    double radius = seg->radius;

    double tt = t;
    if (fabs(tt - start) <= 1e-10)
        tt = start;
    if (fabs(tt - end) <= 1e-10)
        tt = end;

    double ang = tt * UBARC_K_DEG2RAD;
    tan_out->x = cos(ang);
    tan_out->y = sin(ang);

    double bx = seg->base_x;
    double by = seg->base_y;
    double c0 = cos(start * UBARC_K_DEG2RAD);
    double s0 = sin(start * UBARC_K_DEG2RAD);

    if (dir == 1)
    {
        if ((start > tt || tt > end) && !within)
        {
            *status = 2;
        }
        else
        {
            double d = (tt - start) * UBARC_K_DEG2RAD;
            double s = sin(d) * radius;
            double c = radius - cos(d) * radius;

            double vx = s * c0 + bx - c * s0;
            double vy = s * s0 + by + c * c0;
            *(volatile double *)&pt->y = vy;
            *(volatile double *)&pt->x = vx;
        }
    }
    else if (dir == -1)
    {
        if ((end > tt || tt > start) && !within)
        {
            *status = 3;
        }
        else
        {
            double d = (start - tt) * UBARC_K_DEG2RAD;
            double s = sin(d) * radius;
            double c = cos(d) * radius - radius;

            double vx = s * c0 + bx - c * s0;
            double vy = s * s0 + by + c * c0;
            *(volatile double *)&pt->y = vy;
            *(volatile double *)&pt->x = vx;
        }
    }
    else
    {
        pt->x = bx;
        pt->y = by;
    }
}
