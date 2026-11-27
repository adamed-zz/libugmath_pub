








#include <intrin.h>

__declspec(dllimport) extern int MACH__checking_level;
__declspec(dllimport) __declspec(noreturn) void ERROR_internal(const char* file, int line, const char* msg, ...);

extern "C" void* memmove(void* dst, const void* src, unsigned long long count);

struct PNTLST_s
{
    double* points;
    int     num;
    int     alloc;
    int     dim;
};

void PNTLST_remove_points(PNTLST_s* a1, int a2, int a3)
{
    if (a1)
    {
        double* points = a1->points;
        int     dim    = a1->dim;
        int     num    = a1->num;
        if (a3 == num)
        {
            a1->num = 0;
        }
        else
        {
            if (MACH__checking_level > 0 && a3 > num)
            {
                ERROR_internal("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\pntlst_gen.c", 233,
                               "Too Many Points To Remove", a2);
                __debugbreak();
            }
            memmove(points + a2 * dim, points + (a2 + a3) * dim,
                    8 * (long long)(num - a2 - a3) * dim);
            a1->num = num - a3;
        }
    }
}
