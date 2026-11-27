











extern void h016(double* a1, double* a2, double* a3, int* a4, int* a5, int* a6);




extern "C" {
extern double g_basis[10];
extern double g_tab_a[6];
extern double g_tab_b[6];
extern double g_gap[4];
extern double g_acc1[6];
extern double g_acc2[6];
extern double g_tail;
}

void h0734(double* a1, int* a2)
{
    double v4[4];
    double v5[4];
    double v6[4];
    int v7, v8;
    double e0928 = g_basis[1], e0930 = g_basis[2], e0938 = g_basis[3];
    double e0940 = g_basis[4], e0948 = g_basis[5];
    double e0950 = g_basis[6], e0958 = g_basis[7], e0960 = g_basis[8], e0968 = g_basis[9];
    double spint = g_basis[0];
    v4[0] = e0930 * spint * e0960;
    v4[1] = e0938 * spint * e0960 + e0930 * spint * e0968 + e0928 * e0930 * e0960;
    v4[3] = e0928 * e0938 * e0968;
    v4[2] = e0928 * e0938 * e0960 + e0938 * spint * e0968 + e0928 * e0930 * e0968;
    double v2 = e0950 * spint * e0958 + e0940 * e0930 * e0948;
    v5[0] = e0950 * spint * e0950 + e0940 * e0930 * e0940;
    v5[1] = v2 + v2 + e0940 * e0938 * e0940 + e0950 * e0928 * e0950;


    {
        double a5c = e0948 * e0930 * e0948;
        double tm = e0950 * e0928 * e0958 + e0940 * e0938 * e0948;
        double c5c = e0958 * spint * e0958;
        v5[2] = a5c + (tm + tm) + c5c;
    }
    v5[3] = e0958 * e0928 * e0958 + e0948 * e0938 * e0948;
    v6[0] = v4[0] * 4.0 - v5[0];
    v6[1] = v4[1] * 4.0 - v5[1];
    v6[2] = v4[2] * 4.0 - v5[2];
    v6[3] = v4[3] * 4.0 - v5[3];
    h016(v6, a1, v4, &v8, &v7, a2);
}
