









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




void ARC_SPLINE_evaluate_arc_seg_2d(const ARC_SPLINE_1_seg_2d_s* seg, int within, double t,
                                    UGS::Math::Point2* pt, UGS::Math::Vector2* tan, int* status);

void ARC_SPLINE_cre_strt_seg_2d(const UGS::Math::Point2* start, const UGS::Math::Point2* end,
                                const UGS::Math::Vector2* tan, ARC_SPLINE_1_seg_2d_s* seg);

void ARC_SPLINE_ask_is_arc_rather_strt_2d(ARC_SPLINE_1_seg_2d_s* a1, double* a2, int* a3)
{
    *a3 = 0;
    UGS::Math::Point2 v11 = { 0.0, 0.0 };
    if (a1)
    {
        if (a1->type == 1)
        {
            double v5 = a1->radius;
            if (v5 > 1.0 / a2[2])
            {
                UGS::Math::Point2 v12;
                v12.x = a1->base_x;
                v12.y = a1->base_y;
                int v14 = 0;
                if (v5 < 1e-10)
                {
                    *a3 = 2;
                }
                else
                {
                    double v7 = a1->start * UBARC_K_DEG2RAD;
                    UGS::Math::Vector2 v10;
                    v10.x = cos(v7);
                    v10.y = sin(v7);
                    UGS::Math::Vector2 v13;
                    ARC_SPLINE_evaluate_arc_seg_2d(a1, 1, a1->end, &v11, &v13, &v14);
                    if (v14 > 0)
                        *a3 = 2;
                    else
                        ARC_SPLINE_cre_strt_seg_2d(&v12, &v11, &v10, a1);
                }
            }
        }
    }
}
