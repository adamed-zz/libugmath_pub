









#include <cstring>

extern "C" long long sub_180073910(long long* a, long long* b, long long c, long long d);
extern "C" long long sub_180078E80(long long* a, long long* b, long long* c, unsigned char flag);

extern "C" long long sub_180078420(const long long* a1, long long a2, long long a3, char a4) {
    long long result = 0;
    const char* base = reinterpret_cast<const char*>(a1);
    char v5 = a4;
    if (a4 && base[16]) v5 = 0;
    long long cnt = a1[3];
    const long long* m0desc = reinterpret_cast<const long long*>(a1[0]);
    const long long m0data = m0desc[0];

    if (cnt < 48) {
        for (long long i = 0; i < cnt; ++i) {
            long long v23 = a1[4];
            long long v24 = cnt - i - 1;
            if (base[16]) v24 = i;
            long long a[7];
            long long b[7];
            long long v26 = 3;
            a[3] = a2;
            a[6] = 3;
            b[6] = 3;
            b[5] = v24;
            a[1] = 3 - v23 - v24;
            if (v5) v26 = 3 - v23 - v24;
            a[4] = v24 + v23;
            a[5] = 3 - v26;
            a[2] = v26;
            b[3] = a1[0];
            b[4] = v24 + v23 + 1;
            a[0] = a2 + 8 * (9 + v23 + v24 - 3 * v26);
            b[0] = m0data + 8 * (4 * v24 + v23 + 1);
            b[1] = 3 - v24 - v23 - 1;
            b[2] = 0;
            result = sub_180073910(a, b, a1[1] + 8 * v24, a3);
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
        long long v36 = cnt - v13;
        long long v15 = v14 + v13;
        long long v18 = 3 - v14 - v13;
        long long v19 = 0;
        long long v20 = 3;
        if (v5) {
            v19 = v15;
            v20 = 3 - v14 - v13;
        }

        long long a[7];
        long long b[7];
        long long c[3];
        a[0] = a2 + 8 * (v15 + 3 * v19);
        a[1] = v18;
        a[2] = v20;
        a[3] = a2;
        a[4] = v15;
        a[5] = v19;
        a[6] = 3;
        b[0] = m0data + 8 * (v14 + 4 * v13);
        b[1] = 3 - v15;
        b[2] = v36;
        b[3] = a1[0];
        b[4] = v15;
        b[5] = v13;
        b[6] = 3;
        c[0] = a1[1] + 8 * v13;
        c[1] = v36;
        c[2] = *reinterpret_cast<const long long*>(a1[1] + 24);
        result = sub_180078E80(a, b, c, base[16] == 0);
        cnt = a1[3];
    } while (v12 < cnt);
    return result;
}
