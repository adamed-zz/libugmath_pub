






#include <math.h>

namespace UGS
{
namespace Math
{
struct Vector3
{
    double x, y, z;
    Vector3() : x(0.0), y(0.0), z(0.0) {}
    Vector3(double a, double b, double c) : x(a), y(b), z(c) {}
};
struct Point3
{
    double x, y, z;
    Point3() : x(0.0), y(0.0), z(0.0) {}
    Point3(double a, double b, double c) : x(a), y(b), z(c) {}
};
}
}

using UGS::Math::Vector3;
using UGS::Math::Point3;



int VEC3_unitize(const Vector3* u, double tolerance, double* length, Vector3* unit);

int FACET_line_int_plane(Point3* p1, Point3* p2, Vector3* normal, double d, Point3* pt, double* param);

int FACET_plane_plane_int(Vector3* n1, double d1, Vector3* n2, double d2, Point3* pt, Vector3* dir)
{
    double len;

    Point3 p1;

    Vector3 u1;
    VEC3_unitize(n1, 1.0e-10, &len, &u1);

    double p1x = u1.x * -d1;
    double p1y = u1.y * -d1;
    double p1z = u1.z * -d1;
    p1 = Point3(p1x, p1y, p1z);

    Vector3 u2;
    VEC3_unitize(n2, 1.0e-10, &len, &u2);

    double qx = u2.x * -d2;
    double qy = u2.y * -d2;
    double qz = u2.z * -d2;

    dir->x = n2->z * n1->y - n2->y * n1->z;
    dir->y = n2->x * n1->z - n1->x * n2->z;
    dir->z = n1->x * n2->y - n2->x * n1->y;

    double dl = sqrt(dir->x * dir->x + dir->y * dir->y + dir->z * dir->z);



    if (dl <= 1.0e-5)
        return !(fabs((p1x - qx) * n1->x + (p1y - qy) * n1->y + (p1z - qz) * n1->z) < 1.0e-10);

    Point3 p2;
    p2.x = n1->z * dir->y - n1->y * dir->z + p1.x;
    p2.y = n1->x * dir->z - n1->z * dir->x + p1.y;
    p2.z = n1->y * dir->x - n1->x * dir->y + p1.z;

    double t;
    FACET_line_int_plane(&p1, &p2, n2, d2, pt, &t);
    return 2;
}
