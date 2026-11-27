








#include <math.h>

extern double EQ_ask_length_tolerance(void);

void h525(const double* a1, const double* a2, double* a3, int* a4)
{
    double v6 = *a2 - *a1;
    double v9 = a2[1] - a1[1];
    double v11 = sqrt(v6 * v6 + v9 * v9);
    double cx = -v9 * 0.5;
    double cy = v6 * 0.5;
    if (a1[2] < 0.0)
    {
        cx = -(cx);
        cy = -(cy);
    }
    double r2 = fabs(a1[2]);
    double v20;
    if (EQ_ask_length_tolerance() >= fabs(r2 - 0.0))
    {
        v20 = 0.0;
        a3[2] = a1[0];
        a3[3] = a1[1];
    }
    else
    {
        double mx = (a1[0] + a2[0]) * 0.5;
        double my = (a2[1] + a1[1]) * 0.5;
        double k = (r2 - 1.0 / r2) * 0.5;
        a3[2] = mx - k * cx;
        a3[3] = my - k * cy;
        v20 = (1.0 / r2 + r2) * (v11 * 0.25);
    }
    a3[4] = v20;
    a3[0] = *a1;
    a3[1] = a1[1];
    a3[5] = *a2;
    a3[6] = a2[1];
    int v21 = 1;
    if (a1[2] >= 0.0)
        v21 = 3;
    *a4 = v21;
}
