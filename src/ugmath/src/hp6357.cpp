
















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

int eqz(const double* a, const double* b, const int* mode);
void hp6358(const double* a1, const double* a2, const double* a3, const double* a4,
            const double* a5, int* a6, int* a7, double* a8);

struct B2Interval { double lo, hi; };

static const int kMode = 0;

void hp6357(const double* a1, const double* a2, const double* a3, int* a4, double* a5)
{
    double* v5 = a5;
    int v7 = 0;
    *a4 = 0;
    unsigned int v9 = eqz(a3 + 3, a3, &kMode) != 0;
    if (eqz(a3 + 4, a3 + 1, &kMode))
        ++v9;
    if (eqz(a3 + 5, a3 + 2, &kMode))
        ++v9;
    if (v9 > 1)
    {
        *a4 = 2;
        return;
    }
    double v10 = a3[3];
    double v11 = a3[4];
    double v12 = a3[5];
    double v13 = a3[1];
    double v14 = a3[2];


    double v22[3];
    v22[0] = a3[0];
    v22[1] = v13;
    v22[2] = v14;
    double v25[3];
    v25[0] = fabs(v10 - a3[0]);
    v25[1] = fabs(v11 - v13);
    v25[2] = fabs(v12 - v14);
    if (v22[0] > v10)
        v22[0] = v10;
    if (v13 > v11)
        v22[1] = v11;
    if (v14 > v12)
        v22[2] = v12;
    UGS::Math::Vector3 v20;
    v20.x = 1.0;
    v20.y = 0.0;
    v20.z = 0.0;
    B2Interval v19;
    int v30;
    int st;
    hp6358(a1, a2, v22, v25, &v20.x, (int*)&a5, &v30, v5);
    st = *(int*)&a5;
    if (st)
    {
        if (st == 2)
            v7 = 1;
        v20.x = 0.0;
        v20.y = 1.0;
        v20.z = 0.0;
        hp6358(a1, a2, v22, v25 + 1, &v20.x, (int*)&a5, &v30, (double*)&v19);
        st = *(int*)&a5;
        if (st)
        {
            if (st == 2)
            {
                if (v7)
                {
                    double v15 = v5[1];
                    if (v19.lo > v15)
                        return;
                    double v16 = v19.hi;
                    if (*v5 > v16)
                        return;
                    if (v19.lo > *v5)
                        *v5 = v19.lo;
                    if (v15 > v16)
                        v5[1] = v16;
                }
                else
                {
                    v7 = 1;
                    *(B2Interval*)v5 = v19;
                }
            }
            v20.x = 0.0;
            v20.y = 0.0;
            v20.z = 1.0;
            hp6358(a1, a2, v22, v25 + 2, &v20.x, (int*)&a5, &v30, (double*)&v19);
            st = *(int*)&a5;
            if (!st)
                return;
            if (st != 2)
            {
                *a4 = 1;
                return;
            }
            if (!v7)
            {
                *(B2Interval*)v5 = v19;
                *a4 = 1;
                return;
            }
            double v17 = v5[1];
            if (!(v19.lo > v17))
            {
                double v18 = v19.hi;
                if (!(*v5 > v18))
                {
                    if (v19.lo > *v5)
                        *v5 = v19.lo;
                    if (v17 > v18)
                        v5[1] = v18;
                    *a4 = 1;
                }
            }
        }
    }
}
