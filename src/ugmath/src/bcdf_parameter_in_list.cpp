


















#include <intrin.h>
#include <math.h>

struct BCDF_s;

__declspec(dllimport) extern int MACH__checking_level;
__declspec(dllimport) void ERROR_internal(const char* file_name, int line,
                                                     const char* message, ...);

int BCDF_parameter_in_list(struct BCDF_s* a1, double a2, int* a3)
{
    int found = 0;
    __int64* node = *reinterpret_cast<__int64**>(reinterpret_cast<char*>(a1) + 16);
    int hit = 0;
    if (MACH__checking_level > 0 && !node)
    {
        ERROR_internal("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\bcdf_gen.c", 2470,
                       "The Parameter List Has A NULL Value");
        __debugbreak();
        __assume(0);
    }
    __int64 n = *reinterpret_cast<int*>(node + 1);
    int count = 0;
    double* data = reinterpret_cast<double*>(node[0]);
    if (n > 0)
    {
        __int64 i = 0;
        do
        {
            if (found)
                break;
            if (fabs(data[i] - a2) <= 1.0e-10)
            {
                found = 1;
                hit = 1;
                continue;
            }
            if (data[i] > a2)
            {
                found = 1;
            }
            else
            {
                ++count;
                ++i;
            }
        } while (i < n);
    }
    *a3 = count;
    return hit;
}
