









#include <cstdlib>
#include <cstring>
#include <emmintrin.h>

extern "C" long long sub_18007B550(long long* dims, const long long* shape,
                                   const long long* shape_hi, long long flag);

extern "C" long long sub_18008D340(long long, long long, long long, const double*, long long,
                                   const double*, long long, double*, long long, long long, ...);

extern "C" void sub_18007A0B0(double* out, const long long* a2, const long long* a3) {
    const double* p = reinterpret_cast<const double*>(a2[0]);
    const long long n = a2[1];
    const long long* desc = reinterpret_cast<const long long*>(a3[0]);
    const double* m = reinterpret_cast<const double*>(desc[0]);
    const long long rows = desc[1];

    if (rows + 4 < 20 && rows > 0) {
        for (int i = 0; i < 2; ++i) {
            __m128d acc = _mm_setzero_pd();
            for (long long q = 0; q < n; ++q) {
                __m128d v = _mm_loadu_pd(p + 2 * q);
                acc = _mm_add_pd(acc, _mm_mul_pd(_mm_set1_pd(m[i + 2 * q]), v));
            }
            _mm_storeu_pd(out + 2 * i, acc);
        }
        return;
    }

    for (int i = 0; i < 4; ++i) reinterpret_cast<long long*>(out)[i] = 0;
    if (n == 0) return;

    long long shape[2] = {2, 2};
    long long dims[3] = {n, 0, 0};
    sub_18007B550(dims, shape, shape + 1, 1);
    dims[1] = dims[0] * shape[0];
    dims[2] = dims[0] * shape[1];

    void* ws[2] = {nullptr, nullptr};
    sub_18008D340(2, 2, n, p, 2, m, 2, out, 1, 2, 1.0, ws, 0);
    std::free(ws[0]);
    std::free(ws[1]);
}
