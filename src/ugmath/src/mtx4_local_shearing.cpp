
















#include <math.h>

namespace UGS {
namespace Math {

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

struct CSYS_s {
    double origin[3];
    UGS::Math::Vector3 x_axis;
    UGS::Math::Vector3 y_axis;
    UGS::Math::Vector3 z_axis;
};

enum CSYS_axis_type_e {
    CSYS_X_axis = 0,
    CSYS_Y_axis = 1,
    CSYS_Z_axis = 2
};



__declspec(dllimport) void ERROR_assertion_failed(const char* file, int line,
                                                  const char* fmt, ...);



int MTX3_init_x_y_z(const UGS::Math::Vector3* x, const UGS::Math::Vector3* y,
                    const UGS::Math::Vector3* z, UGS::Math::Matrix3* r);

int MTX4_invert(const UGS::Math::TransformMatrix* src, UGS::Math::TransformMatrix* dst);

void MTX4_multiply(const UGS::Math::TransformMatrix* a, const UGS::Math::TransformMatrix* b,
                   UGS::Math::TransformMatrix* out);

using UGS::Math::Matrix3;
using UGS::Math::TransformMatrix;
using UGS::Math::Vector3;

TransformMatrix MTX4_local_shearing(const CSYS_s& csys, CSYS_axis_type_e shear_along_axis,
                                    CSYS_axis_type_e shear_about_axis, double angle)
{
    TransformMatrix mtx;
    mtx.m[0] = 1.0;
    mtx.m[1] = 0.0;
    mtx.m[2] = 0.0;
    mtx.m[3] = 0.0;
    mtx.m[4] = 0.0;
    mtx.m[5] = 1.0;
    mtx.m[6] = 0.0;
    mtx.m[7] = 0.0;
    mtx.m[8] = 0.0;
    mtx.m[9] = 0.0;
    mtx.m[10] = 1.0;
    mtx.m[11] = 0.0;
    mtx.m[12] = 0.0;
    mtx.m[13] = 0.0;
    mtx.m[14] = 0.0;
    mtx.m[15] = 1.0;

    if (shear_along_axis == shear_about_axis) {
        ERROR_assertion_failed("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\mtx4.c", 554,
                               "Never condition true: %s",
                               "shear_along_axis == shear_about_axis");
        return mtx;
    }

    TransformMatrix shear = {1.0, 0.0, 0.0, 0.0,
                             0.0, 1.0, 0.0, 0.0,
                             0.0, 0.0, 1.0, 0.0,
                             0.0, 0.0, 0.0, 1.0};

    if (shear_about_axis == 0) {
        if (shear_along_axis == 1)
            shear.m[1] = tan(angle * -1.0);
        else if (shear_along_axis == 2)
            shear.m[4] = tan(angle);
    } else if (shear_about_axis == 1) {
        if (shear_along_axis == 2)
            shear.m[1] = tan(angle * -1.0);
        else if (shear_along_axis == 0)
            shear.m[4] = tan(angle);
    } else {
        if (shear_along_axis == 0)
            shear.m[1] = tan(angle * -1.0);
        else if (shear_along_axis == 1)
            shear.m[4] = tan(angle);
    }

    Vector3 x_axis = csys.x_axis;
    Vector3 y_axis = csys.y_axis;
    Vector3 z_axis = csys.z_axis;
    Matrix3 rot = {1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0};

    if (shear_about_axis == 0)
        MTX3_init_x_y_z(&y_axis, &z_axis, &x_axis, &rot);
    else if (shear_about_axis == 1)
        MTX3_init_x_y_z(&z_axis, &x_axis, &y_axis, &rot);
    else
        MTX3_init_x_y_z(&x_axis, &y_axis, &z_axis, &rot);

    TransformMatrix m4 = {1.0, 0.0, 0.0, 0.0,
                          0.0, 1.0, 0.0, 0.0,
                          0.0, 0.0, 1.0, 0.0,
                          0.0, 0.0, 0.0, 1.0};
    m4.m[0] = rot.m[0];
    m4.m[1] = rot.m[1];
    m4.m[2] = rot.m[2];
    m4.m[4] = rot.m[3];
    m4.m[5] = rot.m[4];
    m4.m[6] = rot.m[5];
    m4.m[8] = rot.m[6];
    m4.m[9] = rot.m[7];
    m4.m[10] = rot.m[8];

    MTX4_invert(&m4, &m4);
    m4.m[3] = csys.origin[0];
    m4.m[7] = csys.origin[1];
    m4.m[11] = csys.origin[2];
    MTX4_invert(&m4, &m4);
    MTX4_multiply(&m4, &shear, &mtx);
    MTX4_invert(&m4, &shear);
    MTX4_multiply(&mtx, &shear, &mtx);
    return mtx;
}
