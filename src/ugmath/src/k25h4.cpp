







#include <cmath>

static const double kLenTol = 1e-8;
static const double kZero = 0.0;




__declspec(noinline) int VEC2_unitize(const double* a1, double tol, double* out_len, double* a2)
{
    const double len = std::sqrt(a1[0] * a1[0] + a1[1] * a1[1]);
    if (!(tol >= len))
    {
        const double inv = 1.0 / len;
        *out_len = len;
        a2[0] = a1[0] * inv;
        a2[1] = a1[1] * inv;
        return 1;
    }
    *out_len = kZero;
    a2[0] = kZero;
    a2[1] = kZero;
    return 0;
}

__declspec(noinline) void k25h4(double* a1, double* a2, double* a3, int* a4)
{
    const double tol = kLenTol;
    *a4 = 3;
    const double v1[2] = { a3[0] - a1[0], a3[1] - a1[1] };
    const double v2[2] = { a3[0] - a2[0], a3[1] - a2[1] };
    double u1[2];
    double u2[2];
    double len1 = kZero;
    double len2 = kZero;
    VEC2_unitize(v1, tol, &len1, u1);
    VEC2_unitize(v2, tol, &len2, u2);
    const double dot = u2[0] * u1[0] + u2[1] * u1[1];
    if (dot > tol)
    {
        *a4 = 0;
        return;
    }
    if (len2 > len1 && tol >= std::fabs(len1))
    {
        *a4 = 1;
        return;
    }
    if (len1 > len2 && tol >= std::fabs(len2))
    {
        *a4 = 2;
        return;
    }
}
