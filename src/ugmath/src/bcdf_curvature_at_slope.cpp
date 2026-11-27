









#include <math.h>

struct BCDF_s;

double* BCDF_return_crvatr_pars_array(BCDF_s* a, int* count);
double* BCDF_return_slope_pars_array(BCDF_s* a, int* count);

int BCDF_curvature_at_slope(BCDF_s* a, int idx, int* out)
{
    int found = 0;
    int i = 0;
    int ncrv;
    double* crv = BCDF_return_crvatr_pars_array(a, &ncrv);
    if (ncrv <= 0)
        return 0;
    int tmp;
    double* slope = BCDF_return_slope_pars_array(a, &tmp);
    double s = slope[idx];
    if (ncrv > 0)
    {
        while (1)
        {
            if (1.0e-10 >= fabs(*crv - s))
            {
                found = 1;
                break;
            }
            if (s > *crv)
            {
                ++i;
                ++crv;
                if (i < ncrv)
                    continue;
            }
            goto done;
        }
    }
done:
    *out = i;
    return found;
}
