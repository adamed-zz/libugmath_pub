












#include <cstring>

extern void h805(const double* a1, const double* a2, const int* a3, int* a4);
extern void h014(double* a1, double* a2, double* a3, int* a4, int* a5, int* a6);
void movf(const int* a1, const double* a2, double* a3)
{
    memcpy(a3, a2, (size_t)(8 * *a1));
}








extern "C" {
extern double g_basis[10];
extern double g_tab_a[6];
extern double g_tab_b[6];
extern double g_gap[4];
extern double g_acc1[6];
extern double g_acc2[6];
extern double g_tail;
}

void h0732(const int* a1, const double* a2, const double* a3, const double* a4, int* a5, double* a6)
{
    double tbl[6];
    int n = 6;
    int mode = 0;
    double zero = 0.0;
    double v19, v14, v20;
    double c[3];
    double roots[2];
    int st;
    if (*a1 == 1)
        movf(&n, g_tab_a, tbl);
    else
        movf(&n, g_tab_b, tbl);
    h805(a2, &zero, &mode, &st);
    if (st) {
        v14 = tbl[3];
        v19 = tbl[1];
        c[0] = *a4 / *a3 + tbl[5];
    } else {
        double v11 = *a2;
        double v12 = *a3;
        v19 = *a3 * tbl[1] / *a2 + tbl[0];
        v14 = v12 * tbl[3] / v11 + tbl[2];
        c[0] = v12 * tbl[5] / v11 + tbl[4] + *a4 / v11;
    }
    c[1] = v14;
    c[2] = v19;
    h014(c, a6, roots, &st, &mode, a5);
    if (st == 4)
        *a5 = -1;
    (void)v20;
}
