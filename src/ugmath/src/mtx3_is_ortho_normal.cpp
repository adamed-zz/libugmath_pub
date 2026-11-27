

















#include <math.h>

namespace UGS {
namespace Math {

struct Matrix3 {
    double m[9];
};

}
}



#ifdef MTX3_STANDALONE_TEST
#define MTX3_IMPORT
#else
#define MTX3_IMPORT __declspec(dllimport)
#endif
MTX3_IMPORT extern int MACH__checking_level;
extern "C" {
MTX3_IMPORT extern bool RDEBUG__enabled;
MTX3_IMPORT int RDEBUG_ask_flag(const char* name, bool flag);
}
MTX3_IMPORT int lprintf(const char* fmt, ...);
MTX3_IMPORT void ERROR_assertion_failed(const char* file, int line,
                                        const char* fmt, ...);

static const char kSrcFile[] = "o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\mtx3.c";



static __forceinline double dot3(const double* p, const double* q)
{
    return p[0] * q[0] + p[1] * q[1] + p[2] * q[2];
}

bool MTX3_is_ortho_normal(const UGS::Math::Matrix3* a1, double a2)
{


    if (MACH__checking_level && !(a2 > 0.0))
        ERROR_assertion_failed(kSrcFile, 1109, "%s", "tolerance > 0.0");
    if (MACH__checking_level && !(a2 < 10.0 * (1.0e-10)))
        ERROR_assertion_failed(kSrcFile, 1110, "%s", "tolerance < 10.0 * (1.0e-10)");

    const double* m = a1->m;
    const double xx = dot3(m + 0, m + 0);
    const double yy = dot3(m + 3, m + 3);
    const double zz = dot3(m + 6, m + 6);
    const double xy = dot3(m + 0, m + 3);
    const double zy = dot3(m + 6, m + 3);
    const double xz = dot3(m + 0, m + 6);


    if (a2 >= fabs(xx - 1.0)
        && a2 >= fabs(yy - 1.0)
        && a2 >= fabs(zz - 1.0)
        && a2 >= fabs(xy)
        && a2 >= fabs(zy)
        && a2 >= fabs(xz))
        return true;



    if (RDEBUG__enabled && RDEBUG_ask_flag("UGMATH_mtx_debug", true) == 1)
    {
        lprintf("X.X - 1.0 = % 14.12e\n", a1->m[0] * a1->m[0] + a1->m[1] * a1->m[1] + a1->m[2] * a1->m[2] - 1.0);
        lprintf("Y.Y - 1.0 = % 14.12e\n", a1->m[3] * a1->m[3] + a1->m[4] * a1->m[4] + a1->m[5] * a1->m[5] - 1.0);
        lprintf("Z.Z - 1.0 = % 14.12e\n", a1->m[6] * a1->m[6] + a1->m[7] * a1->m[7] + a1->m[8] * a1->m[8] - 1.0);
        double t1, t2, t3;
        t1 = a1->m[1] * a1->m[4];
        t2 = a1->m[3] * a1->m[0];
        t3 = a1->m[2] * a1->m[5];
        lprintf("X.Y       = % 14.12e\n", t1 + t2 + t3);
        t1 = a1->m[6] * a1->m[3];
        t2 = a1->m[7] * a1->m[4];
        t3 = a1->m[8] * a1->m[5];
        lprintf("Y.Z       = % 14.12e\n", t1 + t2 + t3);
        t1 = a1->m[1] * a1->m[7];
        t2 = a1->m[6] * a1->m[0];
        t3 = a1->m[2] * a1->m[8];
        lprintf("Z.X       = % 14.12e\n", t1 + t2 + t3);
    }
    return false;
}


bool MTX3_is_ortho_normal(const UGS::Math::Matrix3* a1)
{
    return MTX3_is_ortho_normal(a1, 1.0e-14);
}
