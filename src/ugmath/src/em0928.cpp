





int em0928(const int* a1, const int* a2, const double* a3) {
    int n1 = *a1;
    int n2 = *a2;
    long long total = (long long)(int)((unsigned int)n1 + (unsigned int)n2);
    int zeros = 0;
    for (long long i = 0; i < total; ++i) {
        double v = a3[i];
        if (v == 0.0) {
            ++zeros;
        } else if (v > 0.0) {
            return n2 - zeros;
        }
    }
    return n2 - zeros;
}
