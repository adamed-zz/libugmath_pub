

























#include <intrin.h>

__declspec(dllimport) extern int MACH__checking_level;
__declspec(dllimport) void ERROR_internal(const char* file_name, int line,
                                                     const char* message, ...);

double BCDF_CALC_single_weight(int n, double* knots, int idx)
{
    if (MACH__checking_level > 0 && n < 2)
    {
        ERROR_internal("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\bcdf_calc.c", 758,
                       "Not Enough Parameters");
        __debugbreak();
        __assume(0);
    }
    if (idx == 0)
        return (knots[1] - knots[0]) * 0.5;
    if (idx == n - 1)
    {
        const double* p = knots + n;
        return (p[-1] - p[-2]) * 0.5;
    }
    const double* p = knots + idx;
    return (p[1] - p[-1]) * 0.5;
}
