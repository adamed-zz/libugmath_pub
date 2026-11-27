






#include <cstdlib>
#include <cstring>

extern "C" long long sub_1800743E0(long long* a, long long* b, long long c, long long d);
extern "C" long long sub_180079470(long long* a, long long* b, long long* c, unsigned char flag);
extern "C" void* sub_180079AB0(long long n);

extern "C" long long sub_1800786B0(const long long* a1, const long long* a2, long long* a3, char a4) {
    long long result = 0;
    const char* base = reinterpret_cast<const char*>(a1);
    char v5 = a4;
    if (a4 && base[16]) v5 = 0;
    long long cnt = a1[3];
    long long v62 = 0;

    if (cnt < 48 || a2[2] <= 1) {
        long long v32 = a2[2];
        if (v32 != a3[1]) {
            std::free(reinterpret_cast<void*>(a3[0]));
            if (v32 <= 0) {
                a3[0] = 0;
            } else {
                a3[0] = reinterpret_cast<long long>(sub_180079AB0(v32));
            }
        }
        a3[1] = v32;
        long long v4 = 0;
        while (a1[3] > 0 && v4 < a1[3]) {
            const long long* m0 = reinterpret_cast<const long long*>(a1[0]);
            long long row = a1[3] - v4 - 1;
            if (base[16]) row = v4;
            long long a2ld = a2[1];
            long long acols = a2[2];
            long long m0ld = m0[1];
            long long dimA = m0ld - a1[4] - row;
            long long adim = v5 ? dimA : acols;
            long long col = a1[4] + row + 1;
            long long ws = a3[0];

            long long a[7];
            a[0] = a2[0] + 8 * (a2ld - dimA + (acols - adim) * a2ld);
            a[1] = dimA;
            a[2] = adim;
            a[3] = (long long)a2;
            a[4] = a2ld - dimA;
            a[5] = acols - adim;
            a[6] = a2ld;

            long long b[7];
            b[0] = m0[0] + 8 * (col + row * m0ld);
            b[1] = m0ld - col;
            b[2] = 0;
            b[3] = a1[0];
            b[4] = col;
            b[5] = row;
            b[6] = m0ld;
            result = sub_1800743E0(a, b, a1[1] + 8 * row, ws);
            v4 = v62 + 1;
            v62 = v4;
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
        const long long* m0 = reinterpret_cast<const long long*>(a1[0]);
        long long v16 = cnt - v13;
        long long m0ld = m0[1];
        long long m0data = m0[0];
        long long v19 = a2[1] - m0ld;
        long long v20 = m0ld - v14 - v13;
        long long v21 = v13 + v14 + v19;
        long long v22 = v5 ? v20 : a2[2];
        long long v25 = v5 ? v21 : 0;
        long long aptr = a2[0] + 8 * (v21 + v25 * a2[1]);
        long long bptr = m0data + 8 * (v14 + v13 + v13 * m0ld);

        long long a[7];
        a[0] = aptr;
        a[1] = v20;
        a[2] = v22;
        a[3] = (long long)a2;
        a[4] = v21;
        a[5] = v25;
        a[6] = a2[1];
        long long b[7];
        b[0] = bptr;
        b[1] = m0ld - (v14 + v13);
        b[2] = v16;
        b[3] = a1[0];
        b[4] = v14 + v13;
        b[5] = v13;
        b[6] = m0ld;
        long long c[7];
        c[0] = a1[1] + 8 * v13;
        c[1] = v16;
        c[2] = 0;
        c[3] = a1[1];
        c[4] = v13;
        c[5] = 0;
        c[6] = *reinterpret_cast<const long long*>(a1[1] + 24);
        result = sub_180079470(a, b, c, base[16] == 0);
        cnt = a1[3];
    } while (v12 < cnt);
    return result;
}
