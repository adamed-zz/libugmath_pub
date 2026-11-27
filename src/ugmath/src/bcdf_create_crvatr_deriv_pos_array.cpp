








#include <cmath>
#include <cstddef>

struct BCDF_s;

extern double* BCDF_return_crvatr_deriv_pars_array(BCDF_s* a, int* n);
extern double* BCDF_return_param_array(BCDF_s* a, int* n);
__declspec(dllimport) void* SM_alloc(size_t nbytes);

int* BCDF_create_crvatr_deriv_pos_array(BCDF_s* a, int* n_deriv)
{
    int i = 0;
    double* derivs = BCDF_return_crvatr_deriv_pars_array(a, n_deriv);
    int n_param;
    double* params = BCDF_return_param_array(a, &n_param);
    int n = *n_deriv;
    int* pos = 0;
    if (n > 0)
    {
        int j = 0;
        pos = (int*)SM_alloc(n * sizeof(int));
        if (n_param > 0)
        {
            int* out = pos;
            do
            {
                if (j >= *n_deriv)
                    break;
                if (fabs(*derivs - *params) <= 1.0e-10)
                {
                    ++j;
                    *out = i + 1;
                    ++derivs;
                    ++out;
                }
                ++i;
                ++params;
            } while (i < n_param);
        }
    }
    return pos;
}
