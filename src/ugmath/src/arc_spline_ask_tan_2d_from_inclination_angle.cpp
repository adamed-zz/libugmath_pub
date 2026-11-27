





#include <cmath>

namespace UGS
{
namespace Math
{
struct Vector2
{
    double x;
    double y;
};
}
}

UGS::Math::Vector2 ARC_SPLINE_ask_tan_2d_from_inclination_angle(double deg)
{
    const double rad = deg * 0.01745329251994328;
    UGS::Math::Vector2 v;
    v.x = std::cos(rad);
    v.y = std::sin(rad);
    return v;
}
