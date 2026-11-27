









#include <intrin.h>

struct PNTLST_s
{
    double* points;
    int     num;
    int     alloc;
    int     dim;
};

__declspec(dllimport) extern int MACH__checking_level;
__declspec(dllimport) void ERROR_internal(const char* file, int line, const char* msg, ...);

void PNTLST_convert_4d_to_3d(PNTLST_s* a1)
{
    double* p = a1->points;
    int dim = a1->dim;
    if (dim != 3)
    {
        if (MACH__checking_level > 0 && dim != 4)
        {
            ERROR_internal("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\pntlst_gen.c", 66,
                           "Dimension Of The Input Points Is Not Valid");
            __debugbreak();
            __assume(0);
        }
        int n = a1->num;
        for (int i = 0; i < n; ++i)
        {
            p[3 * i + 0] = p[4 * i + 0] / p[4 * i + 3];
            p[3 * i + 1] = p[4 * i + 1] / p[4 * i + 3];
            p[3 * i + 2] = p[4 * i + 2] / p[4 * i + 3];
        }
        a1->dim = 3;
    }
}
