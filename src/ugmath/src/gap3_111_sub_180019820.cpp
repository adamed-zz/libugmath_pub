





#include <math.h>
#include <intrin.h>

struct BCDF_s;


int  BCDF_curvature_at_point(BCDF_s* a, int idx, int* out);
int  BCDF_slope_at_point(BCDF_s* a, int idx, int* out);
void BCDF_copy_single_3d_slope(BCDF_s* a, int idx, double* const out, int* flag);
void BCDF_copy_single_3d_crvatr(BCDF_s* a, int idx, double* const out, int* flag);
void BCDF_replace_curvature(BCDF_s* a, double* dir, int idx, int flag);



#ifdef BCDF_STANDALONE_TEST
#define BCDF_IMPORT
#else
#define BCDF_IMPORT __declspec(dllimport)
#endif
extern "C" {
BCDF_IMPORT void ERROR_internal(const char* file, int line, const char* msg, ...);
}

extern "C" void sub_180019820(BCDF_s* a1, int a2, double* a3)
{
    int cidx;
    int cflag;
    double crv[3];
    double slp[3];
    int sflag;
    int sidx;
    double dir[4];

    if (!BCDF_curvature_at_point(a1, a2, &cidx))
        return;

    if (BCDF_slope_at_point(a1, a2, &sidx))
    {
        BCDF_copy_single_3d_slope(a1, sidx, slp, &sflag);
        BCDF_copy_single_3d_crvatr(a1, cidx, crv, &cflag);

        double v6 = crv[0];
        double v7 = crv[1];
        double v8 = crv[2];
        double v10 = sqrt(v6 * v6 + v7 * v7 + v8 * v8);
        if (v10 < 1.0e-10)
            return;




        volatile double* va = a3;
        double a30 = va[0];
        double v11 = v7 / v10;
        double v12 = v6 / v10;
        double v13 = v8 / v10;
        double a31 = va[1];
        double a32 = va[2];
        double v14 = a30 * v12;
        double v15 = v11 * a31;
        double v16 = v13 * a32;
        crv[0] = v12;
        crv[1] = v11;
        crv[2] = v13;
        if (fabs(v14 + v15 + v16) < 1.0e-10)
            return;

        double v17 = slp[1];
        double v18 = slp[0];
        double v19 = slp[2];
        double v21 = sqrt(v18 * v18 + v17 * v17 + v19 * v19);
        double v22 = v17 * (1.0 / v21);
        double v23 = v19 * (1.0 / v21);
        double v24 = v18 * (1.0 / v21);
        slp[1] = v22;
        slp[0] = v24;
        slp[2] = v23;

        double v25 = v22 * v13 - v11 * v23;
        double v26 = (v23 * v12 - v13 * v24) * a3[1] + *a3 * v25
                   + (v11 * v24 - v22 * v12) * a3[2];

        double v27 = *a3 - v25 * v26;
        double v28 = a3[2] - (v11 * v24 - v22 * v12) * v26;
        double w1  = a3[1] - (v23 * v12 - v13 * v24) * v26;

        double v30 = sqrt(w1 * w1 + v27 * v27 + v28 * v28);
        double v31 = 1.0 / v30 * v27;
        double v32 = 1.0 / v30 * w1;
        double v33 = 1.0 / v30 * v28;

        double v34 = v31 * v24 + v22 * v32 + v33 * v23;
        double v35 = v31 * v12 + v11 * v32 + v33 * v13;
        double v36 = v34 * v12 - v11 * v35;
        double v37 = v35 * v12 + v11 * v34;
        if (fabs(v37 * a3[1] + *a3 * v36 + v16) > 1.0e-10)
        {
            v36 = v34 * v12 - v11 * -v35;
            v37 = -v35 * v12 + v11 * v34;
        }

        dir[0] = v36 * v10;
        dir[1] = v37 * v10;
        dir[2] = v13 * v10;
        BCDF_replace_curvature(a1, dir, a2, cflag);
    }
    else
    {
        ERROR_internal("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\bcdf_gen.c",
                       1303, "Point With Assigned Curvature Has No Slope");
        __debugbreak();
        __assume(0);
    }
}
