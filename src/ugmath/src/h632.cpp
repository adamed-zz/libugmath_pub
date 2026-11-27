












#include <math.h>

#include "ugmath/vector3.h"

int eqz(const double* a1, const double* a2, const int* a3);
void vcru3(const double* a1, const double* a2, int* a3, double* a4);
int GetAlgorithmVersion();

int VEC3_unitize(UGS::Math::Vector3* v, double* len);
void h004(const double* a1, const double* a2, const double* a3, double* a4);
void h805(const double* a1, const double* a2, const int* a3, int* a4);
void h310(const double* a1, const double* a2, const double* a3, double* a4);
void h635(const double* a1, const double* a2, const double* a3, const double* a4,
          int* a5, double* a6);

void h632(const double* a1, double* a2, const double* a3, double* a4, int* a5,
          double* a6)
{
    static const double kZero = 0.0;
    static const int kSelNumber = 0;
    static const int kSelLength = 1;

    double len;
    double v22[3];
    double v23[3];
    double v24[4];
    double v26, v27, v28;
    int st;

    len = sqrt(a2[0] * a2[0] + a2[1] * a2[1] + a2[2] * a2[2]);
    if (eqz(&len, &kZero, &kSelNumber))
    {
        a2[0] = 0.0;
        a2[1] = 0.0;
        a2[2] = 0.0;
    }
    else
    {
        a2[0] = a2[0] / len;
        a2[1] = a2[1] / len;
        a2[2] = a2[2] / len;
    }
    len = sqrt(a4[0] * a4[0] + a4[1] * a4[1] + a4[2] * a4[2]);
    if (eqz(&len, &kZero, &kSelNumber))
    {
        a4[0] = 0.0;
        a4[1] = 0.0;
        a4[2] = 0.0;
    }
    else
    {
        a4[0] = a4[0] / len;
        a4[1] = a4[1] / len;
        a4[2] = a4[2] / len;
    }
    *a5 = 1;
    vcru3(a2, a4, &st, v23);
    if (st)
    {
        v22[0] = a3[0] - a1[0];
        v22[1] = a3[1] - a1[1];
        v22[2] = a3[2] - a1[2];
        if (GetAlgorithmVersion() >= 24120)
            VEC3_unitize(reinterpret_cast<UGS::Math::Vector3*>(v22), &v26);
        h004(v22, a2, a4, &v28);
        h805(&v28, &kZero, &kSelNumber, &st);
        *a5 = (st == 1) + 3;
        vcru3(a2, a4, &st, v23);
        vcru3(a2, v23, &st, v24);
        h635(a3, a4, a1, v24, &st, a6);
    }
    else
    {
        h310(a1, a3, a4, &v27);
        h805(&v27, &kZero, &kSelLength, &st);
        if (st)
            *a5 = 2;
    }
}
