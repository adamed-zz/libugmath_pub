










#include <math.h>
#include <xmmintrin.h>
#include <emmintrin.h>

struct BCDF_s;

void BCDF_copy_single_3d_point(BCDF_s *a1, int a2, double *const a3);
void BCDF_copy_single_3d_slope(BCDF_s *a1, int a2, double *const a3, int *a4);
int  BCDF_return_num_of_points(BCDF_s *a1);
int  BCDF_return_periodicity(BCDF_s *a1);
double *BCDF_return_param_array(BCDF_s *a1, int *a2);
int  BCDF_slope_at_point(BCDF_s *a1, int a2, int *a3);
int  BCDF_return_order(BCDF_s *a1);
int  BCDF_return_num_of_crvatrs(BCDF_s *a1);

extern "C" double __fastcall sub_1800151C0(double *a1, double *a2);

extern "C" void __fastcall sub_180013E50(BCDF_s *a1, int a2, int a3, int a4,
                                         double *a5, double *a6)
{
    double p0[3] = {0.0, 0.0, 0.0};
    double p1[3] = {0.0, 0.0, 0.0};
    double slope[3] = {0.0, 0.0, 0.0};
    double d[3];
    int v41[2] = {0, 0};
    int v7 = 0;
    double dp = 0.0;

    double v14 = sqrt(a5[0] * a5[0] + a5[1] * a5[1] + a5[2] * a5[2]);
    if (1.0e-10 > v14)
        return;

    int v15 = BCDF_return_num_of_points(a1);
    int v16 = BCDF_return_periodicity(a1);
    double *v17 = BCDF_return_param_array(a1, v41);

    if (a4 == 1)
    {
        v7 = a2 + 1;
        dp = v17[a2 + 1] - v17[a2];
        BCDF_copy_single_3d_point(a1, a2, p0);
        BCDF_copy_single_3d_point(a1, a2 + 1, p1);
    }
    else if (a4 == -1)
    {
        if (a2 != 0 || v16 != 1)
        {
            v7 = a2 - 1;
            dp = v17[a2] - v17[a2 - 1];
        }
        else
        {
            v7 = v15 - 2;
            dp = v17[v15 - 1] - v17[v15 - 2];
        }
        BCDF_copy_single_3d_point(a1, v7, p0);
        BCDF_copy_single_3d_point(a1, a2, p1);
    }


    d[0] = p1[0] - p0[0];
    d[1] = p1[1] - p0[1];
    d[2] = p1[2] - p0[2];
    double v21 = sqrt(d[1] * d[1] + d[0] * d[0] + d[2] * d[2]);

    double v24 = sub_1800151C0(d, a5);

    double t = 1.0 - v24 * v24;
    t = (0.0 > t) ? 0.0 : t;
    *a6 = sqrt(t) * v21;

    int slope_idx = 0;
    int slope_st = 0;
    if (a3 && BCDF_slope_at_point(a1, v7, &slope_idx))
    {
        BCDF_copy_single_3d_slope(a1, slope_idx, slope, &slope_st);
        v24 = sub_1800151C0(d, slope);
    }


    if (!(0.0 > v24))
    {
        double factor = 2.0 / (v24 + 1.0);
        int order = BCDF_return_order(a1);
        if (BCDF_return_num_of_crvatrs(a1) > 0 || (unsigned int)(order - 5) <= 1)
        {
            double ac = fabs(v24 - 0.0);
            if (ac > 1.0e-10)
            {
                double ac1 = fabs(v24 - 1.0);
                if (ac1 > 1.0e-10)
                {
                    double s = sqrt(1.0 - v24 * v24);
                    double u = (25.0 - v24 * 7.0) * (1.0 - v24);
                    factor = (s * 5.0 - sqrt(u)) / ((s + s) * v24);
                }
                else
                {
                    factor = 1.0;
                }
            }
            else
            {
                factor = 1.6;
            }
        }
        factor = factor * v21 / dp / v14;
        a5[0] = a5[0] * factor;
        a5[1] = a5[1] * factor;
        a5[2] = a5[2] * factor;
    }
}
