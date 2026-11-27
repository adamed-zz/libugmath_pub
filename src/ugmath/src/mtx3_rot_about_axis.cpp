





























#include <math.h>







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


int VEC3_unitize(const UGS::Math::Vector3* u, double tolerance,
                 double* length, UGS::Math::Vector3* unit);
bool MTX3_ortho_normalize(UGS::Math::Matrix3* m);

__declspec(dllimport) int MACH__checking_level;
__declspec(dllimport) void ERROR_assertion_failed(const char* file, int line,
                                                  const char* format, ...);

void MTX3_rot_about_axis(double angle, const UGS::Math::Vector3* axis,
                         UGS::Math::Matrix3* matrix) {
    double sine = 0.0;
    double cosine;
    UGS::Math::Vector3 unit_axis = {0.0, 0.0, 0.0};
    double axis_length;
    if (VEC3_unitize(axis, 1.0e-10, &axis_length, &unit_axis)) {
        sine = sin(angle);
        cosine = cos(angle);
    } else {
        cosine = 1.0;
    }

    const double x = unit_axis.x;
    const double y = unit_axis.y;
    const double z = unit_axis.z;
    const double one_minus_cos = 1.0 - cosine;

    const double zs = z * sine;
    const double ys = y * sine;
    const double mx = one_minus_cos * x;
    const double my = one_minus_cos * y;
    const double xs = x * sine;
    const double mz = one_minus_cos * z;
    const double cxy = mx * y;
    const double cxx = mx * x + cosine;
    const double cyz = my * z;
    const double cxz = mx * z;
    const double cyy = my * y;
    const double czz = mz * z;
    const double zsys_cxy = zs + cxy;

    matrix->m[0] = cxx;
    matrix->m[1] = cxy - zs;
    matrix->m[2] = ys + cxz;
    matrix->m[3] = zsys_cxy;
    matrix->m[4] = cyy + cosine;
    matrix->m[5] = cyz - xs;
    matrix->m[6] = cxz - ys;
    matrix->m[7] = xs + cyz;
    matrix->m[8] = czz + cosine;

    const bool hasModifiedMatrix = MTX3_ortho_normalize(matrix);
    if (MACH__checking_level) {
        if (hasModifiedMatrix)
            ERROR_assertion_failed("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\mtx3.c",
                                   473, "%s", "! hasModifiedMatrix");
    }
}
