






























#include <cmath>
#include <cstring>

namespace {





constexpr double kDblMin = 2.2250738585072014e-308;


int DClass(double x) {
    if (std::isnan(x)) return 2;
    if (std::isinf(x)) return 1;
    if (x == 0.0) return 0;
    if (std::fpclassify(x) == FP_SUBNORMAL) return -2;
    return -1;
}

int DSign(double x) { return std::signbit(x) ? 1 : 0; }


double Fn7DCF0(const double* a) {
    double v[2] = {a[0], a[1]};
    unsigned long long stride = 1;
    do {
        double* q = v;
        unsigned long long n = stride;
        do {
            const double mx = q[0];
            const double my = q[stride];
            const bool mx_nan = (mx != mx);
            const bool my_nan = (my != my);
            const double* sel = (my > mx) ? (q + stride) : q;
            double t = my;
            if (!my_nan) t = *sel;
            double r = mx;
            if (!mx_nan) r = t;
            q[0] = r;
            ++q;
            --n;
        } while (n);
        stride >>= 1;
    } while (stride);
    return v[0];
}


char Fn7C440(double* out, const double* A, long long p, long long q) {
    const double x = A[p + 2 * q];
    const double ax = std::fabs(x);
    if (ax + ax < kDblMin) {
        out[0] = 1.0;
        out[1] = 0.0;
        return 0;
    }
    const double t = (A[3 * p] - A[3 * q]) / (ax + ax);
    const double root = std::sqrt(t * t + 1.0);
    double rho;
    if (!(t > 0.0))
        rho = 1.0 / (t - root);
    else
        rho = 1.0 / (root + t);
    const double sign = !(rho > 0.0) ? -1.0 : 1.0;
    const double den = std::sqrt(rho * rho + 1.0);
    const double inv = 1.0 / den;
    out[0] = inv;
    out[1] = std::fabs(rho) * (x / ax * -sign) * inv;
    return 1;
}


char Fn7DE10(const double* A, long long p, long long q, double* out, double* tmp) {
    const double g00 = A[3 * p];
    const double g01 = A[p + 2 * q];
    const double g10 = A[q + 2 * p];
    const double g11 = A[3 * q];
    double b[4] = {g00, g01, g10, g11};
    double T;
    double S;
    if (std::fabs(g10 - g01) < kDblMin) {
        T = 1.0;
        S = 0.0;
    } else {
        const double t = (g00 + g11) / (g10 - g01);
        const double root = std::sqrt(t * t + 1.0);
        T = t / root;
        S = 1.0 / root;
        if (!(T == 1.0 && S == 0.0)) {
            b[0] = g10 * S + T * g00;
            b[1] = T * g10 - S * g00;
            b[2] = g11 * S + T * g01;
            b[3] = T * g11 - g01 * S;
        }
    }
    const char result = Fn7C440(tmp, b, 0, 1);
    const double o0 = tmp[0];
    const double no1 = -tmp[1];
    out[0] = T * o0 - S * no1;
    out[1] = T * no1 + S * o0;
    return result;
}


double* Fn77F80(double* base, long long i, long long j, const double* cs) {
    const double c = cs[0];
    const double s = cs[1];
    double* pi = base + i;
    double* pj = base + j;
    if (c != 1.0 || s != 0.0) {
        const double t0 = pj[0] * c - pi[0] * s;
        pi[0] = pi[0] * c + pj[0] * s;
        pj[0] = t0;
        const double t1 = pj[2] * c - pi[2] * s;
        pi[2] = pi[2] * c + pj[2] * s;
        pj[2] = t1;
    }
    return pj;
}


double* Fn78010(double* base, long long i, long long j, const double* cs) {
    const double c = cs[0];
    const double s = -cs[1];
    double* pi = base + 2 * i;
    double* pj = base + 2 * j;
    if (c != 1.0 || s != 0.0) {
        const double t0 = pj[0] * c - pi[0] * s;
        pi[0] = pj[0] * s + pi[0] * c;
        pj[0] = t0;
        const double t1 = pj[1] * c - pi[1] * s;
        pi[1] = pj[1] * s + pi[1] * c;
        pj[1] = t1;
    }
    return pj;
}


double Fn7D200(const double* data, long long n, long long* out_index) {
    if (n) {
        long long idx = 0;
        double best = data[0];
        for (long long i = 1; i < n; ++i) {
            if (data[i] > best) {
                best = data[i];
                idx = i;
            }
        }
        *out_index = idx;
        return best;
    }
    *out_index = -1;
    return 0.0;
}

bool Fn8B280(const unsigned char* base) { return base[87] || base[88]; }
bool Fn8B2C0(const unsigned char* base) { return base[89] || base[90]; }

double NanMax(double a, double b) {
    const bool a_nan = (a != a);
    const bool b_nan = (b != b);
    if (a_nan) return b_nan ? a : b;
    if (b_nan) return a;
    return a > b ? a : b;
}


struct Ctx {
    unsigned char* b;
    double* d(long long off) { return reinterpret_cast<double*>(b + off); }
    long long* q(long long off) { return reinterpret_cast<long long*>(b + off); }
    int* i32(long long off) { return reinterpret_cast<int*>(b + off); }
    unsigned char& u8(long long off) { return b[off]; }
};


void Fn87540(unsigned char* obj, const double* m, long long a3) {
    Ctx c{obj};
    if (!c.u8(0x55) || *c.q(0x68) != 2 || *c.q(0x70) != 2 ||
        static_cast<int>(a3) != *c.i32(0x5c)) {
        *c.i32(0x5c) = static_cast<int>(a3);
        *c.q(0x68) = 2;
        c.u8(0x57) = (a3 & 4) != 0;
        *c.q(0x70) = 2;
        c.u8(0x58) = (a3 & 8) != 0;
        *c.i32(0x50) = 0;
        c.u8(0x5a) = (a3 & 0x20) != 0;
        *reinterpret_cast<unsigned short*>(obj + 0x54) = 0x100;
        c.u8(0x59) = (a3 & 0x10) != 0;
        *c.q(0x78) = 2;
    }

    const double av0 = std::fabs(m[0]);
    const double av1 = std::fabs(m[1]);
    const double bv0 = std::fabs(m[2]);
    const double bv1 = std::fabs(m[3]);
    double pair0[2] = {av0, av1};
    double pair1[2] = {bv0, bv1};
    double mx2[2] = {NanMax(pair0[0], pair1[0]), NanMax(pair0[1], pair1[1])};
    double v10 = Fn7DCF0(mx2);

    if (DClass(v10) > 0) {
        *c.i32(0x50) = 3;
        c.u8(0x54) = 1;
        return;
    }
    if (v10 == 0.0) v10 = 1.0;
    const double inv = v10;

    double* nrm = c.d(0x90);
    nrm[0] = m[0] / inv;
    nrm[1] = m[1] / inv;
    nrm[2] = m[2] / inv;
    nrm[3] = m[3] / inv;

    if (*c.q(0x68) == *c.q(0x70)) {
        if (c.u8(0x57) || c.u8(0x58)) {
            c.d(0x00)[0] = 1.0;
            c.d(0x08)[0] = 0.0;
            c.d(0x10)[0] = 0.0;
            c.d(0x18)[0] = 1.0;
        }
        if (c.u8(0x59) || c.u8(0x5a)) {
            c.d(0x20)[0] = 1.0;
            c.d(0x28)[0] = 0.0;
            c.d(0x30)[0] = 0.0;
            c.d(0x38)[0] = 1.0;
        }
    } else {
        c.d(0xc0)[0] = nrm[0];
        c.d(0xc8)[0] = nrm[1];
        c.d(0xd0)[0] = nrm[2];
        c.d(0xd8)[0] = nrm[3];
    }

    const long long dim = *c.q(0x78);
    double v16 = std::fmax(std::fabs(nrm[0]), std::fabs(nrm[3]));

    for (;;) {
        bool rotated = false;
        for (long long i = 1; i < dim; ++i) {
            for (long long j = 0; j < i; ++j) {
                const double thr = std::fmax(v16 * 4.440892098500626e-16, kDblMin);
                if (std::fabs(nrm[2 * j + 1]) > thr || std::fabs(nrm[i + j + 1]) > thr) {
                    rotated = true;
                    double cs[2] = {0.0, 0.0};
                    double tmp[2] = {0.0, 0.0};
                    Fn7DE10(nrm, i, j, cs, tmp);
                    Fn77F80(nrm, i, j, cs);
                    if (Fn8B280(obj)) {
                        const double cs2[2] = {cs[0], -cs[1]};
                        Fn78010(c.d(0x00), i, j, cs2);
                    }
                    Fn78010(nrm, i, j, tmp);
                    if (Fn8B2C0(obj)) {
                        Fn78010(c.d(0x20), i, j, tmp);
                    }


                    v16 = std::fmax(std::fmax(std::fabs(nrm[3 * j]), std::fabs(nrm[3 * i])), v16);
                }
            }
        }
        if (!rotated) break;
    }

    double* norm = c.d(0x40);
    for (long long r = 0; r < dim; ++r) {
        const double head = nrm[3 * r];
        norm[r] = std::fabs(head);
        if (Fn8B280(obj) && head < 0.0) {
            double* row = c.d(0x00) + 2 * r;
            unsigned long long bits = 0;
            std::memcpy(&bits, row, 8);
            bits ^= 0x8000000000000000ull;
            std::memcpy(row, &bits, 8);
            std::memcpy(&bits, row + 1, 8);
            bits ^= 0x8000000000000000ull;
            std::memcpy(row + 1, &bits, 8);
        }
    }
    norm[0] = inv * norm[0];
    norm[1] = inv * norm[1];
    *c.q(0x60) = dim;

    for (long long k = 0; k < dim; ++k) {
        const long long remain = dim - k;
        long long pick = 0;
        if (Fn7D200(norm, remain, &pick) == 0.0) {
            *c.q(0x60) = k;
            break;
        }
        if (pick != 0) {
            const long long at = pick + k;
            const double t = norm[0];
            norm[0] = norm[pick];
            norm[pick] = t;
            if (Fn8B280(obj)) {
                double* rowA = c.d(0x00) + 2 * k;
                double* rowB = c.d(0x00) + 2 * at;
                const double r0 = rowA[0];
                const double r1 = rowA[1];
                rowA[0] = rowB[0];
                rowA[1] = rowB[1];
                rowB[0] = r0;
                rowB[1] = r1;
            }
            if (Fn8B2C0(obj)) {
                double* rowA = c.d(0x20) + 2 * k;
                double* rowB = c.d(0x20) + 2 * at;
                const double r0 = rowA[0];
                const double r1 = rowA[1];
                rowA[0] = rowB[0];
                rowA[1] = rowB[1];
                rowB[0] = r0;
                rowB[1] = r1;
            }
        }
        ++norm;
    }
    c.u8(0x54) = 1;
}


void Fn7A0B0(double* out, const long long* a2, const long long* a3) {
    const long long n_p = a2[1];
    const double* M = reinterpret_cast<const double*>(a3[0]);
    const double* P = reinterpret_cast<const double*>(a2[0]);
    double acc[4] = {0.0, 0.0, 0.0, 0.0};
    for (long long c = 0; c < n_p; ++c) {
        const double m0 = M[2 * c];
        const double m1 = M[2 * c + 1];
        acc[0] += m0 * P[2 * c];
        acc[1] += m0 * P[2 * c + 1];
        acc[2] += m1 * P[2 * c];
        acc[3] += m1 * P[2 * c + 1];
    }
    out[0] = acc[0];
    out[1] = acc[1];
    out[2] = acc[2];
    out[3] = acc[3];
}


void Fn8BA90(double* out, const long long* a2, const long long* a3) {
    alignas(16) unsigned char obj[0x100];
    std::memset(obj, 0, sizeof obj);
    *reinterpret_cast<unsigned long long*>(obj + 0x50) = 0;
    *reinterpret_cast<unsigned short*>(obj + 0x58) = 0;
    *reinterpret_cast<unsigned char*>(obj + 0x5a) = 0;
    *reinterpret_cast<unsigned int*>(obj + 0x5c) = 0;
    *reinterpret_cast<unsigned long long*>(obj + 0x68) = 0xFFFFFFFFFFFFFFFFull;
    *reinterpret_cast<unsigned long long*>(obj + 0x70) = 0xFFFFFFFFFFFFFFFFull;
    *reinterpret_cast<unsigned long long*>(obj + 0x78) = 0;

    double prod[4] = {0.0, 0.0, 0.0, 0.0};
    Fn7A0B0(prod, a2, a3);
    Fn87540(obj, prod, 20);

    const double* v = reinterpret_cast<const double*>(obj);
    const double* blkA = v + 0;
    const double* blkB = v + 4;
    const double* norm = v + 8;

    if (!(1e-19 >= norm[0])) {
        const double t16[2] = {blkA[0] * blkB[0] + blkA[2] * blkB[2],
                              blkA[0] * blkB[1] + blkA[2] * blkB[3]};
        const double t17[2] = {blkA[1] * blkB[0] + blkA[3] * blkB[2],
                              blkA[1] * blkB[1] + blkA[3] * blkB[3]};
        const double det = t17[1] * t16[0] - t17[0] * t16[1];
        if (DSign(det)) {
            out[0] = blkA[0] * blkB[0] - blkA[2] * blkB[2];
            out[1] = blkA[0] * blkB[1] - blkA[2] * blkB[3];
            out[2] = blkA[1] * blkB[0] - blkA[3] * blkB[2];
            out[3] = blkA[1] * blkB[1] - blkA[3] * blkB[3];
        } else {
            out[0] = t16[0];
            out[1] = t16[1];
            out[2] = t17[0];
            out[3] = t17[1];
        }
    } else {
        out[0] = 1.0;
        out[1] = 0.0;
        out[2] = 0.0;
        out[3] = 1.0;
    }
}


double NegateSign(double x) {
    unsigned long long b = 0;
    std::memcpy(&b, &x, 8);
    b ^= 0x8000000000000000ull;
    double y;
    std::memcpy(&y, &b, 8);
    return y;
}

}


extern "C" __declspec(noinline) long long sub_18008BCC0(double* a1, const void* a2,
                                                        const void* a3) {
    const unsigned char* p2 = reinterpret_cast<const unsigned char*>(a2);
    const unsigned char* p3 = reinterpret_cast<const unsigned char*>(a3);
    const long long* aux2 = reinterpret_cast<const long long*>(p2);
    const long long* aux3 = reinterpret_cast<const long long*>(p3);


    double r2[4] = {0.0, 0.0, 0.0, 0.0};
    Fn8BA90(r2, aux2, aux3);
    const double a = r2[0], b = r2[1], c = r2[2], d = r2[3];


    double q[2];
    double t[2];
    std::memcpy(q, p2 + 0x10, sizeof q);
    std::memcpy(t, p3 + 0x10, sizeof t);
    const double q0n = NegateSign(q[0]);
    const double q1n = NegateSign(q[1]);


    const double zero = 0.0;
    const double one = 1.0;
    const double u = (((q1n * c) + (q0n * a)) + zero * zero) + one * t[0];
    const double v = (((q1n * d) + (q0n * b)) + zero * zero) + one * t[1];



    const double m[16] = {a,  c,  0.0, u,
                          b,  d,  0.0, v,
                          0.0, 0.0, 1.0, 0.0,
                          0.0, 0.0, 0.0, 1.0};
    std::memcpy(a1, m, sizeof m);
    return reinterpret_cast<long long>(a1);
}
