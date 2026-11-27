







#include <math.h>
extern void vunt3(const double* a1, int* ok, double* out);

void h310(const double* a1, const double* a2, const double* a3, double* a4)
{
    double v7 = *a1 - *a2;
    double v6 = a1[1] - a2[1];
    double v4 = a1[2] - a2[2];
    double u[3];
    int v13;
    vunt3(a3, &v13, u);
    double v10 = u[0];
    double v11 = u[1];
    double v12 = u[2];
    double v8 = (v12 * v7 - v10 * v4) * (v12 * v7 - v10 * v4)
              + (v11 * v4 - v12 * v6) * (v11 * v4 - v12 * v6)
              + (v10 * v6 - v11 * v7) * (v10 * v6 - v11 * v7);
    *a4 = sqrt(v8);
}
