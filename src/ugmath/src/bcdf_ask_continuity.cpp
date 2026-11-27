





























#include <math.h>

struct BCDF_s
{
    unsigned char unknown_00[0x6C];
    int order;
};

int BCDF_is_ug_spline(BCDF_s* a1);
int BCDF_return_periodicity(BCDF_s* a1);
int BCDF_start_slope_exists(BCDF_s* a1);
double* BCDF_return_slope_pars_array(BCDF_s* a1, int* count);
double* BCDF_return_param_array(BCDF_s* a1, int* count);

int BCDF_ask_continuity(BCDF_s* a1)
{
    int v2 = a1->order - 2;
    if (BCDF_is_ug_spline(a1))
    {
        if (BCDF_return_periodicity(a1))
        {
            if (BCDF_start_slope_exists(a1))
                return 1;
        }
        else
        {
            int v12;
            double* v4 = BCDF_return_slope_pars_array(a1, &v12);
            if (v12)
            {
                double v6 = v4[v12 - 1];
                int v13;
                double* v7 = BCDF_return_param_array(a1, &v13);
                double v8 = *v4 - *v7;
                double v9 = v6 - v7[v13 - 1];
                int b1 = fabs(v9) <= 1.0e-10;
                int b0 = fabs(v8) <= 1.0e-10;
                int v10 = v12;
                if (b0)
                    --v10;
                if (b1)
                    --v10;
                if (v10 > 0)
                    v2 = 1;
            }
        }
    }
    return v2;
}
