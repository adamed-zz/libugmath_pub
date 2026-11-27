





#include <intrin.h>

struct BCDF_s;


struct BCDF_s_crvatr_data
{
    double* data;
    int     count;
    int     pad_0C;
    int     stride;
};

struct BCDF_s
{
    char                  pad_00[0x28];
    BCDF_s_crvatr_data*   crvatr;
    char                  pad_30[0x50 - 0x30];
    int*                  types;
};

extern "C" {
__declspec(dllimport) extern int MACH__checking_level;
__declspec(dllimport) void ERROR_raise(const char* file, int line, int code,
                                       const char* msg, ...);
}

void BCDF_copy_single_3d_crvatr(struct BCDF_s* a, int index, double* const out, int* flag)
{
    BCDF_s_crvatr_data* v4 = a->crvatr;
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
    if (MACH__checking_level > 0 && (index < 0 || index >= v5))
    {
        ERROR_raise("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\bcdf.c",
                    581, 1005315,
                    "An Invalid Curvature Position Was Given By Calling Routine");
        __debugbreak();
        __assume(0);
    }
    int v9 = index * v7;
    out[0] = v8[v9];
    out[1] = v8[v9 + 1];
    out[2] = v8[v9 + 2];
    *flag = a->types[index];
}
