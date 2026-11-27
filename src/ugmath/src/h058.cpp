




#include <math.h>
void vunt3(const double* a1, int* a2, double* a3);
int eqz(const double* a1, const double* a2, const int* a3);
void h053(const double* a1, const double* a2, double* a3);
void h002(double* a1, const double* a2);

void h058(const double* a1, const double* a2, const int* a3, double* a4) {
    static const double kZero = 0.0;
    static const double kOne = 1.0;
    static const double k180 = 180.0;
    static const int kSel = 0;
    int f = 0;
    double u[3], v[3];
    double dot, sq, c, s, y;
    if (*a3 == 1) {
        vunt3(a1, &f, u);
        vunt3(a2, &f, v);
        dot = u[0] * v[0] + u[1] * v[1] + u[2] * v[2];
        sq = dot * dot;
        if (sq > 1.0 || eqz(&sq, &kOne, &kSel)) {
            sq = 1.0;
            c = 1.0;
        } else {
            c = sq;
        }
        s = sqrt(1.0 - c);
        y = dot;
        h053(&s, &y, a4);
        *a4 = *a4 * 57.29577951308235;
    } else {
        double dot2 = a2[0] * a1[0] + a1[1] * a2[1];
        double n1 = a1[0] * a1[0] + a1[1] * a1[1];
        double l1 = sqrt(n1);
        double n2 = a2[0] * a2[0] + a2[1] * a2[1];
        double l2 = sqrt(n2);
        double prod = l1 * l2;
        double cosv = dot2;
        if (eqz(&prod, &kZero, &kSel)) cosv = 1.0;
        else cosv = cosv / prod;
        sq = cosv * cosv;
        if (sq > 1.0 || eqz(&sq, &kOne, &kSel)) {
            sq = 1.0;
            c = 1.0;
        } else {
            c = sq;
        }
        s = sqrt(1.0 - c);
        y = cosv;
        h053(&y, &s, a4);
        *a4 = 90.0 - *a4 * 57.29577951308235;
        h002(a4, &k180);
    }
}
