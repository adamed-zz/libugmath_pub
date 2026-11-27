












#include <math.h>

namespace UGS
{
namespace Math
{
struct Vector3
{
    double x, y, z;
};
}
}

int VEC3_unitize(const UGS::Math::Vector3* u, double tol, double* len_out,
                 UGS::Math::Vector3* out);

void ARC_SPLINE_ask_inscribed_angle_and_type(UGS::Math::Vector3* a1,
                                             UGS::Math::Vector3* a2,
                                             UGS::Math::Vector3* normal,
                                             int mode, double tol,
                                             double* out1, double* angle,
                                             int* type);

double LSFIT_ask_acute_angle_of_lines_3d(UGS::Math::Vector3* a1,
                                         UGS::Math::Vector3* a2, double a3)
{
    UGS::Math::Vector3 normal;
    double aux;
    double len;
    int type = 1;
    double angle = 0.0;

    normal.x = a1->y * a2->z - a1->z * a2->y;
    normal.z = a1->x * a2->y - a1->y * a2->x;
    normal.y = a1->z * a2->x - a1->x * a2->z;

    VEC3_unitize(&normal, 1.0e-10, &len, &normal);
    if (fabs(len - 0.0) <= 1.0e-10)
        return angle;

    ARC_SPLINE_ask_inscribed_angle_and_type(a1, a2, &normal, 0, a3, &aux,
                                            &angle, &type);

    double result = angle;
    if (angle - 1.0e-10 <= 90.0 || angle >= 269.9999999999)
    {
        if (angle + 1.0e-10 > 270.0 && angle < 359.9999999999)
            result = angle + -360.0;
    }
    else
    {
        result = angle + -180.0;
    }
    return fabs(result);
}
