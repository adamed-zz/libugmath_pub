










#include <cstdint>
#include <cstdlib>
#include <cstring>

typedef std::int64_t i64;
typedef std::uint64_t u64;

extern "C" __declspec(noinline) i64 sub_18007D300(i64* a1, u64* a2, i64* a3) {
    double* factors = reinterpret_cast<double*>(a3[0]);
    const i64 n = static_cast<i64>(a2[6]);
    double* src = reinterpret_cast<double*>(a2[5]);
    double scale;
    std::memcpy(&scale, &a2[4], 8);

    (void)*reinterpret_cast<volatile i64*>(reinterpret_cast<char*>(a2) + 0x40);

    double* buf = static_cast<double*>(std::malloc(static_cast<std::size_t>(8 * n)));
    if (buf == nullptr && n != 0) std::abort();

    const i64 v14 = 2 * (n / 2);
    for (i64 i = 0; i < v14; i += 2) {
        buf[i] = scale * src[i];
        buf[i + 1] = scale * src[i + 1];
    }
    if (v14 < n) buf[v14] = scale * src[v14];

    double* data = reinterpret_cast<double*>(a1[0]);
    const i64 len = a1[1];
    const i64 rows = a1[2];
    const i64 stride = *reinterpret_cast<i64*>(a1[6] + 8);
    for (i64 r = 0; r < rows; ++r) {
        double* row = data + r * stride;
        const double f = factors[r];
        i64 first = len;
        if ((reinterpret_cast<u64>(row) & 7) == 0) {
            const i64 pre =
                static_cast<i64>((-static_cast<int>(reinterpret_cast<u64>(row) >> 3)) & 1);
            if (pre < len) first = pre;
        }
        for (i64 i = 0; i < first; ++i) row[i] -= f * buf[i];
        const i64 mid = first + 2 * ((len - first) / 2);
        for (i64 i = first; i < mid; i += 2) {
            row[i] -= f * buf[i];
            row[i + 1] -= f * buf[i + 1];
        }
        for (i64 i = mid; i < len; ++i) row[i] -= f * buf[i];
    }
    std::free(buf);
    return 0;
}
