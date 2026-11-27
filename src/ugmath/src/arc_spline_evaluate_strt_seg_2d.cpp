








struct ARC_SPLINE_1_seg_2d_s;
namespace UGS { namespace Math { struct Point2; struct Vector2; } }


struct ARC_SPLINE_1_seg_2d_s
{
    int    tag;
    int    _pad;
    double d1;
    double d2;
    double d3;
    double d4;
    double d5;
    double d6;
    double d7;
    double d8;
};

namespace UGS { namespace Math {
struct Point2  { double x, y; };
struct Vector2 { double x, y; };
} }

void ARC_SPLINE_evaluate_strt_seg_2d(
    struct ARC_SPLINE_1_seg_2d_s* a,
    double t,
    struct UGS::Math::Point2* pt,
    struct UGS::Math::Vector2* tan,
    int* status)
{
    *status = 0;
    if (a->tag != 0)
    {
        *status = 1;
        return;
    }
    double v6 = a->d7;
    double v7 = a->d1;
    double v8 = a->d2;
    tan->x = v6;
    double v9 = a->d8;
    tan->y = v9;




    *(volatile double*)pt = v6 * t + v7;
    *((volatile double*)pt + 1) = v9 * t + v8;
}
