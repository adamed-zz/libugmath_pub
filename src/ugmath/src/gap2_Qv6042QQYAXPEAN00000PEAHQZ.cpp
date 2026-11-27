#include <cmath>

void h100(const double* a, const double* m, double* out);
void h630(const double* a, const double* b, const double* c, const double* d, int* code, double* out);
void vcru3(const double* a, const double* b, int* ok, double* out);
void vunt3(const double* a, int* ok, double* out);

void v6042(double* a1, double* a2, double* a3, double* a4, double* a5, double* a6, int* a7)
{
    int code;
    int* v7 = a7;
    *a7 = 1;
    double t[3];
    t[0] = a1[0] - a2[0];
    t[1] = a1[1] - a2[1];
    t[2] = a1[2] - a2[2];
    vunt3(t, &code, a5);
    t[0] = a3[0] - a4[0];
    t[1] = a3[1] - a4[1];
    t[2] = a3[2] - a4[2];
    vcru3(a5, t, &code, a5 + 6);
    if (code) {
        vcru3(a5 + 6, a5, &code, a5 + 3);
        if (code) {
            h100(a3, a5, t);
            double v16 = t[2];
            h100(a1, a5, t);
            if (!(fabs(v16 - t[2]) > 1e-10)) {
                h630(a1, a2, a3, a4, &code, a6);
                return;
            }
        }
    }
    *v7 = 2;
}
