











#include <intrin.h>


struct BCDF_s;




#ifdef BCDF_STANDALONE_TEST
#define BCDF_IMPORT
#else
#define BCDF_IMPORT __declspec(dllimport)
#endif
BCDF_IMPORT extern int MACH__checking_level;
BCDF_IMPORT void ERROR_internal(const char* file, int line, const char* msg, ...);

void BCDF_change_order(struct BCDF_s* a, int order)
{
    if (MACH__checking_level > 0)
    {
        if (order > 25)
        {
            ERROR_internal("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\bcdf_gen.c", 2149,
                           "Maximum Order For Spline Exceeded");
            __debugbreak();
            __assume(0);
        }
        if (order < 2)
        {
            ERROR_internal("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\bcdf_gen.c", 2152,
                           "Order Must Be Greater Than 1");
            __debugbreak();
            __assume(0);
        }
    }
    *((int*)a + 27) = order;
}
