








#include <intrin.h>

struct BCDF_s;

__declspec(dllimport) extern int MACH__checking_level;
__declspec(dllimport) void ERROR_internal(const char* file, int line,
                                          const char* msg, ...);

double* BCDF_return_knot_sequence(BCDF_s* a, int* count)
{
    if (MACH__checking_level > 0 && !a)
    {
        ERROR_internal("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\bcdf.c", 447,
                       "Defining Data Structure Is NULL");
        __debugbreak();
        __assume(0);
    }
    *count = *reinterpret_cast<int*>(reinterpret_cast<char*>(a) + 0x74);
    return *reinterpret_cast<double**>(reinterpret_cast<char*>(a) + 0x78);
}
