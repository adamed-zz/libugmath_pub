




#include <cstddef>
#include <cstdint>
#include <xmmintrin.h>

__declspec(dllimport) void* __cdecl SM_alloc(size_t);
__declspec(dllimport) void* __cdecl SM_realloc(void*, size_t);
__declspec(dllimport) void __cdecl SM_free(void*);
extern __declspec(dllimport) int MACH__checking_level;
__declspec(dllimport) void ERROR_internal(const char*, int, const char*, ...);

struct IPNT4_LST_s
{
    void* pnts;
    int num_pnts;
};

void IPNT4_LST_xtract_pnts(IPNT4_LST_s* a1, double (*a2)[4])
{
    if (MACH__checking_level > 0 && *((int*)a1 + 2) < 0)
    {
        ERROR_internal("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\ipnt.c", 142, "IPNT4_LST_xtract_pnts error", a1);
        __debugbreak();
        __assume(0);
    }
    int v2 = 0;
    if (*((int*)a1 + 2) > 0)
    {
        double* v3 = &(*a2)[2];
        do
        {
            __int64 v4 = v2;
            v3 += 4;
            ++v2;
            const char* v5 = (const char*)(*(uint64_t*)a1 + 40 * v4);
            __m128 v6 = _mm_loadu_ps((const float*)v5);
            __m128 v7 = _mm_loadu_ps((const float*)(v5 + 16));
            _mm_storeu_ps((float*)(v3 - 6), v6);
            _mm_storeu_ps((float*)(v3 - 4), v7);
        } while (v2 < *((int*)a1 + 2));
    }
}
