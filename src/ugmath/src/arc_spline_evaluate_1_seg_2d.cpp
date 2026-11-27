













namespace UGS
{
namespace Math
{
struct Point2
{
    double x;
    double y;
};

struct Vector2
{
    double x;
    double y;
};
}
}


struct ARC_SPLINE_1_seg_2d_s
{
    int    tag;
    int    sign;
    double base_x;
    double base_y;
    double angle0;
    double angle1;
    double f28;
    double f30;
    double dir_x;
    double dir_y;
    double radius;
};





void ARC_SPLINE_evaluate_arc_seg_2d(const ARC_SPLINE_1_seg_2d_s* seg, int idx, double t,
                                    UGS::Math::Point2* pt, UGS::Math::Vector2* tan, int* err);

void ARC_SPLINE_evaluate_1_seg_2d(ARC_SPLINE_1_seg_2d_s* seg, int idx, double t,
                                  UGS::Math::Point2* pt, UGS::Math::Vector2* tan, int* err)
{

    if (!seg->tag)
    {
        *err = 0;
        if (seg->tag)
        {
            *err = 1;
        }
        else
        {
            double v7 = seg->dir_x;
            double v8 = seg->base_x;
            double v9 = seg->base_y;
            tan->x = v7;
            double v10 = seg->dir_y;
            tan->y = v10;





            *(volatile double*)pt = v7 * t + v8;
            *((volatile double*)pt + 1) = v10 * t + v9;
        }
    }
    else
    {

        ARC_SPLINE_evaluate_arc_seg_2d(seg, idx, t, pt, tan, err);
    }
}
