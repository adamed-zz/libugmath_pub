









#include <cmath>

namespace UGS {
namespace Math {
struct Vector3 {
    double x;
    double y;
    double z;
};

struct Matrix3 {
    double m[3][3];
};

inline Vector3 operator*(const Matrix3& m, const Vector3& v)
{
    return Vector3{m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2] * v.z,
                   m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2] * v.z,
                   m.m[2][0] * v.x + m.m[2][1] * v.y + m.m[2][2] * v.z};
}
}
}


struct SRF_VALUE {
    double unk_00[3];
    UGS::Math::Vector3 dS_du;
    UGS::Math::Vector3 dS_dv;
    UGS::Math::Vector3 normal;
};


double EQ_ask_length_tolerance();
double VEC3_find_angle_between(const UGS::Math::Vector3*, const UGS::Math::Vector3*);
int VEC3_unitize(UGS::Math::Vector3*, double*);
void MTX3_rot_about_axis(double, const UGS::Math::Vector3*, UGS::Math::Matrix3*);

bool DGEOM_find_1st_derivs_from_normal(
    SRF_VALUE& srf,
    UGS::Math::Vector3& normal,
    bool reverse,
    UGS::Math::Vector3& du,
    UGS::Math::Vector3& dv,
    bool* flipped)
{
    UGS::Math::Vector3 srfN = srf.normal;
    if (EQ_ask_length_tolerance() >= sqrt(srfN.x * srfN.x + srfN.y * srfN.y + srfN.z * srfN.z))
        return false;
    if (EQ_ask_length_tolerance() >= sqrt(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z))
        return false;

    UGS::Math::Vector3 vec = normal;
    double angle = VEC3_find_angle_between(&srfN, &vec);
    *flipped = false;
    if (reverse && angle > 1.5707964267948966)
    {
        angle = 3.141592653589793 - angle;
        vec.x = -vec.x;
        vec.y = -vec.y;
        vec.z = -vec.z;
        *flipped = true;
    }

    if (fabs(angle) <= 1e-7 || fabs(angle - 3.141592653589793) <= 1e-7)
    {
        du.x = srf.dS_du.x;
        du.y = srf.dS_du.y;
        du.z = srf.dS_du.z;
        dv.x = srf.dS_dv.x;
        dv.y = srf.dS_dv.y;
        dv.z = srf.dS_dv.z;
    }
    else
    {
        UGS::Math::Vector3 axis;
        axis.x = srfN.y * vec.z - srfN.z * vec.y;
        axis.y = srfN.z * vec.x - srfN.x * vec.z;
        axis.z = srfN.x * vec.y - srfN.y * vec.x;

        double len;
        VEC3_unitize(&axis, &len);

        UGS::Math::Matrix3 M;
        M.m[0][0] = 1.0;
        M.m[0][1] = 0.0;
        M.m[0][2] = 0.0;
        M.m[1][0] = 0.0;
        M.m[1][1] = 1.0;
        M.m[1][2] = 0.0;
        M.m[2][0] = 0.0;
        M.m[2][1] = 0.0;
        M.m[2][2] = 1.0;
        MTX3_rot_about_axis(angle, &axis, &M);

        du = M * srf.dS_du;
        dv = M * srf.dS_dv;
    }
    return true;
}
