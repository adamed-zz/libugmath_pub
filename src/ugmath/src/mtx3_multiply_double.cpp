









#include "ugmath/b36_math.h"

void MTX3_multiply(const double* a, const double* b, double* out)
{
    MTX3_multiply(reinterpret_cast<const UGS::Math::Matrix3*>(a),
                  reinterpret_cast<const UGS::Math::Matrix3*>(b),
                  reinterpret_cast<UGS::Math::Matrix3*>(out));
}
