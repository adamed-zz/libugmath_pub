










#include <math.h>

extern "C" __declspec(noinline) double sub_18008CB30(long long p)
{
    const double* m = *reinterpret_cast<const double* const*>(p + 8);
    double v5 = fabs(m[3]);
    double v6 = fabs(m[0]);
    double* a = &v5;
    double* b = &v6;
    double* v3 = !(v5 > v6) ? b : a;
    return *v3;
}
