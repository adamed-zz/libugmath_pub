






















#include <cstdint>
#include <intrin.h>

extern "C" void sub_180081400(const long long* view, long long start, long long end);
extern "C" void sub_180081270(const long long* view, long long start, long long end);
extern "C" void sub_180080F50(const long long* view, long long start, long long end);
extern "C" void sub_180081830(const long long* view, long long start, long long end);

namespace {

struct Oword {
    double lo;
    double hi;
};



struct DotOp {
    const double* mat;
    long long count;
    long long pad[11];
    const double* x;
    long long xcnt;
};


struct ScaleSrc {
    long long f0;
    double scale;
    long long f2;
    const double* src;
};



struct Rank1Locals {
    double temp[4];
    long long a2c[7];
};

}

extern "C" void sub_180076EA0(const long long* a1, const long long* a2, const double* a3,
                              long long a4) {
    long long nrows = a1[2];
    if (nrows == 1) {
        double f = 1.0 - *a3;
        double* row = (double*)a1[0];
        long long r = 0;
        do {
            long long cnt = a1[1];
            if (cnt > 0) {


                long long v13 = cnt;
                if (((unsigned long long)row & 7ull) == 0ull) {
                    unsigned long long par = (-((unsigned long long)row >> 3)) & 1ull;
                    long long p = (long long)par;
                    if (p < cnt) v13 = p;
                }
                long long v14 = 0;
                for (; v14 + 4 <= v13; v14 += 4) {
                    row[v14] = f * row[v14];
                    row[v14 + 1] = f * row[v14 + 1];
                    row[v14 + 2] = f * row[v14 + 2];
                    row[v14 + 3] = f * row[v14 + 3];
                }
                for (; v14 < v13; ++v14) row[v14] = f * row[v14];
                long long v17 = v13 + 2 * ((cnt - v13) / 2);
                for (long long i = v13; i < v17; i += 2) {
                    row[i] = f * row[i];
                    row[i + 1] = f * row[i + 1];
                }
                for (long long i = v17; i < cnt; ++i) row[i] = f * row[i];
            }
            ++r;
            row += 3;
        } while (r < a1[2]);
        return;
    }
    if (*a3 == 0.0) return;

    const double* mat = (const double*)a1[0];
    long long count = a1[1];
    const double* mat1 = mat + 3;
    const double* x = (const double*)a2[0];
    long long xcnt = a2[1];
    long long rows = nrows - 1;
    double* work = (double*)a4;



    long long start = count;
    if (((unsigned long long)a4 & 7ull) == 0ull) {
        unsigned long long par = (-((unsigned long long)a4 >> 3)) & 1ull;
        long long p = (long long)par;
        if (p < count) start = p;
    }
    long long mid = start + 2 * ((count - start) / 2);

    DotOp op;
    op.mat = mat1;
    op.count = count;
    for (int i = 0; i < 11; ++i) op.pad[i] = 0;
    op.x = x;
    op.xcnt = xcnt;

    double* dstWork = work;
    long long view[2];
    view[0] = (long long)&dstWork;
    view[1] = (long long)&op;
    sub_180081400(view, 0, start);

    for (long long i = start; i < mid; i += 2) {
        Oword acc;
        acc.lo = 0;
        acc.hi = 0;
        double* alo = (double*)&acc.lo;
        double* ahi = (double*)&acc.hi;
        long long k = 0;
        for (; k + 4 <= rows; k += 4) {
            *alo += x[k] * mat1[i + 3 * k];
            *alo += x[k + 1] * mat1[i + 3 * (k + 1)];
            *alo += x[k + 2] * mat1[i + 3 * (k + 2)];
            *alo += x[k + 3] * mat1[i + 3 * (k + 3)];
            *ahi += x[k] * mat1[i + 1 + 3 * k];
            *ahi += x[k + 1] * mat1[i + 1 + 3 * (k + 1)];
            *ahi += x[k + 2] * mat1[i + 1 + 3 * (k + 2)];
            *ahi += x[k + 3] * mat1[i + 1 + 3 * (k + 3)];
        }
        for (; k < rows; ++k) {
            *alo += x[k] * mat1[i + 3 * k];
            *ahi += x[k] * mat1[i + 1 + 3 * k];
        }
        *(Oword*)(work + i) = acc;
    }

    sub_180081400(view, mid, count);


    double* dstSlot = work;
    double* srcSlot = (double*)mat;
    long long addView[2];
    addView[0] = (long long)&dstSlot;
    addView[1] = (long long)&srcSlot;
    sub_180081270(addView, 0, count);


    double* dstData = (double*)mat;
    ScaleSrc subOp;
    subOp.f0 = a4;
    subOp.scale = *a3;
    subOp.f2 = 0;
    subOp.src = work;
    long long subView[2];
    subView[0] = (long long)&dstData;
    subView[1] = (long long)&subOp;
    sub_180080F50(subView, 0, count);





    Rank1Locals rank1;
    double* dstTemp = rank1.temp;
    ScaleSrc scaleOp;
    scaleOp.f0 = a4;
    scaleOp.scale = *a3;
    scaleOp.f2 = 0;
    scaleOp.src = work;
    long long scaleView[2];
    scaleView[0] = (long long)&dstTemp;
    scaleView[1] = (long long)&scaleOp;
    sub_180081830(scaleView, 0, count);
    for (int i = 0; i < 7; ++i) rank1.a2c[i] = a2[i];
    const double* temp = (const double*)&rank1;



    for (long long r = 0; r < rows; ++r) {
        double* row = (double*)mat1 + 3 * r;
        double xr = x[r];
        long long j0 = 0;
        if (((unsigned long long)row & 7ull) == 0ull) {
            unsigned long long par = (-((unsigned long long)row >> 3)) & 1ull;
            long long p = (long long)par;
            if (p < count) j0 = p;
        }
        long long j1 = j0 + 2 * ((count - j0) / 2);



        __m128d vx = _mm_set_sd(xr);
        for (long long j = 0; j < j0; ++j) {
            __m128d p = _mm_mul_sd(_mm_load_sd(temp + j), vx);
            _mm_store_sd(row + j, _mm_sub_sd(_mm_load_sd(row + j), p));
        }
        for (long long j = j0; j < j1; j += 2) {



            __m128d vtemp = _mm_loadu_pd(temp + j);
            __m128d p = _mm_mul_pd(vtemp, _mm_set_pd(xr, xr));
            _mm_storeu_pd(row + j, _mm_sub_pd(_mm_loadu_pd(row + j), p));
        }
        for (long long j = j1; j < count; ++j) {
            __m128d p = _mm_mul_sd(_mm_load_sd(temp + j), vx);
            _mm_store_sd(row + j, _mm_sub_sd(_mm_load_sd(row + j), p));
        }
    }
}
