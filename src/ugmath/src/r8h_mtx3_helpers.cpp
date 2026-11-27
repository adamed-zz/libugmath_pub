







#include <math.h>

namespace UGS {
namespace Math {

struct Vector3 {
    double x, y, z;
};

struct Matrix3 {
    double m[9];
};

}
}


extern "C" __declspec(dllimport) extern int MACH__checking_level;
extern "C" {
__declspec(dllimport) extern bool RDEBUG__enabled;
__declspec(dllimport) int RDEBUG_ask_flag(const char*, bool);
}
__declspec(dllimport) int lprintf(const char*, ...);
__declspec(dllimport) void ERROR_assertion_failed(const char*, int,
                                                  const char*, ...);


int VEC3_unitize(const UGS::Math::Vector3* v, double tol, double* mag,
                 UGS::Math::Vector3* out);
bool MTX3_is_ortho_normal(const UGS::Math::Matrix3* m, double tol);
int MTX3_init_y_z(const UGS::Math::Vector3* y, const UGS::Math::Vector3* z,
                  UGS::Math::Matrix3* out);
void MTX3_lprintf(int level, const char* label, const UGS::Math::Matrix3* m);
int MTX3_print_diff(const UGS::Math::Matrix3* a1,
                    const UGS::Math::Matrix3* a2);

namespace {

constexpr double kUnitTol = 1.0e-10;
constexpr double kOrthoTol = 1.0e-14;


int mtx3_init_core(const UGS::Math::Vector3* a1, const UGS::Math::Vector3* a2,
                   UGS::Math::Matrix3* a3, bool use_tol) {
    UGS::Math::Vector3 u1 = {0.0, 0.0, 0.0};
    UGS::Math::Vector3 u2 = {0.0, 0.0, 0.0};
    double mag = 0.0;
    if (!VEC3_unitize(a1, kUnitTol, &mag, &u1)) return 0;
    if (!VEC3_unitize(a2, kUnitTol, &mag, &u2)) return 0;

    const double dot = u2.x * u1.x + u2.y * u1.y + u2.z * u1.z;



    if (!(kUnitTol >= fabs(dot)) && !use_tol) return 0;


    UGS::Math::Vector3 n;
    n.x = u2.z * u1.y - u2.y * u1.z;
    n.y = u2.x * u1.z - u2.z * u1.x;
    n.z = u2.y * u1.x - u2.x * u1.y;
    VEC3_unitize(&n, kUnitTol, &mag, &n);

    a3->m[0] = u1.x;
    a3->m[1] = u1.y;
    a3->m[2] = u1.z;
    a3->m[6] = n.x;
    a3->m[7] = n.y;
    a3->m[8] = n.z;
    a3->m[3] = n.y * u1.z - n.z * u1.y;
    a3->m[4] = n.z * u1.x - n.x * u1.z;
    a3->m[5] = n.x * u1.y - n.y * u1.x;

    if (MACH__checking_level) {
        if (!MTX3_is_ortho_normal(a3, kOrthoTol))
            ERROR_assertion_failed(
                "o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\mtx3.c", 540, "%s",
                "MTX3_is_ortho_normal (r)");
    }
    return 1;
}

}

int MTX3_init_impl(const UGS::Math::Vector3* a1,
                   const UGS::Math::Vector3* a2, UGS::Math::Matrix3* a3,
                   bool use_tol) {
    return mtx3_init_core(a1, a2, a3, use_tol);
}

int mtx3_init_common(const UGS::Math::Vector3* a1,
                     const UGS::Math::Vector3* a2, UGS::Math::Matrix3* a3,
                     char use_tol) {
    return mtx3_init_core(a1, a2, a3, use_tol != 0);
}


int MTX3_massage_axes(UGS::Math::Matrix3* a1) {
    int changed = 0;
    double* rows[3] = {&a1->m[0], &a1->m[3], &a1->m[6]};
    for (int r = 0; r < 3; ++r) {
        double* v3 = rows[r];
        int done = 0;
        for (int c = 0; c < 3; ++c) {
            if (done) break;
            double v7 = v3[c];
            if (v7 != 0.0) {
                const double v8 = fabs(v7);
                if (v8 != 1.0) {
                    if (v8 <= kUnitTol) {
                        v7 = 0.0;
                        v3[c] = 0;
                        changed = 1;
                    }
                    if (fabs(fabs(v7) - 1.0) <= kUnitTol) {
                        changed = 1;
                        done = 1;
                        v3[c] = (v7 <= 0.0) ? -1.0 : 1.0;
                        if (c != 0) v3[0] = 0;
                        if (c == 1) {
                            v3[2] = 0;
                        } else {
                            v3[1] = 0;
                            if (c != 2) v3[2] = 0;
                        }
                    }
                }
            }
        }
    }
    return changed;
}


bool MTX3_ortho_normalize_reflection(UGS::Math::Matrix3* a1) {
    double* m = a1->m;
    const double det = (m[4] * m[8] - m[5] * m[7]) * m[0] -
                       (m[1] * m[8] - m[2] * m[7]) * m[3] +
                       (m[1] * m[5] - m[2] * m[4]) * m[6];
    if (det >= 0.0) {
        if (!RDEBUG__enabled) return false;
        if ((unsigned int)RDEBUG_ask_flag("UGMATH_mtx_debug", true) != 1)
            return false;
        lprintf(
            "\northoNormalizeWithReflection() given non-reflection "
            "transform...\n");
        MTX3_lprintf(0, 0, a1);
        return false;
    }
    if (MTX3_is_ortho_normal(a1, kOrthoTol)) {
        if (!RDEBUG__enabled) return false;
        if ((unsigned int)RDEBUG_ask_flag("UGMATH_mtx_debug", true) != 1)
            return false;
        lprintf(
            "\northoNormalizeWithReflection() given already orthonormal "
            "transform...\n");
        MTX3_lprintf(0, 0, a1);
        return false;
    }

    double backup[9];
    for (int i = 0; i < 9; ++i) backup[i] = m[i];

    if (RDEBUG__enabled &&
        (unsigned int)RDEBUG_ask_flag("UGMATH_mtx_debug", true) == 1) {
        lprintf("\northoNormalizeWithReflection()...\n");
        MTX3_lprintf(0, "Before:", a1);
    }

    const double ox0 = m[0], ox1 = m[1], ox2 = m[2];
    const double oy0 = m[3], oy1 = m[4], oy2 = m[5];
    const double oz0 = m[6], oz1 = m[7], oz2 = m[8];


    UGS::Math::Vector3 cr;
    cr.x = oz2 * ox1 - oz1 * ox2;
    cr.y = oz0 * ox2 - oz2 * ox0;
    cr.z = oz1 * ox0 - oz0 * ox1;
    UGS::Math::Vector3 zr = {oz0, oz1, oz2};
    MTX3_init_y_z(&cr, &zr, a1);


    if (m[0] * ox0 + m[1] * ox1 + m[2] * ox2 < 0.0) {
        m[0] = -m[0];
        m[1] = -m[1];
        m[2] = -m[2];
    }
    if (oy0 * m[3] + m[4] * oy1 + m[5] * oy2 < 0.0) {
        m[3] = -m[3];
        m[4] = -m[4];
        m[5] = -m[5];
    }
    if (m[7] * oz1 + m[6] * oz0 + oz2 * m[8] < 0.0) {
        m[6] = -m[6];
        m[7] = -m[7];
        m[8] = -m[8];
    }

    bool changed = true;
    int i = 0;
    for (; i < 9; ++i) {



        if (!(kUnitTol >= fabs(backup[i] - m[i]))) break;
    }
    if (i >= 9) {
        const bool before =
            MTX3_is_ortho_normal(reinterpret_cast<UGS::Math::Matrix3*>(backup),
                                 kOrthoTol);
        changed = before != MTX3_is_ortho_normal(a1, kOrthoTol);
    }

    if (RDEBUG__enabled) {
        if ((unsigned int)RDEBUG_ask_flag("UGMATH_mtx_debug", true) == 1) {
            lprintf("\northoNormalizeWithReflection()...\n");
            MTX3_lprintf(0, "After:", a1);
            if (changed)
                MTX3_print_diff(
                    reinterpret_cast<const UGS::Math::Matrix3*>(backup), a1);
        }
    }
    return changed;
}


int MTX3_print_diff(const UGS::Math::Matrix3* a1,
                    const UGS::Math::Matrix3* a2) {
    double sum = 0.0;
    for (int i = 0; i < 9; ++i) {
        const double d = fabs(a1->m[i] - a2->m[i]);
        lprintf("Difference in element %d = % 14.12e\n", i, d);
        sum = sum + d;
    }
    lprintf("Average difference = % 14.12e\n\n", sum / 9.0);

    double cr[3];
    cr[0] = a1->m[1] * a2->m[2] - a1->m[2] * a2->m[1];
    cr[1] = a1->m[2] * a2->m[0] - a1->m[0] * a2->m[2];
    cr[2] = a1->m[0] * a2->m[1] - a1->m[1] * a2->m[0];
    lprintf("The magnitude of X-axes cross product = % 14.12e\n",
            sqrt(cr[0] * cr[0] + cr[1] * cr[1] + cr[2] * cr[2]));
    cr[0] = a1->m[4] * a2->m[5] - a1->m[5] * a2->m[4];
    cr[1] = a1->m[5] * a2->m[3] - a1->m[3] * a2->m[5];
    cr[2] = a1->m[3] * a2->m[4] - a1->m[4] * a2->m[3];
    lprintf("The magnitude of Y-axes cross product = % 14.12e\n",
            sqrt(cr[0] * cr[0] + cr[1] * cr[1] + cr[2] * cr[2]));
    cr[0] = a1->m[7] * a2->m[8] - a1->m[8] * a2->m[7];
    cr[1] = a1->m[8] * a2->m[6] - a1->m[6] * a2->m[8];
    cr[2] = a1->m[6] * a2->m[7] - a1->m[7] * a2->m[6];
    return lprintf("The magnitude of Z-axes cross product = % 14.12e\n",
                   sqrt(cr[0] * cr[0] + cr[1] * cr[1] + cr[2] * cr[2]));
}
