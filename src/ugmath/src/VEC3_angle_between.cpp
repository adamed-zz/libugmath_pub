




namespace UGS
{
namespace Math
{
struct Vector2
{
    double x;
    double y;
};
struct Vector3
{
    double x;
    double y;
    double z;
};
}
}

extern int MACH__checking_level;
void ERROR_assertion_failed(const char* file, int line, const char* fmt, ...);

#include <cmath>




int VEC3_unitize(const UGS::Math::Vector3* u, double tol, double* out_len, UGS::Math::Vector3* out_unit);

using UGS::Math::Vector3;

double VEC3_angle_between(const Vector3* u, const Vector3* v, const Vector3* axis)
{
    double u_len;
    double v_len;
    Vector3 u_hat = {0.0, 0.0, 0.0};
    Vector3 v_hat = {0.0, 0.0, 0.0};

    int ok_u = VEC3_unitize(u, 1.0e-10, &u_len, &u_hat);
    int ok_v = VEC3_unitize(v, 1.0e-10, &v_len, &v_hat);
    if (!ok_u || !ok_v)
        return 0.0;

    double c0 = v_hat.x * u_hat.z - v_hat.z * u_hat.x;
    double c1 = v_hat.y * u_hat.x - v_hat.x * u_hat.y;
    double dot = v_hat.y * u_hat.y + v_hat.x * u_hat.x + v_hat.z * u_hat.z;
    double c2 = v_hat.z * u_hat.y - v_hat.y * u_hat.z;

    double norm = sqrt(c0 * c0 + c2 * c2 + c1 * c1);
    if (c0 * axis->y + c2 * axis->x + c1 * axis->z < 0.0)
        norm = -norm;

    double angle = atan2(norm, dot);
    if (fabs(angle) <= 1.0e-10)
        return 0.0;
    if (angle < 0.0)
        angle += 6.283185307179586;
    return angle;
}
