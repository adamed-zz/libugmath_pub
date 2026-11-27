








#include <cstdint>

typedef std::int64_t i64;
typedef std::uint64_t u64;



static i64 g_lo;
static i64 g_mid;
static i64 g_hi;

extern "C" void sub_18007B930_set_state(i64 lo, i64 mid, i64 hi) {
    g_lo = lo;
    g_mid = mid;
    g_hi = hi;
}

extern "C" __declspec(noinline) i64 sub_18007B930(i64* a1, i64* a2, i64* a3, i64 a4) {
    const i64 v8 = g_lo;
    const i64 v9 = g_mid;
    const i64 v10 = g_hi;
    i64 result;
    if (a4 <= 1) {
        i64 v23 = *a2;
        i64 v24 = *a3;
        i64 v25 = *a2;
        i64 v26 = *a1;
        result = *a1;
        if (*a2 < *a3) v25 = *a3;
        if (v26 < v25) result = v25;
        if (result >= 48) {
            i64 v27 = *a1;
            i64 v28 = ((v8 - 128) / 256) & 0xFFFFFFFFFFFFFFF8LL;
            if (v28 < 1) v28 = 1;
            if (v26 > v28) {
                v27 = v28;
                if (v26 % v28) v27 = v28 - 8 * ((v28 - v26 % v28 - 1) / (8 * (v26 / v28) + 8));
                *a1 = v27;
                v23 = *a2;
                v24 = *a3;
            }
            i64 v29 = 8 * v27 * v23 + 128;
            u64 v30;
            if (v8 - v29 < 32 * v27)
                v30 = 0x480000uLL / (u64)(32 * v28);
            else
                v30 = (u64)(v8 - v29) / (u64)(8 * v27);
            i64 v31 = (i64)v30;
            u64 v32 = 1572864;
            result = (i64)(0x180000uLL / (u64)(16 * v27));
            i64 v33 = result;
            if (v31 < result) v33 = v31;
            i64 v34 = v33 & 0xFFFFFFFFFFFFFFFCLL;
            if (v24 <= v34) {
                if (v26 != v27) return result;
                i64 v35 = v23;
                i64 v36 = 8 * v27 * v24;
                if (v36 > 1024) {
                    if (v10) {
                        if (v36 <= 0x8000) {
                            v35 = 576;
                            v32 = (u64)v9;
                            if (v23 < 576) v35 = v23;
                        }
                    }
                } else {
                    v32 = (u64)v8;
                }
                result = (i64)(v32 / (u64)(24 * v27));
                i64 v37 = result;
                if (v35 < result) v37 = v35;
                if (v37 <= 4) {
                    if (!v37) return result;
                } else {
                    v37 -= v37 % 4;
                }
                result = v23 / v37;
                if (v23 % v37) {
                    result = 4 * ((v37 - v23 % v37) / (4 * (v23 / v37) + 4));
                    v37 -= result;
                }
                *a2 = v37;
            } else {
                result = v24 / v34;
                if (v24 % v34) {
                    result = 4 * ((v34 - v24 % v34) / (4 * (v24 / v34) + 4));
                    v34 -= result;
                }
                *a3 = v34;
            }
        }
    } else {
        i64 v11 = 8;
        i64 v12 = (v8 - 128) / 256;
        if (v12 > 320) v12 = 320;
        i64 v13 = *a1;
        if (v12 > 8) v11 = v12;
        if (v11 < v13) {
            v13 = v11 - v11 % 8;
            *a1 = v13;
        }
        i64 v14 = (i64)((u64)(v9 - v8) / (u64)(32 * v13));
        i64 v15 = (*a3 + a4 - 1) / a4;
        i64 v17;
        if (v14 > v15) {
            v17 = *a3;
            i64 v18 = v15 - (v15 + 3) % 4;
            result = v18 + 3;
            if (v18 + 3 < *a3) v17 = v18 + 3;
        } else {
            result = v14 % 4;
            v17 = v14 - v14 % 4;
        }
        *a3 = v17;
        if (v10 > v9) {
            i64 v19 = *a2;
            i64 v20 = (i64)((u64)(v10 - v9) / (u64)(8 * *a1 * a4));
            i64 v21 = (*a2 + a4 - 1) / a4;
            if (v20 >= v21 || v20 < 4) {
                i64 v22 = v21 - (v21 + 3) % 4;
                result = v22 + 3;
                if (v22 + 3 < *a2) v19 = v22 + 3;
            } else {
                result = v20 % 4;
                v19 = v20 - v20 % 4;
            }
            *a2 = v19;
        }
    }
    return result;
}
