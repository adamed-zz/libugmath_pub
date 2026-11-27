





#include <math.h>
extern void vunt3(const double* a1, int* ok, double* out);
extern void h805(const double* a, const double* b, const int* mode, int* out);

static const double kOne312 = 1.0;
static const int kMode312 = 0;

void h312(const double* a1, const double* a2, const double* a3, const double* a4, int* a5)
{
    double v11[3], v12[3], v13[3], v14[3];
    int* v5 = a5;
    int ok;
    *a5 = 0;
    v11[0] = *a2 - *a1;
    v11[1] = a2[1] - a1[1];
    v11[2] = a2[2] - a1[2];
    v12[0] = *a4 - *a3;
    v12[1] = a4[1] - a3[1];
    v12[2] = a4[2] - a3[2];
    vunt3(v11, &ok, v13);
    vunt3(v12, &ok, v14);
    double v15 = fabs(v13[0] * v14[0] + v13[1] * v14[1] + v13[2] * v14[2]);
    h805(&v15, &kOne312, &kMode312, &ok);
    if (ok == 1)
        *v5 = 1;
}
