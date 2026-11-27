
















#include <cstdint>
#include <intrin.h>

extern "C" void sub_180080DE0(const long long* view, long long start, long long end);
extern "C" void sub_180080B80(const long long* a1, const long long* a2, const long long* a3,
                              const double* a4);
extern "C" double sub_18007E760(const long long* a1, const double* a2, const char* a3);
extern "C" void sub_18007D650(const long long* a1, const long long* a2, const long long* a3);

namespace {

struct Oword {
    double lo;
    double hi;
};


struct DotDim {
    char pad[0xA8];
    long long rows;
};

}

extern "C" void sub_1800764D0(const long long* a1, const long long* a2, const double* a3,
                              long long a4) {
    long long count = a1[1];
    if (count == 1) {
        double f = 1.0 - *a3;
        const long long ld = *(const long long*)(a1[3] + 8);
        double* row = (double*)a1[0];
        long long rows = a1[2];
        for (long long r = 0; r < rows; ++r) {

            __m128d vf = _mm_set_sd(f);
            _mm_store_sd(row, _mm_mul_sd(vf, _mm_load_sd(row)));
            row += ld;
        }
        return;
    }
    if (*a3 == 0.0) return;

    double* mat = (double*)a1[0];
    long long nrows = a1[2];
    long long rows = count - 1;
    const long long ld = *(const long long*)(a1[3] + 8);
    const long long ld2 = a1[4];
    const double* x = (const double*)a2[0];
    long long xcnt = a2[1];
    double* work = (double*)a4;


    long long start = 0;
    if (((unsigned long long)work & 7ull) == 0ull) {
        unsigned long long par = (-((unsigned long long)work >> 3)) & 1ull;
        long long p = (long long)par;
        if (p < nrows) start = p;
    }
    long long mid = start + 2 * ((nrows - start) / 2);

    double* dstSlot = work;
    double zero = 0.0;
    long long fillView[2] = {(long long)&dstSlot, (long long)&zero};
    sub_180080DE0(fillView, 0, start);
    for (long long i = start; i < mid; i += 2) {
        Oword z;
        z.lo = 0.0;
        z.hi = 0.0;
        *(Oword*)(work + i) = z;
    }
    sub_180080DE0(fillView, mid, nrows);


    if (nrows == 1) {
        double dot = 0.0;
        if (rows != 0) {
            double one = 1.0;
            long long slots[8] = {0, 0, 0, 0, 0, 0, 0, 0};
            slots[1] = (long long)x;
            slots[4] = (long long)(mat + 1);
            DotDim dim;
            for (int i = 0; i < (int)sizeof(dim.pad); ++i) dim.pad[i] = 0;
            dim.rows = rows;
            dot = sub_18007E760(slots, &one, (const char*)&dim);
        }
        work[0] = work[0] + dot;
    } else {
        long long desc[8];
        desc[0] = (long long)(mat + 1);
        desc[1] = rows;
        desc[2] = nrows;
        desc[3] = a1[3];
        desc[4] = count;
        desc[5] = nrows;
        desc[6] = a1[3];
        desc[7] = ld2;
        long long copy[13];
        for (int i = 0; i < 13; ++i) copy[i] = a2[i];
        long long dst[2] = {(long long)work, nrows};
        double one = 1.0;
        sub_180080B80(desc, copy, dst, &one);
    }





    {
        long long j = 0;
        for (; j + 4 <= nrows; j += 4) {
            work[j] = mat[j * ld] + work[j];
            work[j + 1] = mat[(j + 1) * ld] + work[j + 1];
            work[j + 2] = mat[(j + 2) * ld] + work[j + 2];
            work[j + 3] = mat[(j + 3) * ld] + work[j + 3];
        }
        for (; j < nrows; ++j) {
            _mm_store_sd(work + j,
                         _mm_add_sd(_mm_load_sd(work + j), _mm_load_sd(mat + j * ld)));
        }
    }
    const double alpha = *a3;
    for (long long j = 0; j < nrows; ++j) {
        mat[j * ld] = mat[j * ld] - alpha * work[j];
    }


    long long g1[13] = {0};
    g1[0] = (long long)(mat + 1);
    g1[1] = rows;
    g1[2] = nrows;
    g1[3] = a1[0];
    g1[4] = count;
    g1[5] = nrows;
    g1[6] = a1[3];
    g1[7] = ld2;
    g1[8] = a1[5];
    g1[9] = a1[6];
    g1[10] = 1;
    g1[12] = ld;
    long long g2[24] = {0};
    g2[0] = (long long)(mat + 1);
    g2[1] = rows;
    g2[2] = xcnt;
    g2[3] = a1[3];
    g2[4] = (long long)(*(const long long*)&alpha);
    g2[5] = (long long)x;
    g2[6] = xcnt;
    g2[7] = a2[2];
    g2[8] = a2[3];
    g2[9] = a2[4];
    g2[10] = a2[5];
    g2[11] = a2[6];
    g2[12] = a2[7];
    g2[13] = a2[8];
    g2[14] = a2[9];
    g2[15] = a2[10];
    g2[16] = a2[11];
    g2[17] = a2[12];
    g2[19] = (long long)work;
    g2[20] = nrows;
    g2[21] = nrows;
    long long g3[2] = {(long long)work, nrows};
    sub_18007D650(g1, g2, g3);
}
