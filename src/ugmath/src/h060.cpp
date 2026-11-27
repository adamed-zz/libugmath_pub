









#include <cmath>

extern void vunt3(const double* a1, int* ok, double* out);
extern void h053(const double* a1, const double* a2, double* out);

void h060(const double* a1, const double* a2, const double* a3, double* a4)
{
    int ok;
    double u2[3];
    double u1[3];
    double n, d;
    vunt3(a1, &ok, u1);
    if (!ok) {
        *a4 = 0.0;
        return;
    }
    vunt3(a2, &ok, u2);
    if (!ok) {
        *a4 = 0.0;
        return;
    }
    double c0 = u1[1] * u2[2] - u1[2] * u2[1];
    double c1 = u1[2] * u2[0] - u1[0] * u2[2];
    double c2 = u1[0] * u2[1] - u1[1] * u2[0];
    n = sqrt(c0 * c0 + c1 * c1 + c2 * c2);
    if (c1 * a3[1] + c0 * a3[0] + c2 * a3[2] < 0.0)
        n = -n;
    d = u1[0] * u2[0] + u1[1] * u2[1] + u1[2] * u2[2];
    h053(&n, &d, a4);
}
