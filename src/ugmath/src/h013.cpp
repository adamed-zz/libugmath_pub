







#include <cmath>

void h013(double* a1, double* a2, double* a3, double* a4)
{
    *a4 = cos(*a3) * *a2 + *a1;
    a4[1] = sin(*a3) * *a2 + a1[1];
    a4[2] = a1[2];
}
