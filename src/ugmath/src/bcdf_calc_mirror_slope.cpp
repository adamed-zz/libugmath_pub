





















#include <cmath>

double EQ_ask_length_tolerance();

void BCDF_CALC_mirror_slope(double* a1, double* a2, double* a3, double* a4)
{
    const double dx = a3[0] - a2[0];
    const double dy = a3[1] - a2[1];
    const double dz = a3[2] - a2[2];
    const double len2 = dx * dx + dy * dy + dz * dz;
    const double len = std::sqrt(len2);
    if (std::fabs(len) <= EQ_ask_length_tolerance())
    {
        a4[0] = a1[0];
        a4[1] = a1[1];
        a4[2] = a1[2];
    }
    else
    {
        const double ux = dx / len;
        const double uy = dy / len;
        const double uz = dz / len;


        const double y = a1[1];
        const double x = a1[0];
        const double z = a1[2];
        const double d = x * ux + y * uy + z * uz;
        a4[0] = d * ux - (x - d * ux);
        a4[1] = d * uy - (y - d * uy);
        a4[2] = d * uz - (z - d * uz);
    }
}
