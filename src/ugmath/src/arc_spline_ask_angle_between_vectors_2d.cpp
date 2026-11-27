








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

int VEC2_unitize(const UGS::Math::Vector2* u, double tol, double* len_out,
                 UGS::Math::Vector2* out);
void h053(const double* a1, const double* a2, double* a3);

double ARC_SPLINE_ask_angle_between_vectors_2d(UGS::Math::Vector2* a1,
                                               UGS::Math::Vector2* a2, int a3)
{
    UGS::Math::Vector2 uu = {0.0, 0.0};
    UGS::Math::Vector2 vv = {0.0, 0.0};
    double len;
    if (!a3)
    {
        VEC2_unitize(a1, 1.0e-10, &len, &uu);
        VEC2_unitize(a2, 1.0e-10, &len, &vv);
    }
    else
    {
        uu.x = a1->x;
        uu.y = a1->y;
        vv.x = a2->x;
        vv.y = a2->y;
    }
    double dot = vv.y * uu.y + vv.x * uu.x;
    double cross = vv.y * uu.x - vv.x * uu.y;
    double angle;
    h053(&cross, &dot, &angle);
    return angle * 57.29577951308235;
}
