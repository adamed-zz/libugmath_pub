







#include "b37_math.h"

#include <cmath>

bool PLN3_is_segment_intersecting(const PLN3_s* a1, const UGS::Math::Point3* a2,
                                  const UGS::Math::Point3* a3, double a4) {
    double nx = a1->normal.x;
    double ny = a1->normal.y;
    double nz = a1->normal.z;

    double len_sq = ny * ny + nx * nx;
    len_sq += nz * nz;
    double len = sqrt(len_sq);

    double u_dot = (a2->y - a1->origin.y) * ny + (a2->x - a1->origin.x) * nx;
    u_dot += (a2->z - a1->origin.z) * nz;
    double u = u_dot / len;

    double v_dot = (a3->y - a1->origin.y) * ny + (a3->x - a1->origin.x) * nx;
    v_dot += (a3->z - a1->origin.z) * nz;
    double v = v_dot / len;

    double w = u * v;
    return a4 >= std::fabs(w) || !(w > 0.0);
}
