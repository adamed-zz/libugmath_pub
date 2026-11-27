







#include <cmath>

double EQ_ask_number_tolerance(void);
void h006(double *a1, const double *a2, const double *a3, const int *a4,
          const double *a5, int *a6, int *a7);

void h0065(double *a1, double *a2, double *a3, double *a4)
{
    double v9 = *a1;
    double v14 = *a3;
    double v7 = v14;
    int v11 = 1;
    double v10 = v9 + v14;
    int v12 = 0;
    int v13 = 0;
    h006(a2, &v9, &v10, &v11, &v14, &v13, &v12);
    double v8 = (double)v12 * v7 + *a2 - *a1;
    *a4 = v8;
    if (EQ_ask_number_tolerance() >= fabs(v8 - v7))
        *a4 = 0.0;
}
