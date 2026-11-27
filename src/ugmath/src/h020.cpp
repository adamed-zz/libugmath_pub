




#include <math.h>
void h805(const double* a1, const double* a2, const int* a3, int* a4);

void h020(const double* a1, const double* a2, const double* a3, double* a4, double* a5, int* a6) {
    static const double kZero = 0.0;
    static const int kSel = 0;
    *a6 = 0;
    int st;
    h805(a1, &kZero, &kSel, &st);
    if (!st) {
        double v14 = *a2 * *a2 - *a1 * 4.0 * *a3;
        h805(&v14, &kZero, &kSel, &st);
        if (!st) {
            if (!(v14 < 0.0)) {
                double v11 = sqrt(v14);
                *a6 = 2;
                double v12 = *a2;
                if (0.0 > *a2) {
                    *a4 = (v11 - v12) / (*a1 + *a1);
                    *a5 = (*a3 + *a3) / (v11 - *a2);
                } else {
                    *a4 = *a3 * -2.0 / (v12 + v11);
                    *a5 = -(v11 + *a2) / (*a1 + *a1);
                }
            }
        } else {
            double v13 = -*a2 / (*a1 + *a1);
            *a4 = v13;
            *a5 = v13;
            *a6 = 2;
        }
    } else {
        h805(a2, &kZero, &kSel, &st);
        if (st != 1) {
            *a4 = -*a3 / *a2;
            *a6 = 1;
        }
    }
}
