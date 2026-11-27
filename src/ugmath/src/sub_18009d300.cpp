

















#include "ugmath/b36_math.h"

int sub_18009D300(UGS::Math::Matrix3* a1) {
    double* a = a1->m;
    const UGS::Math::Matrix3 original = *a1;
    int rc = 1;


    for (int k = 0; k < 6; ++k) {
        const double v = a[k];
        const double av = std::fabs(v);
        if (!(av <= 1.0e-10)) {
            if (std::fabs(av - 1.0) <= 1.0e-10) a[k] = (v <= 0.0) ? -1.0 : 1.0;
        } else {
            a[k] = 0.0;
        }
    }
    const double det = (a[8] * a[4] - a[7] * a[5]) * a[0] - (a[8] * a[1] - a[7] * a[2]) * a[3] +
                       (a[5] * a[1] - a[2] * a[4]) * a[6];


    const bool reflection = det < 0.0;
    double len = 0.0;
    if (!reflection) {
        if (VEC3_unitize(reinterpret_cast<UGS::Math::Vector3*>(a), 1.0e-10, &len,
                         reinterpret_cast<UGS::Math::Vector3*>(a))) {
            if (VEC3_unitize(reinterpret_cast<UGS::Math::Vector3*>(a + 3), 1.0e-10, &len,
                             reinterpret_cast<UGS::Math::Vector3*>(a + 3))) {
                a[6] = a[5] * a[1] - a[4] * a[2];
                a[7] = a[3] * a[2] - a[5] * a[0];
                a[8] = a[4] * a[0] - a[3] * a[1];
                VEC3_unitize(reinterpret_cast<UGS::Math::Vector3*>(a + 6), 1.0e-10, &len,
                             reinterpret_cast<UGS::Math::Vector3*>(a + 6));
                a[3] = a[7] * a[2] - a[8] * a[1];
                a[4] = a[8] * a[0] - a[6] * a[2];
                a[5] = a[6] * a[1] - a[7] * a[0];
                goto done;
            }
            if (RDEBUG__enabled && (unsigned int)RDEBUG_ask_flag("UGMATH_mtx_debug", true) == 1)
                ERROR_note("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\mtx3_privileged.c", 157,
                           "MTX3_fixup: Y vector of matrix is zero");
        } else if (RDEBUG__enabled &&
                   (unsigned int)RDEBUG_ask_flag("UGMATH_mtx_debug", true) == 1) {
            ERROR_note("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\mtx3_privileged.c", 166,
                       "MTX3_fixup: X vector of matrix is zero");
        }
        rc = 0;
        goto done;
    }
    MTX3_ortho_normalize(a1);
    if (!MTX3_is_ortho_normal(a1)) {
        rc = 0;
        if (!RDEBUG__enabled) return rc;
        if ((unsigned int)RDEBUG_ask_flag("UGMATH_mtx_debug", true) == 1)
            ERROR_note("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\mtx3_privileged.c", 137,
                       "MTX3_fixup: Reflection matrix could not be orthonormalized");
    }
done:
    if (RDEBUG__enabled) {
        if ((unsigned int)RDEBUG_ask_flag("UGMATH_mtx_debug", true) == 1) {
            int changed = 0;
            for (int i = 0; i < 6; ++i) {
                if (std::fabs(a[i] - original.m[i]) > 1.0e-10) {
                    lprintf("MTX3_fixup: Element %d of matrix modified from %25.15f to %25.15f\n",
                            i, original.m[i], a[i]);
                    changed = 1;
                }
            }
            if (changed) {
                if (dword_1800E1B34 < 5) {
                    const char* what = reflection ? "reflection matrix" : "matrix";
                    ERROR_note("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\mtx3_privileged.c", 193,
                               "MTX3_fixup: some %s elements altered - see above", what);
                    ++dword_1800E1B34;
                }
            } else {
                lprintf("MTX3_fixup: The input matrix was not changed!\n");
            }
        }
    }
    return rc;
}
