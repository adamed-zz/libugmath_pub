









struct alignas(16) Pair2 {
    double x;
    double y;
};

union Bits {
    long long i;
    double d;
};

extern "C" __declspec(noinline) double sub_18007DCF0(const double* a) {
    union alignas(16) {
        Pair2 p;
        double v[2];
    } u;
    u.p = *(const Pair2*)a;
    unsigned long long stride = 1;
    do {
        double* q = u.v;
        unsigned long long n = stride;
        do {
            const double* lo = q;
            const double* hi = q + stride;
            volatile Bits nmx;
            nmx.i = -1;
            double mx = *lo;
            double xm = (mx == mx) ? nmx.d : 0.0;
            volatile Bits nmy;
            nmy.i = -1;
            double my = *hi;
            double ym = (my == my) ? nmy.d : 0.0;
            const double* sel = (my > mx) ? hi : lo;
            double t = my;
            if (ym != 0.0) t = *sel;
            double r = mx;
            if (xm != 0.0) r = t;
            *q++ = r;
            --n;
        } while (n);
        stride >>= 1;
    } while (stride);
    return u.v[0];
}
