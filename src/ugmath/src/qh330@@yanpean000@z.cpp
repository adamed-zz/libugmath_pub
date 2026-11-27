





#include <math.h>

double h330(double* a1, double* a2, double* a3, double* a4)
{
    double v4 = *a1;
    double v5 = a1[1];
    double v6 = a1[2];
    double v1 = a3[1] - v5;
    double v7 = a3[1] - v5;
    double v8 = *a4;
    double v9 = a4[1];
    double v10 = a4[2];
    double v11 = *a2 - *a1;
    double v12 = a2[1] - v5;
    double v13 = a2[2] - v6;
    double v27 = a3[2] - v6;
    double v30 = *a3 - *a1;
    double v28 = v9 * v7 + *a4 * v30 + v10 * v27;
    double v14 = v12 * v12 + v11 * v11 + v13 * v13;
    double v15 = v9 * v12 + *a4 * v11 + v10 * v13;
    double v29 = -v14 - -v15 * v15;
    if (fabs(v29) <= 1.0e-10)
        goto LABEL_6;
    {
        double v16 = (-(v12 * v7 + v11 * v30 + v13 * v27) - -v15 * v28) / v29;


        if (!(v16 >= 0.0) || !(1.0 >= v16))
        {
            if (0.0 > v16)
                goto LABEL_7;
            goto LABEL_6;
        }
        {
            double v17 = -v16;
            double v18 = (v14 * v28 - v15 * (v12 * v7 + v11 * v30 + v13 * v27)) / v29;
            double v19 = v18 * v8 + v11 * v17 + v30;
            double v20 = v18 * v9 + v12 * v17 + v1;
            double v21 = v18 * v10 + v13 * v17 + v27;
            return v19 * v19 + v20 * v20 + v21 * v21;
        }
    }
LABEL_6:
    v4 = *a2;
    v5 = a2[1];
    v6 = a2[2];
LABEL_7:
    {
        double v22 = v5 - a3[1];
        double v23 = v4 - *a3;
        double v24 = v6 - a3[2];
        double v25 = v9 * v22 + v8 * v23 + v10 * v24;
        double v19 = v8 * v25 - v23 * 1.0;
        double v20 = v9 * v25 - v22 * 1.0;
        double v21 = v10 * v25 - v24 * 1.0;
        return v19 * v19 + v20 * v20 + v21 * v21;
    }
}
