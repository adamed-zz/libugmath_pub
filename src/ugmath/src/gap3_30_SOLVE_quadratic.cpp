
#include <math.h>
double EQ_ask_number_tolerance();
int sub_1800AC240(const double *a1, double *a2);
int SOLVE_quadratic(const double * const a1, double * const a2)
{
    double tol = EQ_ask_number_tolerance();
    if (tol >= fabs(a1[2]))
    {
        if (!(tol >= fabs(a1[1])))
        {
            *a2 = -*a1 / a1[1];
            return 1;
        }
        return 0;
    }
    return sub_1800AC240(a1, a2);
}
