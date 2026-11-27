








#include <math.h>

extern void vunt3(const double* a1, int* a2, double* a3);
extern void h805(const double* a1, const double* a2, const int* a3, int* a4);

static const int kMode1 = 1;
static const int kMode1b = 1;

void h431(const double* a1, const double* a2, const double* a3, int* a4, double* a5, double* a6)
{
    double* v6 = a5;
    double v8 = a3[2] - a1[2];
    double v11 = *a3 - *a1;
    double v13y = a3[1] - a1[1];
    double dir[3];
    int u;
    vunt3(a2, &u, dir);
    double v12 = dir[1] * v13y + dir[0] * v11 + dir[2] * v8;
    double len2 = v13y * v13y + v11 * v11 + v8 * v8;
    double v27 = v12;
    double v14 = sqrt(len2);
    double v28 = fabs(v12);
    double v26 = v14;
    int s;
    h805(&v28, &v26, &kMode1, &s);
    if (s == 1)
    {
        *a4 = 2;
        v6[0] = a3[0];
        v6[1] = a3[1];
        v6[2] = a3[2];
        *a6 = 0.0;
        return;
    }
    double v15 = v27;
    *a4 = 1;
    v6[0] = dir[0] * v15 + *a1;
    v6[1] = dir[1] * v15 + a1[1];
    v6[2] = dir[2] * v15 + a1[2];
    h805(&v26, &v27, &kMode1b, &s);
    if (s == 1)
    {
        *a6 = 0.0;
        return;
    }
    double v21 = v26 * v26 - v27 * v27;
    *a6 = sqrt(v21);
}
