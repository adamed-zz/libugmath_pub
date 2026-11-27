








#include <math.h>

struct BCDF_s;


int BCDF_return_order(BCDF_s *a1);
int BCDF_return_num_of_crvatrs(BCDF_s *a1);
double *BCDF_return_slope_pars_array(BCDF_s *a1, int *n);
double *BCDF_return_param_array(BCDF_s *a1, int *m);

int BCDF_is_ug_spline(BCDF_s *a1)
{
    int result = 0;
    int n;
    int m;

    if (BCDF_return_order(a1) != 4 || BCDF_return_num_of_crvatrs(a1))
        return 0;

    double *sl = BCDF_return_slope_pars_array(a1, &n);
    double *pr = BCDF_return_param_array(a1, &m);

    if (n >= 2 && fabs(sl[0] - pr[0]) <= 1e-10)
    {
        if (fabs(sl[n - 1] - pr[m - 1]) <= 1e-10)
            result = 1;
    }

    return result;
}
