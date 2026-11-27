

















#include <cmath>

namespace UGS
{
namespace Math
{


struct TransformMatrix
{
    double m[16];
};


struct Vector3
{
    double x, y, z;
};

}
}


double EQ_ask_length_tolerance();
int VEC3_unitize(const UGS::Math::Vector3 *u, double tolerance,
                 double *length, UGS::Math::Vector3 *unit);
bool VEC3_is_parallel(const UGS::Math::Vector3 *u,
                      const UGS::Math::Vector3 *v, double tolerance);

bool MTX4_is_translation_in_direction(UGS::Math::TransformMatrix *m, double *dir)
{
    UGS::Math::Vector3 translation = {m->m[3], m->m[7], m->m[11]};
    double length;
    VEC3_unitize(&translation, EQ_ask_length_tolerance(), &length, &translation);
    return VEC3_is_parallel(&translation,
                            reinterpret_cast<const UGS::Math::Vector3 *>(dir),
                            std::sin(1e-5 * 0.01745329251994328)) != 0;
}
