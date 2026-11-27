






















#include <cstdint>
#include <cstring>

typedef std::int64_t i64;

extern "C" long long sub_180081DF0(long long a1, long long a2, long long a3, long long* a4);

extern "C" __declspec(noinline) long long sub_18007CBC0(long long* a1, long long* a2,
                                                        long long* a3)
{
    double* data = reinterpret_cast<double*>(a1[0]);
    const i64 ld = a1[2];
    const i64 n = a2[2];
    const i64 m = a2[1];
    double* base = reinterpret_cast<double*>(a2[0]);
    double* diag = reinterpret_cast<double*>(a3[0]);

    long long result = n;
    i64 count = 0;
    for (i64 k = n - 1; k >= 0; --k, ++count) {
        if (count > 0) {
            const i64 stride = *reinterpret_cast<i64*>(a2[3] + 8);
            const i64 v13 = n - count;
            long long A[13];
            long long U[26];
            long long V[13];
            std::memset(A, 0, sizeof A);
            std::memset(U, 0, sizeof U);
            std::memset(V, 0, sizeof V);
            double* dst = data + (k * ld + ld - count);
            A[0] = reinterpret_cast<long long>(dst);
            i64 bits;
            std::memcpy(&bits, &diag[k], 8);
            bits ^= static_cast<i64>(0x8000000000000000ull);
            U[3] = bits;
            U[4] = reinterpret_cast<long long>(base + (k * stride + k + 1));
            U[5] = m - k - 1;
            V[0] = reinterpret_cast<long long>(base + (stride * v13 + k + 1));
            V[1] = m - k - 1;
            V[2] = count;
            V[6] = a2[3];

            for (i64 i = 0; i < count; ++i) dst[i] = 0.0;
            long long one;
            const double kOne = 1.0;
            std::memcpy(&one, &kOne, 8);
            sub_180081DF0(reinterpret_cast<long long>(A), reinterpret_cast<long long>(U),
                          reinterpret_cast<long long>(V), &one);
            i64 c = 0;
            for (i64 col = n - 1; col > k; --col, ++c) {
                const i64 idx = k * ld + col;
                const double t = data[idx];
                data[idx] = t * data[col * (ld + 1)];
                if (c > 0) {
                    double* d = data + (ld - c + k * ld);
                    const double* s = data + (ld - c + col * ld);
                    for (i64 i = 0; i < c; ++i) d[i] += t * s[i];
                }
            }
        }
        std::memcpy(&result, &diag[k], 8);
        data[k * (ld + 1)] = diag[k];
    }
    return result;
}
