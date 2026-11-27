
























#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <bit>
#include <cmath>
#include <cstdint>

extern "C" double sub_1800AAC40(int n, const double* values, double* sum_out,
                                double* accum);



extern "C" double g_ugm_solve_cubic_flag;

namespace {

constexpr double kTolHi = std::bit_cast<double>(uint64_t(0x3D3C25C268497682ull));
constexpr double kTolLo = std::bit_cast<double>(uint64_t(0x3CC203AF9EE75616ull));
constexpr double kTwoPi = std::bit_cast<double>(uint64_t(0x401921FB54442D18ull));
constexpr double kFourPi = std::bit_cast<double>(uint64_t(0x402921FB54442D18ull));
constexpr double kThird = std::bit_cast<double>(uint64_t(0x3FD5555555555555ull));

inline int MagBin(double a) {
    if (a > 100000.0) return 3;
    if (a > 1.0) return 2;
    return (a > 0.00001) ? 1 : 0;
}

inline int Half(double v) { return (v > 0.0) ? 0 : 1; }


inline double Fold(const double* b) {
    double s = b[1] + b[0];
    s = s + 0.0;
    s = s + (b[3] + b[2]);
    s = s + (b[5] + b[4]);
    s = s + (b[7] + b[6]);
    return s;
}

}

extern "C" int sub_1800ABB60(const double* a1, double* a2) {
    const double A = a1[2] / a1[3];
    const double C = a1[0] / a1[3];
    const double B = a1[1] / a1[3];
    const double h = A / 3.0;
    const double g = g_ugm_solve_cubic_flag;
    const double tol = (g > 0.0) ? kTolHi : kTolLo;
    const double v9 = A * A;
    const double v11 = B * -3.0;

    double bins[8] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

    const double absA2 = fabs(v9);
    int lvl = MagBin(absA2);
    double sumA = absA2 + 0.0;
    double bucket;
    bucket = bins[2 * lvl + Half(v9)] + v9;
    bins[2 * lvl + Half(v9)] = bucket;

    const double abs3B = fabs(v11);
    lvl = MagBin(abs3B);
    sumA = sumA + abs3B;
    bucket = bins[2 * lvl + Half(v11)] + v11;
    bins[2 * lvl + Half(v11)] = bucket;

    const double v23 = sumA + 0.0;
    const double v25 = sumA + g;
    const double c27 = C * 27.0;
    const double v71a = v23;

    const double v26 = (A + A) * v9;
    const double v27 = (A * -9.0) * B;
    const double foldA = Fold(bins);
    for (int i = 0; i < 8; ++i) bins[i] = 0.0;

    const double abs26 = fabs(v26);
    lvl = MagBin(abs26);
    double sumB = abs26 + 0.0;
    bucket = bins[2 * lvl + Half(v26)] + v26;
    bins[2 * lvl + Half(v26)] = bucket;

    const double abs27 = fabs(v27);
    lvl = MagBin(abs27);
    sumB = sumB + abs27;
    bucket = bins[2 * lvl + Half(v27)] + v27;
    bins[2 * lvl + Half(v27)] = bucket;

    const double absC27 = fabs(c27);
    lvl = MagBin(absC27);
    sumB = sumB + absC27;
    bucket = bins[2 * lvl + Half(c27)] + c27;
    bins[2 * lvl + Half(c27)] = bucket;

    const double foldB = Fold(bins);
    const double v70a = sumB + v71a;


    double q[5];
    q[0] = (v9 * B) * B;
    q[1] = ((B * -4.0) * B) * B;
    q[2] = (C * -27.0) * C;
    q[3] = ((v9 * -4.0) * A) * C;
    q[4] = ((A * 18.0) * B) * C;
    double sumQ = 0.0;
    double scale = v70a;
    const double ret = sub_1800AAC40(5, q, &sumQ, &scale);



    if (!(v25 * tol >= fabs(foldA)) ||
        !((sumB + g_ugm_solve_cubic_flag) * tol >= fabs(foldB))) {
        if (ret > 0.0 && foldA > 0.0) {
            const double ff = foldA / 9.0;
            const double qq = foldB / 54.0;
            double t = (ff * ff) * ff;
            const double sq = sqrt(t);
            const double aq = fabs(qq);
            double arg;
            if (sq > aq) {
                arg = qq / sq;
            } else {
                arg = (qq > 0.0) ? 1.0 : -1.0;
            }
            const double th = acos(arg);
            const double amp = sqrt(ff) * -2.0;
            a2[0] = cos(th / 3.0) * amp - h;
            a2[1] = cos((th + kTwoPi) / 3.0) * amp - h;
            a2[2] = cos((th + kFourPi) / 3.0) * amp - h;
            return 3;
        }
        const double t3 = (g_ugm_solve_cubic_flag * 2.5 + sumQ) * tol;
        const double absRet = fabs(ret);
        if (!(t3 >= absRet)) {
            const double a108 = absRet / 108.0;
            const double qq = foldB / 54.0;
            const double ff = foldA / 9.0;
            const double p = pow(sqrt(a108) + fabs(qq), kThird);
            double res = ff / p + p;
            if (qq > 0.0) res = -res;
            a2[0] = res - h;
            return 1;
        }
        const double sv = sqrt(fabs(foldA) / 9.0);
        const double sign = (foldB > 0.0) ? 1.0 : -1.0;
        const double s = sv * sign;
        a2[0] = s * -2.0 - h;
        a2[1] = s - h;
        a2[2] = s - h;
        return 3;
    }


    const double nh = -h;
    a2[0] = nh;
    a2[1] = nh;
    a2[2] = nh;
    return 3;
}
