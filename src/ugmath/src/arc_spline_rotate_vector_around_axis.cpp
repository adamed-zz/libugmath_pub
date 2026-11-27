




















#pragma once






namespace UGS {
namespace Math {

struct Vector3 {
    double x;
    double y;
    double z;
};

struct Matrix3 {
    double m[9];
};

}
}




void MTX3_rot_about_axis(double angle_rad,
                         const UGS::Math::Vector3* axis,
                         UGS::Math::Matrix3* matrix);
int VEC3_unitize(const UGS::Math::Vector3* u, double tolerance,
                 double* length, UGS::Math::Vector3* unit);

void ARC_SPLINE_rotate_vector_around_axis(UGS::Math::Vector3* vector,
                                          UGS::Math::Vector3* axis,
                                          double angle_deg,
                                          bool normalize,
                                          UGS::Math::Vector3* out) {
    UGS::Math::Matrix3 m = {{1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0}};
    MTX3_rot_about_axis(angle_deg * 0.01745329251994328, axis, &m);

    const double x = vector->x;
    const double y = vector->y;
    const double z = vector->z;
    UGS::Math::Vector3 rotated;
    rotated.y = x * m.m[3] + y * m.m[4] + z * m.m[5];
    rotated.z = x * m.m[6] + y * m.m[7] + z * m.m[8];
    rotated.x = x * m.m[0] + y * m.m[1] + z * m.m[2];
    *out = rotated;

    if (normalize) {
        double length;
        VEC3_unitize(out, 1.0e-10, &length, out);
    }
}
