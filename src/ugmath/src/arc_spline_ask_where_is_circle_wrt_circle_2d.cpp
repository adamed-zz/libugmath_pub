







#include <math.h>

struct ARC_SPLINE_1_seg_2d_s
{
    int    tag;
    char   _pad0[0x24];
    double center_x;
    double center_y;
    char   _pad1[0x10];
    double radius;
};

int __cdecl ARC_SPLINE_ask_where_is_circle_wrt_circle_2d(
    ARC_SPLINE_1_seg_2d_s* seg1,
    ARC_SPLINE_1_seg_2d_s* seg2,
    double                 tol)
{
    if (!seg1)
        return 1;

    double x1 = seg1->center_x;
    double y1 = seg1->center_y;

    double r1;
    if (seg1->tag == 0)
        r1 = 1.0e19;
    else if (seg1->tag == 1)
        r1 = seg1->radius;
    else
        return 1;

    if (!seg2)
        return 1;

    double r2;
    if (seg2->tag == 0)
        r2 = 1.0e19;
    else if (seg2->tag == 1)
        r2 = seg2->radius;
    else
        return 1;

    double d = sqrt((x1 - seg2->center_x) * (x1 - seg2->center_x) +
                    (y1 - seg2->center_y) * (y1 - seg2->center_y));

    if (fabs(d - (r1 + r2)) <= tol)
        return 0;
    if (d > r1 + r2)
        return 1;

    int res = -1;
    double diff = r1 - r2;
    if (tol >= fabs(diff))
    {
        if (tol >= d)
            res = -6;
    }
    else if (r2 > r1)
    {
        double v = r2 - r1;
        if (tol >= fabs(v - d))
            res = -3;
        else if (d > v)
            res = -5;
    }
    else
    {
        if (tol >= fabs(diff - d))
            res = -2;
        else if (d > diff)
            res = -4;
    }
    return res;
}
