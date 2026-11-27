




void h022(const int* a1, double* a2, double* a3) {
    int n = *a1;
    for (int i = 0; i < n; ++i) {
        double t = a2[i];
        a2[i] = a3[i];
        a3[i] = t;
    }
}
