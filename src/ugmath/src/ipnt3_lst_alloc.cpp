




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

void IPNT3_LST_alloc(IPNT3_LST_s* a1, int a2)
{
    if (MACH__checking_level > 0 && a2 < 0)
    {
        ERROR_internal("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\ipnt.c", 38, "IPNT3_LST_alloc error");
        __debugbreak();
        __assume(0);
    }
    *((int*)a1 + 2) = a2;
    *(void**)a1 = SM_alloc(32LL * a2);
}
