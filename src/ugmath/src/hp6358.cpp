













#include <cmath>

namespace UGS
{
namespace Math
{
struct Vector3
{
    double x, y, z;
};
}
}

double EQ_ask_length_tolerance();
int VEC3_unitize(const UGS::Math::Vector3* u, double tol, double* len_out,
                 UGS::Math::Vector3* out);
void h633(const double* a1, const double* a2, const double* a3, const double* a4,
          int* a5, double* a6, double* a7);

void hp6358(const double* a1, const double* a2, const double* a3, const double* a4,
            const double* a5, int* a6, int* a7, double* a8)
{
    *a6 = 0;
    double len;
    UGS::Math::Vector3 dir;
    int ok = VEC3_unitize((const UGS::Math::Vector3*)a5, EQ_ask_length_tolerance(), &len,
                          &dir);
    *a7 = ok != 0;
    double base[3];
    base[0] = a3[0] + dir.x * *a4;
    base[1] = a3[1] + dir.y * *a4;
    base[2] = a3[2] + dir.z * *a4;
    double res[4];
    int st;
    double t;
    h633(a1, a2, base, &dir.x, &st, res, &t);
    if (st == 1)
    {
        a8[0] = t;
        a8[1] = t;
        if (!*a7)
        {
            *a6 = 2;
            return;
        }
        base[0] = a3[0];
        base[1] = a3[1];
        base[2] = a3[2];
        dir.x = dir.x * -1.0;
        dir.y = dir.y * -1.0;
        dir.z = dir.z * -1.0;
        h633(a1, a2, base, &dir.x, &st, res, &t);
        if (st == 1)
        {
            if (a8[0] > t)
            {
                a8[0] = t;
                *a6 = 2;
            }
            else
            {
                a8[1] = t;
                *a6 = 2;
            }
        }
        else
        {
            *a6 = 1;
        }
    }
    else if (st == 2)
    {
        *a6 = 1;
    }
    else
    {
        double d1 = (base[1] - a1[1]) * dir.y + (base[0] - a1[0]) * dir.x +
                    (base[2] - a1[2]) * dir.z;
        double d2 = (a3[0] - a1[0]) * (dir.x * -1.0) -
                    (a3[1] - a1[1]) * (dir.y * 1.0) - (a3[2] - a1[2]) * (dir.z * 1.0);

        if (!(d1 < 0.0) && !(d2 < 0.0))
            *a6 = 1;
    }
}
