

























#include <cstdint>
#include <cstring>
#include <intrin.h>

extern "C" void sub_180080DE0(const long long* view, long long start, long long end);
extern "C" void sub_18008F800(long long a1, long long a2, const long long* a3,
                              const long long* a4, double* a5, long long a6, double a7);
extern "C" void sub_180081270(const long long* view, long long start, long long end);
extern "C" void sub_180080F50(const long long* view, long long start, long long end);
extern "C" void sub_18007D9A0(const long long* a1, const long long* a2, const long long* a3,
                              void* a4, void* a5);

extern "C" void sub_1800778F0(const long long* a1, const long long* a2, const double* a3,
                              long long a4) {
    double* mat = (double*)a1[0];
    long long count = a1[1];
    long long nrows = a1[2];

    if (nrows == 1) {

        const double f = 1.0 - *a3;
        __m128d vf = _mm_set_sd(f);
        if (((unsigned long long)mat & 7ull) != 0ull) {
            for (long long k = 0; k < count; ++k)
                _mm_store_sd(mat + k, _mm_mul_sd(vf, _mm_load_sd(mat + k)));
        } else {
            long long head = count;
            long long par = (-((unsigned long long)mat >> 3)) & 1ull;
            if (par < count) head = par;
            long long mid = head + 2 * ((count - head) / 2);
            for (long long k = 0; k < head; ++k)
                _mm_store_sd(mat + k, _mm_mul_sd(vf, _mm_load_sd(mat + k)));
            for (long long k = head; k < mid; k += 2) {
                _mm_store_sd(mat + k, _mm_mul_sd(vf, _mm_load_sd(mat + k)));
                _mm_store_sd(mat + k + 1, _mm_mul_sd(vf, _mm_load_sd(mat + k + 1)));
            }
            for (long long k = mid; k < count; ++k)
                _mm_store_sd(mat + k, _mm_mul_sd(vf, _mm_load_sd(mat + k)));
        }
        return;
    }
    if (*a3 == 0.0) return;

    const double alpha = *a3;
    long long alphaBits;
    std::memcpy(&alphaBits, &alpha, 8);
    const long long ld = *(const long long*)(a1[3] + 8);
    double* work = (double*)a4;
    double* A1 = mat + ld;
    const double* x = (const double*)a2[0];
    long long xcnt = a2[1];


    long long head0 = count;
    {
        long long par = (-((unsigned long long)work >> 3)) & 1ull;
        if (par < count) head0 = par;
    }
    long long mid0 = head0 + 2 * ((count - head0) / 2);
    double zero = 0.0;
    long long* dstSlot = (long long*)work;
    long long zview[4] = {(long long)&dstSlot, (long long)&zero, 0, 0};
    sub_180080DE0(zview, 0, head0);
    {
        __m128d z = _mm_setzero_pd();
        for (long long k = head0; k < mid0; k += 2) _mm_storeu_pd(work + k, z);
    }
    sub_180080DE0(zview, mid0, count);


    if (count == 1) {
        __m128d acc = _mm_setzero_pd();
        if (xcnt != 0) {
            acc = _mm_mul_sd(_mm_load_sd(x), _mm_load_sd(A1));
            for (long long k = 1; k < xcnt; ++k) {
                __m128d prod = _mm_mul_sd(_mm_load_sd(x + k), _mm_load_sd(A1 + k * ld));
                acc = _mm_add_sd(acc, prod);
            }
        }
        _mm_store_sd(work, _mm_add_sd(acc, _mm_load_sd(work)));
    } else {
        long long ab[2] = {(long long)A1, ld};
        long long bb[2] = {(long long)x, 1};
        sub_18008F800(count, nrows - 1, ab, bb, work, 1, 1.0);
    }


    long long head1 = count;
    {
        long long par = (-((unsigned long long)work >> 3)) & 1ull;
        if (par < count) head1 = par;
    }
    long long mid1 = head1 + 2 * ((count - head1) / 2);
    long long* workSlot = (long long*)work;
    long long* matSlot = (long long*)mat;
    long long aview[4] = {(long long)&workSlot, (long long)&matSlot, 0, 0};
    sub_180081270(aview, 0, head1);
    for (long long k = head1; k < mid1; k += 2)
        _mm_storeu_pd(work + k, _mm_add_pd(_mm_loadu_pd(mat + k), _mm_loadu_pd(work + k)));
    sub_180081270(aview, mid1, count);


    long long head2 = count;
    if (((unsigned long long)mat & 7ull) == 0ull) {
        long long par = (-((unsigned long long)mat >> 3)) & 1ull;
        if (par < count) head2 = par;
    }
    long long mid2 = head2 + 2 * ((count - head2) / 2);
    long long sv0[2] = {(long long)mat, ld};
    long long sdk[4] = {0, alphaBits, 0, (long long)work};
    long long sview[4] = {(long long)sv0, (long long)sdk, 0, 0};
    sub_180080F50(sview, 0, head2);
    {
        __m128d va = _mm_unpacklo_pd(_mm_set_sd(alpha), _mm_set_sd(alpha));
        for (long long k = head2; k < mid2; k += 2) {
            __m128d prod = _mm_mul_pd(va, _mm_loadu_pd(work + k));
            _mm_storeu_pd(mat + k, _mm_sub_pd(_mm_loadu_pd(mat + k), prod));
        }
    }
    sub_180080F50(sview, mid2, count);


    long long g1[13];
    g1[0] = (long long)A1;
    g1[1] = count;
    g1[2] = nrows - 1;
    g1[3] = a1[0];
    g1[4] = count;
    g1[5] = nrows;
    g1[6] = a1[3];
    g1[7] = a1[4];
    g1[8] = a1[5];
    g1[9] = a1[6];
    g1[10] = 0;
    g1[11] = 1;
    g1[12] = ld;
    long long g2[22] = {0};
    g2[0] = (long long)mat;
    g2[1] = count;
    g2[2] = count;
    g2[3] = a1[0];
    g2[4] = alphaBits;
    g2[5] = (long long)work;
    g2[6] = count;
    g2[8] = a1[5];
    g2[9] = a1[6];
    for (int i = 0; i < 7; ++i) g2[10 + i] = a2[i];
    long long g3[7];
    for (int i = 0; i < 7; ++i) g3[i] = a2[i];
    char dummy = 0;
    sub_18007D9A0(g1, g2, g3, &dummy, &dummy);
}
