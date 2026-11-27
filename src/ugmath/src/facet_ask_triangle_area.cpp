











#include <math.h>

namespace UGS { namespace Math {

struct Point3
{
    double x;
    double y;
    double z;
};

}}


static __forceinline double dist_sq(const UGS::Math::Point3* a, const UGS::Math::Point3* b)
{
    double dx = a->x - b->x;
    double dy = a->y - b->y;
    double dz = a->z - b->z;
    return dy * dy + dx * dx + dz * dz;
}

double FACET_ask_triangle_area(UGS::Math::Point3* a1, UGS::Math::Point3* a2, UGS::Math::Point3* a3)
{
    double a = sqrt(dist_sq(a1, a2));
    double b = sqrt(dist_sq(a2, a3));
    double c = sqrt(dist_sq(a3, a1));
    double s = (b + a + c) * 0.5;
    double t = (s - a) * s * (s - b) * (s - c);
    if (t <= 0.0)
        return 0.0;
    return sqrt(t);
}
