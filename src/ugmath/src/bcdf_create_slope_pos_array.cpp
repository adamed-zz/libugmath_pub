








#include <math.h>

struct BCDF_s;

double* BCDF_return_slope_pars_array(struct BCDF_s* a, int* count);
double* BCDF_return_param_array(struct BCDF_s* a, int* count);
__declspec(dllimport) void* __cdecl SM_alloc(unsigned __int64 size);

int* BCDF_create_slope_pos_array(struct BCDF_s* a, int* out_count)
{
    int i = 0;
    double* slopes = BCDF_return_slope_pars_array(a, out_count);
    int npar;
    double* par = BCDF_return_param_array(a, &npar);
    int nslope = *out_count;
    int* pos = 0;
    if (nslope > 0)
    {
        pos = (int*)SM_alloc(4LL * nslope);
        int j = 0;
        if (npar > 0)
        {
            int* out = pos;
            do
            {
                if (j >= *out_count)
                    break;
                if (fabs(*slopes - *par) <= 1.0e-10)
                {
                    ++j;
                    *out = i + 1;
                    ++slopes;
                    ++out;
                }
                ++i;
                ++par;
            } while (i < npar);
        }
    }
    return pos;
}
