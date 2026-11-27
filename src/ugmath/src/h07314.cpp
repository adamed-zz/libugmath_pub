














extern "C" {
extern double g_basis[10];
extern double g_tab_a[6];
extern double g_tab_b[6];
extern double g_gap[4];
extern double g_acc1[6];
extern double g_acc2[6];
extern double g_tail;
}

void h07314(const int* a1, const int* a2, const double* a3, const double* a4, double* a5)
{
    int v5 = *a2;
    double v6 = *a4;
    if (*a1) {
        double v8 = (double)*a1 * *a3;
        g_tab_b[4] = g_tab_b[4] + v8;
        g_acc2[0] = g_acc2[0] + v8;
        g_acc2[2] = g_acc2[2] + v8;
        g_acc2[4] = g_acc2[4] + v8;
        for (long long v7 = 0; v7 < 7; v7 += 2)
            a5[v7] = v8 + a5[v7];
    }
    if (v5) {
        double v10 = (double)v5 * v6;
        g_tab_b[5] = g_tab_b[5] + v10;
        g_acc2[1] = g_acc2[1] + v10;
        g_acc2[3] = g_acc2[3] + v10;
        g_acc2[5] = g_acc2[5] + v10;
        for (long long v9 = 1; v9 < 8; v9 += 2)
            a5[v9] = v10 + a5[v9];
    }
}
