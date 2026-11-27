







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

double FACET_point_plane_dist(UGS::Math::Point3* p, UGS::Math::Vector3* n, double d)
{
    return p->x * n->x + p->y * n->y + p->z * n->z + d;
}
