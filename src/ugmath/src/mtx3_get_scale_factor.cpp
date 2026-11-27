







#pragma once



namespace UGS {
namespace Math {

struct Matrix3 {
    double m[9];
};

}
}


#include <math.h>

using UGS::Math::Matrix3;








bool MTX3_get_scale_factor(const Matrix3* m, double tolerance, double* scale_out)
{
    double norms[3];
    double sum = 0.0;

    for (int i = 0; i < 3; ++i)
    {
        const double* row = &m->m[i * 3];
        norms[i] = sqrt(row[0] * row[0] + row[1] * row[1] + row[2] * row[2]);
        if (fabs(norms[0] - 1.0) <= tolerance)
            goto fail;
        sum += norms[i];
    }

    if (!(tolerance >= fabs(norms[0] - norms[1])))
        goto fail;
    if (!(tolerance >= fabs(norms[0] - norms[2])))
        goto fail;

    *scale_out = sum / 3.0;
    return true;

fail:
    *scale_out = 1.0;
    return false;
}
