

















#include <cmath>








extern "C" {
double g_basis[10];
double g_tab_a[6];
double g_tab_b[6];
double g_gap[4];
double g_acc1[6];
double g_acc2[6];
double g_tail;
}

extern int eqz(const double* a, const double* b, const int* mode);

static const int kMode = 0;

void h0733()
{
    double zero = 0.0;
    int mode = 0;
    g_basis[1] = g_tab_a[1];
    g_basis[2] = -g_tab_b[0];
    g_basis[3] = -g_tab_b[1];
    g_basis[7] = -g_tab_b[3];
    g_basis[0] = g_tab_a[0];
    g_basis[4] = g_tab_a[2];
    g_basis[5] = g_tab_a[3];
    g_basis[6] = -g_tab_b[2];
    g_basis[8] = g_tab_a[4] - g_tab_b[4];
    g_basis[9] = g_tab_a[5] - g_tab_b[5];
    double v3 = g_basis[2] * g_basis[2] + g_basis[0] * g_basis[0] +
                g_basis[4] * g_basis[4] + g_basis[6] * g_basis[6] + g_basis[8] * g_basis[8];
    if (!eqz(&v3, &zero, &mode)) {
        double v0 = std::sqrt(v3);
        g_basis[0] /= v0;
        g_basis[2] /= v0;
        g_basis[4] /= v0;
        g_basis[6] /= v0;
        g_basis[8] /= v0;
    }
    v3 = g_basis[3] * g_basis[3] + g_basis[1] * g_basis[1] + g_basis[5] * g_basis[5] +
         g_basis[7] * g_basis[7] + g_basis[9] * g_basis[9];
    if (!eqz(&v3, &zero, &mode)) {
        double v1 = std::sqrt(v3);
        g_basis[1] /= v1;
        g_basis[3] /= v1;
        g_basis[5] /= v1;
        g_basis[7] /= v1;
        g_basis[9] /= v1;
    }
}
