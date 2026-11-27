













#include <cstdint>

extern "C" __int64 __fastcall sub_180084BC0(__int64 a1, __int64 a2, __int64* a3, __int64 cols,
                                            __int64 rows) {
    (void)a1;
    const double* src = reinterpret_cast<const double*>(a3[0]);
    const __int64 stride = a3[1];
    double* dst = reinterpret_cast<double*>(a2);

    __int64 v6 = 0;
    __int64 v9 = 0;

    const __int64 v8 = (((rows >> 63) & 3) + rows) & ~static_cast<__int64>(3);
    const __int64 v11 = v8 + 2 * ((rows % 4) / 2);


    if (((rows >> 63) & 3) + rows >= 0 && v8 != 0) {
        do {
            for (__int64 i = 0; i < cols; ++i) {
                const double* s = src + v9 + stride * i;
                dst[v6] = s[0];
                dst[v6 + 1] = s[1];
                dst[v6 + 2] = s[2];
                dst[v6 + 3] = s[3];
                v6 += 4;
            }
            v9 += 4;
        } while (v9 < v8);
    }


    for (; v9 < v11; v9 += 2) {
        for (__int64 j = 0; j < cols; v6 += 2) {
            const double* s = src + v9 + stride * j;
            dst[v6] = s[0];
            dst[v6 + 1] = s[1];
            ++j;
        }
    }


    for (; v9 < rows; ++v9) {
        for (__int64 j = 0; j < cols; ++v6) {
            dst[v6] = src[v9 + stride * j];
            ++j;
        }
    }


    if (rows > 0 && cols > 0) return reinterpret_cast<__int64>(src);
    return (rows % 4) / 2;
}
