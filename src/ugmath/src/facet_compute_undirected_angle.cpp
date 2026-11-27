







#include <cmath>

namespace UGS { namespace Math {
struct Vector3 { double x, y, z; };
} }

double FACET_compute_undirected_angle(UGS::Math::Vector3* a1, UGS::Math::Vector3* a2)
{
    const double d = a1->x * a2->x + a1->y * a2->y + a1->z * a2->z;
    const double c1 = a1->y * a2->z - a1->z * a2->y;
    const double c2 = a1->z * a2->x - a1->x * a2->z;
    const double c3 = a1->x * a2->y - a1->y * a2->x;
    const double s = c1 * c1 + c2 * c2 + c3 * c3;
    return atan2(sqrt(s), d);
}
