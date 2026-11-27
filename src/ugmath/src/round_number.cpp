#include "ugmath/round_number.h"

#include <cmath>















namespace UGS {
namespace Math {

double __cdecl RoundDownNumber(double value, int digits)
{
    double scale = pow(10.0, (double)digits);
    value *= scale;
    if (value < 0.0)
        value = ceil(value);
    else
        value = floor(value);
    if (1.0e-10 >= fabs(value - 0.0))
        return value;
    return value / scale;
}

}
}
