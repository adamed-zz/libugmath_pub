







#include <math.h>

void h614a(const double* a1, const double* a2, double* a3)
{
    double v6 = sin(*a1) * *a2;
    *a3 = v6 / cos(*a1);
    double v7 = sin(a1[1]) * *a2;
    a3[1] = v7 / cos(a1[1]);
}
