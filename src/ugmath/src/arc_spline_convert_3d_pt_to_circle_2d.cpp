














#include <math.h>

namespace UGS { namespace Math { struct Point3; } }
struct ARC_SPLINE_1_seg_2d_s;

namespace UGS
{
namespace Math
{
struct Point3
{
    double x;
    double y;
    double z;
};
}
}

struct ARC_SPLINE_1_seg_2d_s
{
    int    tag;
    int    d04;
    double d08;
    double d10;
    double d18;
    double d20;
    double d28;
    double d30;
    double d38;
    double d40;
    double d48;
    double d50;
};

void __cdecl ARC_SPLINE_convert_3d_pt_to_circle_2d(UGS::Math::Point3* p, bool* created,
                                                   ARC_SPLINE_1_seg_2d_s* seg)
{
    const double x = p->x;
    const double y = p->y;
    const double rr = x * x + y * y - p->z;
    double r;
    if (fabs(rr - 0.0) <= 0x1.79ca10c924224p-67)
    {
        *created = true;
        r = 0.0;
    }
    else if (rr > 0.0)
    {
        *created = true;
        r = sqrt(rr);
        if (!(r >= 0.0))
            return;
    }
    else
    {
        *created = false;
        return;
    }


    *(volatile int*)&seg->tag = 1;
    *(volatile int*)&seg->d04 = 1;
    *(volatile double*)&seg->d08 = r;
    *(volatile double*)&seg->d10 = 0.0;
    *(volatile double*)&seg->d18 = 90.0;
    *(volatile double*)&seg->d20 = 450.0;
    *(volatile double*)&seg->d28 = x;
    *(volatile double*)&seg->d30 = y;
    *(volatile double*)&seg->d38 = 0.0;
    *(volatile double*)&seg->d40 = 0.0;
    seg->d48 = r;
    seg->d50 = r;
}
