






namespace UGS { namespace Math {
struct Vector2 { double x; double y; };
} }

void h053(const double* a1, const double* a2, double* a3);

double ARC_SPLINE_ask_central_angle_between_tangents_2d(
    UGS::Math::Vector2* a1, UGS::Math::Vector2* a2, int* a3)
{
    double v8 = a2->x * a1->x + a2->y * a1->y;
    double v9 = a1->x * a2->y - a2->x * a1->y;
    double v10;
    h053(&v9, &v8, &v10);
    const double deg = v10 * 57.29577951308235;
    double result = (deg > 180.0) ? 360.0 - deg : deg;
    if (deg > 180.0)
        *a3 = -1;
    else
        *a3 = 1;
    return result;
}
