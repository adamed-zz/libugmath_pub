





extern void vcru3(const double* a1, const double* a2, int* ok, double* out);

void h309(const double* a1, const double* a2, const double* a3, const double* a4,
          double* a5, double* a6)
{
    double v7 = a2[1] - a1[1];
    double v8 = a2[2] - a1[2];
    double v10 = a3[2] - a1[2];
    double v12 = a3[1] - a1[1];
    double v13 = *a3 - *a1;
    double v26[3];
    v26[0] = *a2 - *a1;
    double n[3];
    n[0] = v13;
    n[1] = v12;
    n[2] = v10;
    double v23 = n[0];
    double v24 = n[1];
    double v25 = n[2];
    v26[1] = v7;
    v26[2] = v8;
    double v27[3];
    v27[0] = v7 * v10 - v8 * v12;
    v27[1] = v13 * v8 - v26[0] * v10;
    v27[2] = v26[0] * v12 - v13 * v7;
    int v28;
    vcru3(v27, v26, &v28, n);
    v23 = n[0];
    v24 = n[1];
    v25 = n[2];
    double v15 = v24 * *a4;
    double v16 = v25 * *a4;
    double v17 = v23 * *a4;
    double v18 = v15 + a1[1];
    double v19 = v16 + a1[2];
    *a5 = v17 + *a1;
    a5[1] = v18;
    a5[2] = v19;
    double v20 = v15 + a2[1];
    double v21 = v16 + a2[2];
    *a6 = v17 + *a2;
    a6[1] = v20;
    a6[2] = v21;
}
