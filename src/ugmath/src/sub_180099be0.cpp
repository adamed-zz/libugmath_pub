





























#include "ugmath/b36_math.h"

int sub_180099BE0(bool check, UGS::Math::Matrix3* m, bool foreign, double* scale) {
    const int kDebug = 0;
    double v15 = 1.0;
    int rc = 0;
    double* a = m->m;
    const double det = (a[4] * a[8] - a[5] * a[7]) * a[0] - (a[1] * a[8] - a[2] * a[7]) * a[3] +
                       (a[1] * a[5] - a[2] * a[4]) * a[6];
    if (check) {
        if (RDEBUG__enabled) {
            if ((unsigned int)RDEBUG_ask_flag("UGMATH_mtx_debug", true) == 1)
                MTX3_lprintf(kDebug, "Entering MTX3_fixup_foreign:", m);
        }
    }
    bool identity = false;
    if (MTX3_is_ortho_normal(m, 1.0e-14)) {
        if (det < 0.0 && !foreign) {
            rc = 1;
            identity = true;
        }
    } else {
        if (MTX3_apply_scale_factor(m, 0.000001, &v15)) rc = 2;
        if (det < 0.0) {
            if (foreign) {
                sub_18009C3E0(m);
            } else {
                rc = 1;
                identity = true;
            }
        } else if (!MTX3_ortho_normalize(m) && rc != 2) {
            rc = 3;
            identity = true;
        }
    }
    if (identity) {
        a[1] = 0.0;
        a[0] = 1.0;
        a[4] = 1.0;
        a[8] = 1.0;
        a[2] = 0.0;
        a[3] = 0.0;
        a[5] = 0.0;
        a[6] = 0.0;
        a[7] = 0.0;
    }
    if (scale) *scale = v15;
    if (RDEBUG__enabled) {
        if ((unsigned int)RDEBUG_ask_flag("UGMATH_mtx_debug", true) == 1) {
            const char* msg;
            if (rc) {
                if (rc == 1)
                    msg = "MTX_FOREIGN_REFLECTION";
                else if (rc == 2)
                    msg = "MTX_FOREIGN_SCALE";
                else
                    msg = "MTX_FOREIGN_NOFIXUP";
            } else {
                msg = "MTX_FOREIGN_OK";
            }
            lprintf("MTX3_fixup_foreign returning %s, scale: %g\n", msg, v15);
            if (check) MTX3_lprintf(kDebug, "Exiting MTX3_fixup_foreign:", m);
        }
    }
    return rc;
}
