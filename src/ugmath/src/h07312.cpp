












extern void h0736(const double* a1, double* a2);
extern void h006(double* a1, const double* a2, const double* a3, const int* a4,
                 const double* a5, int* a6, int* a7);
extern int eqz(const double* a1, const double* a2, const int* a3);
extern void h07313(const int* a1, const int* a2, const double* a3, const double* a4, double* a5);
extern void h07314(const int* a1, const int* a2, const double* a3, const double* a4, double* a5);

void h07312(const int* a1, const int* a2, const double* a3, const double* a4, double* a5,
            double* a6)
{
    int v6 = *a1;
    int v8 = *a2;
    double v21 = 0.0;
    int v19 = 0;
    int v17 = v6;
    int v18 = v8;
    double v16 = *a3;
    double v15 = *a4;
    double v24[4];
    double v25[4];
    double v20;
    int v22 = 0;
    int v23 = 0;
    int v26 = 0;
    int v27 = 0;
    if (v6 != 1 && v8 != 1)
        return;
    h0736(a5, v24);
    if (v17 == 1) {
        h006(v24, &v21, &v16, &v17, &v16, &v22, &v27);
        v20 = (double)v27 * v16 + v24[0];
        if (eqz(&v20, &v16, &v19))
            --v27;
    } else {
        v27 = 0;
    }
    if (v18 == 1) {
        h006(v25, &v21, &v15, &v18, &v15, &v23, &v26);
        v20 = (double)v26 * v15 + v25[0];
        if (eqz(&v20, &v15, &v19))
            --v26;
    } else {
        v26 = 0;
    }
    if (v27 || v26)
        h07313(&v27, &v26, &v16, &v15, a5);
    h0736(a6, v24);
    if (v17 == 1) {
        h006(v24, &v21, &v16, &v17, &v16, &v22, &v27);
        v20 = (double)v27 * v16 + v24[0];
        if (eqz(&v20, &v16, &v19))
            --v27;
    } else {
        v27 = 0;
    }
    if (v18 == 1) {
        h006(v25, &v21, &v15, &v18, &v15, &v23, &v26);
        v20 = (double)v26 * v15 + v25[0];
        if (eqz(&v20, &v15, &v19))
            --v26;
    } else {
        v26 = 0;
    }
    if (v27 || v26)
        h07314(&v27, &v26, &v16, &v15, a6);
}
