








#include <math.h>

struct BCDF_s;

double* BCDF_return_param_array(struct BCDF_s* a, int* count);
double* BCDF_return_slope_pars_array(struct BCDF_s* a, int* count);

int BCDF_slope_at_point(struct BCDF_s* a, int idx, int* out)
{
    int i = 0;
    int found = 0;
    int count;
    double* slope = BCDF_return_slope_pars_array(a, &count);
    if (count <= 0)
        return 0;
    int range_n[4];
    double* p = BCDF_return_param_array(a, range_n);
    double t = p[idx];
    double range = fabs(p[range_n[0] - 1] - p[0]);
    double eps = range * 1.0e-10;
    double lo;
    if (idx > 0)
        lo = p[idx - 1];
    else
        lo = t - range;
    double hi;
    if (idx < range_n[0] - 1)
        hi = p[idx + 1];
    else
        hi = t + range;
    if (count > 0)
    {
        do
        {
            double s = slope[i];
            if (eps >= fabs(s - t))
            {
                double d = fabs(t - s);
                if ((fabs(lo - s) > d && fabs(hi - s) > d) || range_n[0] == 1)
                    found = 1;
            }
            if (!(s < t - eps))
                break;
            if (found)
                break;
            ++i;
        } while (i < count);
    }
    *out = i;
    return found;
}
