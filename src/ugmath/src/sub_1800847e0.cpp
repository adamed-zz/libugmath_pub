


























#include <cstdint>

extern "C" __int64 __fastcall sub_1800847E0(__int64 a1, __int64 a2, __int64* a3, __int64 cols,
                                            __int64 rows) {
    (void)a1;
    const double* src = reinterpret_cast<const double*>(a3[0]);
    const __int64 stride = a3[1];
    double* dst = reinterpret_cast<double*>(a2);

    __int64 d = 0;
    __int64 rb = 0;


    for (int pass = 0; pass < 2; ++pass) {
        const __int64 blk = (pass == 0) ? 4 : 2;
        const __int64 rem = rows - rb;
        const __int64 end = rb + (rem - rem % blk);
        for (; rb < end; rb += blk) {
            __int64 c = 0;
            const __int64 c2 = 2 * (cols / 2);
            for (; c < c2; c += 2) {
                for (__int64 t = 0; t < blk; t += 2) {

                    dst[d + t] = src[(rb + t) * stride + c];
                    dst[d + t + 1] = src[(rb + t + 1) * stride + c];
                    dst[d + blk + t] = src[(rb + t) * stride + c + 1];
                    dst[d + blk + t + 1] = src[(rb + t + 1) * stride + c + 1];
                }
                d += 2 * blk;
            }
            if (c < cols) {
                for (__int64 t = 0; t < blk; ++t) dst[d + t] = src[(rb + t) * stride + c];
                d += blk;
            }
        }
    }


    for (; rb < rows; ++rb) {
        for (__int64 c = 0; c < cols; ++c) dst[d++] = src[rb * stride + c];
    }
    return rows;
}
