























struct BCDF_s;



struct BCDF_points_s
{
    double* coords;
    int     count;
    int     unused;
    int     dim;
};

struct BCDF_s
{
    BCDF_points_s* points;
};

#ifdef BCDF_SMOKE

extern int MACH__checking_level;
extern void ERROR_raise(const char* file, int line, int code, const char* msg, ...);
#else


__declspec(dllimport) extern int MACH__checking_level;
__declspec(dllimport) void ERROR_raise(const char* file, int line, int code,
                                       const char* msg, ...);
#endif

void BCDF_copy_single_3d_point(struct BCDF_s* a, int index, double* const out)
{
    BCDF_points_s* v4 = a->points;
    if (MACH__checking_level > 0)
    {
        if (!v4)
        {
            ERROR_raise("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\bcdf.c",
                        476, 1005304, "No Points Allocated In Defining Data Structure.");
            __debugbreak();
            __assume(0);
        }
        if (index < 0 || index >= v4->count)
        {
            ERROR_raise("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\bcdf.c",
                        480, 1005302, "Point Position Too Large For Point Array.");
            __debugbreak();
            __assume(0);
        }
    }
    double* v5 = v4->coords;
    int v6 = v4->dim;
    if (MACH__checking_level > 0 && (unsigned)(v6 - 3) > 1)
    {
        ERROR_raise("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\bcdf.c",
                    487, 1005313, "Point Dimension Is Not 3 Or 4.");
        __debugbreak();
        __assume(0);
    }
    int v7 = index * v6;
    double v8 = v5[v7];
    if (v6 == 3)
    {
        out[0] = v8;
        int v9 = 3 * index;
        out[1] = v5[v9 + 1];
        out[2] = v5[v9 + 2];
    }
    else
    {
        out[0] = v8 / v5[v7 + 3];
        out[1] = v5[v7 + 1] / v5[v7 + 3];
        out[2] = v5[v7 + 2] / v5[v7 + 3];
    }
}
