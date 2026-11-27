








struct alignas(16) Pair2 {
    double x;
    double y;
};

extern "C" __declspec(noinline) double sub_18007DDB0(const double* a) {
    union alignas(16) {
        Pair2 p;
        double v[2];
    } u;
    u.p = *(const Pair2*)a;
    for (unsigned long long stride = 1; stride; stride >>= 1) {
        double* q = u.v;
        for (unsigned long long n = stride; n; --n) {
            const double* lo = q;
            const double* hi = q + stride;
            *q++ = *((*hi > *lo) ? hi : lo);
        }
    }
    return u.v[0];
}
