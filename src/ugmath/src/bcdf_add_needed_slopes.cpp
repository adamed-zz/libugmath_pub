

















#include <intrin.h>

struct BCDF_s;

int BCDF_return_num_of_points(struct BCDF_s*);
int BCDF_return_num_of_slopes(struct BCDF_s*);
int BCDF_return_periodicity(struct BCDF_s*);
int BCDF_return_order(struct BCDF_s*);
int BCDF_start_slope_exists(struct BCDF_s*);
int BCDF_end_slope_exists(struct BCDF_s*);
void BCDF_CALC_auto_slope(struct BCDF_s*, int, double*);
void BCDF_CALC_mirror_slope(double*, double*, double*, double*);
void BCDF_replace_slope(struct BCDF_s*, double*, int, int);
void BCDF_copy_single_3d_point(struct BCDF_s*, int, double* const);
void BCDF_copy_single_3d_slope(struct BCDF_s*, int, double* const, int*);
extern "C" void sub_180015F00(struct BCDF_s*, int);



#ifdef BCDF_STANDALONE_TEST
#define BCDF_IMPORT
#else
#define BCDF_IMPORT __declspec(dllimport)
#endif
BCDF_IMPORT extern int MACH__checking_level;
BCDF_IMPORT void ERROR_internal(const char* file, int line, const char* msg, ...);

void BCDF_add_needed_slopes(struct BCDF_s* a1)
{


    double v9[3];
    double v10[3];
    double v11[3];
    double v12[3];
    int v13;

    int v2 = BCDF_return_num_of_points(a1);
    int started = BCDF_start_slope_exists(a1);
    int v4 = BCDF_end_slope_exists(a1);

    if (MACH__checking_level > 0 && !a1)
    {
        ERROR_internal("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\bcdf_gen.c", 3147,
                       "Defining Data Structure Is NULL");
        __debugbreak();
        __assume(0);
    }

    if (*((unsigned long long*)a1 + 1))
    {
        if (!started)
        {
            if (v4 == 1)
            {
                BCDF_CALC_auto_slope(a1, 0, v9);
                BCDF_replace_slope(a1, v9, 0, 0);
            }
        }
        else if (started == 1 && !v4)
        {
            BCDF_CALC_auto_slope(a1, v2 - 1, v9);
            BCDF_replace_slope(a1, v9, v2 - 1, 0);
        }
        return;
    }
    if ((unsigned int)BCDF_return_periodicity(a1) || (unsigned int)BCDF_return_order(a1) != 4)
        return;
    if (v2 == 2)
    {
        if (!started)
        {
            if (!v4)
            {
                BCDF_CALC_auto_slope(a1, 0, v9);
                BCDF_replace_slope(a1, v9, 0, 0);
                sub_180015F00(a1, started + 1);
                return;
            }
            if (v4 == 1)
            {
                int v6 = BCDF_return_num_of_points(a1);
                int v7 = BCDF_return_num_of_slopes(a1);
                BCDF_copy_single_3d_point(a1, 0, v10);
                BCDF_copy_single_3d_point(a1, v6 - 1, v9);
                BCDF_copy_single_3d_slope(a1, v7 - 1, v11, &v13);
                BCDF_CALC_mirror_slope(v11, v10, v9, v12);
                BCDF_replace_slope(a1, v12, 0, v13);
            }
        }
        else if (started == 1 && !v4)
        {
            int v8 = BCDF_return_num_of_points(a1);
            BCDF_copy_single_3d_point(a1, 0, v11);
            BCDF_copy_single_3d_point(a1, v8 - 1, v12);
            BCDF_copy_single_3d_slope(a1, 0, v10, &v13);
            BCDF_CALC_mirror_slope(v10, v11, v12, v9);
            BCDF_replace_slope(a1, v9, v8 - 1, v13);
        }
    }
    else
    {
        if (!started)
        {
            BCDF_CALC_auto_slope(a1, 0, v10);
            BCDF_replace_slope(a1, v10, 0, 0);
        }
        if (!v4)
            sub_180015F00(a1, v2 - 1);
    }
}
