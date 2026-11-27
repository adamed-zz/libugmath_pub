




















#include <math.h>

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

}

extern "C" long long sub_180061400(int n, int m, double* A, long long unused_a4, int flag,
                                   int* perm, int unused_a7, double* nn, double* n0,
                                   double* orig) {
    if (m > 0) {
        for (int j = 0; j < m; ++j) {
            const double v = SafeNorm(n, A + (long long)j * n);
            n0[j] = v;
            nn[j] = v;
            orig[j] = v;
            if (flag) perm[j] = j;
        }
    }

    const long long mn = (n <= m) ? n : m;
    if (mn <= 0) return mn;

    for (int k = 0; k < (int)mn; ++k) {
        if (flag) {
            int maxi = k;
            for (int i = k; i < m; ++i)
                if (nn[i] > nn[maxi]) maxi = i;
            if (maxi != k) {
                for (int t = 0; t < n; ++t) {
                    const long long a = (long long)k * n + t;
                    const long long b = (long long)maxi * n + t;
                    const double tmp = A[a];
                    A[a] = A[b];
                    A[b] = tmp;
                }
                nn[maxi] = nn[k];
                orig[maxi] = orig[k];
                const int ti = perm[k];
                perm[k] = perm[maxi];
                perm[maxi] = ti;
            }
        }
        const long long kd = (long long)k * n + k;
        double v = SafeNorm(n - k, A + kd);
        if (!(v == 0.0)) {
            if (0.0 > A[kd]) v = -v;
            for (int i = k; i < n; ++i) A[(long long)k * n + i] /= v;
            A[kd] = A[kd] + 1.0;
            if (k + 1 < m) {
                for (int j = k + 1; j < m; ++j) {
                    double w = 0.0;
                    for (int i = k; i < n; ++i)
                        w = w + A[(long long)k * n + i] * A[(long long)j * n + i];
                    w = w / A[kd];
                    for (int i = k; i < n; ++i) {
                        const long long ji = (long long)j * n + i;
                        A[ji] = A[ji] - w * A[(long long)k * n + i];
                    }
                    if (flag) {
                        const double curn = nn[j];
                        if (!(curn == 0.0)) {
                            const double r = A[(long long)j * n + k] / curn;
                            double t = 1.0 - r * r;
                            if (0.0 > t) t = 0.0;
                            const double s = sqrt(t) * curn;
                            nn[j] = s;
                            const double q = s / orig[j];
                            if (0.05 * q * q <= 1.2e-16) {
                                const double nv =
                                    SafeNorm(n - k - 1, A + (long long)j * n + (k + 1));
                                nn[j] = nv;
                                orig[j] = nv;
                            }
                        }
                    }
                }
            }
        }
        nn[k] = -v;
    }
    return (long long)(unsigned int)(m - n);
}
