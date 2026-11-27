


#include <math.h>

extern "C" int dep_eqz(const double* a, const double* b, const int* mode);

void m4024(double* a1, double* a2, double* a3) {
    double v4 = 0.0;
    const double v6 = a1[1] - a1[4];
    const double v9 = a1[3] - a1[0];
    double v16 = 0.0;
    int v15 = 0;
    const double len = sqrt(v9 * v9 + v6 * v6);
    const int v12 = dep_eqz(a1 + 2, &v16, &v15);
    const double v13 = a1[2];
    if (!v12) v4 = 1.0 / v13;
    *a3 = fabs(v13 + v4) * (len * 0.25);
    const double v14 = (a1[2] - v4) * 0.25;
    *a2 = (a1[0] + a1[3]) * 0.5 - v14 * v6;
    a2[1] = (a1[4] + a1[1]) * 0.5 - v14 * v9;
}
