












#include <math.h>
#include <string.h>

namespace {

const double kTiny = 3.834e-20;
const double kBigScale = 1.304e19;


inline void NormAcc(double y, double& big_acc, double& direct, double& tiny_acc, double& big_scale,
                    double& tiny_scale, double big_thresh) {
    if (!(y > kTiny)) {
        if (!(y > tiny_scale)) {
            if (!(y == 0.0)) tiny_acc = tiny_acc + y / tiny_scale * (y / tiny_scale);
        } else {
            tiny_acc = tiny_acc * (tiny_scale / y) * (tiny_scale / y);
            tiny_scale = y;
            tiny_acc = tiny_acc + 1.0;
        }
    } else if (!(big_thresh > y)) {
        if (!(y > big_scale)) {
            big_acc = big_acc + y / big_scale * (y / big_scale);
        } else {
            double t = big_acc * (big_scale / y) * (big_scale / y);
            big_scale = y;
            big_acc = t + 1.0;
        }
    } else {
        direct = direct + y * y;
    }
}

double SafeNorm(int n, const double* v) {
    double big_acc = 0.0;
    double direct = 0.0;
    double tiny_acc = 0.0;
    double big_scale = 0.0;
    double tiny_scale = 0.0;
    const double big_thresh = kBigScale / (double)n;
    for (int i = 0; i < n; ++i) {
        const double y = fabs(v[i]);
        NormAcc(y, big_acc, direct, tiny_acc, big_scale, tiny_scale, big_thresh);
    }
    if (!(big_acc == 0.0)) {
        double q = direct / big_scale / big_scale + big_acc;
        return sqrt(q) * big_scale;
    } else if (!(direct == 0.0)) {
        double t = tiny_scale * tiny_acc;
        if (!(direct >= tiny_scale)) {
            direct = direct / tiny_scale + t;
        } else {
            tiny_scale = tiny_scale / direct * t + 1.0;
        }
        double r = tiny_scale * direct;
        return sqrt(r);
    } else {
        return sqrt(tiny_acc) * tiny_scale;
    }
}


inline double MaxSD(double dst, double src) {
    if (dst != dst || src != src) return src;
    return dst > src ? dst : src;
}
inline double MinSD(double dst, double src) {
    if (dst != dst || src != src) return src;
    return dst < src ? dst : src;
}


unsigned long long GivensSolve(int n, double* A, int ld, const int* perm, const double* mult,
                               const double* rhs, double* diagOut, double* work, double* xvec) {
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
                if (!(fabs(xv) > fabs(dg))) {
                    const double t = xv / dg;
                    const double s = sqrt((0.25 * t) * t + 0.25);
                    const double c = 0.5 / s;
                    p = t * c;
                    q = c;
                } else {
                    const double t = dg / xv;
                    const double s = sqrt((0.25 * t) * t + 0.25);
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

    unsigned long long rbits;
    memcpy(&rbits, &xvec[n - 1], sizeof(rbits));
    return rbits;
}

}

extern "C" unsigned long long sub_180060490(int n, double* A, int ld, int* perm, const double* w,
                                            const double* b, double tol, double* lambda,
                                            double* sol, double* piv, double* x, double* r) {

    int rank = n;
    if (n > 0) {
        for (int i = 0; i < n; ++i) {
            x[i] = b[i];
            const double dg = A[(long long)i * (ld + 1)];
            if (dg == 0.0) {
                if (rank == n) rank = i;
                x[i] = 0.0;
            } else if (rank < n) {
                x[i] = 0.0;
            }
        }
    }


    const long long rk = rank;
    if (rk >= 1) {
        for (long long idx = rk - 1; idx >= 0; --idx) {
            const double v = x[idx] / A[idx * (ld + 1)];
            x[idx] = v;
            for (long long k = 0; k < idx; ++k) x[k] = x[k] - v * A[idx * ld + k];
        }
    }


    if (n > 0) {
        for (int i = 0; i < n; ++i) sol[perm[i]] = x[i];
        for (int i = 0; i < n; ++i) r[i] = sol[i] * w[i];
    }
    const double norm0 = SafeNorm(n, r);
    if (0.1 * tol >= norm0 - tol) {
        *lambda = 0.0;
        return (unsigned long long)(size_t)lambda;
    }


    double v77 = 0.0;
    if (rank >= n) {
        for (int i = 0; i < n; ++i) x[i] = r[perm[i]] / norm0 * w[perm[i]];
        for (int i = 0; i < n; ++i) {
            double s = 0.0;
            for (int k = 0; k < i; ++k) s = s + x[k] * A[(long long)i * ld + k];
            x[i] = (x[i] - s) / A[(long long)i * (ld + 1)];
        }
        const double n105 = SafeNorm(n, x);
        v77 = (norm0 - tol) / tol / n105 / n105;
    }


    if (n > 0) {
        for (int i = 0; i < n; ++i) {
            double s = 0.0;
            for (int k = 0; k <= i; ++k) s = s + b[k] * A[(long long)i * ld + k];
            x[i] = s / w[perm[i]];
        }
    }
    const double nrm2 = SafeNorm(n, x);
    double upper = nrm2 / tol;
    if (upper == 0.0) upper = 1e-38 / (tol < 0.1 ? tol : 0.1);
    double lam = MaxSD(*lambda, v77);
    lam = MinSD(lam, upper);
    *lambda = lam;
    double cur;
    if (lam == 0.0) {
        cur = nrm2 / norm0;
        *lambda = cur;
    } else {
        cur = lam;
    }


    double v74 = norm0 - tol;
    int iter = 0;
    for (;;) {
        ++iter;
        if (cur == 0.0) {
            cur = MaxSD(1e-38, 0.001 * upper);
            *lambda = cur;
        }
        const double s = sqrt(cur);
        if (n > 0)
            for (int i = 0; i < n; ++i) x[i] = s * w[i];
        GivensSolve(n, A, ld, perm, x, b, sol, piv, r);
        if (n > 0)
            for (int i = 0; i < n; ++i) r[i] = sol[i] * w[i];
        const double newn = SafeNorm(n, r);
        const double old74 = v74;
        v74 = newn - tol;
        if (0.1 * tol >= fabs(v74)) break;
        if (v77 == 0.0) {
            if (old74 >= v74) {
                if (0.0 > old74) break;
            }
        }
        if (iter == 10) break;
        if (n > 0)
            for (int i = 0; i < n; ++i) x[i] = r[perm[i]] / newn * w[perm[i]];
        for (int k = 0; k < n; ++k) {
            x[k] = x[k] / piv[k];
            for (int i = k + 1; i < n; ++i) x[i] = x[i] - x[k] * A[(long long)k * ld + i];
        }
        const double nrm110 = SafeNorm(n, x);
        double t2 = v74 / tol / nrm110 / nrm110;
        if (v74 > 0.0) {
            if (!(v77 >= *lambda)) v77 = *lambda;
        }
        if (0.0 > v74) {
            if (!(*lambda >= upper)) upper = *lambda;
        }
        t2 = t2 + *lambda;
        cur = MaxSD(v77, t2);
        *lambda = cur;
    }
    if (iter == 0) {
        *lambda = 0.0;
        return (unsigned long long)(size_t)lambda;
    }
    return (unsigned long long)(unsigned)iter;
}
