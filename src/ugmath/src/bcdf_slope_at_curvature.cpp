





#include <math.h>

struct BCDF_s;

double* BCDF_return_crvatr_pars_array(BCDF_s* a, int* count);
double* BCDF_return_slope_pars_array(BCDF_s* a, int* count);
double* BCDF_return_slope_array(BCDF_s* a, int* count1, int* count2);


__declspec(dllimport) extern int MACH__checking_level;
__declspec(dllimport) void ERROR_internal(const char* file, int line, const char* message, ...);

int BCDF_slope_at_curvature(BCDF_s* a1, int a2, int* a3, double* a4)
{
    __int64 v4 = a2;
    int v8 = 0;
    int v16;
    int v17;
    int v18;
    double* v9 = BCDF_return_crvatr_pars_array(a1, &v17);
    if (v17 <= 0)
        return 0;
    double v11 = v9[v4];
    double* v12 = BCDF_return_slope_pars_array(a1, &v16);
    int v13 = 0;
    if (v16 > 0)
    {
        do
        {
            if (1.0e-10 >= fabs(*v12 - v11))
                goto FOUND;
            ++v13;
            ++v12;
        } while (v13 < v16);
        goto LABEL_8;
    FOUND:
        *a3 = v13;
        double* v14 = BCDF_return_slope_array(a1, &v16, &v18);
        v8 = 1;
        __int64 v15 = v13 * v18;
        a4[0] = v14[v15];
        a4[1] = v14[v15 + 1];
        a4[2] = v14[v15 + 2];
    }
LABEL_8:
    if (MACH__checking_level > 0 && v8 != 1)
    {
        ERROR_internal(
            "o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\bcdf_gen.c",
            2891,
            "Point With Assigned Curvature Has No Slope");
        __debugbreak();
    }
    return v8;
}
