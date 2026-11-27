





#include <cmath>

namespace UGS {
namespace Math {

struct Vector3 {
    double x, y, z;
};

struct TransformMatrix {
    double m[16];
};

}
}


extern double EQ_ask_length_tolerance();
extern int VEC3_unitize(const UGS::Math::Vector3* u, double tol, double* len_out,
                        UGS::Math::Vector3* out);
extern bool MTX4_is_point_on_rotation_axis(UGS::Math::TransformMatrix* m, double* const p);

bool MTX4_is_rotation_about_axis(UGS::Math::TransformMatrix* m, double* const axis,
                                 double* const point)
{
    double tol = EQ_ask_length_tolerance();

    double len;
    UGS::Math::Vector3 unit;
    VEC3_unitize(reinterpret_cast<const UGS::Math::Vector3*>(axis), tol, &len, &unit);

    double v7 = unit.x * m->m[0] + unit.y * m->m[1] + unit.z * m->m[2];
    double v8 = unit.x * m->m[4] + unit.y * m->m[5] + unit.z * m->m[6];
    double v9 = unit.x * m->m[8] + unit.y * m->m[9] + unit.z * m->m[10];

    double e0 = (unit.x - v7) * (unit.x - v7);
    double e1 = (unit.y - v8) * (unit.y - v8);
    double e2 = (unit.z - v9) * (unit.z - v9);
    double err = sqrt(e0 + e1 + e2);

    return tol >= err && (!point || MTX4_is_point_on_rotation_axis(m, point));
}
