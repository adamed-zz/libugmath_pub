







#include <cmath>
#include <emmintrin.h>

double EQ_ask_number_tolerance(void);
void h015(double *a1, double *a2, double *a3, double *a4, double *a5, int *a6);

void h015a(double *a1, double *a2, double *a3, double *a4, double *a5, int *a6)
{
    double v10 = EQ_ask_number_tolerance();
    double v11 = v10 * EQ_ask_number_tolerance();
    h015(a1, a2, a3, a4, a5, a6);
    if (*a6 == 2)
    {
        double v12 = *a1;
        double v13 = a1[1];
        double v14 = a1[2];
        double v15 = v12 * v12 + v13 * v13 + v14 * v14;
        if (!(v11 >= fabs(v15)))
        {
            double v16 = *a2;
            double v17 = a2[1];
            double v18 = a2[2];
            double v19 = v16 * v16 + v17 * v17 + v18 * v18;
            if (!(v11 >= fabs(v19)))
            {
                double v20 = *a3 * *a3 + a3[1] * a3[1] + a3[2] * a3[2];
                if (!(v11 >= fabs(v20)))
                {
                    double v21;
                    if (v15 < 0.0)
                        v21 = sqrt(v15);
                    else
                        v21 = _mm_sqrt_pd(_mm_set_sd(v15)).m128d_f64[0];
                    double v23 = 1.0 / v21;
                    double v24;
                    if (v19 < 0.0)
                        v24 = sqrt(v19);
                    else
                        v24 = _mm_sqrt_pd(_mm_set_sd(v19)).m128d_f64[0];
                    double v25 = 1.0 / v24;
                    double v26;
                    if (v20 < 0.0)
                        v26 = sqrt(v20);
                    else
                        v26 = _mm_sqrt_pd(_mm_set_sd(v20)).m128d_f64[0];
                    double inv3 = 1.0 / v26;
                    double u3[3];
                    u3[0] = a3[0] * inv3;
                    u3[1] = a3[1] * inv3;
                    u3[2] = a3[2] * inv3;
                    double u1[3];
                    u1[0] = v12 * v23;
                    u1[1] = v13 * v23;
                    u1[2] = v14 * v23;
                    double u2[3];
                    u2[0] = v16 * v25;
                    u2[1] = v17 * v25;
                    u2[2] = v18 * v25;
                    h015(u1, u2, u3, a4, a5, a6);
                    if (*a6 == 1)
                    {
                        double v28 = v25 * a5[1];
                        double v29 = inv3 * a5[2];
                        *a5 = v23 * *a5;
                        a5[1] = v28;
                        a5[2] = v29;
                    }
                }
            }
        }
    }
}
