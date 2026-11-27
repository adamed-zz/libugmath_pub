









#include <intrin.h>

struct BCDF_s;

int BCDF_return_num_of_points(struct BCDF_s* a1);
int BCDF_return_periodicity(struct BCDF_s* a1);
int BCDF_slope_at_point(struct BCDF_s* a1, int a2, int* a3);
void BCDF_copy_single_3d_slope(struct BCDF_s* a1, int a2, double* const a3, int* a4);
double DGEOM_crv_curvature(double* a1, double* a2, double* a3);

extern "C" void sub_1800134C0(struct BCDF_s* a1, int a2, double* a3);
extern "C" void sub_1800137C0(struct BCDF_s* a1, int a2, double* a3);
extern "C" void sub_180012B30(struct BCDF_s* a1, int a2, double* a3);
extern "C" void sub_1800131F0(struct BCDF_s* a1, int a2, int a3, double* a4);

#ifdef BCDF_CALC_AC_TEST
extern int MACH__checking_level;
void ERROR_raise(const char* a1, int a2, int a3, const char* a4, ...);
#else
__declspec(dllimport) extern int MACH__checking_level;
__declspec(dllimport) void ERROR_raise(const char* a1, int a2, int a3, const char* a4, ...);
#endif

void BCDF_CALC_auto_curvature(struct BCDF_s* a1, int a2, double* a3)
{
    int n1 = BCDF_return_num_of_points(a1) - 1;
    if (MACH__checking_level > 0 && (a2 > n1 || a2 < 0))
    {
        ERROR_raise("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\bcdf_calc.c", 145, 1005315,
                    "An Invalid Point Position Was Given By Calling Routine");
        __debugbreak();
    }

    int flag;
    double deriv[6];
    int slope_idx;
    if (a2 == 0)
    {
        if (BCDF_return_periodicity(a1) == 1)
            sub_1800134C0(a1, 2, deriv);
        else
            sub_1800137C0(a1, 2, deriv);
    }
    else if (a2 == n1)
    {
        sub_180012B30(a1, 2, deriv);
    }
    else
    {
        sub_1800131F0(a1, a2, 2, deriv);
    }

    if (BCDF_slope_at_point(a1, a2, &slope_idx))
        BCDF_copy_single_3d_slope(a1, slope_idx, deriv, &flag);

    DGEOM_crv_curvature(deriv, deriv + 3, a3);
}
