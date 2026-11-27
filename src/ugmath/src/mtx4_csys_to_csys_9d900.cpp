














#include <math.h>

namespace UGS {
namespace Math {

struct Point3 {
    double x, y, z;
};

struct Vector3 {
    double x, y, z;
};

struct Matrix3 {
    double m[9];
};

struct TransformMatrix {
    double m[16];
};

}
}




extern int MTX3_init(const UGS::Math::Vector3* a1, const UGS::Math::Vector3* a2,
                     UGS::Math::Matrix3* out);




extern void sub_18009FBD0(const UGS::Math::Point3* origin1, const UGS::Math::Matrix3* axes1,
                          const UGS::Math::Point3* origin2, const UGS::Math::Matrix3* axes2,
                          UGS::Math::TransformMatrix* out);

int MTX4_csys_to_csys(const UGS::Math::Point3* origin1, const UGS::Math::Vector3* x_axis1,
                      const UGS::Math::Vector3* y_axis1, const UGS::Math::Point3* origin2,
                      const UGS::Math::Vector3* x_axis2, const UGS::Math::Vector3* y_axis2,
                      UGS::Math::TransformMatrix* out)
{
    UGS::Math::Matrix3 axes1 = { { 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0 } };
    UGS::Math::Matrix3 axes2 = { { 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0 } };

    if (sqrt(x_axis1->x * x_axis1->x + x_axis1->y * x_axis1->y
             + x_axis1->z * x_axis1->z) <= 1.0e-10)
        return 1;
    if (sqrt(y_axis1->x * y_axis1->x + y_axis1->y * y_axis1->y
             + y_axis1->z * y_axis1->z) <= 1.0e-10)
        return 1;
    if (sqrt(x_axis2->x * x_axis2->x + x_axis2->y * x_axis2->y
             + x_axis2->z * x_axis2->z) <= 1.0e-10)
        return 1;
    if (sqrt(y_axis2->x * y_axis2->x + y_axis2->y * y_axis2->y
             + y_axis2->z * y_axis2->z) <= 1.0e-10)
        return 1;

    MTX3_init(x_axis1, y_axis1, &axes1);
    MTX3_init(x_axis2, y_axis2, &axes2);
    sub_18009FBD0(origin1, &axes1, origin2, &axes2, out);
    return 0;
}
