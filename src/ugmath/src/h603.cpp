












#include <math.h>

extern void h053(const double* a1, const double* a2, double* a3);
extern void h401(const double* a1, const double* a2, const double* a3, double* a4);
extern void h200(const double* a1, const double* a2, double* a3);
extern void h805(const double* a1, const double* a2, const int* a3, int* a4);
extern void h003(const double* a1, const double* a2, double* a3);
extern void h002(double* a1, const double* a2);

static const double kZero = 0.0;
static const int kMode1 = 1;
static const double kTwoPi = 6.283185307179586;

void h603(const double* a1, const double* a2, const double* a3, const double* a4,
          int* a5, double* a6)
{
    *a5 = 1;
    double v28 = -*a2;
    double v21;
    h053(&v28, a2 + 1, &v21);
    double v25[2];
    h401(a1, a2, a3, v25);
    double v29;
    h200(v25, a3, &v29);
    double v27 = sqrt(v29);
    int flag;
    h805(&v27, a4, &kMode1, &flag);
    if (flag == 1)
        goto L15;
    v28 = v27 - *a4;

    if (!(0.0 > v28))
    {

        if (v28 != 0.0)
            return;
        goto L15;
    }
    *a5 = 3;
    {
        double v12 = *a4 * *a4 - v29;
        double v13 = sqrt(v12);
        double v23 = v13;
        int flag2;
        h805(&v27, &kZero, &kMode1, &flag2);
        if (flag2 != 1)
        {
            double v26[2];
            v26[0] = v25[0] - *a3;
            v26[1] = v25[1] - a3[1];
            double v22;
            h003(v26, a2, &v22);
            if (v22 < 0.0)
                v27 = -v27;
        }
        double v24;
        h053(&v23, &v27, &v24);
        a6[0] = v24 + v21;
        a6[1] = v21 - v24;
        h002(a6, &kTwoPi);
        h002(a6 + 1, &kTwoPi);
        double v18 = a6[1];
        if (a6[0] > v18)
            a6[1] = v18 + kTwoPi;
        return;
    }
L15:
    *a5 = 2;
    a6[0] = v21;
}
