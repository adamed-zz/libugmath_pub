












#include <math.h>
#include <intrin.h>


struct BCDF_s;



__declspec(dllimport) extern int MACH__checking_level;
__declspec(dllimport) void ERROR_internal(const char* file, int line, const char* msg, ...);


int BCDF_return_order(struct BCDF_s* a);
int BCDF_return_periodicity(struct BCDF_s* a);
int BCDF_return_num_of_points(struct BCDF_s* a);
int BCDF_return_num_of_constraints(struct BCDF_s* a);
double* BCDF_return_param_array(struct BCDF_s* a, int* count);
int BCDF_return_num_of_slopes(struct BCDF_s* a);
int BCDF_return_num_of_crvatrs(struct BCDF_s* a);
int BCDF_slope_at_curvature(struct BCDF_s* a, int index, int* flag, double* slope);
void BCDF_copy_single_3d_crvatr(struct BCDF_s* a, int index, double* const out, int* flag);
double BCDF_return_ls_tolerance(struct BCDF_s* a);
int BCDF_return_ls_num_of_segments(struct BCDF_s* a);

int BCDF_check_defining_data(struct BCDF_s* a1)
{
    int order = BCDF_return_order(a1);
    int periodicity = BCDF_return_periodicity(a1);
    int num_points = BCDF_return_num_of_points(a1);

    if ((periodicity == 0 && num_points <= 1) ||
        (periodicity == 1 && num_points <= 2))
        return 1005322;

    int num_constraints = BCDF_return_num_of_constraints(a1);
    if (num_constraints < order)
        return 1005311;
    if (num_constraints >= 2147483600)
        return 1005317;

    int npars;
    double* pars = BCDF_return_param_array(a1, &npars);
    for (int i = 1; i < npars; i++)
    {
        if (pars[i - 1] >= pars[i])
            return 1005323;
    }

    if (BCDF_return_num_of_slopes(a1) > 0 && order <= 2)
        return 1005321;

    int num_crvatrs = BCDF_return_num_of_crvatrs(a1);
    int np = 0;
    if (num_crvatrs > 0)
    {
        if (order <= 3)
            return 1005321;
        for (int i = 0; i < num_crvatrs; i++)
        {
            int tmp;
            double slope[3];
            double crv[3];
            int flag;
            if (!BCDF_slope_at_curvature(a1, i, &tmp, slope))
                return 1005318;
            BCDF_copy_single_3d_crvatr(a1, i, crv, &flag);
            if (fabs(slope[0] * crv[0] + slope[1] * crv[1] + slope[2] * crv[2]) > 0.0000001)
                return 1005320;
        }
    }

    if (MACH__checking_level > 0 && !a1)
    {
        ERROR_internal("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\bcdf_gen.c", 3147,
                       "Defining Data Structure Is NULL");
        __debugbreak();
        __assume(0);
    }

    if (*((void**)a1 + 1))
    {
        double tol = BCDF_return_ls_tolerance(a1);
        int num_segments = BCDF_return_ls_num_of_segments(a1);
        if (*((void**)a1 + 1))
        {
            np = BCDF_return_num_of_points(a1);
            BCDF_return_num_of_slopes(a1);
            if ((unsigned int)BCDF_return_periodicity(a1) == 1)
                --np;
        }
        int n = np - order + 1;
        if (n <= 0)
            return 1005322;
        if (num_segments)
        {
            if (num_segments <= 0 || num_segments > n)
                return 1005005;
        }
        else if (tol < 0.0)
        {
            return 1005006;
        }
    }
    return 0;
}
