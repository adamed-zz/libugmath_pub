




#include <math.h>

namespace UGS { namespace Math {
struct Point3 { double x, y, z; };
struct Vector3 { double x, y, z; };
struct TransformMatrix { double m[4][4]; };
}}

using UGS::Math::Point3;
using UGS::Math::Vector3;
using UGS::Math::TransformMatrix;

int VEC3_ask_perpendicular(const Vector3* v, Vector3* out);
int VEC3_unitize(const Vector3* v, double tol, double* outlen, Vector3* out);
int MTX4_invert(const TransformMatrix* in, TransformMatrix* out);

void LSFIT_cre_local_csys(Point3* origin, Vector3* dir, Vector3* axis,
                          TransformMatrix* xform, TransformMatrix* inv)
{
    Vector3 xaxis, yaxis;
    double len = sqrt(dir->x * dir->x + dir->y * dir->y + dir->z * dir->z);
    double d1, d2;
    if (len <= 1.0e-10) {
        VEC3_ask_perpendicular(axis, &xaxis);
        VEC3_unitize(&xaxis, 1.0e-10, &d1, &xaxis);
        yaxis.x = axis->y * xaxis.z - axis->z * xaxis.y;
        yaxis.y = axis->z * xaxis.x - axis->x * xaxis.z;
        yaxis.z = axis->x * xaxis.y - axis->y * xaxis.x;
        VEC3_unitize(&yaxis, 1.0e-10, &d1, &yaxis);
    } else {
        double d = -(axis->x * dir->x + axis->y * dir->y + axis->z * dir->z);
        yaxis.x = axis->x * d + dir->x;
        yaxis.y = axis->y * d + dir->y;
        yaxis.z = axis->z * d + dir->z;
        VEC3_unitize(&yaxis, 1.0e-10, &d2, &yaxis);
        xaxis.x = axis->z * yaxis.y - axis->y * yaxis.z;
        xaxis.y = axis->x * yaxis.z - axis->z * yaxis.x;
        xaxis.z = axis->y * yaxis.x - axis->x * yaxis.y;
        VEC3_unitize(&xaxis, 1.0e-10, &d2, &xaxis);
    }
    xform->m[0][3] = 0.0;
    xform->m[1][3] = 0.0;
    xform->m[2][3] = 0.0;
    xform->m[3][3] = 1.0;
    xform->m[3][0] = origin->x;
    xform->m[3][1] = origin->y;
    xform->m[3][2] = origin->z;
    xform->m[0][0] = xaxis.x;
    xform->m[0][1] = xaxis.y;
    xform->m[0][2] = xaxis.z;
    xform->m[1][0] = yaxis.x;
    xform->m[1][1] = yaxis.y;
    xform->m[1][2] = yaxis.z;
    xform->m[2][0] = axis->x;
    xform->m[2][1] = axis->y;
    xform->m[2][2] = axis->z;
    MTX4_invert(xform, inv);
}
