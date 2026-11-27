




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


double EQ_ask_length_tolerance();
int VEC3_unitize(const UGS::Math::Vector3* u, double tol, double* out_len,
                 UGS::Math::Vector3* out_unit);

double VEC3_find_angle_between(const UGS::Math::Vector3* u1,
                               const UGS::Math::Vector3* u2)
{
    UGS::Math::Vector3 u1n = {0.0, 0.0, 0.0};
    UGS::Math::Vector3 u2n = {0.0, 0.0, 0.0};
    double len;

    double tol = EQ_ask_length_tolerance();
    int ok1 = VEC3_unitize(u1, tol, &len, &u1n);
    int ok2 = VEC3_unitize(u2, tol, &len, &u2n);
    if (!ok1 || !ok2)
        return 0.0;

    double dot = u2n.y * u1n.y + u2n.x * u1n.x + u2n.z * u1n.z;
    if (dot > 1.0)
        return 0.0;
    if (dot < -1.0)
        return 3.141592653589793;
    return std::acos(dot);
}
