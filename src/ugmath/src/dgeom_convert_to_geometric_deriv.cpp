





#include <cmath>

int DGEOM_convert_to_geometric_deriv(double *const a1, int a2, double *const a3)
{
    a3[0] = a1[0];
    a3[1] = a1[1];
    a3[2] = a1[2];
    if (a2)
    {
        double v6 = a1[3];
        double v8 = sqrt(v6 * v6 + a1[4] * a1[4] + a1[5] * a1[5]);
        if (1.0e-10 > v8)
            return -2;
        a3[3] = v6 / v8;
        a3[4] = a1[4] / v8;
        a3[5] = a1[5] / v8;
        if (a2 != 1)
        {
            double v10 = a1[4];
            double v11 = a1[3];
            double v12 = a1[5];
            double v13 = a1[6];
            double v14 = v10 * a1[8] - v12 * a1[7];
            double v15 = v8 * v8;
            double v30 = v11 * a1[7] - v13 * v10;
            double v29 = v13 * v12 - v11 * a1[8];
            a3[6] = (v12 * v29 - v10 * v30) / (v8 * v8 * (v8 * v8));
            a3[7] = (v11 * v30 - v12 * v14) / (v8 * v8 * (v8 * v8));
            a3[8] = (v10 * v14 - v11 * v29) / (v8 * v8 * (v8 * v8));
            if (a2 != 2)
            {
                double v16 = a1[5];
                double v17 = a1[8];
                double v18 = a1[6];
                double v19 = v15 * v15 * v8;
                double v20 = a1[7];
                double v21 = a1[3];
                double v28 = v19;
                double v22 = a1[4];
                double v23 = v19 * v15;
                double v24 = v21 * a1[10] - a1[9] * v22;
                double v25 = v22 * a1[11] - v16 * a1[10];
                double v26 = a1[9] * v16 - v21 * a1[11];
                double v27 = (v20 * v22 + v18 * v21 + v17 * v16) * 4.0;
                a3[9] = ((v16 * v26 - v22 * v24) + (v17 * v29 - v20 * v30)) / v28 - (v16 * v29 - v22 * v30) * v27 / v23;
                a3[10] = ((v21 * v24 - v16 * v25) + (v18 * v30 - v17 * v14)) / v28 - (v21 * v30 - v16 * v14) * v27 / v23;
                a3[11] = ((v22 * v25 - v21 * v26) + (v20 * v14 - v18 * v29)) / v28 - (v22 * v14 - v21 * v29) * v27 / v23;
            }
        }
    }
    return 0;
}
