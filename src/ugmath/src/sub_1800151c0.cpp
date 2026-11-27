







#include <math.h>
#include <xmmintrin.h>
#include <emmintrin.h>
#include <algorithm>

extern "C" double __fastcall sub_1800151C0(double *a1, double *a2)
{
    double len1 = sqrt(a1[0] * a1[0] + a1[1] * a1[1] + a1[2] * a1[2]);
    double len2 = sqrt(a2[0] * a2[0] + a2[1] * a2[1] + a2[2] * a2[2]);
    double u1, u2, dot;

    if (1.0e-10 > len1 || 1.0e-10 > len2)
        return 1.0;
    u1 = 1.0 / len1;
    u2 = 1.0 / len2;
    dot = (a2[1] * u2) * (a1[1] * u1)
        + (a2[0] * u2) * (a1[0] * u1)
        + (a2[2] * u2) * (a1[2] * u1);
    if (fabs(dot) <= 1.0e-10)
        return 0.0;
    if (fabs(dot - 1.0) <= 1.0e-10)
        return 1.0;

    return _mm_cvtsd_f64(_mm_max_sd(_mm_set_sd(-1.0), _mm_set_sd(dot)));
}
