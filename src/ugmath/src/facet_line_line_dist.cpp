











#include <cmath>

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

double FACET_line_point_dist(UGS::Math::Point3* a1, UGS::Math::Point3* a2,
                             UGS::Math::Point3* a3);

double FACET_line_line_dist(UGS::Math::Point3* a1, UGS::Math::Vector3* a2,
                            UGS::Math::Point3* a3, UGS::Math::Vector3* a4)
{
    double ny = a4->x * a2->z - a2->x * a4->z;
    double nx = a4->z * a2->y - a4->y * a2->z;
    double nz = a2->x * a4->y - a4->x * a2->y;
    double len = sqrt(ny * ny + nx * nx + nz * nz);
    if (len < 1e-6)
    {
        UGS::Math::Point3 t;
        t.x = a3->x + a4->x;
        t.y = a3->y + a4->y;
        t.z = a3->z + a4->z;
        return FACET_line_point_dist(a3, &t, a1);
    }
    return ((a3->y - a1->y) * ny + (a3->x - a1->x) * nx
            + (a3->z - a1->z) * nz) / len;
}
