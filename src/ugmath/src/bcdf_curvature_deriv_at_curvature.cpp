








#include <math.h>

struct BCDF_s;

double* BCDF_return_crvatr_deriv_pars_array(BCDF_s* a, int* count);
double* BCDF_return_crvatr_pars_array(BCDF_s* a, int* count);

int BCDF_curvature_deriv_at_curvature(BCDF_s* a1, int a2, int* a3)
{
    int n_deriv;
    int n_params;
    double* deriv = BCDF_return_crvatr_deriv_pars_array(a1, &n_deriv);
    double* param = BCDF_return_crvatr_pars_array(a1, &n_params);
    int count = 0;
    unsigned int found = 0;
    *a3 = 0;
    if (a2 < n_params && n_deriv > 0)
    {
        if (param)
        {
            if (deriv)
            {
                double t = param[a2];
                if (n_deriv > 0)
                {
                    __int64 i = 0;
                    do
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
                    } while (i < n_deriv);
                }
            }
        }
    }
    *a3 = count;
    return found;
}
