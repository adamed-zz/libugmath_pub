







#include <cstdlib>

extern "C" void sub_18008CF30(long long* res, long long count, long long r8, long long r9);
extern "C" void sub_18007C590(long long* res, const long long* b, long long c);
extern "C" void sub_18007BD10(long long data, long long count, long long* flag);
extern "C" void sub_180080410(long long* dst, const long long* b, const long long* a,
                              const long long* scale);
extern "C" void sub_1800802F0(long long* dst, const long long* b, const long long* a,
                              const long long* scale);
extern "C" void sub_1800800B0(long long* dst, const long long* b, const long long* a,
                              const long long* scale);
extern "C" void sub_1800816E0(long long* view, long long n, long long m);
extern "C" void sub_18007E2C0(const long long* a1, const long long* b, const long long* c,
                              const long long* scale);
extern "C" void sub_180093FC0(long long a, long long b);

namespace {

const long long kMax = 0x7FFFFFFFFFFFFFFFLL;

struct Oword {
    long long lo;
    long long hi;
};

inline long long Mul(long long a, long long b) {
    return (long long)((unsigned long long)a * (unsigned long long)b);
}

}

extern "C" long long sub_180078E80(const long long* a1, const long long* a2, long long a3,
                                   char a4) {
    long long v43[3];
    long long v37[3];
    long long v45[7];
    long long v49[7];
    long long v39[2];
    long long v41[2];
    long long v53;
    unsigned long long v9 = 0;

    v43[0] = 0;
    v43[1] = 0;
    v43[2] = 0;

    long long v8 = a2[2];
    if (v8 && v8 > kMax / v8) sub_180093FC0((long long)a1, kMax % v8);
    sub_18008CF30(v43, Mul(v8, v8), v8, v8);
    sub_18007C590(v43, a2, a3);


    for (int k = 0; k < 7; ++k) {
        v45[k] = a2[k];
        v49[k] = a1[k];
    }

    v37[0] = 0;
    v37[1] = 0;
    v37[2] = 0;

    long long v12 = a2[2];
    long long v50 = a1[2];
    long long v15 = v50;
    if (v12 && v50) {
        if (v12 > kMax / v50) sub_180093FC0((long long)a1, kMax % v50);
    }
    sub_18008CF30(v37, Mul(v50, v12), v12, v50);
    long long v17 = v37[1];
    if (v37[1] != v12 || v37[2] != v15) {
        if (!v12 || !v15 || v12 <= kMax / v15) {
            sub_18008CF30(v37, Mul(v15, v12), v12, v15);
            v17 = v37[1];
        } else {
            sub_180093FC0((long long)a1, kMax % v15);
        }
    }

    v53 = 0;
    sub_18007BD10(v37[0], Mul(v17, v37[2]), &v53);
    v53 = 0x3FF0000000000000LL;
    sub_180080410(v37, v45, v49, &v53);

    v45[0] = 0;
    v45[1] = 0;
    v45[2] = 0;

    long long v20 = 0;
    long long v23 = 0;
    long long v28 = 0;
    long long v29 = 0;

    if (a4) {
        if (v43[1]) {
            if (v37[2] && v43[1] > kMax / v37[2])
                sub_180093FC0((long long)a1, kMax % v37[2]);
        } else if (!v37[2]) {
            goto after_alloc1;
        }
        sub_18008CF30(v45, Mul(v43[1], v37[2]), v43[1], v37[2]);
    after_alloc1:
        v20 = v45[2];
        {
            long long v21 = v45[1];
            long long v22 = Mul(v45[1], v20);
            v23 = v45[0];
            v39[0] = 0;
            sub_18007BD10(v45[0], v22, v39);
            v39[0] = 0x3FF0000000000000LL;
            sub_1800802F0(v45, v43, v37, v39);
            v39[0] = v23;
            v39[1] = v21;
            if (v37[1] != v21 || v37[2] != v20) {
                if (v21 && v20 && v21 > kMax / v20)
                    sub_180093FC0((long long)a1, kMax % v20);
                sub_18008CF30(v37, v22, v21, v20);
            }
            v41[0] = v37[0];
            v41[1] = v37[1];
            v45[0] = (long long)&v41[0];
            v45[1] = (long long)&v39[0];
            v45[2] = (long long)&v53;
            v45[3] = (long long)&v37[0];
            v28 = Mul(v37[1], v37[2]);
            v29 = 2 * (v28 / 2);
            if (v29 > 0) {
                v9 = 0;
                char* dst = (char*)(long long)v37[0];
                for (;;) {
                    *(Oword*)(dst + 8 * v9) = *(Oword*)(v39[0] + 8 * (long long)v9);
                    v9 += 2;
                    if ((long long)v9 >= v29) break;
                    dst = (char*)(long long)v41[0];
                }
            }
        }
    } else {
        v41[0] = (long long)&v43[0];
        v41[1] = (long long)&v37[0];
        if (v43[2]) {
            if (v37[2] && v43[2] > kMax / v37[2])
                sub_180093FC0((long long)a1, kMax % v37[2]);
        } else if (!v37[2]) {
            goto after_alloc2;
        }
        sub_18008CF30(v45, Mul(v43[2], v37[2]), v43[2], v37[2]);
    after_alloc2:
        v20 = v45[2];
        {
            long long v30 = v45[1];
            long long v31 = Mul(v45[1], v20);
            v23 = v45[0];
            v39[0] = 0;
            sub_18007BD10(v45[0], v31, v39);
            v39[0] = 0x3FF0000000000000LL;
            sub_1800800B0(v45, v41, v37, v39);
            v41[0] = v23;
            v41[1] = v30;
            if (v37[1] != v30 || v37[2] != v20) {
                if (v30 && v20 && v30 > kMax / v20)
                    sub_180093FC0((long long)a1, kMax % v20);
                sub_18008CF30(v37, v31, v30, v20);
            }
            long long v35 = v37[0];
            v39[0] = v37[0];
            v39[1] = v37[1];
            v45[0] = (long long)&v39[0];
            v45[1] = (long long)&v41[0];
            v45[2] = (long long)&v53;
            v45[3] = (long long)&v37[0];
            v28 = Mul(v37[1], v37[2]);
            v29 = 2 * (v28 / 2);
            if (v29 > 0) {
                v9 = 0;
                for (;;) {
                    *(Oword*)(v35 + 8 * (long long)v9) =
                        *(Oword*)(v41[0] + 8 * (long long)v9);
                    v9 += 2;
                    if ((long long)v9 >= v29) break;
                    v35 = v39[0];
                }
            }
        }
    }

    sub_1800816E0(v45, v29, v28);
    free((void*)v23);


    for (int k = 0; k < 7; ++k) v45[k] = a2[k];
    v49[0] = (long long)&v37[0];
    v53 = (long long)0xBFF0000000000000ULL;
    sub_18007E2C0(a1, v45, v37, &v53);
    free((void*)v37[0]);
    free((void*)v43[0]);
    return 0;
}
