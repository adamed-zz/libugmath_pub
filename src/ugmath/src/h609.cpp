









#include <math.h>

void h609(const double* a1, const double* a2, const double* a3, const double* a4,
          int* a5, double* a6, double* a7, double a8)
{
    double v10, v11, v12, v13, v14, v16, v17, v18, v20, v21, v23, v24, v25, v26, v27;
    double v28, v29, v30, v31;
    int v19, v22;
    v10 = 1.0e-10 * a8;
    v11 = *a1;
    v12 = a1[1];
    *a5 = 1;
    v13 = *a3 - v11;
    v14 = a3[1] - v12;
    v16 = sqrt(v14 * v14 + v13 * v13);
    v17 = *a2;
    v18 = *a4;
    if (v10 > v16)
    {
        v19 = 4;
        if (v10 <= fabs(v17 - v18))
            v19 = 1;
        *a5 = v19;
        return;
    }
    v20 = v18 + v17;
    if (v10 > fabs(v18 + v17 - v16))
        goto LABEL_15;
    if (!(v16 - v20 < 0.0))
    {
        if (v16 - v20 != 0.0)
            return;
        goto LABEL_15;
    }
    v21 = fabs(v17 - v18);
    if (v10 > fabs(v21 - v16))
        goto LABEL_15;
    if (v16 - v21 < 0.0)
        return;
    if (v16 - v21 == 0.0)
    {
    LABEL_15:
        v22 = 2;
        goto LABEL_16;
    }
    v22 = 3;
LABEL_16:
    *a5 = v22;
    v23 = *a4 + *a2;
    v24 = ((*a2 - *a4) * v23 / v16 + v16) * 0.5;
    v25 = (v23 - v16) * (v23 + v16) * (*a2 + v16 - *a4) * (*a4 + v16 - *a2);
    v26 = sqrt(0.0 > v25 ? 0.0 : v25);
    v27 = v26 * 0.5 / v16;
    if (v22 == 2)
        v27 = 0.0;
    v28 = v24 * v13;
    v29 = v27 * v14;
    v30 = v24 * v14;
    v31 = v27 * v13;
    a6[0] = (v28 - v29) / v16 + v11;
    a7[0] = (v29 + v28) / v16 + v11;
    a6[1] = (v31 + v30) / v16 + v12;
    a7[1] = (v30 - v31) / v16 + v12;
}
