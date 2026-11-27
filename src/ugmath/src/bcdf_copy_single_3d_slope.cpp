








#include <intrin.h>

struct BCDF_s;


struct BCDF_slope_data
{
    double* data;
    int     count;
    int     pad_0C;
    int     stride;
};

struct BCDF_s
{
    char              pad_00[0x18];
    BCDF_slope_data*  slope;
    char              pad_20[0x48 - 0x20];
    int*              flags;
};

__declspec(dllimport) extern int MACH__checking_level;
__declspec(dllimport) void ERROR_raise(const char* file, int line, int code,
                                       const char* msg, ...);
void BCDF_copy_single_3d_slope(struct BCDF_s* a, int index, double* const out, int* flag)
{
    BCDF_slope_data* v4 = a->slope;
    int v5 = 0;
    int v7 = 0;
    double* v8;
    if (!v4)
    {
        v8 = 0;
    }
    else
    {
        v5 = v4->count;
        v7 = v4->stride;
        v8 = v4->data;
    }
    if (MACH__checking_level > 0)
    {
        if (!v8)
        {
            ERROR_raise("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\bcdf.c",
                        533, 1005305,
                        "No Slope Allocated In Defining Data Structure.");
            __debugbreak();
            __assume(0);
        }
        if (index < 0 || index >= v5)
        {
            ERROR_raise("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\bcdf.c",
                        537, 1005315,
                        "An Invalid Slope Position Was Given By Calling Routine");
            __debugbreak();
            __assume(0);
        }
    }
    int v9 = index * v7;
    out[0] = v8[v9];
    out[1] = v8[v9 + 1];
    out[2] = v8[v9 + 2];
    *flag = a->flags[index];
}
