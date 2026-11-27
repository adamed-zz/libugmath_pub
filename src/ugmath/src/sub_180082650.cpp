




#include <windows.h>
#include <cstdint>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <malloc.h>
#include <intrin.h>
#include <emmintrin.h>
extern "C" __int64* sub_180079B50(__int64* a1, __int64* a2);
extern "C" void* sub_180079AB0(unsigned long long a1);
extern "C" __declspec(noreturn) void sub_180093FC0();

extern "C" long long* sub_180082650(__int64* a1, __int64* a2)
{
    __int64 v26[7];
    sub_180079B50(v26, a2);
    a1[0] = 0;
    a1[1] = 0;
    __int64 v6 = v26[1];
    char* v7 = (char*)v26[0];
    __int64 v8 = v26[2];
    char* v9 = 0;
    if (v6 == 2)
    {
        if (!v8)
            goto LABEL_13;
        goto LABEL_6;
    }
    if (!(v6 && v8))
        goto LABEL_13;
LABEL_6:
    if (v6 > 0x7FFFFFFFFFFFFFFFLL / v8)
        sub_180093FC0();
    if (v6 * v8)
    {
        free(0);
        if (v6 * v8 <= 0)
        {
            a1[0] = 0;
            v9 = 0;
        }
        else
        {
            v9 = (char*)sub_180079AB0((unsigned __int64)(v6 * v8));
            a1[0] = (__int64)v9;
        }
    }
    a1[1] = v8;
    if (v8 > 0)
    {
        do
        {
            *(__m128i*)v9 = *(__m128i*)v7;
            v7 += 8 * v6;
            v9 += 16;
            --v8;
        } while (v8);
    }
LABEL_13:
    free((void*)v26[0]);
    __int64 v10 = a1[1];
    __m128d v11 = _mm_set_sd((double)v10);
    __m128d v12 = _mm_unpacklo_pd(v11, v11);
    __m128d* v13 = (__m128d*)a1[0];
    if (v10)
    {
        __m128d v15 = v13[0];
        __int64 v16 = 1;
        unsigned __int64 v14 = (unsigned __int64)(v10 - 1) & 0xFFFFFFFFFFFFFFFCULL;
        if (v14 > 1)
        {
            __m128d* v17 = v13 + 3;
            unsigned __int64 v18 = ((v14 - 2) >> 2) + 1;
            v16 = 4 * (__int64)v18 + 1;
            do
            {
                v15 = _mm_add_pd(v15, _mm_add_pd(_mm_add_pd(v17[-2], v17[-1]), _mm_add_pd(v17[1], *v17)));
                v17 += 4;
                --v18;
            } while (v18);
        }
        if (v16 < v10)
        {
            __m128d* v19 = v13 + v16;
            __int64 v20 = v10 - v16;
            do
            {
                v15 = _mm_add_pd(v15, *v19++);
                --v20;
            } while (v20);
        }
        _mm_storeu_pd((double*)((char*)a1 + 16), _mm_div_pd(v15, v12));
        __int64 v5 = 0;
        if (v10 >= 4)
        {
            unsigned __int64 v22 = ((unsigned __int64)(v10 - 4) >> 2) + 1;
            v5 = 4 * (__int64)v22;
            double* p = (double*)v13 + 3;
            for (unsigned __int64 it = 0; it < v22; ++it)
            {
                p[-3] = p[-3] - *(double*)((char*)a1 + 16);
                p[-2] = p[-2] - *(double*)((char*)a1 + 24);
                p[-1] = p[-1] - *(double*)((char*)a1 + 16);
                p[0] = p[0] - *(double*)((char*)a1 + 24);
                p[1] = p[1] - *(double*)((char*)a1 + 16);
                p[2] = p[2] - *(double*)((char*)a1 + 24);
                p[3] = p[3] - *(double*)((char*)a1 + 16);
                p[4] = p[4] - *(double*)((char*)a1 + 24);
                p += 8;
            }
        }
        if (v5 < v10)
        {
            double* q = (double*)&v13[v5];
            __int64 v24 = v10 - v5;
            do
            {
                *q = *q - *(double*)((char*)a1 + 16);
                q[1] = q[1] - *(double*)((char*)a1 + 24);
                q += 2;
                --v24;
            } while (v24);
        }
    }
    else
    {
        _mm_storeu_pd((double*)((char*)a1 + 16), _mm_div_pd(_mm_setzero_pd(), v12));
    }
    return a1;
}
