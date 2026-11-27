








#include <math.h>

struct BCDF_s;

double* BCDF_return_param_array(struct BCDF_s* a, int* count);
double* BCDF_return_slope_pars_array(struct BCDF_s* a, int* count);

int BCDF_end_slope_exists(struct BCDF_s* a)
{
    int n_slope;
    double* slopes = BCDF_return_slope_pars_array(a, &n_slope);
    if (!n_slope)
        return n_slope;
    double last_slope = slopes[n_slope - 1];
    int n_param;
    double* params = BCDF_return_param_array(a, &n_param);
    return fabs(last_slope - params[n_param - 1]) <= 1.0e-10;
}
