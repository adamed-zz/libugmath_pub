










#include <cmath>
#include <intrin.h>

struct BCDF_s;
struct PNTLST_s;

int BCDF_return_num_of_points(struct BCDF_s* a1);
double* BCDF_return_param_array(struct BCDF_s* a1, int* a2);
int BCDF_return_periodicity(struct BCDF_s* a1);
double PNTLST_calc_point_distance(struct PNTLST_s* a1, int a2, int a3);

extern "C" void sub_1800134C0(struct BCDF_s* a1, int a2, double* a3);
extern "C" void sub_1800137C0(struct BCDF_s* a1, int a2, double* a3);
extern "C" void sub_180012B30(struct BCDF_s* a1, int a2, double* a3);
extern "C" void sub_1800131F0(struct BCDF_s* a1, int a2, int a3, double* a4);
extern "C" void sub_180013E50(struct BCDF_s* a1, int a2, int a3, int a4, double* a5, double* a6);

void h813(const int* a1, const double* a2, const double* a3, const double* a4, double* a5);

#ifdef BCDF_CALC_NS_TEST
extern int MACH__checking_level;
void ERROR_raise(const char* a1, int a2, int a3, const char* a4, ...);
#else
__declspec(dllimport) extern int MACH__checking_level;
__declspec(dllimport) void ERROR_raise(const char* a1, int a2, int a3, const char* a4, ...);
#endif

void BCDF_CALC_normalized_slope(struct BCDF_s* a1, int a2, int a3, double* a4)
{
    if ((unsigned int)a2 <= 1)
        return;

    int type_map[6] = { 1, 2, 5, 3, 4, 5 };

    int n = BCDF_return_num_of_points(a1);
    if (MACH__checking_level > 0 && (a3 < 0 || a3 >= n))
    {
        ERROR_raise("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\bcdf_calc.c", 828, 1005315,
                    "The Point Position Is Not Valid For The Array Of Points");
        __debugbreak();
    }

    int param_count;
    double* params = BCDF_return_param_array(a1, &param_count);
    PNTLST_s* pntlst = *(PNTLST_s**)a1;
    int period = BCDF_return_periodicity(a1);

    double dist_sum;
    double dp;
    if (a3 == 0)
    {
        if (period == 0)
        {
            dist_sum = PNTLST_calc_point_distance(pntlst, 0, 1);
            dp = params[1] - params[0];
            goto LABEL_14;
        }
        if (period == 1)
        {
            int last = n - 1;
            int prev = n - 2;
            double d = PNTLST_calc_point_distance(pntlst, prev, last);
            dist_sum = d + PNTLST_calc_point_distance(pntlst, 0, 1);
            dp = (params[last] - params[prev]) + (params[1] - params[0]);
            goto LABEL_14;
        }
    }
    if (a3 == n - 1)
    {
        dist_sum = PNTLST_calc_point_distance(pntlst, n - 2, n - 1);
        dp = params[n - 1] - params[n - 2];
    }
    else
    {
        double d = PNTLST_calc_point_distance(pntlst, a3, a3 + 1);
        dist_sum = d + PNTLST_calc_point_distance(pntlst, a3 - 1, a3);
        dp = params[a3 + 1] - params[a3 - 1];
    }
LABEL_14:

    int type_out = type_map[(int)a2];

    int n1 = BCDF_return_num_of_points(a1) - 1;
    if (MACH__checking_level > 0 && (a3 > n1 || a3 < 0))
    {
        ERROR_raise("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\bcdf_calc.c", 145, 1005315,
                    "An Invalid Point Position Was Given By Calling Routine");
        __debugbreak();
    }

    double scratch[4];
    if (a3 == 0)
    {
        if (BCDF_return_periodicity(a1) == 1)
            sub_1800134C0(a1, 1, scratch);
        else
            sub_1800137C0(a1, 1, scratch);
    }
    else if (a3 == n1)
    {
        sub_180012B30(a1, 1, scratch);
    }
    else
    {
        sub_1800131F0(a1, a3, 1, scratch);
    }

    h813(&type_out, &dp, &dist_sum, scratch, a4);

    if ((unsigned int)(type_out - 4) <= 1)
    {
        int n2 = BCDF_return_num_of_points(a1);
        int period2 = BCDF_return_periodicity(a1);
        if (a3 != 0 || period2 != 0)
        {
            if (a3 == n2 - 1)
            {
                double o32;
                sub_180013E50(a1, a3, 1, -1, a4, &o32);
            }
            else
            {
                double c1[3];
                c1[0] = a4[0];
                c1[1] = a4[1];
                c1[2] = a4[2];
                double o33;
                sub_180013E50(a1, a3, 1, 1, c1, &o33);

                double c2[3];
                c2[0] = a4[0];
                c2[1] = a4[1];
                c2[2] = a4[2];
                double o32;
                sub_180013E50(a1, a3, 1, -1, c2, &o32);

                double sum = o32 + o33;
                double w;
                if (!(1.0e-10 >= fabs(sum)))
                    w = o33 / sum;
                else
                    w = 0.5;

                a4[0] = (1.0 - w) * c2[0] + w * c1[0];
                a4[1] = (1.0 - w) * c2[1] + w * c1[1];
                a4[2] = (1.0 - w) * c2[2] + w * c1[2];
            }
        }
        else
        {
            double o33;
            sub_180013E50(a1, 0, 1, 1, a4, &o33);
        }
    }
}
