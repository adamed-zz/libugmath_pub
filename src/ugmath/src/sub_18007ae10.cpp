







#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <cstdint>
#include <cstdlib>

extern "C" void sub_1800743E0(const long long* a1, const long long* a2,
                              const double* a3, long long a4);
extern "C" void sub_1800778F0(const long long* a1, const long long* a2,
                              const double* a3, long long a4);
extern "C" void sub_1800935F0(long long* view);
extern "C" void sub_180093FC0();
extern "C" void* sub_180079AB0(long long n);
extern "C" void sub_18008CF30(long long* a1, long long a2, long long a3, long long a4);
extern "C" void sub_1800786B0(long long* a1, long long* a2, long long* a3, char a4);
extern "C" void sub_180080DE0(const long long* view, long long start, long long end);


__forceinline void FillIdentity(long long* a2) {
    long long n0 = a2[1];
    long long rows = a2[2];
    char* row = (char*)a2[0];
    long long r = 0;
    if (rows > 0) {
        do {
            long long c = 0;
            long long n = a2[1];
            if (n > 0) {
                char* p = row;
                do {
                    *(long long*)p = (c == r) ? 0x3FF0000000000000LL : 0LL;
                    ++c;
                    n = a2[1];
                    p += 8;
                } while (c < n);
            }
            ++r;
            row += 8 * n0;
        } while (r < rows);
    }
}


__forceinline void ClearRow(long long* a2, long long i, long long* zeroSlot, long long* dummy) {
    long long n = a2[1];
    long long len = n - i - 1;
    long long p = (long long)((char*)a2[0] + 8 * i * n + 8 * (i + 1));
    long long h = len;
    if ((p & 7) == 0) {
        long long par = (-(long long)((unsigned long long)p >> 3)) & 1;
        if (par < len) h = par;
    }
    long long mid = h + 2 * ((len - h) / 2);
    long long view[4];
    long long dst = p;
    *zeroSlot = 0;
    view[0] = (long long)&dst;
    view[1] = (long long)zeroSlot;
    view[2] = (long long)dummy;
    view[3] = 0;
    sub_180080DE0(view, 0, h);

    for (long long j = h; j < mid; j += 2) {
        *(long long*)((char*)dst + 8 * j) = *zeroSlot;
        *(long long*)((char*)dst + 8 * (j + 1)) = *zeroSlot;
    }
    sub_180080DE0(view, mid, len);
}



__forceinline void LoopBody(long long* a1, long long* a2, long long* a3, long long i,
                     long long* zeroSlot, long long* dummy, bool clearRow) {
    long long n = a2[1];
    long long nrows = a2[2];
    long long* m = (long long*)a1[0];
    long long off = a1[4];
    long long v25 = n - off - i;
    long long d1[7];
    long long d2[7];
    d1[0] = (long long)((char*)(uintptr_t)a2[0] + 8 * ((n - v25) + (nrows - v25) * n));
    d1[1] = v25;
    d1[2] = v25;
    d1[3] = (long long)a2;
    d1[4] = n - v25;
    d1[5] = nrows - v25;
    d1[6] = n;
    d2[0] = (long long)((char*)(uintptr_t)m[0] + 8 * (i * n + i + off + 1));
    d2[1] = n - (i + off + 1);
    d2[2] = 0;
    d2[3] = (long long)m;
    d2[4] = i + off + 1;
    d2[5] = i;
    d2[6] = n;
    const double* x = (const double*)(a1[1] + 8 * i);
    if (*(unsigned char*)((char*)a1 + 16) == 0)
        sub_1800743E0(d1, d2, x, a3[0]);
    else
        sub_1800778F0(d1, d2, x, a3[0]);
    if (clearRow) ClearRow(a2, i, zeroSlot, dummy);
}

extern "C" void sub_18007AE10(long long* a1, long long* a2, long long* a3) {
    long long* m = (long long*)a1[0];
    long long n = m[1];
    if (n != a3[1]) {
        free((void*)a3[0]);
        if (n <= 0)
            a3[0] = 0;
        else
            a3[0] = (long long)sub_180079AB0(n);
    }
    a3[1] = n;
    long long k = a1[3];
    long long zeroSlot = 0;
    long long dummy = 0;
    if (a2[0] == m[0] && a2[1] == m[1]) {

        long long cnt = a2[2] < n ? a2[2] : n;
        long long idx = 0;
        if (cnt >= 4) {
            char* p = (char*)a2[0] + 16 + 16 * n;
            long long rep = ((cnt - 4) >> 2) + 1;
            idx = 4 * rep;
            do {
                *(long long*)(p - 16 - 16 * n) = 0x3FF0000000000000LL;
                *(long long*)(p - 8 - 8 * n) = 0x3FF0000000000000LL;
                *(long long*)p = 0x3FF0000000000000LL;
                *(long long*)(p + 8 * (n + 1)) = 0x3FF0000000000000LL;
                p += 8 * (4 * n + 4);
            } while (--rep);
        }
        if (idx < cnt) {
            char* p = (char*)a2[0] + 8 * (idx * (n + 1));
            long long rep = cnt - idx;
            do {
                *(long long*)p = 0x3FF0000000000000LL;
                p += 8 * (n + 1);
            } while (--rep);
        }
        long long w0[2];
        long long* ap = a2;
        long long view[4];
        w0[0] = a2[0];
        w0[1] = a2[1];
        view[0] = (long long)w0;
        view[1] = (long long)&zeroSlot;
        view[2] = (long long)&dummy;
        view[3] = (long long)&ap;
        sub_1800935F0(view);
        for (long long i = k - 1; i >= 0; --i)
            LoopBody(a1, a2, a3, i, &zeroSlot, &dummy, true);
        long long n2 = m[1];
        long long rest = n2 - k;
        for (long long i = 0; i < rest; ++i)
            ClearRow(a2, i, &zeroSlot, &dummy);
        return;
    }

    long long nn = m[1];
    if (k > 48) {
        if (nn != 0 && nn > 0x7FFFFFFFFFFFFFFFLL / nn)
            sub_180093FC0();
        sub_18008CF30(a2, nn * nn, nn, nn);
        FillIdentity(a2);
        sub_1800786B0(a1, a2, a3, 1);
        return;
    }
    if (nn != 0 && nn > 0x7FFFFFFFFFFFFFFFLL / nn)
        sub_180093FC0();
    sub_18008CF30(a2, nn * nn, nn, nn);
    FillIdentity(a2);
    for (long long i = k - 1; i >= 0; --i)
        LoopBody(a1, a2, a3, i, &zeroSlot, &dummy, false);
}
