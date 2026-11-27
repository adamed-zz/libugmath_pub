



#include <cmath>
#include <immintrin.h>

double EQ_ask_length_tolerance();
void h430(const double* a1, const double* a2, const double* a3, double* a4);

bool bc_POLE_project_to_line2(double* const a1, double* const a2, double* const a3, double* const a4)
{
    double p[3];
    p[0] = a1[0] / a1[3];
    p[1] = a1[1] / a1[3];
    p[2] = a1[2] / a1[3];
    double q[3];
    q[0] = a2[0] / a2[3];
    q[1] = a2[1] / a2[3];
    q[2] = a2[2] / a2[3];
    double len = sqrt(a3[0] * a3[0] + a3[1] * a3[1] + a3[2] * a3[2]);
    __m128d lv = _mm_set_sd(len);
    __m128d av = _mm_and_pd(lv, _mm_castsi128_pd(_mm_set1_epi64x(0x7FFFFFFFFFFFFFFFll)));
    double alen = _mm_cvtsd_f64(av);
    double tol = EQ_ask_length_tolerance();
    if (!(tol >= alen))
    {
        double t[3];
        t[0] = a3[0] / len + q[0];
        t[1] = a3[1] / len + q[1];
        t[2] = a3[2] / len + q[2];
        double out[3];
        h430(q, t, p, out);
        a4[0] = out[0] * a1[3];
        a4[1] = out[1] * a1[3];
        a4[2] = out[2] * a1[3];
        a4[3] = a1[3];
        return true;
    }
    return false;
}
