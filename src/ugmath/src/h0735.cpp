










#include <cmath>




extern "C" {
extern double g_basis[10];
extern double g_tab_a[6];
extern double g_tab_b[6];
extern double g_gap[4];
extern double g_acc1[6];
extern double g_acc2[6];
extern double g_tail;
}

void h0735(const double* a1, const int* a2, double* a3, double* a4, int* a5)
{
    double e0928 = g_basis[1], e0930 = g_basis[2], e0938 = g_basis[3];
    double e0940 = g_basis[4], e0948 = g_basis[5];
    double e0950 = g_basis[6], e0958 = g_basis[7], e0960 = g_basis[8], e0968 = g_basis[9];
    double spint = g_basis[0];
    double v9 = 0.0, v10 = 0.0, v11 = 0.0;
    *a5 = 1;
    int i = 0;
    for (;;) {
        double t = *a1;
        double v6 = t * e0928 + spint;
        v11 = t * e0958 + e0950;
        double v7 = t * e0938 + e0930;
        double v8 = t * e0948 + e0940;
        v9 = v11 * -0.5 / v7;
        v10 = (v6 + v6 + v8) / v7;
        v11 = v11 * v11 / (v7 * v7) - (t * e0968 + e0960 + v6 + v8) / v7 * 4.0;

        if (!(v11 < 0.0))
            break;
        ++i;
        ++a1;
        if (i >= *a2) {
            *a5 = 0;
            return;
        }
    }
    double v12 = std::sqrt(v11) * 0.5;
    a3[1] = 1.0;
    double v13 = v10 / (v12 * -2.0);
    *a3 = -v13;
    a3[2] = (v12 + v9 - v13) * -1.0;
    *a4 = v13;
    a4[2] = (v9 - v12 + v13) * -1.0;
    a4[1] = 1.0;
}
