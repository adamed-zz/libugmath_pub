




#include <intrin.h>
#include <math.h>

struct BCDF_s;

namespace UGS {
namespace Math {

struct Vector3
{
    double x;
    double y;
    double z;
};

}
}

#ifdef BCDF_STANDALONE_TEST
#define BCDF_IMPORT
#else
#define BCDF_IMPORT __declspec(dllimport)
#endif
BCDF_IMPORT void ERROR_internal(const char* file, int line, const char* msg, ...);

extern void BCDF_CALC_auto_curvature(struct BCDF_s* a, int pos, double* out);
extern int BCDF_slope_at_point(struct BCDF_s* a, int pos, int* slope);
extern void BCDF_copy_single_3d_slope(struct BCDF_s* a, int index, double* const out, int* flag);
extern int VEC3_ask_perpendicular(const UGS::Math::Vector3* u, UGS::Math::Vector3* v);
extern void BCDF_replace_curvature(struct BCDF_s* a, double* curv, int idx, int type);

void BCDF_change_curvature(struct BCDF_s* a1, int a2, double* a3, int a4, double a5)
{
    if (a2 == 0)
    {
        BCDF_replace_curvature(a1, a3, a4, 0);
        return;
    }
    if (a2 != 1)
        return;

    double curv[3];
    BCDF_CALC_auto_curvature(a1, a4, curv);
    double len = sqrt(curv[0] * curv[0] + curv[1] * curv[1] + curv[2] * curv[2]);
    if (len < 1.0e-10)
    {
        int slope;
        if (BCDF_slope_at_point(a1, a4, &slope))
        {
            double t[3];
            int flag;
            BCDF_copy_single_3d_slope(a1, slope, t, &flag);
            double inv = 1.0 / sqrt(t[0] * t[0] + t[1] * t[1] + t[2] * t[2]);
            t[0] *= inv;
            t[1] *= inv;
            t[2] *= inv;
            VEC3_ask_perpendicular((const UGS::Math::Vector3*)t, (UGS::Math::Vector3*)curv);
            len = sqrt(curv[0] * curv[0] + curv[1] * curv[1] + curv[2] * curv[2]);
        }
        else
        {
            ERROR_internal("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\bcdf_gen.c", 1092,
                           "Point With Assigned Curvature Has No Slope");
            __debugbreak();
            __assume(0);
        }
    }
    curv[0] = 1.0 / a5 * curv[0] / len;
    curv[1] = 1.0 / a5 * curv[1] / len;
    curv[2] = 1.0 / a5 * curv[2] / len;
    BCDF_replace_curvature(a1, curv, a4, 1);
}
