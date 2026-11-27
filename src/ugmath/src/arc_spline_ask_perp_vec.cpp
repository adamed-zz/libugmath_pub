





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

void ARC_SPLINE_ask_perp_vec(int mode, const UGS::Math::Vector2* v, UGS::Math::Vector2* out)
{
    out->x = -v->y;
    out->y = v->x;
    if (mode == 1)
    {
        out->x = -out->x;
        out->y = -out->y;
    }
}
