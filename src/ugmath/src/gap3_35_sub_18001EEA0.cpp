









#include <cmath>
#include <emmintrin.h>

namespace UGS
{
namespace Math
{
struct Vector3
{
    double x, y, z;
};
}
}

using UGS::Math::Vector3;

extern "C" __int64 sub_18001FDC0(const double* a1, const double* a2, const double* a3, double* a4,
                      double* a5, Vector3* a6);

extern "C" __int64 sub_18001EEA0_cppref(const double* a1, const double* a2, const double* a3, const double* a4,
                      const double* a5, const double* a6, const double* a7, const double* a8,
                      const double* a9, const double* a10, int a11, const double* a12,
                      double* a13, double* a14)
{
    (void)a11;
    double* v14 = a13;
    double* v16 = a14;
    if (a13 || a14)
    {
        double s99 = 0.0;
        double c13 = 0.0;
        Vector3 v103 = {0.0, 0.0, 0.0};
        __int64 result = sub_18001FDC0(a10, a1, a2, &s99, &c13, &v103);
        if ((int)result)
            return result;

        double v21 = *a12;
        double v22 = a12[1];
        double v23 = a12[2];
        double v24 = *a6;
        double v25 = *a5;
        double v26 = *a12 * *a1 + v22 * a1[1] + v23 * a1[2];
        double v27 = *a2 * *a12 + a2[1] * v22 + a2[2] * v23;
        double v28 = *a8;
        double v29 = *a3 * *a12 + a3[1] * v22 + a3[2] * v23;
        double v30 = a5[1] * v22;
        double v31 = *a4 * *a12 + a4[1] * v22 + a4[2] * v23;
        c13 = v29;
        double v32 = v25 * v21 + v30 + a5[2] * v23;
        double v33 = a7[1] * v22;
        double v34 = v24 * v21 + a6[1] * v22 + a6[2] * v23;
        s99 = v32;
        double v88 = v34;
        double v93 = *a7 * v21 + v33 + a7[2] * v23;
        double v35 = *a9;
        double v36 = a8[2] * v23;
        double v37 = v28 * v21 + a8[1] * v22;
        double v38 = *a9 * v21;
        double v100 = a9[1];
        double v39 = v37 + v36;
        double v97 = a9[2];
        double v102 = v39;
        double v101 = v35;
        double v91 = v38 + v100 * v22 + v97 * v23;

        double v40, v41, v43, v44, v45, v46, v90, v95, v96;
        if (fabs(v26) <= fabs(v27))
        {
            v90 = 1.0;
            v45 = 0.0;
            v40 = -v26 / v27;
            v96 = 0.0;
            v44 = 1.0;
            v95 = v40;
            v46 = 0.0;
            v41 = -(v40 * v31 + c13 + (v40 * s99 + v31) * v40) / v27;

            v43 = -((v40 * v91 * v40 + (v40 * v39 + v40 * v39)) + v88 + v41 * s99 +
                    (v40 * v39 * v40 + (v40 * v93 + v40 * v93) + v88 + v41 * v31) * v40 +
                    ((v40 * s99 + v31) + (v40 * s99 + v31)) * v41) /
                  v27;
        }
        else
        {
            v40 = 1.0;
            v95 = 1.0;
            v41 = 0.0;
            v90 = -v27 / v26;
            double v42 = v90 * v29 + v31;
            v43 = 0.0;
            v44 = v90;
            v45 = -(v90 * v31 + v32 + v42 * v90) / v26;
            v96 = v45;

            v46 = -((v90 * v88 * v90 + (v90 * v93 + v90 * v93) + v102 + v45 * c13) * v90 +
                    (v90 * v93 * v90 + (v90 * v102 + v90 * v102) + v91 + v45 * v31) +
                    (v42 + v42) * v45) /
                  v26;
        }

        double v47 = v40 * v40;
        double v48 = v44 * v44;
        double v49 = v44 * v44 * v44;
        double v50 = v45 * v40 + v44 * v41;
        double v51 = v40 * v40 * v40;
        double v52 = *a2 * v95;
        c13 = (v44 + v44) * v40;
        double v53 = v44 * 3.0;
        double v54 = v50 * 3.0;
        double v55 = v53 * v90 * v40;
        double v56 = v53 * v95;
        double v57 = v53 * v45;
        double v58 = v56 * v95;
        double v59 = v95 * 3.0 * v41;
        double v92 = *a1 * v90 + v52;
        double v89 = v48 * *a3 + c13 * *a4 + v47 * *a5 + (*a1 * v96 + *a2 * v41);
        double v60 = a2[1] * v95;
        double v61 = a1[1] * v90;

        v101 = (v101 * v51 + *a6 * v49 + (*a1 * v46 + *a2 * v43)) + v54 * *a4 +
               (*a8 * v58 + *a7 * v55) + (v59 * *a5 + v57 * *a3);
        double v62 = v48 * a3[1];
        double v63 = v61 + v60;
        double v64 = v48 * a3[2];
        double v65 = c13 * a4[1];
        s99 = v63;
        double v66 = v47 * a5[1];
        double v67 = v47 * a5[2];
        double v94 = v62 + v65 + v66 + (a1[1] * v96 + a2[1] * v41);
        double v68 = a1[2] * v90;

        v100 = (v100 * v51 + a6[1] * v49 + (a1[1] * v46 + a2[1] * v43)) + v54 * a4[1] +
               (a8[1] * v58 + a7[1] * v55) + (v59 * a5[1] + v57 * a3[1]);
        double v69 = a2[2] * v95 + v68;
        double v70 = c13 * a4[2] + v64;
        double v71 = a2[2];
        double v72 = v71 * v43;
        double v73 = v70 + v67;
        double v74 = a1[2];
        c13 = v73;
        double v75 = v73 + (v71 * v41 + v74 * v96);
        double v76 = a3[2] * v57;
        double v77 = s99;

        double v98 = (v97 * v51 + a6[2] * v49 + (v72 + v74 * v46)) + v54 * a4[2] +
                     (a8[2] * v58 + a7[2] * v55) + (v59 * a5[2] + v76);
        double v78 = v92 * v92 + v77 * v77 + v69 * v69;
        double v79 = sqrt(v78);
        double v80 = v101;
        double v81 = v100;
        double v82 = 1.0 / v79;
        double v83 = v94 * v77 + v89 * v92 + v69 * v75;
        double v84 = -v83 * v82 * v82 * v82 * v82;

        double v85 = (v77 * v100 + v101 * v92 + v69 * v98 +
                      ((v94 * v94 + v89 * v89) + v75 * v75) +
                      v83 * 4.0 * v84 * v78) *
                     (-v82 * v82 * v82 * v82 * v82);
        if (v14)
        {



            __m128d s82 = _mm_set_sd(v82);
            __m128d p0 = _mm_mul_sd(_mm_set_sd(v89), s82);
            p0 = _mm_mul_sd(p0, s82);
            __m128d q0 = _mm_mul_sd(_mm_set_sd(v84), _mm_set_sd(v92));
            v14[0] = _mm_cvtsd_f64(_mm_add_sd(p0, q0));
            __m128d p1 = _mm_mul_sd(_mm_set_sd(v94), s82);
            p1 = _mm_mul_sd(p1, s82);
            __m128d q1 = _mm_mul_sd(_mm_set_sd(v84), _mm_set_sd(v77));
            v14[1] = _mm_cvtsd_f64(_mm_add_sd(p1, q1));
            __m128d p2 = _mm_mul_sd(_mm_set_sd(v75), s82);
            p2 = _mm_mul_sd(p2, s82);
            __m128d q2 = _mm_mul_sd(_mm_set_sd(v69), _mm_set_sd(v84));
            v14[2] = _mm_cvtsd_f64(_mm_add_sd(p2, q2));
        }
        if (v16)
        {
            double v86 = v82 * v82 * v82;
            double v87 = v82 * 3.0 * v84;


            __m128d a0 = _mm_mul_sd(_mm_set_sd(v80), _mm_set_sd(v86));
            a0 = _mm_add_sd(a0, _mm_mul_sd(_mm_set_sd(v89), _mm_set_sd(v87)));
            a0 = _mm_add_sd(a0, _mm_mul_sd(_mm_set_sd(v92), _mm_set_sd(v85)));
            v16[0] = _mm_cvtsd_f64(a0);
            __m128d a1 = _mm_mul_sd(_mm_set_sd(v86), _mm_set_sd(v81));
            a1 = _mm_add_sd(a1, _mm_mul_sd(_mm_set_sd(v94), _mm_set_sd(v87)));
            a1 = _mm_add_sd(a1, _mm_mul_sd(_mm_set_sd(v77), _mm_set_sd(v85)));
            v16[1] = _mm_cvtsd_f64(a1);
            __m128d a2 = _mm_mul_sd(_mm_set_sd(v86), _mm_set_sd(v98));
            a2 = _mm_add_sd(a2, _mm_mul_sd(_mm_set_sd(v75), _mm_set_sd(v87)));
            a2 = _mm_add_sd(a2, _mm_mul_sd(_mm_set_sd(v69), _mm_set_sd(v85)));
            v16[2] = _mm_cvtsd_f64(a2);
        }
    }
    return 0;
}
