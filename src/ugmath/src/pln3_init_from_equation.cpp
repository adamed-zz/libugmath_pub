



















#include <cmath>

namespace UGS
{
namespace Math
{
struct Vector3
{
    double x, y, z;
};
}
}


struct PLN3_s
{
    double origin[3];
    double normal[3];
};


double EQ_ask_length_tolerance();



int VEC3_unitize(UGS::Math::Vector3* u, double* len_out);


bool PLN3_init_from_equation(PLN3_s& a1, double const* const a2)
{
    UGS::Math::Vector3* n = reinterpret_cast<UGS::Math::Vector3*>(a1.normal);
    n->x = a2[0];
    n->y = a2[1];
    n->z = a2[2];

    double len;
    VEC3_unitize(n, &len);

    double const alen = std::fabs(len);
    if (!(EQ_ask_length_tolerance() >= alen))
    {
        a1.origin[0] = a2[3] * a2[0] / (len * len);
        a1.origin[1] = a2[3] * a2[1] / (len * len);
        double const d = a2[3];
        a1.origin[2] = d * a2[2] / (len * len);
        return true;
    }
    return false;
}
