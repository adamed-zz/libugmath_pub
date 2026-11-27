










#include <math.h>

extern void vunt3(const double* a1, int* a2, double* a3);
extern void h805(const double* a1, const double* a2, const int* a3, int* a4);

static const double kZero = 0.0;
static const int kMode0 = 0;

void h602a(const double* a1, const double* a2, const double* a3, const double* a4,
           double* a5, double* a6, int* a7)
{
    double v35[3], v38[3];
    int dummy;
    vunt3(a2, &dummy, v35);
    vunt3(a4, &dummy, v38);
    double v11 = v35[0] * v35[0] + v35[1] * v35[1] + v35[2] * v35[2];
    double v12 = v38[0] * v35[0] + v38[1] * v35[1] + v38[2] * v35[2];
    double v13 = v38[0] * v38[0] + v38[1] * v38[1] + v38[2] * v38[2];
    double v42 = v13 * v11 - v12 * v12;
    h805(&v42, &kZero, &kMode0, a7);
    if (*a7 != 1)
    {
        *a7 = 0;
        double v16 = *a1 - *a3;
        double v17 = a1[1] - a3[1];
        double v18 = a1[2] - a3[2];
        double v24 = v35[0] * v16 + v35[1] * v17;
        double v27 = -(v24 + v35[2] * v18);
        double v28 = -(v38[0] * v16 + v38[1] * v17 + v38[2] * v18);
        double v29 = (v27 * v13 - v28 * v12) / v42;
        a5[1] = (v27 * v12 - v28 * v11) / v42;
        a5[0] = v29;
        double v30 = v35[1] * v29 + a1[1];
        double v31 = v35[2] * v29 + a1[2];
        a6[0] = v35[0] * v29 + *a1;
        a6[1] = v30;
        a6[2] = v31;
        double v32 = a5[1];
        double v33 = v38[1] * v32 + a3[1];
        double v34 = v38[2] * v32 + a3[2];
        a6[3] = v38[0] * v32 + *a3;
        a6[4] = v33;
        a6[5] = v34;
    }
}
