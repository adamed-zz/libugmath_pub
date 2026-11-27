



















#include <math.h>

namespace UGS
{
namespace Math
{
struct Vector3
{
    double x;
    double y;
    double z;
};
}
}

int VEC3_unitize(const UGS::Math::Vector3* v, double eps, double* len_out, UGS::Math::Vector3* out);
bool VEC3_is_parallel(const UGS::Math::Vector3* u, const UGS::Math::Vector3* v, double tolerance);
bool VEC3_is_perpendicular(const UGS::Math::Vector3* u, const UGS::Math::Vector3* v, double tolerance);
double VEC3_angle_between(const UGS::Math::Vector3* u, const UGS::Math::Vector3* v, const UGS::Math::Vector3* normal);

void ARC_SPLINE_ask_inscribed_angle_and_type(UGS::Math::Vector3* a1, UGS::Math::Vector3* a2, UGS::Math::Vector3* a3,
                                             int a4, double a5, double* a6, double* a7, int* a8)
{
    double len;
    const double v13 = sin(a5 * 0.01745329251994328);
    const double v18 = sin((a5 < 0.001 ? a5 : 0.001) * 0.01745329251994328);

    *a6 = 0.0;
    *a7 = 0.0;
    *a8 = -2;

    UGS::Math::Vector3 v35 = {0.0, 0.0, 0.0};
    UGS::Math::Vector3 v33 = {0.0, 0.0, 1.0};

    UGS::Math::Vector3 v29;
    UGS::Math::Vector3 v31;
    v31 = *a1;
    v29 = *a2;

    VEC3_unitize(&v31, 1.0e-10, &len, &v31);
    VEC3_unitize(&v29, 1.0e-10, &len, &v29);

    UGS::Math::Vector3 v27;
    if (a3)
    {
        v27 = *a3;
        VEC3_unitize(&v27, 1.0e-10, &len, &v27);
    }
    else
    {
        v27 = v33;
    }

    if (!VEC3_is_parallel(&v31, &v29, v13))
    {
        (void)VEC3_is_parallel(&v27, &v33, v13);

        v35.x = v29.z * v31.y - v29.y * v31.z;
        v35.y = v31.z * v29.x - v29.z * v31.x;
        v35.z = v29.y * v31.x - v29.x * v31.y;
        VEC3_unitize(&v35, 1.0e-10, &len, &v35);

        (void)VEC3_is_parallel(&v27, &v35, v13);
        const bool p1 = VEC3_is_perpendicular(&v27, &v35, v13);
        const bool p2 = VEC3_is_perpendicular(&v33, &v35, v13);
        if (p1)
        {
            if (p2)
            {
                UGS::Math::Vector3 v37;
                const double d31 = fabs(v33.x * v31.x + v33.y * v31.y + v33.z * v31.z);
                const double d29 = fabs(v33.x * v29.x + v33.y * v29.y + v33.z * v29.z);
                if (d29 < d31)
                    v37 = v29;
                else
                    v37 = v31;
                VEC3_unitize(&v37, 1.0e-10, &len, &v37);

                v27.x = v37.y * v33.z - v37.z * v33.y;
                v27.y = v37.z * v33.x - v37.x * v33.z;
                v27.z = v37.x * v33.y - v37.y * v33.x;
                VEC3_unitize(&v27, 1.0e-10, &len, &v27);
            }
            else
            {
                v27 = v35;
            }
        }
    }

    const bool is_par = VEC3_is_parallel(&v31, &v29, v18);

    if (a4)
    {
        double len2;
        double d = -(v31.x * v27.x + v31.y * v27.y + v31.z * v27.z);
        v31.x += d * v27.x;
        v31.y += d * v27.y;
        v31.z += d * v27.z;
        VEC3_unitize(&v31, 1.0e-10, &len2, &v31);

        d = -(v29.x * v27.x + v29.y * v27.y + v29.z * v27.z);
        v29.x += d * v27.x;
        v29.y += d * v27.y;
        v29.z += d * v27.z;
        VEC3_unitize(&v29, 1.0e-10, &len2, &v29);
    }

    const double v26 = VEC3_angle_between(&v31, &v29, &v27) * 57.29577951308235;
    *a7 = v26;

    if (is_par && (v29.x * v31.x + v29.y * v31.y + v29.z * v31.z) > 0.0)
    {
        *a6 = 180.0;
        *a8 = -1;
    }
    else if (!(v26 < 180.0))
    {
        *a6 = 360.0 - (v26 - 180.0);
        *a8 = 0;
    }
    else
    {
        *a6 = 180.0 - v26;
        *a8 = 1;
    }

    if (a5 > fabs(*a6 - 180.0))
        *a8 = -1;
}
