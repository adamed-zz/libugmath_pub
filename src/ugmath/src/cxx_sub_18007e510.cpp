













extern "C" double sub_18007E510(void* ws, void* unused, void* cfg)
{
    (void)unused;
    const double* x = *(const double**)((char*)ws + 8);
    const double* y = *(const double**)((char*)ws + 32);
    long long n = *(long long*)((char*)cfg + 120);

    if (n <= 1)
        return x[0] * y[0];

    double a0 = x[0] * y[0];
    double a1 = x[1] * y[1];
    double sum;
    if (n / 2 * 2 > 2) {
        double b0 = x[2] * y[2];
        double b1 = x[3] * y[3];
        long long v6 = n / 4 * 4;
        for (long long i = 4; i < v6; i += 4) {
            a0 += x[i] * y[i];
            a1 += x[i + 1] * y[i + 1];
            b0 += x[i + 2] * y[i + 2];
            b1 += x[i + 3] * y[i + 3];
        }
        a0 += b0;
        a1 += b1;
        if (n / 2 * 2 > v6) {
            long long j = n / 4 * 4;
            a0 += x[j] * y[j];
            a1 += x[j + 1] * y[j + 1];
        }
    }
    sum = a0 + a1;
    for (long long i = n / 2 * 2; i < n; ++i)
        sum += x[i] * y[i];
    return sum;
}
