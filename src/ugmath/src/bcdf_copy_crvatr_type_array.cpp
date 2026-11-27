






















#include <stddef.h>

struct BCDF_s;


__declspec(dllimport) void* __cdecl SM_alloc(size_t);

int* __cdecl BCDF_copy_crvatr_type_array(struct BCDF_s* a)
{
    char* p = (char*)a;
    unsigned __int64 v = *(unsigned __int64*)(p + 0x28);
    if (v)
        v = *(unsigned int*)(v + 8);
    __int64 n = (int)v;
    int* src = *(int**)(p + 0x50);
    int* dst = (int*)SM_alloc(4 * n);
    if (n > 0)
    {
        for (__int64 i = 0; i < n; ++i)
            dst[i] = src[i];
    }
    return dst;
}
