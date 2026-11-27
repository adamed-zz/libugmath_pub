#include "types.h"

using UGS::Math::Vector3;



void VEC3_make_trihedral(const Vector3* u, const Vector3* v, Vector3* proj,
                         Vector3* perp, Vector3* scaled)
{
    double vy = v->y;
    double vx = v->x;
    double vz = v->z;
    double dot = vy * u->y + vx * u->x + vz * u->z;

    double sx = vx * dot;
    double sy = vy * dot;
    double sz = vz * dot;
    scaled->x = sx;
    scaled->y = sy;
    scaled->z = sz;

    proj->x = u->x - scaled->x;
    proj->y = u->y - scaled->y;
    proj->z = u->z - scaled->z;

    Vector3 t;
    t.x = v->y * proj->z - proj->y * v->z;
    t.y = proj->x * v->z - v->x * proj->z;
    t.z = v->x * proj->y - proj->x * v->y;
    *perp = t;
}
