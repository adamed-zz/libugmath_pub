








namespace UGS { namespace Math { struct Point2; } }

struct ARC_SPLINE_1_seg_2d_s;


struct ARC_SPLINE_1_seg_2d_s
{
    int    tag;
    int    kind;
    double radius;
    double zero10;
    double angle0;
    double angle1;
    double cx;
    double cy;
    double zero38;
    double zero40;
    double r48;
    double r50;
};

namespace UGS { namespace Math { struct Point2 { double x; double y; }; } }





void ARC_SPLINE_cre_circle_from_center_and_radius_2d(struct UGS::Math::Point2* c,
                                                     double r,
                                                     struct ARC_SPLINE_1_seg_2d_s* seg)
{
    *(volatile int*)&seg->tag = 1;
    *(volatile int*)&seg->kind = 1;
    *(volatile double*)&seg->radius = r;
    *(volatile double*)&seg->zero10 = 0.0;
    *(volatile double*)&seg->angle0 = 90.0;
    *(volatile double*)&seg->angle1 = 450.0;
    *(volatile double*)&seg->cx = c->x;
    *(volatile double*)&seg->cy = c->y;
    *(volatile double*)&seg->zero38 = 0.0;
    *(volatile double*)&seg->zero40 = 0.0;
    seg->r48 = r;
    seg->r50 = r;
}
