







#include <cstdint>

typedef struct
{
    long long q[6];
} Params;

extern "C" void sub_180080D00(long long** a1, long long first, long long last)
{
    long long i = first;
    long long n = last;
    if (first < last)
    {
        Params* p = (Params*)a1[1];
        const double* src = (const double*)p->q[1];
        double* dst = (double*)**a1;
#pragma loop(no_vector)
        for (; i < n; ++i)
            dst[i] = src[i] / ((double*)p)[3];
    }
}
