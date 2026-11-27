









#include <math.h>

extern void vunt3(const double* a1, int* a2, double* a3);

void h551(const double* a1, const double* a2, int const* a3, int const* a4,
          int const* a5, double* a6)
{
    double v6 = *a1;
    double v9 = *a2;
    double v10 = v6 * v6 + v9 * v9 + 1.0;
    double v11 = v10 - (*a1 + v6) * v6;
    double v12 = sqrt(v11);
    double v23 = v12 * (double)*a3;
    double v13 = v10 - (v9 + v9) * v9;
    double v14 = sqrt(v13);
    double v24 = v14 * (double)*a4;
    double v10b = v10 - 2.0;
    double v15 = sqrt(v10b);
    double v25 = v15 * (double)*a5;

    double q[3];
    q[0] = v23;
    q[1] = v24;
    q[2] = v25;
    int dummy;
    vunt3(q, &dummy, a6 + 6);
    double v17 = a6[7];
    double v18 = a6[8] * 0.0;
    double v19 = a6[6];
    double v26[3];
    v26[1] = v19 - v18;
    v26[0] = v18 - v17;
    v26[2] = v17 * 0.0 - v19 * 0.0;
    vunt3(v26, &dummy, a6);
    double v20 = a6[1];
    double v21 = a6[0];
    double v22 = a6[2] * v23;
    double v27[3];
    v27[0] = a6[2] * v24 - v20 * v25;
    v27[1] = v21 * v25 - v22;
    v27[2] = v20 * v23 - v21 * v24;
    vunt3(v27, &dummy, a6 + 3);
}
