















#include <cstdint>

extern "C" void sub_180073910(const long long* d1, const long long* d2, const double* p,
                              long long a3);
extern "C" void sub_180076EA0(const long long* d1, const long long* d2, const double* p,
                              long long a3);
extern "C" void sub_180080DE0(const long long* view, long long start, long long end);
extern "C" void sub_180078190(const long long* a1, long long* a2, long long a3, long long one);

namespace {

const long long kOne = 0x3FF0000000000000LL;

struct Oword {
    long long lo;
    long long hi;
};



struct FillView {
    long long f0;
    long long f1;
    long long f2;
    long long f3;
    long long f4;
    long long f5;
    long long f6;
};



__forceinline void ZeroFill(long long target, long long count, long long row) {
    long long value = 0;
    long long slotA = 3;
    long long slotB[2];
    slotB[0] = 0;
    slotB[1] = 3;
    FillView view;
    view.f0 = (long long)&target;
    view.f1 = (long long)&value;
    view.f2 = (long long)&slotA;
    view.f3 = (long long)&slotB[0];
    view.f4 = row;
    view.f5 = 3;
    view.f6 = 3;
    long long v18 = count;
    if ((target & 7) == 0) {
        unsigned par = (unsigned)(-(int)(target >> 3)) & 1u;
        long long p = (long long)par;
        if (p < count) v18 = p;
    }
    long long v21 = v18 + 2 * ((count - v18) / 2);
    sub_180080DE0((const long long*)&view, 0, v18);
    for (long long i = v18; i < v21; i += 2) {
        Oword z;
        z.lo = 0;
        z.hi = 0;
        *(Oword*)(target + 8 * i) = z;
    }
    sub_180080DE0((const long long*)&view, v21, count);
}

}

extern "C" void sub_18007A340(const long long* a1, long long* a2, long long a3) {
    long long v4 = a1[3];
    long long k = a1[4];

    a2[0] = kOne;

    if (a2 == (long long*)a1[0]) {
        a2[4] = kOne;
        a2[8] = kOne;
        a2[3] = 0;
        a2[6] = 0;
        a2[7] = 0;

        if (v4 - 1 >= 0) {
            long long v8 = v4 - 1;
            long long v12 = 2 - v8;
            long long* rowPtr = (long long*)a2 + 3 * v8;
            long long rowOff = 8 * v8 + 8;
            do {
                long long d1[7];
                long long d2[7];
                d1[0] = (long long)&a2[4 * (v8 + k)];
                d1[1] = 3 - k - v8;
                d1[2] = 3 - k - v8;
                d1[3] = (long long)a2;
                d1[4] = v8 + k;
                d1[5] = v8 + k;
                d1[6] = 3;
                d2[0] = (long long)((char*)a1[0] + 8 * (3 * v8) + 8 * (v8 + k + 1));
                d2[1] = 3 - (v8 + k + 1);
                d2[2] = d2[1];
                d2[3] = v8 + k + 1;
                d2[4] = v8;
                d2[5] = 3;
                d2[6] = 0;
                const double* p = (const double*)(a1[1] + 8 * v8);
                if (a1[2] == 0)
                    sub_180073910(d1, d2, p, a3);
                else
                    sub_180076EA0(d1, d2, p, a3);

                ZeroFill((long long)((char*)rowPtr + rowOff), v12, v8);

                rowPtr -= 3;
                rowOff -= 8;
                --v8;
                ++v12;
            } while (v8 >= 0);
        }

        long long v57 = 3 - v4;
        if (v57 > 0) {
            long long v9 = 2;
            long long* rowPtr = (long long*)a2;
            long long rowOff = 8;
            for (long long i = 0; i < v57; ++i) {
                ZeroFill((long long)((char*)rowPtr + rowOff), v9, i);
                rowPtr += 3;
                rowOff += 8;
                --v9;
            }
        }
    } else {
        a2[1] = 0;
        a2[2] = 0;
        a2[3] = 0;
        a2[4] = kOne;
        a2[5] = 0;
        a2[6] = 0;
        a2[7] = 0;
        a2[8] = kOne;

        if (v4 <= 48) {
            for (long long v31 = v4 - 1; v31 >= 0; --v31) {
                long long d1[7];
                long long d2[7];
                d1[0] = (long long)&a2[4 * (v31 + k)];
                d1[1] = 3 - k - v31;
                d1[2] = 3 - k - v31;
                d1[3] = (long long)a2;
                d1[4] = v31 + k;
                d1[5] = v31 + k;
                d1[6] = 3;
                d2[0] = (long long)a1[0] + 8 * (4 * v31 + k + 1);
                d2[1] = 2 - (v31 + k);
                d2[2] = d2[1];
                d2[3] = v31 + k + 1;
                d2[4] = v31;
                d2[5] = 3;
                d2[6] = 0;
                const double* p = (const double*)(a1[1] + 8 * v31);
                if (a1[2] == 0)
                    sub_180073910(d1, d2, p, a3);
                else
                    sub_180076EA0(d1, d2, p, a3);
            }
        } else {
            sub_180078190(a1, a2, a3, 1);
        }
    }
}
