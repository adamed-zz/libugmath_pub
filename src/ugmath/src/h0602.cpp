











#include <cmath>

extern void vunt3(const double* a1, int* ok, double* out);
extern void h053(const double* a1, const double* a2, double* out);

extern const double g_h0602_axis0;
extern const double g_h0602_axis1;
extern const double g_h0602_axis2;

void h0602(const double* a1, const double* a2, double* a3)
{
    double u1[4];
    double u2[4];
    int ok;
    u1[0] = a1[0];
    u1[1] = a1[1];
    u1[2] = 0.0;
    u1[3] = 0.0;
    u2[0] = a2[0];
    u2[1] = a2[1];
    u2[2] = 0.0;
    u2[3] = 0.0;
    vunt3(u1, &ok, u1);
    if (!ok) {
        *a3 = 0.0;
        return;
    }
    vunt3(u2, &ok, u2);
    if (!ok) {
        *a3 = 0.0;
        return;
    }
    double c0 = u1[1] * u2[2] - u2[1] * u1[2];
    double c1 = u2[0] * u1[2] - u1[0] * u2[2];
    double c2 = u1[0] * u2[1] - u2[0] * u1[1];
    double n = sqrt(c1 * c1 + c0 * c0 + c2 * c2);
    double s = c0 * g_h0602_axis0 + c1 * g_h0602_axis1 + c2 * g_h0602_axis2;
    double d = u1[0] * u2[0] + u2[1] * u1[1] + u2[2] * u1[2];
    if (s < 0.0)
        n = -n;
    h053(&n, &d, a3);
}
