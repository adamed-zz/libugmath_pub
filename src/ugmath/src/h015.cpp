







#include <cmath>

double EQ_ask_number_tolerance(void);

void h015(double *a1, double *a2, double *a3, double *a4, double *a5, int *a6)
{
    double v10 = a3[2] * a2[1] - a3[1] * a2[2];
    double v11 = *a2 * a3[2] - *a3 * a2[2];
    double v12 = *a2 * a3[1] - *a3 * a2[1];
    double v13 = v10 * *a1 - v11 * a1[1] + v12 * a1[2];
    if (!(EQ_ask_number_tolerance() >= fabs(v13)))
    {
        *a6 = 1;
        double v14 = v10 * *a4 - v11 * a4[1] + v12 * a4[2];
        *a5 = v14;
        double v15 = (a3[2] * a4[1] - a3[1] * a4[2]) * *a1
                   - (a3[2] * *a4 - *a3 * a4[2]) * a1[1]
                   + (a3[1] * *a4 - *a3 * a4[1]) * a1[2];
        a5[1] = v15;
        double v16 = a4[2];
        double v17 = a4[1];
        double v18 = *a1;
        double v19 = a1[1];
        double v20 = a1[2];
        double v21 = a2[1] * *a4;
        double v22 = a2[1] * v16 - a2[2] * v17;
        double v23 = a2[2] * *a4;
        double v24 = *a2;
        a5[1] = v15 / v13;
        *a5 = v14 / v13;
        a5[2] = (v22 * v18 - (v24 * v16 - v23) * v19 + (v24 * v17 - v21) * v20) / v13;
    }
    else
    {
        *a6 = 2;
    }
}
