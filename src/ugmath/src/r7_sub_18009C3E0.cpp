



#include "devhdr/sub_18009C3E0_types.h"

#include <math.h>

extern "C" bool sub_18009C3E0(UGS::Math::Matrix3 *a1)
{
    double det = (a1->m[4] * a1->m[8] - a1->m[5] * a1->m[7]) * a1->m[0] -
                 (a1->m[1] * a1->m[8] - a1->m[2] * a1->m[7]) * a1->m[3] +
                 (a1->m[1] * a1->m[5] - a1->m[2] * a1->m[4]) * a1->m[6];

    if (!(det < 0.0))
    {
        if (RDEBUG__enabled && RDEBUG_ask_flag("UGMATH_mtx_debug", true) == 1)
        {
            lprintf("\northoNormalizeWithReflection() given non-reflection transform...\n");
            MTX3_lprintf(0, 0, a1);
        }
        return false;
    }

    if (MTX3_is_ortho_normal(a1, 1.0e-14))
    {
        if (RDEBUG__enabled && RDEBUG_ask_flag("UGMATH_mtx_debug", true) == 1)
        {
            lprintf("\northoNormalizeWithReflection() given already orthonormal transform...\n");
            MTX3_lprintf(0, 0, a1);
        }
        return false;
    }

    {
        UGS::Math::Matrix3 before = *a1;

        if (RDEBUG__enabled && RDEBUG_ask_flag("UGMATH_mtx_debug", true) == 1)
        {
            lprintf("\northoNormalizeWithReflection()...\n");
            MTX3_lprintf(0, "Before:", a1);
        }

        UGS::Math::Vector3 z = {a1->m[6], a1->m[7], a1->m[8]};
        double x0 = a1->m[0], x1 = a1->m[1], x2 = a1->m[2];
        double y0 = a1->m[3], y1 = a1->m[4], y2 = a1->m[5];
        UGS::Math::Vector3 v;
        v.x = x1 * z.z - x2 * z.y;
        v.y = x2 * z.x - x0 * z.z;
        v.z = x0 * z.y - x1 * z.x;
        MTX3_init_y_z(&v, &z, a1);

        double n0 = a1->m[0], n1 = a1->m[1], n2 = a1->m[2];
        double n3 = a1->m[3], n4 = a1->m[4], n5 = a1->m[5];
        double n6 = a1->m[6], n7 = a1->m[7], n8 = a1->m[8];
        if (n1 * x1 + n0 * x0 + n2 * x2 < 0.0)
        {
            n0 = -n0;
            n1 = -n1;
            n2 = -n2;
            a1->m[0] = n0;
            a1->m[1] = n1;
            a1->m[2] = n2;
        }
        if (n3 * y0 + n4 * y1 + n5 * y2 < 0.0)
        {
            v.x = -n3;
            v.y = -n4;
            v.z = -n5;
            a1->m[3] = v.x;
            a1->m[4] = v.y;
            a1->m[5] = v.z;
        }
        if (n7 * z.y + n6 * z.x + z.z * n8 < 0.0)
        {
            n6 = -n6;
            n7 = -n7;
            n8 = -n8;
            a1->m[6] = n6;
            a1->m[7] = n7;
            a1->m[8] = n8;
        }

        bool changed = false;
        int i = 0;
        do
        {
            if (!(fabs(before.m[i] - a1->m[i]) <= 1.0e-10))
            {
                changed = true;
                break;
            }
        } while (++i < 9);
        if (!changed)
            changed = MTX3_is_ortho_normal(a1, 1.0e-14) !=
                      MTX3_is_ortho_normal(&before, 1.0e-14);

        if (RDEBUG__enabled && RDEBUG_ask_flag("UGMATH_mtx_debug", true) == 1)
        {
            lprintf("\northoNormalizeWithReflection()...\n");
            MTX3_lprintf(0, "After:", a1);
            if (changed)
                sub_18009C880(before.m, a1->m);
        }
        return changed;
    }
}
