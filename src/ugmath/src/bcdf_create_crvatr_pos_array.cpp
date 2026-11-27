







#include <cmath>
#include <cstddef>

struct BCDF_s;

extern double* BCDF_return_crvatr_pars_array(BCDF_s* a, int* n);
extern double* BCDF_return_param_array(BCDF_s* a, int* n);
__declspec(dllimport) void* SM_alloc(size_t nbytes);

int* BCDF_create_crvatr_pos_array(BCDF_s* a, int* n_crvatr)
{
    int i = 0;
    double* pars = BCDF_return_crvatr_pars_array(a, n_crvatr);
    int n_param;
    double* params = BCDF_return_param_array(a, &n_param);
    int n = *n_crvatr;
    if (n > 0)
    {
        int* pos = (int*)SM_alloc(n * sizeof(int));
        int j = 0;
        if (n_param > 0)
        {
            int* out = pos;
            do
            {
                if (j >= *n_crvatr)
                    break;
                if (fabs(*pars - *params) <= 1.0e-10)
                {
                    ++j;
                    *out = i + 1;
                    ++pars;
                    ++out;
                }
                ++i;
                ++params;
            } while (i < n_param);
        }
        return pos;
    }
    return 0;
}
