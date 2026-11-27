









#include <math.h>


double EQ_ask_number_tolerance(void);
int SOLVE_cubic(double const *const a1, double *const a2);
extern "C" int sub_1800AC240(double const *const coeffs, double *y);
extern "C" int sub_1800AC470(double const *const a1, double *const a2);




extern "C" {
double g_ugm_solve_quartic_flag;
}

int SOLVE_quartic(double const *const a, double *const roots)
{
    unsigned int n = 0;
    double tol = EQ_ask_number_tolerance();
    double a4 = a[4];
    double abs_a4 = fabs(a4);
    g_ugm_solve_quartic_flag = 0;
    if (abs_a4 <= tol)
        return SOLVE_cubic(a, roots);
    double a0 = a[0];
    if (fabs(a0) <= tol * tol * tol * tol)
    {
        int k = SOLVE_cubic(a + 1, roots);
        roots[k] = 0.0;
        return k + 1;
    }
    if (!(tol >= fabs(a[1])) || !(tol >= fabs(a[3])))
        return sub_1800AC470(a, roots);

    double a2 = a[2];
    int m = 0;
    double y[2];
    double c[3];
    c[0] = a0;
    c[1] = a2;
    c[2] = a4;
    double tol2 = EQ_ask_number_tolerance();
    if (tol2 >= abs_a4)
    {
        if (!(tol2 >= fabs(a2)))
        {
            m = 1;
            y[0] = -a0 / a2;
        }
    }
    else
    {
        m = sub_1800AC240(c, y);
    }

    int j = 0;
    for (int i = 0; i < m; ++i)
    {
        double v = y[i];
        if (v > 0.0)
        {
            double s = sqrt(v);
            roots[j] = s;
            n += 2;
            roots[j + 1] = -s;
            j += 2;
        }
    }
    return n;
}
