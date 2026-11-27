






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
    Point3() { x = 0.0; y = 0.0; z = 0.0; }
};

struct Vector3
{
    double x;
    double y;
    double z;
    Vector3() : x(0.0), y(0.0), z(0.0) {}
};
}
}


int VEC3_unitize(const UGS::Math::Vector3* u, double tol, double* mag, UGS::Math::Vector3* unit_out);
void FACET_point_line_proj(UGS::Math::Point3* p, UGS::Math::Point3* q, UGS::Math::Vector3* dir,
                           int normalize, UGS::Math::Point3* proj, double* t);


UGS::Math::Vector3 LSFIT_internal_1820(double t, const UGS::Math::Vector3* q);


static __forceinline double dist_sq(const UGS::Math::Point3* a, const UGS::Math::Point3* b)
{
    double dx = a->x - b->x;
    double dy = a->y - b->y;
    double dz = a->z - b->z;
    return dy * dy + dx * dx + dz * dz;
}

void LSFIT_cre_circumcircle_of_triangle(UGS::Math::Point3* p1, UGS::Math::Point3* p2,
                                        UGS::Math::Point3* p3, UGS::Math::Point3* center,
                                        double* radius)
{
    double d12 = sqrt(dist_sq(p1, p2));
    double d23 = sqrt(dist_sq(p2, p3));
    double d31 = sqrt(dist_sq(p3, p1));

    UGS::Math::Point3 foot;

    double s = (d12 + d23 + d31) * 0.5;
    double a2 = (s - d12) * s * (s - d23) * (s - d31);
    double R = d12 * d23 * d31 / sqrt(a2) * 0.25;
    *radius = R;

    double h = sqrt(R * R - d12 * 0.25 * d12);

    UGS::Math::Vector3 sum;
    sum.x = p2->x + p3->x;
    sum.y = p2->y + p3->y;
    sum.z = p2->z + p3->z;
    UGS::Math::Vector3 c;
    c = LSFIT_internal_1820(0.5, &sum);

    UGS::Math::Vector3 dir;
    dir.x = p3->x - p2->x;
    dir.y = p3->y - p2->y;
    dir.z = p3->z - p2->z;
    FACET_point_line_proj(p1, p2, &dir, 0, &foot, (double*)&radius);

    UGS::Math::Vector3 v;
    v.x = p1->x - foot.x;
    v.y = p1->y - foot.y;
    v.z = p1->z - foot.z;
    double mag;
    VEC3_unitize(&v, 1.0e-10, &mag, &v);

    center->y = v.y * h + c.y;
    center->z = v.z * h + c.z;
    center->x = v.x * h + c.x;
}
