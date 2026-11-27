





#include "b37_math.h"

#include <cmath>

bool PLN3_is_coincident(const PLN3_s* a1, const PLN3_s* a2, double a3, double a4) {
    if (!VEC3_is_parallel(&a1->normal, &a2->normal, a4))
        return false;

    double dx = a2->origin.x - a1->origin.x;
    double dy = a2->origin.y - a1->origin.y;
    double dz = a2->origin.z - a1->origin.z;

    double d = dy * a1->normal.y + dx * a1->normal.x;
    d += dz * a1->normal.z;

    double len_sq = a1->normal.x * a1->normal.x + a1->normal.y * a1->normal.y;
    len_sq += a1->normal.z * a1->normal.z;
    double len = sqrt(len_sq);

    return a3 >= std::fabs(d / len);
}
