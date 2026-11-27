










#include <math.h>

extern void h805(const double* a1, const double* a2, const int* a3, int* a4);

static const double kZero = 0.0;
static const int kMode0 = 0;

void h601(const double* a1, const double* a2, int* a3, double* a4)
{
    *a3 = 1;
    double p1 = a2[1];
    double p2 = a1[1];
    p1 *= *a1;
    p2 *= *a2;
    double det = p1 - p2;
    int s;
    h805(&det, &kZero, &kMode0, &s);
    if (s != 1)
    {
        *a3 = 2;
        double q1 = a2[1];
        double q2 = a1[1];
        q1 *= a1[2];
        q2 *= a2[2];
        a4[0] = (q1 - q2) / det;
        double r1 = *a1;
        double r2 = *a2;
        r1 *= a2[2];
        r2 *= a1[2];
        a4[1] = (r1 - r2) / det;
    }
}
