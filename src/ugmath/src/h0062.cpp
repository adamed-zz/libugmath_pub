






#include <cmath>

double EQ_ask_number_tolerance(void);
void h006(double *a1, const double *a2, const double *a3, const int *a4,
          const double *a5, int *a6, int *a7);

void h0062(double *a1, int *a2, double *a3, double *a4, int *a5)
{
    long long slot;
    double v11 = 0.0;
    *a4 = *a1;
    *a5 = 0;
    if (*a2 == 1)
    {
        h006(a1, &v11, a3, a2, a3, (int *)&slot, a5);
        if ((int)slot == 1)
        {
            double v9 = (double)*a5 * *a3 + *a1;
            *a4 = v9;
            double v10 = fabs(v9 - *a3);
            if (EQ_ask_number_tolerance() >= v10)
            {
                *a4 = 0.0;
                --*a5;
            }
        }
    }
}
