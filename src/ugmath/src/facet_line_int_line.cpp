














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
                                   double* a5, double* a6);

int FACET_line_int_line(UGS::Math::Point3* a1, UGS::Math::Vector3* a2,
                        UGS::Math::Point3* a3, UGS::Math::Vector3* a4,
                        double* a5, double* a6)
{
    *a6 = -1.0;
    *a5 = -1.0;
    double dot = a2->x * a4->x + a2->y * a4->y + a2->z * a4->z;
    if (fabs(dot * dot - 1.0) > 0.0)
    {
        FACET_line_line_closest_point(a1, a2, a3, a4, a5, a6);
        return 1;
    }
    return 0;
}
