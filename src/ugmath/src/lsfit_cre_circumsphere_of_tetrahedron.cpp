






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

void LSFIT_cre_circumcircle_of_triangle(UGS::Math::Point3 *, UGS::Math::Point3 *,
                                        UGS::Math::Point3 *, UGS::Math::Point3 *, double *);
int VEC3_unitize(const UGS::Math::Vector3 *, double, double *, UGS::Math::Vector3 *);
void FACET_line_line_closest_point(UGS::Math::Point3 *, UGS::Math::Vector3 *,
                                   UGS::Math::Point3 *, UGS::Math::Vector3 *, double *, double *);

void LSFIT_cre_circumsphere_of_tetrahedron(UGS::Math::Point3 *a1, UGS::Math::Point3 *a2,
                                           UGS::Math::Point3 *a3, UGS::Math::Point3 *a4,
                                           UGS::Math::Point3 *a5, double *a6)
{
    UGS::Math::Point3 c1 = {0.0, 0.0, 0.0};
    UGS::Math::Point3 c2 = {0.0, 0.0, 0.0};
    double rr;
    LSFIT_cre_circumcircle_of_triangle(a1, a3, a4, &c1, &rr);
    LSFIT_cre_circumcircle_of_triangle(a2, a3, a4, &c2, &rr);

    UGS::Math::Vector3 v2 = {a2->x - a3->x, a2->y - a3->y, a2->z - a3->z};
    UGS::Math::Vector3 v4 = {a4->x - a3->x, a4->y - a3->y, a4->z - a3->z};
    UGS::Math::Vector3 v1 = {a1->x - a3->x, a1->y - a3->y, a1->z - a3->z};

    UGS::Math::Vector3 n1 = {v4.y * v2.z - v4.z * v2.y,
                             v4.z * v2.x - v4.x * v2.z,
                             v4.x * v2.y - v4.y * v2.x};
    double len;
    VEC3_unitize(&n1, 1.0e-10, &len, &n1);

    UGS::Math::Vector3 n2 = {v1.y * v4.z - v1.z * v4.y,
                             v1.z * v4.x - v1.x * v4.z,
                             v1.x * v4.y - v1.y * v4.x};
    VEC3_unitize(&n2, 1.0e-10, &len, &n2);

    double t, s;
    FACET_line_line_closest_point(&c2, &n1, &c1, &n2, &t, &s);

    a5->x = n1.x * t + c2.x;
    a5->y = n1.y * t + c2.y;
    a5->z = n1.z * t + c2.z;

    double dx = a1->x - a5->x;
    double dy = a1->y - a5->y;
    double dz = a1->z - a5->z;
    *a6 = std::sqrt(dx * dx + dy * dy + dz * dz);
}
