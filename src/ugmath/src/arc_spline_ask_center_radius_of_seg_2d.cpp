








struct ARC_SPLINE_1_seg_2d_s
{
    int    tag;
    char   _pad0[0x24];
    double center_x;
    double center_y;
    char   _pad1[0x10];
    double radius;
};

namespace UGS { namespace Math {
struct Point2
{
    double x;
    double y;
};
} }

void ARC_SPLINE_ask_center_radius_of_seg_2d(
    const ARC_SPLINE_1_seg_2d_s* seg,
    int* tag,
    double* radius,
    UGS::Math::Point2* center,
    int* err)
{
    *tag = -1;
    *radius = 0.0;
    *err = 0;
    if (!seg)
    {
        *err = 1;
        return;
    }
    *tag = seg->tag;
    center->x = seg->center_x;
    center->y = seg->center_y;
    int t = seg->tag;
    if (t == -1)
    {
        *radius = 0.0;
        t = seg->tag;
    }
    if (t == 0)
    {
        *radius = 1.0e19;
    }
    else if (t == 1)
    {
        double r = seg->radius;
        *radius = r;
        if (r < 1.0e-10)
            *tag = -1;
    }
    else
    {
        *err = 2;
    }
}
