














#include <math.h>

void vcru3(const double* a1, const double* a2, int* a3, double* a4);
int eqz(const double* a1, const double* a2, const int* a3);
void h635(const double* a1, const double* a2, const double* a3, const double* a4,
          int* a5, double* a6);

void h6343(const double* a1, const double* a2, const double* a3, const double* a4,
           const double* a5, const double* a6, int* a7, double* a8)
{
    static const double kZero = 0.0;
    static const int kSelNumber = 0;

    double v27[3];
    double v30[3];
    double v33[4];
    double v35;
    int st;

    *a7 = 3;
    vcru3(a2, a4, &st, v27);
    if (!st)
    {

        v35 = (a3[0] - a1[0]) * a2[0] + (a3[1] - a1[1]) * a2[1] + (a3[2] - a1[2]) * a2[2];
        if (eqz(&v35, &kZero, &kSelNumber))
        {

            vcru3(a2, a6, &st, v27);
            if (st)
            {
                v30[0] = v27[1] * a2[2] - v27[2] * a2[1];
                v30[1] = v27[2] * a2[0] - v27[0] * a2[2];
                v30[2] = v27[0] * a2[1] - v27[1] * a2[0];
                *a7 = 2;
                h635(a1, v30, a3, a4, &st, a8);
                return;
            }
            v35 = (a5[0] - a1[0]) * a2[0] + (a5[1] - a1[1]) * a2[1] + (a5[2] - a1[2]) * a2[2];
            if (eqz(&v35, &kZero, &kSelNumber))
            {
                *a7 = 2;
                a8[0] = a1[0];
                a8[1] = a1[1];
                a8[2] = a1[2];
                return;
            }
        }
        *a7 = 3;
        return;
    }

    v30[0] = v27[1] * a2[2] - v27[2] * a2[1];
    v30[1] = v27[2] * a2[0] - v27[0] * a2[2];
    v30[2] = v27[0] * a2[1] - v27[1] * a2[0];
    h635(a1, v30, a3, a4, &st, v33);
    h635(v33, v27, a5, a6, &st, a8);
    if (st == 2)
    {
        *a7 = 1;
        return;
    }
    if (st == 1)
    {
        *a7 = 3;
        return;
    }
    *a7 = 2;
    a8[0] = v33[0];
    a8[1] = v33[1];
    a8[2] = v33[2];
}
