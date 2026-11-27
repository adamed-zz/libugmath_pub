


















#include <cstdint>

extern "C" __int64 __fastcall sub_180084F30(__int64 a1, __int64 a2, __int64* a3, __int64 cols,
                                            __int64 rows) {
    (void)a1;
    const double* src = reinterpret_cast<const double*>(a3[0]);
    const __int64 stride = a3[1];
    double* dst = reinterpret_cast<double*>(a2);

    __int64 v6 = 0;
    __int64 r = 0;
    __int64 result = rows;
    const __int64 v8 = (((rows >> 63) & 3) + rows) & ~static_cast<__int64>(3);


    if (((rows >> 63) & 3) + rows >= 0 && v8 != 0) {
        for (; r < v8; r += 4) {
            for (__int64 c = 0; c < cols; ++c) {
                const double* s = src + r * stride + c;
                dst[v6] = s[0];
                dst[v6 + 1] = s[stride];
                dst[v6 + 2] = s[2 * stride];
                dst[v6 + 3] = s[3 * stride];
                v6 += 4;
            }
            result = r + 4;
        }
    }


    for (; r < rows; ++r) {
        result = reinterpret_cast<__int64>(src + stride * r);
        for (__int64 c = 0; c < cols; ++c) dst[v6++] = src[r * stride + c];
    }
    return result;
}
