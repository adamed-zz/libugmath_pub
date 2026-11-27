

































#include <cmath>

namespace UGS { namespace Math { struct Point3 { double x, y, z; }; } }
using UGS::Math::Point3;

void ARC_SPLINE_re_order_3pts_3d(double tol, Point3* a2, Point3* a3, Point3* a4, int* a5)
{
    *a5 = 0;
    double x1 = a2->x, y1 = a2->y, z1 = a2->z;
    double x2 = a3->x, y2 = a3->y, z2 = a3->z;
    double s12 = (y1 - y2) * (y1 - y2);
    s12 += (x1 - x2) * (x1 - x2);
    s12 += (z1 - z2) * (z1 - z2);
    double d12 = sqrt(s12);
    double x3 = a4->x, y3 = a4->y, z3 = a4->z;
    double s23 = (y2 - y3) * (y2 - y3);
    s23 += (x2 - x3) * (x2 - x3);
    s23 += (z2 - z3) * (z2 - z3);
    double d23 = sqrt(s23);
    double dx13 = x1 - x3, dy13 = y1 - y3, dz13 = z1 - z3;
    double s13 = dy13 * dy13;
    s13 += dx13 * dx13;
    s13 += dz13 * dz13;
    double d13 = sqrt(s13);
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
                a2->x = x2; a2->y = y2; a2->z = z2;
                a3->x = x3; a3->y = y3; a3->z = z3;
                a4->x = x1; a4->y = y1; a4->z = z1;
                *a5 = 1;
            }
            else
            {
                a2->x = x3; a2->y = y3; a2->z = z3;
                a3->x = x1; a3->y = y1; a3->z = z1;
                a4->x = x2; a4->y = y2; a4->z = z2;
                *a5 = 2;
            }
        }
    }
}
