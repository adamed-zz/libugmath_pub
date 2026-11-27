



#include <math.h>

struct BCDF_s;

double* BCDF_return_crvatr_deriv_pars_array(BCDF_s* a1, int* count);
double* BCDF_return_slope_pars_array(BCDF_s* a1, int* count);
void BCDF_copy_single_3d_slope(BCDF_s* a1, int idx, double* out, int* types);

int BCDF_slope_at_curvature_deriv(BCDF_s* a1, int a2, int* a3, double* a4)
{
    __int64 v4 = a2;
    int v17;
    int v18;
    double* v8 = BCDF_return_crvatr_deriv_pars_array(a1, &v17);
    double* v9 = BCDF_return_slope_pars_array(a1, &v18);
    int v10 = 0;
    double* v11 = v9;
    unsigned int v12 = 0;
    int v16[4];
    *a3 = 0;
    if ((int)v4 < v17 && v18 > 0)
    {
        if (v8)
        {
            if (v9)
            {
                double v13 = v8[v4];
                __int64 v14 = 0;
                while (v14 < v18)
                {
                    if (v12)
                        break;
                    if (1.0e-10 >= fabs(v11[v14] - v13))
                    {
                        v12 = 1;
                    }
                    else if (v13 > v11[v14])
                    {
                        ++v10;
                        ++v14;
                    }
                }
            }
        }
    }
    *a3 = v10;
    if (v12 == 1)
    {
        BCDF_copy_single_3d_slope(a1, v10, a4, v16);
    }
    return v12;
}
