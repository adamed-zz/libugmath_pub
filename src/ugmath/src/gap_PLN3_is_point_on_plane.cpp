




#include "b37_math.h"

#include <cmath>

bool PLN3_is_point_on_plane(const PLN3_s* a1, const UGS::Math::Point3* a2, double a3) {
    double dx = a2->x - a1->origin.x;
    double dy = a2->y - a1->origin.y;
    double dz = a2->z - a1->origin.z;

    double d = dy * a1->normal.y + dx * a1->normal.x;
    d += dz * a1->normal.z;

    double len_sq = a1->normal.x * a1->normal.x + a1->normal.y * a1->normal.y;
    len_sq += a1->normal.z * a1->normal.z;
    double len = sqrt(len_sq);

    return a3 >= std::fabs(d / len);
}
