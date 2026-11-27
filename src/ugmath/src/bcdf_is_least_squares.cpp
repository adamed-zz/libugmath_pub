








#include <intrin.h>

struct BCDF_s;

__declspec(dllimport) extern int MACH__checking_level;
__declspec(dllimport) void ERROR_internal(const char* file, int line, const char* msg, ...);

int BCDF_is_least_squares(struct BCDF_s* a)
{
    if (MACH__checking_level > 0 && !a)
    {
        ERROR_internal("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\bcdf_gen.c", 3147,
                       "Defining Data Structure Is NULL");
        __debugbreak();
        __assume(0);
    }
    return *((unsigned long long*)a + 1) != 0;
}
