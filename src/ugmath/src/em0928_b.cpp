





int em0928_b(int a1, int a2, double* a3) {
    double thr = a3[a2 - 1];
    long long total = (long long)(int)((unsigned int)a1 + (unsigned int)a2);
    int cnt = 0;
    for (long long i = 0; i < total; ++i) {
        double v = a3[i];
        if (v == thr) {
            ++cnt;
        } else if (v > thr) {
            return a2 - cnt;
        }
    }
    return a2 - cnt;
}
