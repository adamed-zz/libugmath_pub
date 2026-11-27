












#include <cmath>

#include "kits/b24_kit/b24_types.h"

using namespace UGS::Math;

extern "C" __declspec(noinline) bool b24_are_complement_points(int axis,
                                                               const Point3* a,
                                                               const Point3* b,
                                                               double tol) {
    bool ok;
    if (axis == 0) {
        ok = tol >= std::fabs(a->y - b->y);
        ok = ok && (tol >= std::fabs(a->z - b->z));
    } else if (axis == 1) {
        ok = tol >= std::fabs(a->x - b->x);
        ok = ok && (tol >= std::fabs(a->z - b->z));
    } else if (axis == 2) {
        ok = tol >= std::fabs(a->x - b->x);
        ok = ok && (tol >= std::fabs(a->y - b->y));
    } else {
        ok = false;
    }
    return ok;
}
