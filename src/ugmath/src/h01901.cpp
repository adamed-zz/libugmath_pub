





void h805(const double* a1, const double* a2, const int* a3, int* a4);

void h01901(const double* a1, const double* a2, double* a3) {
    *a3 = 0.0;
    double v7 = *a1 * *a1 + a1[1] * a1[1] + a1[2] * a1[2];
    int v6 = 0;
    const int sel = 0;
    const double zero = 0.0;
    h805(&v7, &zero, &sel, &v6);
    if (v6 != 1) *a3 = (a2[1] * a1[1] + *a1 * *a2 + a2[2] * a1[2]) / v7;
}
