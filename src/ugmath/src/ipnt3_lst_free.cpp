




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

void IPNT3_LST_free(IPNT3_LST_s* a1)
{
    if (MACH__checking_level > 0 && *((int*)a1 + 2) < 0)
    {
        ERROR_internal("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\ipnt.c", 58, "IPNT3_LST_free error");
        __debugbreak();
        __assume(0);
    }
    SM_free(*(void**)a1);
    *((int*)a1 + 2) = -1;
    *(void**)a1 = 0;
}
