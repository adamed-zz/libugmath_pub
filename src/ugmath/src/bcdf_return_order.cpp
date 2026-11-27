










#include <intrin.h>


struct BCDF_s;




#ifdef BCDF_STANDALONE_TEST
#define BCDF_IMPORT
#else
#define BCDF_IMPORT __declspec(dllimport)
#endif
BCDF_IMPORT extern int MACH__checking_level;
BCDF_IMPORT void ERROR_internal(const char* file, int line, const char* msg, ...);

int BCDF_return_order(struct BCDF_s* a)
{
    if (MACH__checking_level > 0 && !a)
    {
        ERROR_internal("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\bcdf.c", 206,
                       "Defining Data Structure Is NULL");
        __debugbreak();
        __assume(0);
    }
    return *((unsigned int*)a + 27);
}
