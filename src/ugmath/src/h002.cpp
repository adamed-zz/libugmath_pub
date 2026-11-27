







#include <cmath>
#include <emmintrin.h>

double EQ_ask_number_tolerance(void);
__m128d sub_1800B2800(double *a1, double *a2);

void h002(double *a1, const double *a2)
{
    if (!(0.0 > *a2))
    {
        if (EQ_ask_number_tolerance() >= fabs(*a2 - *a1))
        {
            *a1 = 0.0;
            return;
        }
        double v4 = EQ_ask_number_tolerance();
        double v5 = *a2;
        if (!(v4 >= fabs(*a2 - 0.0)))
        {
            double v6 = *a1;
            if (*a1 > 0.0)
            {
                __m128d r7 = sub_1800B2800(a1, (double *)a2);
                double v7 = r7.m128d_f64[0];
                if (!(EQ_ask_number_tolerance() >= fabs(v7 - 0.0)))
                {
                    *a1 = v7;
                    return;
                }
                *a1 = 0.0;
                return;
            }
            if (!(v6 >= 0.0))
                v6 = -v6;
            double v8 = v6 / v5;
            double v9;
            if (!(v6 / v5 >= 0.0))
                v9 = -floor(-v8);
            else
                v9 = floor(v8);
            double v10 = v6 - v5 * v9;
            if (EQ_ask_number_tolerance() >= fabs(v10 - 0.0))
            {
                *a1 = 0.0;
                return;
            }
            *a1 = *a2 - v10;
            if (EQ_ask_number_tolerance() >= fabs(*a1 - 0.0))
                *a1 = 0.0;
        }
    }
}
