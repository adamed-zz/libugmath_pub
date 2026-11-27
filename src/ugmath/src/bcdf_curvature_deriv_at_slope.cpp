










#include <math.h>

struct BCDF_s;

double* BCDF_return_crvatr_deriv_pars_array(BCDF_s* a, int* count);
double* BCDF_return_slope_pars_array(BCDF_s* a, int* count);

int BCDF_curvature_deriv_at_slope(BCDF_s* a1, int a2, int* a3)
{
    int n_deriv;
    int n_slope;
    double* deriv = BCDF_return_crvatr_deriv_pars_array(a1, &n_deriv);
    double* slope = BCDF_return_slope_pars_array(a1, &n_slope);
    int count = 0;
    unsigned int found = 0;
    *a3 = 0;
    if (a2 < n_slope && n_deriv > 0)
    {
        if (slope)
        {
            if (deriv)
            {
                double t = slope[a2];
                __int64 i = 0;
                while (i < n_deriv)
                {
                    if (found)
                        break;



                    if (fabs(deriv[i] - t) <= 1.0e-10)
                    {
                        found = 1;
                        continue;
                    }
                    if (t > deriv[i])
                    {
                        ++count;
                        ++i;
                    }
                }
            }
        }
    }
    *a3 = count;
    return found;
}
