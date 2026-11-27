







#include <cmath>

double EQ_ask_number_tolerance(void);
void h006(double *a1, const double *a2, const double *a3, const int *a4,
          const double *a5, int *a6, int *a7);

void h0063(double *a1, const double *a2, const double *a3, const int *a4,
           const double *a5, int *a6, int *a7, double *a8)
{
    *a6 = 0;
    *a7 = 0;
    *a8 = *a1;
    if (*a4 == 1)
    {
        h006(a1, a2, a3, a4, a5, a6, a7);
        double v11 = (double)*a7 * *a5 + *a1;
        *a8 = v11;
        double v12 = *a3 - *a2;
        double v13 = fabs(v11 - *a3);
        if (EQ_ask_number_tolerance() >= v13)
        {
            double v14 = fabs(*a5 - v12);
            if (EQ_ask_number_tolerance() >= v14)
            {
                *a8 = *a2;
                --*a7;
            }
        }
    }
}
