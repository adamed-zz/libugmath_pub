








#include <math.h>

struct BCDF_s;

double* BCDF_return_param_array(struct BCDF_s* a, int* count);
double* BCDF_return_slope_pars_array(struct BCDF_s* a, int* count);

int BCDF_start_slope_exists(struct BCDF_s* a1)
{
    int n_slope;
    int n_param;
    double* slope_pars = BCDF_return_slope_pars_array(a1, &n_slope);
    if (n_slope == 0)
        return 0;
    return fabs(*slope_pars - *BCDF_return_param_array(a1, &n_param)) <= 1.0e-10;
}
