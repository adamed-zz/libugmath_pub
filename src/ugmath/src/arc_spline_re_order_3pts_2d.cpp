































#include <cmath>

namespace UGS { namespace Math { struct Point2 { double x, y; }; } }
using UGS::Math::Point2;

void ARC_SPLINE_re_order_3pts_2d(double tol, Point2* a2, Point2* a3, Point2* a4, int* a5)
{
    *a5 = 0;
    double x1 = a2->x, y1 = a2->y;
    double x2 = a3->x, y2 = a3->y;
    double d12 = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    double x3 = a4->x, y3 = a4->y;
    double d23 = sqrt((x2 - x3) * (x2 - x3) + (y2 - y3) * (y2 - y3));
    double d13 = sqrt((x1 - x3) * (x1 - x3) + (y1 - y3) * (y1 - y3));
    if (tol >= d13 || tol >= d12 || tol >= d23)
    {
        *a5 = -1;
    }
    else
    {
        double m = d12 > d23 ? d12 : d23;
        m = m > d13 ? m : d13;
        if (!(fabs(m - d13) <= 1e-10))
        {
            if (fabs(m - d12) <= 1e-10)
            {
                a2->x = x2; a2->y = y2;
                a3->x = x3; a3->y = y3;
                a4->x = x1; a4->y = y1;
                *a5 = 1;
            }
            else
            {
                a2->x = x3; a2->y = y3;
                a3->x = x1; a3->y = y1;
                a4->x = x2; a4->y = y2;
                *a5 = 2;
            }
        }
    }
}
