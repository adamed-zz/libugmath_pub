
















#include <cmath>

namespace UGS {
namespace Math {

double __cdecl RoundUpNumber(double value, int digits)
{
    double v4 = value;
    double v5 = pow(10.0, (double)digits);
    double v6 = v4 * v5;
    double v7 = v5;
    double v8;
    if (v6 < 0.0)
        v8 = floor(v6);
    else
        v8 = ceil(v6);
    double v9 = v8;
    if (1.0e-10 >= fabs(v8 - 0.0))
        return v9;
    return v8 / v7;
}

}
}
