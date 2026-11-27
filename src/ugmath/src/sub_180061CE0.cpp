













#include <cmath>
#include <cstring>

extern "C" unsigned long long sub_180061CE0(int n, double* A, int ld, const int* perm,
                                            const double* mult, const double* rhs,
                                            double* diagOut, double* work, double* xvec) {
    if (n <= 0) return (unsigned long long)(long long)ld;


    {
        long long base = 0;
        for (int i = 0; i < n; ++i) {
            long long dst = base;
            long long src = base;
            for (int t = 0; t < n - i; ++t) {
                A[dst] = A[src];
                ++dst;
                src += ld;
            }
            diagOut[i] = A[base];
            xvec[i] = rhs[i];
            base += (long long)ld + 1;
        }
    }


    for (int j = 0; j < n; ++j) {
        const double d = mult[perm[j]];
        if (!(d == 0.0)) {
            for (int t = j; t < n; ++t) work[t] = 0.0;
            work[j] = d;
            double extra = 0.0;
            for (int k = j + 1; k <= n; ++k) {
                const double xv = work[k - 1];
                if (xv == 0.0) continue;
                const int di = (k - 1) * (ld + 1);
                double* const dp = A + (long long)di;
                const double dg = *dp;
                double p, q;
                if (!(std::fabs(xv) > std::fabs(dg))) {
                    const double t = xv / dg;
                    const double s = std::sqrt((0.25 * t) * t + 0.25);
                    const double c = 0.5 / s;
                    p = t * c;
                    q = c;
                } else {
                    const double t = dg / xv;
                    const double s = std::sqrt((0.25 * t) * t + 0.25);
                    const double c = 0.5 / s;
                    p = c;
                    q = t * c;
                }
                *dp = xv * p + dg * q;
                const double y = xvec[k - 1];
                const double en = extra * q - y * p;
                xvec[k - 1] = y * q + p * extra;
                extra = en;
                const int rbase = (k - 1) * (ld + 1) + 1;
                for (int t2 = 0; t2 < n - k; ++t2) {
                    double* const ap = A + (long long)rbase + t2;
                    const double a = *ap;
                    const double wv = work[k + t2];
                    *ap = wv * p + a * q;
                    work[k + t2] = wv * q - a * p;
                }
            }
        }
        const long long ji = (long long)j * (ld + 1);
        work[j] = A[ji];
        A[ji] = diagOut[j];
    }


    int qd = n;
    for (int i = 0; i < n; ++i) {
        if (work[i] == 0.0) {
            if (qd == n) qd = i;
            xvec[i] = 0.0;
        } else if (qd < n) {
            xvec[i] = 0.0;
        }
    }


    if (qd >= 1) {
        for (int s = qd - 1; s >= 0; --s) {
            double acc = 0.0;
            const long long abase = (long long)s * ld;
            for (int i = s + 1; i < qd; ++i) acc += A[abase + i] * xvec[i];
            xvec[s] = (xvec[s] - acc) / work[s];
        }
    }


    for (int i = 0; i < n; ++i) diagOut[perm[i]] = xvec[i];

    unsigned long long r;
    std::memcpy(&r, &xvec[n - 1], sizeof(r));
    return r;
}
