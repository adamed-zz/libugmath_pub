








#include <intrin.h>


typedef struct PNTLST_s {
    double* points;
    int num;
    int alloc;
    int dim;
} PNTLST_s;


extern __declspec(dllimport) int MACH__checking_level;
__declspec(dllimport) void ERROR_raise(const char* file, int line, int code, const char* msg, ...);


extern "C" double sqrt(double);

double PNTLST_calc_point_distance(PNTLST_s* pntlst, int i, int j)
{
    double* points = pntlst->points;
    int dim = pntlst->dim;
    if (MACH__checking_level > 0)
    {
        if (i < 0 || i >= pntlst->num || j < 0 || j >= pntlst->num)
        {
            ERROR_raise("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\pntlst_gen.c", 586,
                        1005351, "Invalid Point Position Given");
            __debugbreak();
            __assume(0);
        }
    }
    double sum = 0.0;
    for (int k = 0; k < dim; k++)
    {
        double d = points[j * dim + k] - points[i * dim + k];
        sum += d * d;
    }
    return sqrt(sum);
}
