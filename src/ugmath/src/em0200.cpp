






void em0200(const double* a1, const double* a2, double* a3, double* a4, double* a5) {
    *a3 = a1[1] - a2[1];
    double v5 = *a2 - *a1;
    *a4 = v5;
    *a5 = (*a1 * *a3 + v5 * a1[1]) * -1.0;
}
