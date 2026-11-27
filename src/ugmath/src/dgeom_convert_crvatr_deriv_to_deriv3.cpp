














#include <cmath>

void DGEOM_convert_crvatr_deriv_to_deriv3(double* const a1, double* const a2,
                                          double* const a3, double* const a4)
{
    const double w  = a1[0] * a1[0] + a1[1] * a1[1] + a1[2] * a1[2];
    const double s  = std::sqrt(w);
    const double s2 = s * s;
    const double s3 = s2 * s;
    const double t  = 3.0 * ((a2[0] * w - a2[0] * s2) * a1[0]
                           + (a2[1] * w - a2[1] * s2) * a1[1]
                           + (a2[2] * w - a2[2] * s2) * a1[2]);
    const double z  = 0.0 / s;

    a4[0] = a2[0] * t + a1[0] * z + s3 * a3[0];
    a4[1] = a2[1] * t + a1[1] * z + s3 * a3[1];
    a4[2] = a2[2] * t + a1[2] * z + s3 * a3[2];
}
