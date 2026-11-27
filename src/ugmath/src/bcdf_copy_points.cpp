







struct BCDF_s;
struct PNTLST_s;

__declspec(dllimport) extern int MACH__checking_level;
__declspec(dllimport) void ERROR_raise(const char* file, int line, int code,
                                       const char* msg, ...);
extern double* PNTLST_copy_points(struct PNTLST_s*, int*, int*);

double* BCDF_copy_points(struct BCDF_s* a, int* c1, int* c2)
{
    PNTLST_s* node = *(PNTLST_s**)a;
    if (MACH__checking_level > 0 && !node)
    {
        ERROR_raise("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\bcdf.c",
                    728, 1005304, "Point Array Is NULL");
        __debugbreak();
        __assume(0);
    }
    return PNTLST_copy_points(node, c1, c2);
}
