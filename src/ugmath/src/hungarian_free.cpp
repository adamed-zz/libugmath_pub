



#include <cstddef>
#include <cstdint>
#include <xmmintrin.h>

__declspec(dllimport) void* __cdecl SM_alloc(size_t);
__declspec(dllimport) void* __cdecl SM_realloc(void*, size_t);
__declspec(dllimport) void __cdecl SM_free(void*);
extern __declspec(dllimport) int MACH__checking_level;
__declspec(dllimport) void ERROR_internal(const char*, int, const char*, ...);

struct hungarian_problem_t
{
    int n;
    void* rows;
    void* other;
};

void hungarian_free(hungarian_problem_t* a1)
{
    int v2 = 0;
    if (a1->n > 0)
    {
        __int64 v3 = 0;
        do
        {
            ++v2;
            SM_free(*(void**)(v3 + (uint64_t)a1->rows));
            v3 += 8;
        } while (v2 < a1->n);
    }
    SM_free(a1->rows);
    SM_free(a1->other);
    a1->rows = 0;
    a1->other = 0;
}
