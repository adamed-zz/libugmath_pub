






#include <math.h>


double EQ_ask_number_tolerance(void);
int SOLVE_quadratic(double const *const a1, double *const a2);
extern "C" int sub_1800ABB60(double const *const a1, double *const a2);








extern "C" {
double g_ugm_solve_cubic_flag;
}

int SOLVE_cubic(double const *const a1, double *const a2)
{
    double tol = EQ_ask_number_tolerance();
    double abs_a3 = fabs(a1[3]);
    g_ugm_solve_cubic_flag = 0;
    if (abs_a3 <= tol)
        return SOLVE_quadratic(a1, a2);
    if (fabs(a1[0]) <= tol * tol * tol)
    {
        int n = SOLVE_quadratic(a1 + 1, a2);
        a2[n] = 0.0;
        return n + 1;
    }
    return sub_1800ABB60(a1, a2);
}
