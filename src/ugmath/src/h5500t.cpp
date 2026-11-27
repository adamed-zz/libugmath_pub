








#include <math.h>

int h5500t(const double* a, const double* b, const double* tol)
{
    for (int i = 0; i < 6; i++)
    {
        if (fabs(a[i] - b[i]) > *tol)
            return 0;
    }
    return 1;
}
