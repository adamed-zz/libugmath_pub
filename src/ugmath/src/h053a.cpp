


















#include <math.h>

int eqz(const double* v, const double* ref, const int* mode);

namespace
{

const double kZero = 0.0;
const int kMode = 0;
}

void h053a(const double* a, const double* b, double* out)
{
    if (!eqz(a, &kZero, &kMode))
    {
        if (!eqz(b, &kZero, &kMode))
        {
            *out = atan(*a / *b);
        }
        else
        {
            *out = 1.5707963267948966;
            if (*a < 0.0)
                *out = -1.5707963267948966;
        }
    }
    else
    {
        *out = 0.0;
    }
}
