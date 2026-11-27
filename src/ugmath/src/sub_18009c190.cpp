










namespace UGS {
namespace Math {

struct Matrix3 {
    double m[9];
};

}
}



bool MTX3_is_ortho_normal(const UGS::Math::Matrix3* matrix, double tolerance);


__declspec(dllimport) extern int MACH__checking_level;
__declspec(dllimport) void ERROR_assertion_failed(const char* file, int line,
                                                  const char* fmt, ...);

extern "C" void sub_18009C190(double cr, double sr, double cp, double sp,
                              double cy, double sy,
                              UGS::Math::Matrix3* rot_mat) {
    rot_mat->m[0] = cp * cy;
    rot_mat->m[3] = cp * sy;
    rot_mat->m[6] = -sp;
    rot_mat->m[1] = sp * cy * sr - sy * cr;
    rot_mat->m[4] = sp * sy * sr + cr * cy;
    rot_mat->m[7] = sr * cp;
    rot_mat->m[2] = sp * cy * cr + sy * sr;
    rot_mat->m[5] = sp * sy * cr - sr * cy;
    rot_mat->m[8] = cr * cp;

    if (MACH__checking_level) {
        if (!MTX3_is_ortho_normal(rot_mat, 1.0e-14))
            ERROR_assertion_failed(
                "o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\mtx3.c", 334, "%s",
                "MTX3_is_ortho_normal (rot_mat)");
    }
}
