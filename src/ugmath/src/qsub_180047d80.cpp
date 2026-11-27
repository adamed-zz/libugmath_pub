







#include <windows.h>

extern "C" void* g_b15_raw_base;

extern "C" int sub_180047D80(const char* a1, const double* a2)
{
    void** slot = (void**)((char*)g_b15_raw_base + 0xB9450);
    void* cl_addr = *slot;
    if (*(int*)cl_addr < 1)
        return (int)(long long)(unsigned long long)cl_addr;
    typedef int (*Fn_lprintf)(const char*, ...);
    Fn_lprintf lprintf = (Fn_lprintf)*(void**)((char*)g_b15_raw_base + 0xB93F0);
    const char* fmt = (const char*)((char*)g_b15_raw_base + 0xBAB30);
    return lprintf(fmt, a1,
                   a2[0], a2[3], a2[6],
                   a2[1], a2[4], a2[7],
                   a2[2], a2[5], a2[8]);
}
