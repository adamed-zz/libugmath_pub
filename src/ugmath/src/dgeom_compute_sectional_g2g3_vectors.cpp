








#include <cmath>

namespace UGS {
namespace Math {
struct Vector3 {
    double x;
    double y;
    double z;
};
}
}


double EQ_ask_length_tolerance();
double EQ_ask_length_squared_tolerance();


int VEC3_unitize(const UGS::Math::Vector3* v, double tol, double* len, UGS::Math::Vector3* out);


int sub_18001F940(double* a1, double* a2, double* a3, double* a4, double* a5,
                  double* a10, UGS::Math::Vector3* t1, UGS::Math::Vector3* t2,
                  double* a12);
int sub_18001EEA0(double* a1, double* a2, double* a3, double* a4, double* a5,
                  double* a6, double* a7, double* a8, double* a9, double* a10,
                  UGS::Math::Vector3* t1, UGS::Math::Vector3* t2, double* v14,
                  double* a13);

int DGEOM_compute_sectional_G2G3_vectors(
    double* a1, double* a2, double* a3, double* a4, double* a5, double* a6,
    double* a7, double* a8, double* a9, double* a10, int a11, double* a12,
    double* a13)
{
    if (a12)
        a12[0] = a12[1] = a12[2] = 0.0;
    if (a13)
        a13[0] = a13[1] = a13[2] = 0.0;
    if (!a10)
        return 1;

    UGS::Math::Vector3 t1;
    t1.x = a1[1] * a2[2] - a1[2] * a2[1];
    t1.y = a1[2] * a2[0] - a1[0] * a2[2];
    t1.z = a1[0] * a2[1] - a1[1] * a2[0];

    double len;
    VEC3_unitize(&t1, EQ_ask_length_tolerance(), &len, &t1);
    if (EQ_ask_length_tolerance() > len)
        return 1;

    UGS::Math::Vector3 t2;
    t2.x = a10[1] * t1.z - a10[2] * t1.y;
    t2.y = a10[2] * t1.x - a10[0] * t1.z;
    t2.z = a10[0] * t1.y - a10[1] * t1.x;

    VEC3_unitize(&t2, EQ_ask_length_tolerance(), &len, &t2);
    if (EQ_ask_length_tolerance() > len)
        return 1;

    double l1 = a1[0] * a1[0] + a1[1] * a1[1] + a1[2] * a1[2];
    double dot = a1[0] * a2[0] + a1[1] * a2[1] + a1[2] * a2[2];
    double l2 = a2[0] * a2[0] + a2[1] * a2[1] + a2[2] * a2[2];

    if (EQ_ask_length_squared_tolerance() > l1)
        return 1;
    if (EQ_ask_length_squared_tolerance() > l2)
        return 1;
    len = l2 * l1 - dot * dot;
    if (EQ_ask_length_squared_tolerance() >= std::fabs(len))
        return 1;

    if (a11) {
        if (a11 == 1)
            return sub_18001F940(a1, a2, a3, a4, a5, a10, &t1, &t2, a12);
        if (a11 != 2)
            return 1;
    }
    return sub_18001EEA0(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, &t1, &t2,
                         (a11 == 2) ? 0 : a12, a13);
}
