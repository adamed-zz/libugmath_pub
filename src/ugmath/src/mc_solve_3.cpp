









#include <math.h>
#include <intrin.h>

struct _iobuf;
extern "C" __declspec(dllimport) struct _iobuf * __cdecl __acrt_iob_func(unsigned _Index);

namespace UGS { namespace System {
__declspec(dllimport) int __cdecl SYSS_fprintf(struct _iobuf *, const char *, ...);
} }

__declspec(dllimport) void __cdecl ERROR_raise(const char *, int, int, const char *, ...);



__declspec(noreturn) __forceinline void MC_solve_3_trap(void) { __debugbreak(); }

#define DET3(a) \
    ((a)[0][0] * (a)[1][1] * (a)[2][2] \
   + (a)[0][1] * (a)[1][2] * (a)[2][0] \
   + (a)[0][2] * (a)[1][0] * (a)[2][1] \
   - (a)[1][1] * (a)[2][0] * (a)[0][2] \
   - (a)[2][1] * (a)[1][2] * (a)[0][0] \
   - (a)[1][0] * (a)[2][2] * (a)[0][1])

void __cdecl MC_solve_3(double (* const a)[4], double * const x)
{
    double det;
    double t;

    det = DET3(a);

    if (fabs(det) < 0.00000001)
    {
        UGS::System::SYSS_fprintf(__acrt_iob_func(1),
                                  "\nERROR: zero determinant in 3 by 3 system\n");
        ERROR_raise("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\mc_math.c", 342, 17,
                    "zero determinant in linear system");
        MC_solve_3_trap();
    }

    t = a[0][0]; a[0][0] = a[0][3]; a[0][3] = t;
    t = a[1][0]; a[1][0] = a[1][3]; a[1][3] = t;
    t = a[2][0]; a[2][0] = a[2][3]; a[2][3] = t;
    x[0] = DET3(a) / det;

    t = a[0][0]; a[0][0] = a[0][3]; a[0][3] = t;
    t = a[1][0]; a[1][0] = a[1][3]; a[1][3] = t;
    t = a[2][0]; a[2][0] = a[2][3]; a[2][3] = t;

    t = a[0][1]; a[0][1] = a[0][3]; a[0][3] = t;
    t = a[1][1]; a[1][1] = a[1][3]; a[1][3] = t;
    t = a[2][1]; a[2][1] = a[2][3]; a[2][3] = t;
    x[1] = DET3(a) / det;

    t = a[0][1]; a[0][1] = a[0][3]; a[0][3] = t;
    t = a[1][1]; a[1][1] = a[1][3]; a[1][3] = t;
    t = a[2][1]; a[2][1] = a[2][3]; a[2][3] = t;

    t = a[0][2]; a[0][2] = a[0][3]; a[0][3] = t;
    t = a[1][2]; a[1][2] = a[1][3]; a[1][3] = t;
    t = a[2][2]; a[2][2] = a[2][3]; a[2][3] = t;
    x[2] = DET3(a) / det;

    t = a[0][2]; a[0][2] = a[0][3]; a[0][3] = t;
    t = a[1][2]; a[1][2] = a[1][3]; a[1][3] = t;
    t = a[2][2]; a[2][2] = a[2][3]; a[2][3] = t;
}
