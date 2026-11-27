




#include <windows.h>
#include <cstdint>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <malloc.h>
#include <intrin.h>
#include <emmintrin.h>
extern "C" __int64 sub_180080890(void* a1, void* a2, void* a3, double* a4);

extern "C" __int64 sub_180081DF0(long long a1, long long a2, long long a3, double* a4)
{
    unsigned char A[0x68];
    unsigned char U[0xB8];
    unsigned char V[0x68];
    memcpy(A, (const void*)a1, 0x68);
    memcpy(U + 0x10, (const void*)(a2 + 0x10), 0xA8);
    memcpy(V, (const void*)a3, 0x68);
    return sub_180080890(V, U, A, a4);
}
