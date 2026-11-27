





#include <math.h>

int find_closest_reals(int a1, double* a2, int a3, int a4, double a5) {
    signed int v5 = 0;
    int v6 = a1 - 1;
    double v8 = 0.0;
    int v9 = -1;
    if (a3 >= 0) v5 = a3;
    if (a4 > v6) a4 = v6;
    for (int v10 = v5; v10 <= a4; ++v10) {
        double v11 = fabs(a5 - a2[v10]);
        if (v10 == v5) {
            v9 = v5;
            v8 = v11;
        } else if (v8 > v11) {
            v9 = v10;
            v8 = v11;
        }
    }
    return v9;
}
