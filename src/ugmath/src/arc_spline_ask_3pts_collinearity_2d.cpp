







namespace UGS
{
namespace Math
{
struct Point2
{
    double x, y;
};

struct Vector2
{
    double x, y;
};
}
}









void __cdecl ARC_SPLINE_re_order_3pts_2d(double tol, UGS::Math::Point2* a2,
                                         UGS::Math::Point2* a3, UGS::Math::Point2* a4,
                                         int* a5);







int __cdecl VEC2_unitize(const UGS::Math::Vector2* u, double tol, double* len_out,
                         UGS::Math::Vector2* out);

#include <math.h>

union Slot
{
    UGS::Math::Point2 pt;
    UGS::Math::Vector2 vec;
};

int __cdecl ARC_SPLINE_ask_3pts_collinearity_2d(const UGS::Math::Point2* a1,
                                                const UGS::Math::Point2* a2,
                                                const UGS::Math::Point2* a3,
                                                const double* const a4, int a5, int* a6)
{
    int result = 0;
    *a6 = -1;
    Slot p[3];
    p[0].pt = *a1;
    p[1].pt = *a2;
    p[2].pt = *a3;
    double len3;
    ARC_SPLINE_re_order_3pts_2d(a4[0], &p[0].pt, &p[1].pt, &p[2].pt, (int*)&len3);

    double d3x = p[2].pt.x - p[0].pt.x;
    double d3y = p[2].pt.y - p[0].pt.y;
    double d1x = p[0].pt.x - p[1].pt.x;
    double d1y = p[0].pt.y - p[1].pt.y;
    double d2x = p[2].pt.x - p[1].pt.x;
    double d2y = p[2].pt.y - p[1].pt.y;
    p[2].vec.x = d3x;
    p[2].vec.y = d3y;
    VEC2_unitize(&p[2].vec, 1.0e-10, &len3, &p[1].vec);

    if (a4[0] > len3)
        return 2;
    double rad = a4[1] * 0.01745329251994328;
    double cotang = a4[0] / tan(rad);
    double cosang = cos(rad);
    double len1 = sqrt(d1x * d1x + d1y * d1y);
    double len2 = sqrt(d2x * d2x + d2y * d2y);
    if (a4[0] > len1 || a4[0] > len2)
    {
        result = 1;
    }
    else if (a4[0] > fabs(d1x) && a4[0] > fabs(d2x) && len3 > cotang)
    {
        result = 1;
    }
    else if (a4[0] > fabs(d1y) && a4[0] > fabs(d2y) && len3 > cotang)
    {
        result = 1;
    }
    else
    {
        double dot1 = p[1].vec.x * d1x + p[1].vec.y * d1y;
        double dot2 = p[1].vec.x * d2x + p[1].vec.y * d2y;
        if (fabs(dot1) >= fabs(dot2))
        {
            if (fabs(dot1 / len1) > cosang)
                result = 1;
        }
        else
        {
            result = fabs(dot2 / len2) > cosang;
        }
    }
    if (a5 == 2 && !result)
    {
        double cross = (a1->y - a2->y) * (a3->x - a2->x) - (a1->x - a2->x) * (a3->y - a2->y);
        if (cross > 0.0)
            *a6 = 0;
        else if (cross < 0.0)
            *a6 = 1;
    }
    return result;
}
