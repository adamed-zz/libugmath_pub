


















#include <math.h>
#include <intrin.h>

struct BCDF_s;


__declspec(dllimport) extern int MACH__checking_level;
__declspec(dllimport) __declspec(noreturn) void ERROR_internal(const char* file_name,
                                                                int line,
                                                                const char* message, ...);


double* BCDF_return_crvatr_deriv_pars_array(BCDF_s* a1, int* count);
double* BCDF_return_param_array(BCDF_s* a1, int* count);

int BCDF_point_at_curvature_deriv(BCDF_s* a1, int a2)
{
    int v12;
    int v13;
    double* crv_deriv = BCDF_return_crvatr_deriv_pars_array(a1, &v12);
    double* params = BCDF_return_param_array(a1, &v13);
    int count = 0;
    int found = 0;
    if (a2 < v12 && v13 > 0)
    {
        if (crv_deriv)
        {
            if (params)
            {
                double value = crv_deriv[a2];
                __int64 i = 0;
                while (i < v13)
                {
                    if (found)
                        break;
                    if (fabs(params[i] - value) <= 1.0e-10)
                        found = 1;
                    else if (value > params[i])
                    {
                        ++count;
                        ++i;
                    }
                }
            }
        }
    }
    if (MACH__checking_level > 0 && found != 1)
    {
        ERROR_internal("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\bcdf_gen.c", 4130,
                       "Bcurve Defining Data Structure Corrupt");
        __debugbreak();
    }
    return count;
}
