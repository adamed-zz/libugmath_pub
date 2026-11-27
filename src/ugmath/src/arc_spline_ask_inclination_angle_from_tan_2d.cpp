











namespace UGS
{
namespace Math
{
struct Vector2;
}
}

extern void h053(const double*, const double*, double*);

double ARC_SPLINE_ask_inclination_angle_from_tan_2d(const struct UGS::Math::Vector2* v)
{
    const double* a1 = reinterpret_cast<const double*>(v);
    double v1 = a1[1];
    double v3 = a1[0];
    double v4 = v1;
    double v5;
    h053(&v4, &v3, &v5);
    return v5 * 57.29577951308235;
}
