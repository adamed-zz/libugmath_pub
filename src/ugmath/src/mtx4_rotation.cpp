







#include <cmath>

namespace UGS {
namespace Math {
struct Point3 {
    double x, y, z;
};
struct Vector3 {
    double x, y, z;
};
struct TransformMatrix {
    double m[16];
};
}
}


int __cdecl VEC3_unitize(const UGS::Math::Vector3*, double, double*,
                         UGS::Math::Vector3*);


void __cdecl h923(double*, double*, double*);

void __cdecl MTX4_multiply(const UGS::Math::TransformMatrix*,
                           const UGS::Math::TransformMatrix*,
                           UGS::Math::TransformMatrix*);

int __cdecl MTX4_rotation(const UGS::Math::Point3* point,
                          const UGS::Math::Vector3* axis, double angle,
                          UGS::Math::TransformMatrix* mtx) {
    UGS::Math::Vector3 u = {0.0, 0.0, 0.0};
    double ulen;

    double len =
        sqrt(axis->x * axis->x + axis->y * axis->y + axis->z * axis->z);
    if (len <= 1.0e-10)
        return 1;


    UGS::Math::TransformMatrix t = {{1.0, 0.0, 0.0, -point->x,
          0.0, 1.0, 0.0, -point->y,
          0.0, 0.0, 1.0, -point->z,
          0.0, 0.0, 0.0, 1.0}};

    const double px = point->x;
    const double py = point->y;
    const double pz = point->z;

    VEC3_unitize(axis, 1.0e-10, &ulen, &u);

    if (angle < 0.0) {
        u.x = -u.x;
        u.y = -u.y;
        u.z = -u.z;
    }

    double rad = fabs(angle) * 0.01745329251994328;


    UGS::Math::TransformMatrix rot;
    h923(&u.x, &rad, rot.m);


    UGS::Math::TransformMatrix r = {{rot.m[0], rot.m[1], rot.m[2], 0.0,
                                     rot.m[3], rot.m[4], rot.m[5], 0.0,
                                     rot.m[6], rot.m[7], rot.m[8], 0.0,
                                     0.0,      0.0,      0.0,      1.0}};

    MTX4_multiply(&t, &r, &rot);


    t = {{1.0, 0.0, 0.0, px,
          0.0, 1.0, 0.0, py,
          0.0, 0.0, 1.0, pz,
          0.0, 0.0, 0.0, 1.0}};

    MTX4_multiply(&rot, &t, mtx);
    return 0;
}
