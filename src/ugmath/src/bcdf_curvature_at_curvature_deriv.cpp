










#include <math.h>

struct BCDF_s;

double* BCDF_return_crvatr_deriv_pars_array(BCDF_s* a, int* count);
double* BCDF_return_crvatr_pars_array(BCDF_s* a, int* count);
void BCDF_copy_single_3d_crvatr(BCDF_s* a, int index, double* const out, int* flag);

int BCDF_curvature_at_curvature_deriv(BCDF_s* a1, int a2, int* a3, double* a4)
{
    int n_deriv;
    int n_crvatr;
    double* deriv = BCDF_return_crvatr_deriv_pars_array(a1, &n_deriv);
    double* pars = BCDF_return_crvatr_pars_array(a1, &n_crvatr);
    int count = 0;
    unsigned int found = 0;
    *a3 = 0;
    if (a2 < n_deriv && n_crvatr > 0)
    {
        if (deriv)
        {
            if (pars)
            {
                double t = deriv[a2];
                __int64 n = n_crvatr;
                if (n > 0)
                {
                    __int64 i = 0;
                    do
                    {
                        if (found)
                            break;



                        if (fabs(pars[i] - t) <= 1.0e-10)
                        {
                            found = 1;
                            continue;
                        }
                        if (t > pars[i])
                        {
                            ++count;
                            ++i;
                        }
                    } while (i < n);
                }
            }
        }
    }
    *a3 = count;
    if (found == 1)
    {
        int flag[4];
        BCDF_copy_single_3d_crvatr(a1, count, a4, flag);
    }
    return found;
}
