























#include <cmath>

namespace UGS {
namespace Math {

struct Vector3 { double x, y, z; };

}
}

int VEC3_unitize(UGS::Math::Vector3* v, double* len);
double EQ_ask_length_tolerance();

bool DGEOM_convert_1st_derivs_uv_to_xy(const double* const a1, const double* const a2, double* const a3)
{
    double n[3];
    n[0] = a1[1] * a2[2] - a1[2] * a2[1];
    n[1] = a2[0] * a1[2] - a1[0] * a2[2];
    n[2] = a1[0] * a2[1] - a2[0] * a1[1];
    double len;
    VEC3_unitize((UGS::Math::Vector3*)n, &len);
    const double abslen = fabs(len);
    if (EQ_ask_length_tolerance() >= abslen)
        return false;
    const double absz = fabs(n[2]);
    if (EQ_ask_length_tolerance() >= absz)
        return false;
    a3[0] = -n[0] / n[2];
    a3[1] = -n[1] / n[2];
    return true;
}
