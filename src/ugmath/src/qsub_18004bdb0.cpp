






#include <windows.h>

extern "C" void* g_b15_raw_base;

extern "C" void* sub_18004BDB0()
{
    typedef void* (*Fn_alloc)(unsigned long long);
    Fn_alloc SM_alloc = (Fn_alloc)*(void**)((char*)g_b15_raw_base + 0xB9448);
    void* p = SM_alloc(0x40);
    if (!p)
    {
        typedef void (*Fn_err)(int, int, const char*);
        Fn_err err = (Fn_err)*(void**)((char*)g_b15_raw_base + 0xE08D8);
        err(2, 3, (const char*)((char*)g_b15_raw_base + 0xBAD62));
        return 0;
    }
    return p;
}
