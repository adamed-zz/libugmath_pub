









#include <cmath>

namespace UGS {
namespace Math {
struct Point2 {
    double x;
    double y;
};
}
}


struct ARC_SPLINE_1_seg_2d_s {
    int kind;
    int flags;
    double base_x;
    double base_y;
    double ang0;
    double ang1;
    double center_x;
    double center_y;
    double dir_x;
    double dir_y;
    double radius;
    double pad_50;
};

int ARC_SPLINE_ask_where_is_pt_wrt_circle_2d(UGS::Math::Point2* a1, ARC_SPLINE_1_seg_2d_s* a2, double a3)
{
    double v3 = a3 * a3;
    double cx = *((double*)a2 + 5);
    double cy = *((double*)a2 + 6);
    double v4 = !*((int*)a2) ? 1.0e19 : *((double*)a2 + 9);
    double v5 = (cx - a1->x) * (cx - a1->x) + (cy - a1->y) * (cy - a1->y) - v4 * v4;
    if (v3 >= fabs(fabs(v5) - v3))
        return 0;
    return (v5 < 0.0) ? -1 : 1;
}
