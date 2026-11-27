













#include <intrin.h>

struct BCDF_s;
struct PNTLST_s;



__declspec(dllimport) extern int MACH__checking_level;
__declspec(dllimport) void ERROR_raise(const char* file, int line, int code,
                                       const char* msg, ...);



extern double* PNTLST_copy_points(PNTLST_s* p, int* a2, int* a3);

double* BCDF_copy_parameters(BCDF_s* a, int* count)
{
    PNTLST_s* node =
        *reinterpret_cast<PNTLST_s**>(reinterpret_cast<char*>(a) + 0x10);
    if (MACH__checking_level > 0 && !node)
    {
        ERROR_raise("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\bcdf.c", 702,
                    1005303, "Parameter Array Is NULL");
        __debugbreak();
        __assume(0);
    }
    int tmp;
    return PNTLST_copy_points(node, count, &tmp);
}
