





#include <math.h>

void h055(const double* a1, double* a2) {
    double v2 = *a1;
    double v4 = *a1;
    if (!(*a1 >= 0.0)) v4 = -v4;
    if (v4 < 1.0) {
        double v5 = 1.0 - v2 * v2;
        double v6 = sqrt(v5);
        *a2 = 0x1.921fb54442d18p+0 - atan(v2 / v6);
    } else {
        *a2 = 0.0;
        if (*a1 < 0.0) *a2 = 0x1.921fb54442d18p+1;
    }
}
