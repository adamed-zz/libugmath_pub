







struct Row4 {
    double v[4];
};

void em0914(int* a1, double* a2, double* a3, double* a4) {
    long long n = *a1;
    Row4 buf[0x4e60 / sizeof(Row4)];
    Row4* R = buf;
    if (n >= 0) {
        for (long long i = 0; i <= n; ++i) R[i] = ((const Row4*)a2)[i];
    }
    if (n >= 1) {
        for (long long i = 1; i <= n; ++i) {
            const Row4* prev = R + 26 * (i - 1);
            Row4* cur = R + 26 * i;
            for (long long r = 0; r <= n - i; ++r) {
                for (int c = 0; c < 4; ++c) {
                    double t = prev[r + 1].v[c];
                    t = t + prev[r].v[c];
                    cur[r].v[c] = t * 0.5;
                }
            }
        }
    }
    if (n >= 0) {
        for (long long k = 0; k <= n; ++k) {
            const Row4* s = R + 26 * k;
            const Row4* m = R + 26 * (n - k) + k;
            for (int c = 0; c < 4; ++c) a3[4 * k + c] = s->v[c];
            for (int c = 0; c < 4; ++c) a4[4 * k + c] = m->v[c];
        }
    }
}
