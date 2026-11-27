







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

int __cdecl VEC3_unitize(const UGS::Math::Vector3* u, double tol, double* len_out,
                         UGS::Math::Vector3* dir_out);

double FACET_line_point_dist(UGS::Math::Point3* p1, UGS::Math::Point3* p2,
                             UGS::Math::Point3* p3)
{
    UGS::Math::Vector3 dir = {0.0, 0.0, 0.0};
    double len;

    UGS::Math::Vector3 d;
    UGS::Math::Vector3 w;

    d.y = p2->y - p1->y;
    d.x = p2->x - p1->x;
    w.z = p3->z - p1->z;
    w.x = p3->x - p1->x;
    d.z = p2->z - p1->z;
    w.y = p3->y - p1->y;

    double sq;

    if (VEC3_unitize(&d, 1e-5, &len, &dir))
    {
        double cx = w.y * dir.z - w.z * dir.y;
        double cy = w.z * dir.x - w.x * dir.z;
        double cz = w.x * dir.y - w.y * dir.x;
        sq = cy * cy + cx * cx + cz * cz;
    }
    else
    {
        sq = w.x * w.x + w.y * w.y + w.z * w.z;
    }

    return sqrt(sq);
}
