








#include <intrin.h>


typedef struct PNTLST_s {
    double* points;
    int num;
    int alloc;
    int dim;
} PNTLST_s;


extern __declspec(dllimport) int MACH__checking_level;
extern __declspec(dllimport) void ERROR_internal(const char* file, int line, const char* msg, ...);


extern "C" void* __cdecl memcpy(void* dst, const void* src, unsigned __int64 size);
#pragma intrinsic(memcpy)

void PNTLST_copy_single_point(PNTLST_s* pntlst, int pos, double* dst)
{
    double* points = pntlst->points;
    int dim = pntlst->dim;
    if (MACH__checking_level > 0 && (pos < 0 || pos > pntlst->num - 1))
    {
        ERROR_internal("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\pntlst_gen.c", 507,
                       "Invalid Point Position Given", (long long)dim);
        __debugbreak();
        __assume(0);
    }
    memcpy(dst, points + pos * dim, 8 * (long long)dim);
}
