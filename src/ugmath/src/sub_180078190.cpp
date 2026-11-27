








#include <cstring>

extern "C" long long sub_180073910(long long* a, long long* b, long long c, long long d);
extern "C" long long sub_1800789B0(long long* a, long long* b, long long* c, unsigned char flag,
                                   long long p5, long long p6, long long p7, long long p8,
                                   long long p9, long long p10, long long p11);

extern "C" long long sub_180078190(const long long* a1, long long a2, long long a3, char a4) {
    long long result = 0;
    const char* base = reinterpret_cast<const char*>(a1);
    char v5 = a4;
    if (a4 && base[16]) v5 = 0;
    long long cnt = a1[3];

    if (cnt < 48) {
        for (long long i = 0; i < cnt; ++i) {
            long long v21 = a1[4];
            long long v22 = cnt - i - 1;
            if (base[16]) v22 = i;
            long long a[7] = {0, 0, 0, 0, 0, 0, 0};
            long long b[7] = {0, 0, 0, 0, 0, 0, 0};
            a[3] = a2;
            a[6] = 3;
            b[6] = 3;
            b[5] = v22;
            long long v24 = 3;
            a[1] = 3 - v21 - v22;
            if (v5) v24 = 3 - v21 - v22;
            a[4] = v22 + v21;
            a[5] = 3 - v24;
            a[2] = v24;
            b[3] = a1[0];
            b[4] = v22 + v21 + 1;
            a[0] = a2 + 8 * (9 + v21 + v22 - 3 * v24);
            b[0] = a1[0] + 8 * (4 * v22 + v21 + 1);
            b[1] = 3 - v22 - v21 - 1;
            result = sub_180073910(a, b, a1[1] + 8 * v22, a3);
            cnt = a1[3];
        }
        return result;
    }

    long long v10;
    if (cnt >= 96) {
        v10 = 48;
    } else {
        v10 = (cnt + 1) / 2;
    }
    long long v11 = v10;
    long long v12 = 0;
    do {
        long long v13;
        if (base[16]) {
            v13 = v12;
            if (v11 + v12 < cnt) cnt = v11 + v12;
        } else {
            cnt -= v12;
            v13 = 0;
            if (cnt - v10 > 0) v13 = cnt - v10;
        }
        long long v14 = a1[4];
        v12 += v11;
        long long v35 = a1[0];
        long long v34 = cnt - v13;
        long long v15 = v14 + v13;
        long long v16 = 3 - v14 - v13;
        long long v17 = v14 + 4 * v13;
        long long v19 = v5 ? v15 : 0;
        long long v18 = v5 ? v16 : 3;

        long long a[7];
        long long b[7];
        long long c[3] = {0, 0, 0};
        a[0] = a2 + 8 * (v15 + 3 * v19);
        a[1] = v16;
        a[2] = v18;
        a[3] = a2;
        a[4] = v15;
        a[5] = v19;
        a[6] = 3;
        b[0] = v35 + 8 * v17;
        b[1] = 3 - v15;
        b[2] = v34;
        b[3] = v35;
        b[4] = v15;
        b[5] = v13;
        b[6] = 3;
        c[0] = a1[1] + 8 * v13;
        c[1] = v34;

        result = sub_1800789B0(a, b, c, base[16] == 0, a[0], v16, v18, a2, v15, v19, 3);
        cnt = a1[3];
    } while (v12 < cnt);
    return result;
}
