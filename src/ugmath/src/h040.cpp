






void h006(double* a1, const double* a2, const double* a3, const int* a4, const double* a5,
          int* a6, int* a7);

void h040(const double* a1, double* a2) {
    int mode = 1;
    double span = 6.283185307179586;
    int status;
    int turns;
    h006(a2, a1, a1 + 1, &mode, &span, &status, &turns);
    if (status != 1) {
        double v4 = (*a1 + a1[1]) * 0.5;
        double v5 = v4 + 3.141592653589793;
        h006(a2, &v4, &v5, &mode, &span, &status, &turns);
        if (status != 1) {
            v5 = v4;
            v4 = v4 + -3.141592653589793;
            h006(a2, &v4, &v5, &mode, &span, &status, &turns);
        }
    }
    *a2 = (double)turns * 6.283185307179586 + *a2;
}
