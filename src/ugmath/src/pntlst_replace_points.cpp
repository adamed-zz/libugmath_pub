








#include <intrin.h>

__declspec(dllimport) extern int MACH__checking_level;
__declspec(dllimport) __declspec(noreturn) void ERROR_internal(const char* file, int line, const char* msg, ...);

extern "C" void* memcpy(void* dst, const void* src, unsigned long long count);

struct PNTLST_s
{
    double* points;
    int     num;
    int     alloc;
    int     dim;
};

void PNTLST_replace_points(PNTLST_s* a1, int a2, int a3, double* a4)
{
    double* points = a1->points;
    int     dim    = a1->dim;
    if (MACH__checking_level > 0 && a2 + a3 > a1->num)
    {
        ERROR_internal("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\pntlst_gen.c", 277,
                       "Too Many Points To Replace", a4);
        __debugbreak();
    }
    memcpy(points + a3 * dim, a4, 8 * (long long)a2 * dim);
}
