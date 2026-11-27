












#include <math.h>

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

struct Vector3
{
    double x;
    double y;
    double z;
};

}
}

void FACET_line_line_closest_point(UGS::Math::Point3* a1, UGS::Math::Vector3* a2,
                                   UGS::Math::Point3* a3, UGS::Math::Vector3* a4,
                                   double* a5, double* a6)
{
    double d11 = a2->x * a2->x + a2->y * a2->y + a2->z * a2->z;
    double d22 = a4->x * a4->x + a4->y * a4->y + a4->z * a4->z;
    double e = a1->x * a4->x + a1->y * a4->y + a1->z * a4->z;
    double d = a1->x * a2->x + a1->y * a2->y + a1->z * a2->z;
    double e2 = a3->x * a4->x + a3->y * a4->y + a3->z * a4->z;
    double b = a4->x * a2->x + a4->y * a2->y + a4->z * a2->z;
    double d2 = a3->x * a2->x + a3->y * a2->y + a3->z * a2->z;
    double det = d22 * d11 - b * b;
    if (fabs(det) > 1.0e-10)
    {
        double x = e - e2;
        double y = d2 - d;
        *a5 = (x * b + y * d22) / det;
        *a6 = (y * b + x * d11) / det;
    }
    else if (fabs(d22) > 1.0e-6)
    {
        *a5 = 0.0;
        *a6 = (e - e2) / (d22 * d22);
    }
    else
    {
        if (fabs(d11) > 1.0e-6)
            *a5 = (d2 + d) / (d11 * d11);
        else
            *a5 = 0.0;
        *a6 = 0.0;
    }
}
