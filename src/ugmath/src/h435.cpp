










#include <math.h>

extern void h002(double* a1, const double* a2);
extern void h805(const double* a1, const double* a2, const int* a3, int* a4);
extern void h053(const double* a1, const double* a2, double* a3);

static const double kZero = 0.0;
static const int kMode0 = 0;
static const double kTwoPi = 6.283185307179586;

void h435(const double* a1, const double* a2, const double* a3, const double* a4,
          const double* a5, int* a6, double* a7, double* a8)
{
    double v9 = *a4;
    double* v10 = a7;
    double v40 = *a3;
    double v39 = v9;
    h002(&v40, &kTwoPi);
    h002(&v39, &kTwoPi);
    int t;
    h805(&v39, &kZero, &kMode0, &t);
    if (v40 > v39 || t == 1)
        v39 = v39 + kTwoPi;
    const double* v12 = a5;
    double v41 = *a5 - *a1;
    double v37 = a5[1] - a1[1];
    double v38;
    h053(&v37, &v41, &v38);
    int v14 = 1;
    double v15 = v38;
    double v16 = v40;
    *a6 = 1;
    double v18 = v39;
    if (!(v38 < v40) && v39 >= v15)
    {
        *a6 = 2;
        v14 = 2;
    }
    double v19 = v15 + kTwoPi;
    bool useThird = (v19 >= v16 && v18 >= v19);
    if (useThird)
        *a6 = 2;
    double v20 = *a2;
    double v21 = *a1;
    if (useThird || v14 == 2)
    {
        double v22 = cos(v19) * v20 + v21;
        *v10 = v22;
        double v23 = sin(v19) * *a2 + a1[1];
        v10[1] = v23;
        double v24y = v12[1] - v23;
        double v24x = *v12 - v22;
        *a8 = sqrt(v24y * v24y + v24x * v24x);
        return;
    }
    double v26 = cos(v16) * v20 + v21;
    double v27 = sin(v16) * v20 + a1[1];
    double v28 = cos(v18) * v20 + v21;
    double v29 = sin(v18);
    double v30 = *v12;
    double v31y = v12[1];
    double v32 = v29 * v20 + a1[1];
    double v34 = sqrt((v31y - v27) * (v31y - v27) + (v30 - v26) * (v30 - v26));
    double v35 = sqrt((v31y - v32) * (v31y - v32) + (v30 - v28) * (v30 - v28));
    if (v35 <= v34)
    {
        *v10 = v28;
        v10[1] = v32;
        *a8 = v35;
    }
    else
    {
        *v10 = v26;
        v10[1] = v27;
        *a8 = v34;
    }
}
