









#include <cmath>
#include <emmintrin.h>

double EQ_ask_number_tolerance(void);

void h006(double *a1, const double *a2, const double *a3, const int *a4,
          const double *a5, int *a6, int *a7)
{
    int hit = 0;
    int off = 0;
    double v13;
    double v10hi;
    __m128d v22;
    if (!(*a3 >= *a2))
    {
        v22 = _mm_set_pd(*a2, *a3);
        v13 = *a3;
        v10hi = *a2;
    }
    else
    {
        v22 = _mm_set_pd(*a3, *a2);
        v13 = *a2;
        v10hi = *a3;
    }
    double a1v = *a1;
    if (EQ_ask_number_tolerance() >= fabs(*a1 - v13))
    {
        *a1 = v13;
        hit = 1;
        goto DONE;
    }
    if (!(a1v > v13))
        goto SCALE;
    if (EQ_ask_number_tolerance() >= fabs(*a1 - v10hi))
    {
        *a1 = v10hi;
        hit = 1;
        goto DONE;
    }
    if (!(a1v > v10hi))
    {
        hit = 1;
        goto DONE;
    }
SCALE:
    {
        double period = (*a4 == 1) ? *a5 : (v10hi - v13);
        __m128d v18 = _mm_div_pd(_mm_sub_pd(v22, _mm_set_pd(a1v, a1v)),
                                 _mm_set_pd(period, period));
        double v19 = v18.m128d_f64[1];
        if (!(v19 > 0.0))
        {
            if (v18.m128d_f64[0] < 0.0)
            {
                double v21 = -v18.m128d_f64[0];
                if (v21 > 2147483647.0 || v21 < -2147483647.0)
                    v21 = 0.0;
                off = -(int)v21;
                int b = EQ_ask_number_tolerance() >= fabs((double)off - v19);
                if (b == 1 || v19 > (double)off)
                    hit = 1;
            }
        }
        else
        {
            if (v19 > 2147483647.0 || v19 < -2147483647.0)
                v19 = 0.0;
            off = (int)v19;
            double v20 = (double)(int)v19;
            int b = EQ_ask_number_tolerance() >= fabs(v20 - v18.m128d_f64[0]);
            if (b == 1 || v20 > v18.m128d_f64[0])
                hit = 1;
        }
    }
DONE:
    *a6 = hit;
    *a7 = off;
}
