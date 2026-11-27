










#include <cstdlib>

extern "C" void sub_18008CF30(long long* res, long long count, long long r8, long long r9);
extern "C" void sub_18007C590(long long* res, const long long* b, long long c);
extern "C" void sub_18007BD10(long long data, long long count, long long* scale);
extern "C" void sub_18007FD50(long long* dst, const long long* a, const long long* b,
                              const long long* scale);
extern "C" void sub_1800801D0(long long* dst, const long long* a, const long long* b,
                              const long long* scale);
extern "C" void sub_18007FF90(long long* dst, const long long* a, const long long* b,
                              const long long* scale);
extern "C" void sub_1800816E0(long long* view, long long n, long long m);
extern "C" void sub_18007E200(const long long* a1, const long long* b, const long long* c,
                              const long long* scale);
extern "C" void sub_180093FC0(long long a, long long b);

namespace {

const long long kMax = 0x7FFFFFFFFFFFFFFFLL;

struct Oword {
    long long lo;
    long long hi;
};


struct Mat3 {
    long long cell[6];
    long long dimA;
    long long dimB;
};

inline long long Mul(long long a, long long b) {
    return (long long)((unsigned long long)a * (unsigned long long)b);
}

}

extern "C" long long sub_1800789B0(const long long* a1, const long long* a2, long long a3,
                                   char a4) {
    long long v35[3];
    long long v40[7];
    long long v44[7];
    Mat3 m;
    long long v33[3];
    long long v31[2];
    long long v48;
    unsigned long long v9 = 0;

    v35[0] = 0;
    v35[1] = 0;
    v35[2] = 0;

    long long v8 = a2[2];
    if (v8 && v8 > kMax / v8) sub_180093FC0((long long)a1, kMax % v8);
    sub_18008CF30(v35, Mul(v8, v8), v8, v8);
    sub_18007C590(v35, a2, a3);

    for (int k = 0; k < 7; ++k) {
        v40[k] = a2[k];
        v44[k] = a1[k];
    }
    m.dimA = v40[2];
    m.dimB = v44[2];
    v48 = 0;
    sub_18007BD10((long long)m.cell, Mul(v44[2], v40[2]), &v48);
    v48 = 0x3FF0000000000000LL;
    sub_18007FD50(m.cell, v40, v44, &v48);

    long long v15 = 0;
    long long v17 = 0;

    if (a4) {
        v33[0] = 0;
        v33[1] = 0;
        v33[2] = 0;
        if (v35[1]) {
            if (m.dimB && v35[1] > kMax / m.dimB) sub_180093FC0((long long)a1, kMax % m.dimB);
        } else if (!m.dimB) {
            goto L7;
        }
        sub_18008CF30(v33, Mul(v35[1], m.dimB), v35[1], m.dimB);
        v15 = v33[2];
    L7:
        {
            long long v16 = v33[1];
            v17 = v33[0];
            v31[0] = 0;
            sub_18007BD10(v33[0], Mul(v33[1], v15), &v31[0]);
            v31[0] = 0x3FF0000000000000LL;
            sub_1800801D0(v33, v35, m.cell, &v31[0]);

            long long v18 = v17;
            v31[0] = v17;
            v31[1] = v16;
            long long v19 = m.dimA;
            long long v20;
            if (m.dimA != v16 || (v20 = m.dimB, m.dimB != v15)) {
                m.dimA = v16;
                m.dimB = v15;
                v19 = v16;
                v20 = v15;
            }
            unsigned char* dst = (unsigned char*)m.cell;
            v33[0] = (long long)m.cell;
            v33[1] = v19;
            v40[0] = (long long)&v33[0];
            v40[1] = (long long)&v31[0];
            v40[2] = (long long)&v48;
            v40[3] = (long long)m.cell;
            long long v22 = Mul(v20, v19);
            long long v23 = 2 * (v22 / 2);
            if (v23 > 0) {
                v9 = 0;
                for (;;) {
                    *(Oword*)(dst + 8 * v9) = *(Oword*)(v18 + 8 * (long long)v9);
                    v9 += 2;
                    if ((long long)v9 >= v23) break;
                    v18 = v31[0];
                    dst = (unsigned char*)v33[0];
                }
            }
            long long v28 = v22;
            long long v29 = v23;
            sub_1800816E0(v40, v29, v28);
            free((void*)v17);
            goto L29;
        }
    } else {
        v33[0] = (long long)&v35[0];
        v33[1] = (long long)m.cell;
        v40[0] = 0;
        v40[1] = 0;
        v40[2] = 0;
        if (v35[2]) {
            if (m.dimB && v35[2] > kMax / m.dimB) sub_180093FC0((long long)a1, kMax % m.dimB);
        } else if (!m.dimB) {
            goto L20;
        }
        sub_18008CF30(v40, Mul(v35[2], m.dimB), v35[2], m.dimB);
        v15 = v40[2];
    L20:
        {
            long long v24 = v40[1];
            v17 = v40[0];
            v31[0] = 0;
            sub_18007BD10(v40[0], Mul(v40[1], v15), &v31[0]);
            v31[0] = 0x3FF0000000000000LL;
            sub_18007FF90(v40, v33, m.cell, &v31[0]);

            long long v25 = v17;
            v33[0] = v17;
            v33[1] = v24;
            long long v26 = m.dimA;
            long long v27;
            if (m.dimA != v24 || (v27 = m.dimB, m.dimB != v15)) {
                m.dimA = v24;
                m.dimB = v15;
                v26 = v24;
                v27 = v15;
            }
            unsigned char* dst = (unsigned char*)m.cell;
            v31[0] = (long long)m.cell;
            v31[1] = v26;
            v40[0] = (long long)&v31[0];
            v40[1] = (long long)&v33[0];
            v40[2] = (long long)&v48;
            v40[3] = (long long)m.cell;
            long long v22 = Mul(v27, v26);
            long long v29 = 2 * (v22 / 2);
            if (v29 > 0) {
                v9 = 0;
                for (;;) {
                    *(Oword*)(dst + 8 * v9) = *(Oword*)(v25 + 8 * (long long)v9);
                    v9 += 2;
                    if ((long long)v9 >= v29) break;
                    v25 = v33[0];
                    dst = (unsigned char*)v31[0];
                }
            }
            long long v28 = v22;
            sub_1800816E0(v40, v29, v28);
            free((void*)v17);
        }
    }

L29:
    for (int k = 0; k < 7; ++k) v40[k] = a2[k];
    v44[0] = (long long)m.cell;
    v48 = (long long)0xBFF0000000000000ULL;
    sub_18007E200(a1, v40, m.cell, &v48);
    free((void*)v35[0]);
    return 0;
}
