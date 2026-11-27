




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

void IPNT3_LST_xtract_pnts(IPNT3_LST_s* a1, double (*a2)[3])
{
    if (MACH__checking_level > 0 && *((int*)a1 + 2) < 0)
    {
        ERROR_internal("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\ipnt.c", 93, "IPNT3_LST_xtract_pnts error", a2);
        __debugbreak();
        __assume(0);
    }
    int v4 = 0;
    if (*((int*)a1 + 2) > 0)
    {
        double* v5 = &(*a2)[2];
        do
        {
            v5 += 3;
            __int64 v6 = 32LL * v4++;
            __int64 v7 = *(uint64_t*)a1 + v6;
            __m128 v8 = _mm_loadu_ps((const float*)v7);
            double v9 = *(const double*)(v7 + 16);
            _mm_storeu_ps((float*)(v5 - 5), v8);
            *(double*)(v5 - 3) = v9;
        } while (v4 < *((int*)a1 + 2));
    }
}
