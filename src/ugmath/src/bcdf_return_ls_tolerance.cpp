









#include <intrin.h>

struct BCDF_s;

__declspec(dllimport) extern int MACH__checking_level;
__declspec(dllimport) void ERROR_internal(const char* file, int line,
                                          const char* msg, ...);

double BCDF_return_ls_tolerance(struct BCDF_s* a)
{
    if (MACH__checking_level > 0)
    {
        if (!a)
        {
            ERROR_internal("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\bcdf.c", 159,
                           "Defining Data Structure Is NULL");
            __debugbreak();
            __assume(0);
        }
        if (!*reinterpret_cast<unsigned long long*>(reinterpret_cast<char*>(a) + 8))
        {
            ERROR_internal("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\bcdf.c", 162,
                           "Weights List Has A NULL Value");
            __debugbreak();
            __assume(0);
        }
    }
    return *reinterpret_cast<double*>(reinterpret_cast<char*>(a) + 0x60);
}
