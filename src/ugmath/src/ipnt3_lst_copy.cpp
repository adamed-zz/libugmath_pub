




#include <cstddef>
#include <cstdint>
#include <xmmintrin.h>

__declspec(dllimport) void* __cdecl SM_alloc(size_t);
__declspec(dllimport) void* __cdecl SM_realloc(void*, size_t);
__declspec(dllimport) void __cdecl SM_free(void*);
extern __declspec(dllimport) int MACH__checking_level;
__declspec(dllimport) void ERROR_internal(const char*, int, const char*, ...);

struct IPNT3_LST_s
{
    void* pnts;
    int num_pnts;
};

void IPNT3_LST_copy(IPNT3_LST_s* a1, IPNT3_LST_s* a2)
{
    if (MACH__checking_level > 0 && *((int*)a1 + 2) < 0)
    {
        ERROR_internal("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\ipnt.c", 72, "IPNT3_LST_copy error");
        __debugbreak();
        __assume(0);
    }
    __int64 v4 = *((int*)a1 + 2);
    if (MACH__checking_level > 0 && (int)v4 < 0)
    {
        ERROR_internal("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\ipnt.c", 48, "IPNT3_LST_alloc error");
        __debugbreak();
        __assume(0);
    }
    void* v5 = *(void**)a2;
    *((int*)a2 + 2) = (int)v4;
    *(void**)a2 = SM_realloc(v5, 32 * v4);
    int v6 = 0;
    int v7 = *((int*)a1 + 2);
    *((int*)a2 + 2) = v7;
    if (v7 > 0)
    {
        __int64 v8 = 0;
        do
        {
            v8 += 32;
            ++v6;
            *(uint64_t*)(v8 + (uint64_t)*(void**)a2 - 32) =
                *(uint64_t*)(v8 + (uint64_t)*(void**)a1 - 32);
            *(uint64_t*)(v8 + (uint64_t)*(void**)a2 - 24) =
                *(uint64_t*)(v8 + (uint64_t)*(void**)a1 - 24);
            *(uint64_t*)(v8 + (uint64_t)*(void**)a2 - 16) =
                *(uint64_t*)(v8 + (uint64_t)*(void**)a1 - 16);
        } while (v6 < *((int*)a2 + 2));
    }
}
