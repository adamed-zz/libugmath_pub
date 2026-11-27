




#include <windows.h>
#include <cstdint>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <malloc.h>
#include <intrin.h>
#include <emmintrin.h>
extern "C" void* sub_180079AB0(unsigned long long a1);
extern "C" void* sub_180079A60(unsigned long long a1);
extern "C" __declspec(noreturn) void sub_180093FC0();

extern "C" __int64 sub_180082290(__int64 a1, __int64 a2, __int64 a3)
{
    __int64 v4 = a2;
    *(__int64*)a1 = 0;
    *(__int64*)(a1 + 8) = 0;
    if (a2)
    {
        if (a3)
        {
            if (a2 > 0x7FFFFFFFFFFFFFFFLL / a3)
                sub_180093FC0();
        }
    }
    __int64 v6 = a3 * v4;
    if (v6)
    {
        free(0);
        if (v6 <= 0)
            *(__int64*)a1 = 0;
        else
            *(__int64*)a1 = (__int64)sub_180079AB0((unsigned __int64)v6);
    }
    *(__int64*)(a1 + 8) = a3;
    if (a3 < v4)
        v4 = a3;
    *(__int64*)(a1 + 40) = v4;
    *(__int64*)(a1 + 48) = 0;
    *(__int64*)(a1 + 56) = 0;
    if ((int)a3)
    {
        free(0);
        if ((int)a3 <= 0)
            *(__int64*)(a1 + 48) = 0;
        else
            *(__int64*)(a1 + 48) = (__int64)sub_180079A60((unsigned __int64)(int)a3);
    }
    *(__int64*)(a1 + 56) = (int)a3;
    *(__int64*)(a1 + 64) = 0;
    *(__int64*)(a1 + 72) = 0;
    if (a3)
    {
        free(0);
        if (a3 <= 0)
            *(__int64*)(a1 + 64) = 0;
        else
            *(__int64*)(a1 + 64) = (__int64)sub_180079AB0((unsigned __int64)a3);
    }
    *(__int64*)(a1 + 72) = a3;
    *(__int64*)(a1 + 80) = 0;
    *(__int64*)(a1 + 88) = 0;
    if (a3)
    {
        free(0);
        if (a3 <= 0)
            *(__int64*)(a1 + 80) = 0;
        else
            *(__int64*)(a1 + 80) = (__int64)sub_180079AB0((unsigned __int64)a3);
    }
    *(__int64*)(a1 + 88) = a3;
    *(__int64*)(a1 + 96) = 0;
    *(__int64*)(a1 + 104) = 0;
    if (a3)
    {
        free(0);
        if (a3 <= 0)
            *(__int64*)(a1 + 96) = 0;
        else
            *(__int64*)(a1 + 96) = (__int64)sub_180079AB0((unsigned __int64)a3);
    }
    *(__int64*)(a1 + 104) = a3;
    *(__int64*)(a1 + 112) = 0;
    *(__int64*)(a1 + 120) = 0;
    if (a3)
    {
        free(0);
        if (a3 <= 0)
            *(__int64*)(a1 + 112) = 0;
        else
            *(__int64*)(a1 + 112) = (__int64)sub_180079AB0((unsigned __int64)a3);
    }
    *(__int64*)(a1 + 120) = a3;
    *(unsigned short*)(a1 + 128) = 0;
    return a1;
}
