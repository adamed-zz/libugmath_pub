












#include <intrin.h>


struct BCDF_s;




__declspec(dllimport) extern int MACH__checking_level;
__declspec(dllimport) void ERROR_internal(const char* file, int line, const char* msg, ...);

int BCDF_return_ls_num_of_segments(struct BCDF_s* a)
{
    if (MACH__checking_level > 0)
    {
        if (!a)
        {
            ERROR_internal("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\bcdf.c", 183,
                           "Defining Data Structure Is NULL");
            __debugbreak();
            __assume(0);
        }
        if (!*((void**)a + 1))
        {
            ERROR_internal("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\bcdf.c", 186,
                           "Weights List Has A NULL Value");
            __debugbreak();
            __assume(0);
        }
    }
    return *((int*)a + 26);
}
