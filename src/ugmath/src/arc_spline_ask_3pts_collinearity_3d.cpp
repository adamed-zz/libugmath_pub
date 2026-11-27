












namespace UGS
{
namespace Math
{
struct Point3
{
    double x, y, z;
};

struct Vector3
{
    double x, y, z;
};
}
}








int __cdecl VEC3_unitize(const UGS::Math::Vector3* u, double tol, double* len_out,
                         UGS::Math::Vector3* out);








void __cdecl ARC_SPLINE_re_order_3pts_3d(double tol, UGS::Math::Point3* a2,
                                         UGS::Math::Point3* a3, UGS::Math::Point3* a4,
                                         int* a5);

#include <math.h>

int __cdecl ARC_SPLINE_ask_3pts_collinearity_3d(UGS::Math::Point3* a1, UGS::Math::Point3* a2,
                                                UGS::Math::Point3* a3, double* a4, int* a5)
{
    int result = 0;
    UGS::Math::Point3 p1 = *a1;
    UGS::Math::Point3 p2 = *a2;
    UGS::Math::Point3 p3 = *a3;
    ARC_SPLINE_re_order_3pts_3d(a4[0], &p1, &p2, &p3, a5);

    UGS::Math::Vector3 d3 = {p3.x - p1.x, p3.y - p1.y, p3.z - p1.z};
    UGS::Math::Vector3 d1 = {p1.x - p2.x, p1.y - p2.y, p1.z - p2.z};
    UGS::Math::Vector3 d2 = {p3.x - p2.x, p3.y - p2.y, p3.z - p2.z};
    double len3;
    UGS::Math::Vector3 unit;
    VEC3_unitize(&d3, 1.0e-10, &len3, &unit);

    if (a4[0] > len3)
        return 2;
    double cosang = cos(a4[1] * 0.01745329251994328);
    double len1 = sqrt(d1.x * d1.x + d1.y * d1.y + d1.z * d1.z);
    double len2 = sqrt(d2.x * d2.x + d2.y * d2.y + d2.z * d2.z);
    if (a4[0] > len1 || a4[0] > len2)
    {
        result = 1;
    }
    else
    {
        double dot1 = unit.x * d1.x + unit.y * d1.y + unit.z * d1.z;
        double dot2 = unit.x * d2.x + unit.y * d2.y + unit.z * d2.z;
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
    return result;
}
