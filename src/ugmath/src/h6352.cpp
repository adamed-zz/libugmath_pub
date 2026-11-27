














#include <math.h>

double EQ_ask_length_tolerance();
int SOLVE_quadratic(const double* a1, double* a2);

void h6352(const double* a1, const double* a2, const double* a3, double* a4,
           double* a5, double* a6, int* a7)
{
    double coeff[3];
    double roots[2] = {0.0, 0.0};
    int v22;

    *a7 = 0;
    double v14 = EQ_ask_length_tolerance();
    double v12 = a1[1] - a3[1];
    double v13 = a1[0] - a3[0];
    double v15 = a1[2] - a3[2];
    double v16 = v13 * a2[0];
    double v17 = a2[0] * a3[3] + a2[1] * a3[4] + a2[2] * a3[5];
    double v18 = v13 * a3[3] + v12 * a3[4] + v15 * a3[5];
    double v19 = v15 * a2[2];
    double v44 = 1.0 - v17 * v17;


    double v20d = v16 + v12 * a2[1] + v19 - v18 * v17;
    double v20 = v20d + v20d;
    double v21 = v12 * v12 + v13 * v13 + v15 * v15 - v18 * v18 - a3[7];

    coeff[1] = v20;
    coeff[0] = v21;
    coeff[2] = v44;
    v22 = SOLVE_quadratic(coeff, roots);
    *a7 = v22;
    if (!v22)
        return;

    {
        double v23 = roots[0];
        double v24 = v23;
        if (v23 < 0.0)
            v24 = -v23;
        double v25 = roots[1];
        double v26 = v25;
        if (v25 < 0.0)
            v26 = -v25;
        if (v26 > v24 || v22 == 1)
        {
            a4[0] = v23;
            a4[1] = v25;
        }
        else
        {
            a4[0] = v25;
            a4[1] = v23;
        }
    }

    long long v27 = *a7;
    if (v27 >= 1)
    {
        double* v29 = a5 + 1;
        double* v40 = a6;
        double* pa4 = a4;
        do
        {
            double v30 = *a2 * *pa4 + *a1;
            double v38 = a2[1] * *pa4 + a1[1];
            double v31 = a2[2] * *pa4 + a1[2];
            double v32 = a3[4];
            double v33 = a3[3];
            double v34 = a3[5];
            *(v29 - 1) = v30;
            *v29 = v38;
            v29[1] = v31;
            double v35 = (v30 - *a3) * v33 + (v38 - a3[1]) * v32
                       + (v31 - a3[2]) * v34;
            double v36 = v32 * v35 + a3[1];
            double v37 = v31 - (v34 * v35 + a3[2]);
            double q0 = v30 - (v33 * v35 + *a3);
            double q1 = v38 - v36;
            double n = q1 * q1 + q0 * q0 + v37 * v37;
            double v39 = sqrt(n);
            if (v39 > v14)
            {
                double inv = 1.0 / v39;
                v40[0] = q0 * inv;
                v40[1] = q1 * inv;
                v40[2] = v37 * inv;
            }
            ++pa4;
            v29 += 3;
            v40 += 3;
            --v27;
        } while (v27);
    }
}
