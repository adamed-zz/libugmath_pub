











namespace UGS { namespace Math { struct Point2; } }
struct ARC_SPLINE_1_seg_2d_s;

namespace UGS
{
namespace Math
{
struct Point2
{
    double x;
    double y;
};
}
}

struct ARC_SPLINE_1_seg_2d_s
{
    int    tag;
    int    sub;
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

void ARC_SPLINE_cre_single_point_circle_2d(const struct UGS::Math::Point2* p, struct ARC_SPLINE_1_seg_2d_s* seg)
{
    seg->tag = -1;
    seg->sub = 1;
    seg->d08 = p->x;
    seg->d10 = p->y;
    seg->d18 = 90.0;
    seg->d20 = 450.0;
    seg->d28 = p->x;
    seg->d30 = p->y;
    seg->d38 = 0.0;
    seg->d40 = 0.0;
    seg->d48 = 0.0;
    seg->d50 = 0.0;
}
