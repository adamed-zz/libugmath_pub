




















#include <emmintrin.h>
extern void h053(const double* a1, const double* a2, double* a3);

static inline double ARC_SPLINE_snap(double x) { return _mm_cvtsd_f64(_mm_set_sd(x)); }

double __cdecl ARC_SPLINE_ask_angle_from_tan(double a1, double a2, int a3)
{
    double v8;
    h053(&a1, &a2, &v8);
    double result = v8 * 57.29577951308235;
    double v5;
    if (a3 == 90)
    {
        if (!(result > 90.0 && result < 270.0))
        {
            v5 = ARC_SPLINE_snap(result);
            if (result >= 270.0 && result < 360.0)
                v5 = ARC_SPLINE_snap(result) - 360.0;
        }
        else
        {
            v5 = result - 180.0;
        }
        return v5;
    }
    else if (a3 == 180 && result > 180.0)
        return result - 360.0;
    return result;
}
