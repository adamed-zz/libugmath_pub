





#include "b37_math.h"

#include <cmath>

bool PLN3_is_equal(const PLN3_s* a1, const PLN3_s* a2, double a3, double a4) {
    double dnx = a1->normal.x - a2->normal.x;
    double dny = a1->normal.y - a2->normal.y;
    double dnz = a1->normal.z - a2->normal.z;
    double dn_sq = dnx * dnx + dny * dny;
    dn_sq += dnz * dnz;
    double dn = sqrt(dn_sq);


    if (!(a4 >= dn))
        return false;

    double dx = a2->origin.x - a1->origin.x;
    double dy = a2->origin.y - a1->origin.y;
    double dz = a2->origin.z - a1->origin.z;

    double dot = dy * a1->normal.y + dx * a1->normal.x;
    dot += dz * a1->normal.z;

    double len_sq = a1->normal.y * a1->normal.y + a1->normal.x * a1->normal.x;
    len_sq += a1->normal.z * a1->normal.z;
    double len = sqrt(len_sq);

    return a3 >= std::fabs(dot / len);
}
