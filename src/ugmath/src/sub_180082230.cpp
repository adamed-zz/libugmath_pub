




#include <windows.h>
#include <cstdint>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <malloc.h>
#include <intrin.h>
#include <emmintrin.h>
extern "C" void sub_180082230(long long a1, long long a2)
{
    long long n = *(long long*)(a1 + 8);
    if (n)
    {
        double* data = *(double**)a1;
        long long idx = 1;
        double maxv = data[0];
        *(double*)(a2 + 16) = maxv;
        *(long long*)a2 = 0;
        *(long long*)(a2 + 8) = 0;
        while (idx < n)
        {
            double v = data[idx];
            if (v > maxv)
            {
                *(double*)(a2 + 16) = v;
                maxv = v;
                *(long long*)a2 = idx;
                *(long long*)(a2 + 8) = 0;
            }
            ++idx;
        }
    }
}
