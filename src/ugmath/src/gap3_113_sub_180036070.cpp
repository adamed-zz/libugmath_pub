







#include <cstdlib>
#include <cstring>

extern "C" void* SM_calloc(size_t n, size_t sz);

extern "C" __int64 sub_180036070(int* a1, const double* a2, const double* a3, void** a4)
{
    int v4 = a1[5];
    int v7 = a1[4];
    int v8 = a1[1] - 1;
    int v9 = a1[0];
    int ncol = a1[3];
    if (a1[6] + 1 <= v8)
        v8 = a1[6] + 1;
    int v38 = a1[2];
    int v39 = v8;
    int v40 = v4 + v7;
    int v11 = v38 ? v8 + v4 : a1[5];
    double* out = (double*)SM_calloc((__int64)ncol * (v9 + v7 + v11), 8);
    __int64 result = 0;
    if (v9 > 0)
    {
        for (int i = 0; i < v9; ++i)
        {
            result = (__int64)(out + (__int64)i * ncol);
            memcpy(out + (__int64)i * ncol, a2 + (__int64)i * ncol, 8ull * ncol);
        }
    }
    if (v40 > 0)
    {
        for (int j = 0; j < v40; ++j)
        {
            __int64 dst = ((__int64)v9 + j) * ncol;
            result = (__int64)(out + dst);
            memcpy(out + dst, a3 + (__int64)j * ncol, 8ull * ncol);
        }
    }
    if (v38 && v39 > 0)
    {
        for (int k = 0; k < v39; ++k)
        {
            __int64 dst = ((__int64)v9 + v40 + k) * ncol;
            result = (__int64)(out + dst);
            if (ncol > 0)
                memset(out + dst, 0, 8ull * ncol);
        }
    }
    *a4 = out;


    if (!v38)
    {
        __int64 bits = 0;
        if (ncol > 0)
        {
            const double* lastv = 0;
            if (v40 > 0)
                lastv = a3 + (__int64)(v40 - 1) * ncol + (ncol - 1);
            else if (v9 > 0)
                lastv = a2 + (__int64)(v9 - 1) * ncol + (ncol - 1);
            if (lastv)
                memcpy(&bits, lastv, 8);
        }
        result = bits;
    }
    return result;
}
