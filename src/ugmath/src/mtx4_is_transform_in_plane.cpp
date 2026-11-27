






















#include <cmath>

namespace UGS {
namespace Math {

struct Vector3 {
    double x;
    double y;
    double z;
};

struct Matrix3 {
    double m[9];
};

struct TransformMatrix {
    double m[16];
};

}
}


double __cdecl EQ_ask_length_tolerance();
int __cdecl VEC3_unitize(const UGS::Math::Vector3* u, double tol, double* len_out,
                         UGS::Math::Vector3* out);
bool __cdecl VEC3_is_perpendicular(const UGS::Math::Vector3* v1,
                                   const UGS::Math::Vector3* v2, double tol);
bool __cdecl MTX3_is_identity(const UGS::Math::Matrix3* matrix, double tol);
bool __cdecl MTX4_is_rotation_about_axis(UGS::Math::TransformMatrix* tm,
                                         double* const axis,
                                         double* const point);

bool __cdecl MTX4_is_transform_in_plane(UGS::Math::TransformMatrix* tm, double* axis) {
    UGS::Math::Matrix3 rot;
    rot.m[0] = tm->m[0];
    rot.m[1] = tm->m[1];
    rot.m[2] = tm->m[2];
    rot.m[3] = tm->m[4];
    rot.m[4] = tm->m[5];
    rot.m[5] = tm->m[6];
    rot.m[6] = tm->m[8];
    rot.m[7] = tm->m[9];
    rot.m[8] = tm->m[10];
    UGS::Math::Vector3 trans;
    trans.x = tm->m[3];
    trans.y = tm->m[7];
    trans.z = tm->m[11];
    double len;
    VEC3_unitize(&trans, EQ_ask_length_tolerance(), &len, &trans);
    double angtol = std::cos(1.57079615226197);
    return VEC3_is_perpendicular(&trans, reinterpret_cast<const UGS::Math::Vector3*>(axis),
                                 angtol) &&
           (MTX3_is_identity(reinterpret_cast<const UGS::Math::Matrix3*>(&rot), 1.0e-10) ||
            MTX4_is_rotation_about_axis(tm, axis, nullptr));
}
