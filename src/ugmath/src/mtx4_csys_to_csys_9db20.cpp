







#include <math.h>

namespace UGS
{
namespace Math
{
struct Vector3
{
    double x, y, z;
};

struct Point3
{
    double x, y, z;
};


struct Matrix3
{
    double m[9];
};


struct TransformMatrix
{
    double m[16];
};
}
}

int MTX3_init_x_y_z(const UGS::Math::Vector3* x, const UGS::Math::Vector3* y,
                    const UGS::Math::Vector3* z, UGS::Math::Matrix3* r);


void sub_18009FBD0(const UGS::Math::Point3* origin1,
                   const UGS::Math::Matrix3* m1,
                   const UGS::Math::Point3* origin2,
                   const UGS::Math::Matrix3* m2,
                   UGS::Math::TransformMatrix* m);

int MTX4_csys_to_csys(const UGS::Math::Point3* origin1,
                      const UGS::Math::Vector3* x1,
                      const UGS::Math::Vector3* y1,
                      const UGS::Math::Vector3* z1,
                      const UGS::Math::Point3* origin2,
                      const UGS::Math::Vector3* x2,
                      const UGS::Math::Vector3* y2,
                      const UGS::Math::Vector3* z2,
                      UGS::Math::TransformMatrix* m)
{
    const double tol = 1.0e-10;

    if (sqrt(x1->x * x1->x + x1->y * x1->y + x1->z * x1->z) <= tol)
        return 1;
    if (sqrt(y1->x * y1->x + y1->y * y1->y + y1->z * y1->z) <= tol)
        return 1;
    if (sqrt(z1->x * z1->x + z1->y * z1->y + z1->z * z1->z) <= tol)
        return 1;
    if (sqrt(x2->x * x2->x + x2->y * x2->y + x2->z * x2->z) <= tol)
        return 1;
    if (sqrt(y2->x * y2->x + y2->y * y2->y + y2->z * y2->z) <= tol)
        return 1;
    if (sqrt(z2->x * z2->x + z2->y * z2->y + z2->z * z2->z) <= tol)
        return 1;

    UGS::Math::Matrix3 m1 = {1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0};
    if (MTX3_init_x_y_z(x1, y1, z1, &m1) != 1)
        return 1;

    UGS::Math::Matrix3 m2 = {1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0};
    if (MTX3_init_x_y_z(x2, y2, z2, &m2) != 1)
        return 1;

    sub_18009FBD0(origin1, &m1, origin2, &m2, m);
    return 0;
}
