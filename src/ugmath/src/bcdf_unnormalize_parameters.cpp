








#include <intrin.h>

struct BCDF_s;

double* BCDF_return_param_array(BCDF_s* a1, int* a2);
double* BCDF_return_slope_pars_array(BCDF_s* a1, int* a2);
double* BCDF_return_crvatr_pars_array(BCDF_s* a1, int* a2);
double* BCDF_return_crvatr_deriv_pars_array(BCDF_s* a1, int* a2);

#ifdef BCDF_UNNORM_TEST
extern int MACH__checking_level;
void ERROR_internal(const char* a1, int a2, const char* a3, ...);
#else
__declspec(dllimport) extern int MACH__checking_level;
__declspec(dllimport) void ERROR_internal(const char* a1, int a2, const char* a3, ...);
#endif

void BCDF_unnormalize_parameters(BCDF_s* a1, double a2)
{
    int n1, n2, n3, n4;
    double* p = BCDF_return_param_array(a1, &n1);
    if (MACH__checking_level > 0 && !p)
    {
        ERROR_internal("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\bcdf_gen.c", 3556,
                       "The Parameter Array Is NULL");
        __debugbreak();
        __assume(0);
    }
    p[0] = 0.0;
    for (int i = 0; i < n1; i++)
        p[i] *= a2;
    p = BCDF_return_slope_pars_array(a1, &n2);
    for (int i = 0; i < n2; i++)
        p[i] *= a2;
    p = BCDF_return_crvatr_pars_array(a1, &n3);
    for (int i = 0; i < n3; i++)
        p[i] *= a2;
    p = BCDF_return_crvatr_deriv_pars_array(a1, &n4);
    for (int i = 0; i < n4; i++)
        p[i] *= a2;
}
