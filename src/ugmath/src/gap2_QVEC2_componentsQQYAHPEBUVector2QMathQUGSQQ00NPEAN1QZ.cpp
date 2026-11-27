#include <cmath>

namespace UGS {
namespace Math {
struct Vector2 {
    double x, y;
};
}
}

int VEC2_components(const UGS::Math::Vector2* a1, const UGS::Math::Vector2* a2,
                    const UGS::Math::Vector2* a3, double a4, double* a5, double* a6)
{
    const double v6 = a2->y * a1->x - a2->x * a1->y;
    const double v7 = fabs(v6);
    const int result = !(a4 >= v7);
    if (result) {
        *a5 = (a2->y * a3->x - a2->x * a3->y) / v6;
        *a6 = (a3->y * a1->x - a1->y * a3->x) / v6;
    } else {
        *a5 = INFINITY;
        *a6 = INFINITY;
    }
    return result;
}
