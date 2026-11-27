








#include <cmath>

namespace {


const double kZeroRef = 0.0;
const int kModeAbs = 0;

}




__declspec(noinline)
void h053_is_zero(const double* value, const double* ref, const int* mode, int* out)
{
    const double tol = 1e-10;
    (void)mode;

    *out = (tol >= std::fabs(*value - *ref)) ? 1 : 0;
}

void h053(const double* a1, const double* a2, double* a3)
{
    int v9;
    h053_is_zero(a1, &kZeroRef, &kModeAbs, &v9);
    if ( !v9 )
    {
        h053_is_zero(a2, &kZeroRef, &kModeAbs, &v9);
        if ( !v9 )
        {
            const double v6 = atan(*a1 / *a2);
            *a3 = v6;
            double v8 = v6;
            if ( *a2 > 0.0 && *a1 < 0.0 )
            {
                v8 = v6 + 6.283185307179586;
                *a3 = v8;
            }
            if ( *a2 < 0.0 )
            {
                if ( *a1 < 0.0 )
                {
                    v8 = v8 + 3.141592653589793;
                    *a3 = v8;
                }
                if ( *a2 < 0.0 && *a1 > 0.0 )
                    *a3 = v8 + 3.141592653589793;
            }
            return;
        }
        *a3 = 1.5707963267948966;
        if ( *a1 < 0.0 )
            *a3 = 4.71238898038469;
        return;
    }
    *a3 = 0.0;
    if ( *a2 < 0.0 )
        *a3 = 3.141592653589793;
}
