#include "ugmath/vector_magnitude.h"



















#include <cmath>

namespace UGS {
namespace Math {


static __forceinline double AbsV(double v)
{
    if (v >= 0.0)
        return v;
    else
        return -v;
}

double __cdecl VectorMagnitude(const double* const p, int n)
{
    double m = AbsV(p[0]);
    for (int i = 1; i < n; ++i)
    {
        const double a = AbsV(p[i]);
        if (!(m > a))
        {
            if (p[i] >= 0.0)
                m = p[i];
            else
                m = -p[i];
        }
    }

    double sum = 0.0;
    if (m < 1e-12)
        return 0.0;

    for (int i = 0; i < n; ++i)
    {
        const double t = p[i] / m;
        sum += t * t;
    }
    return std::sqrt(sum) * m;
}

float __cdecl VectorMagnitude(const float* const v)
{
    double d[3];
    d[0] = v[0];
    d[1] = v[1];
    d[2] = v[2];
    return (float)VectorMagnitude(d, 3);
}

}
}
