
















#include <intrin.h>
#include <math.h>

struct BCDF_s;

__declspec(dllimport) extern int MACH__checking_level;
__declspec(dllimport) void ERROR_internal(const char* file_name, int line,
                                                     const char* message, ...);


double* BCDF_return_slope_pars_array(BCDF_s* a1, int* count);
double* BCDF_return_param_array(BCDF_s* a1, int* count);

int BCDF_point_at_slope(BCDF_s* a1, int a2)
{
    int v10;
    int v11;
    double* v4 = BCDF_return_slope_pars_array(a1, &v11);
    double* v5 = BCDF_return_param_array(a1, &v10);
    int v6 = 0;
    int v7 = 0;
    __int64 v8 = 0;
    while (v7 < v10)
    {
        if (fabs(v4[a2] - v5[v8]) <= 1.0e-10)
        {
            v6 = 1;
            break;
        }
        ++v7;
        ++v8;
    }
    if (MACH__checking_level > 0 && v6 != 1)
    {
        ERROR_internal("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\bcdf_gen.c", 2525,
                       "Bcurve Defining Data Structure Corrupt");
        __debugbreak();
    }
    return v7;
}
