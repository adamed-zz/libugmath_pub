







#include <cmath>
#include <cstddef>
#include <cstring>

#include "ugmath/point3.h"
#include "ugmath/vector3.h"
#include "ugmath/mtx4.h"

namespace UGS {
namespace Math {
struct Vector2 {
    double x, y;
};
}
}


using P3 = UGS::Math::Point3;
using V3 = UGS::Math::Vector3;
using V2 = UGS::Math::Vector2;
using M4 = UGS::Math::TransformMatrix;

void ARC_SPLINE_adjust_vec_on_pln(bool flag, V3* normal, V3* vec);
int VEC3_unitize(const V3* v, double tol, double* len, V3* out);
int VEC2_unitize(const V2* v, double tol, double* len, V2* out);
void LSFIT_cre_local_csys(P3* origin, V3* xaxis, V3* zaxis, M4* m, M4* local);
double* sub_18005E110(double* out, double* in, double* m);
double ARC_SPLINE_ask_angle_from_tan(double a1, double a2, int a3);
double ARC_SPLINE_ask_inclination_angle_from_tan_2d(const V2* v);
void ARC_SPLINE_rotate_vector_around_axis(V3* v, V3* axis, double angle, bool flag, V3* out);
double LSFIT_ask_dist_of_two_straight_lines(P3* a1, V3* a2, P3* a3, V3* a4, double* a5,
                                            P3* a6, double* a7, P3* a8, double* a9, bool* a10,
                                            bool* a11);
double LSFIT_ask_dist_pt_to_line_3d(P3* p, P3* origin, V3* dir, double tol, P3* foot,
                                    double* dist);
void ARC_SPLINE_transform_vec_3d(V3* v, M4* m, bool flag, V3* out);


struct CSYS_s;
void LSFIT_line_to_points_3d(P3* pts, int n, V3* dir, int* fit_type, int* status,
                             P3* out_pt, V3* out_dir, double* dev, CSYS_s* csys);


void* SM_alloc(size_t n);
void* SM_realloc(void* p, size_t n);
void SM_free(void* p);

namespace {
const double kUnitTol = 1.0e-10;
const double kMinDen = 1.0e-19;
}

extern "C" void sub_1800523D0(int a1, const double* a2, long long a3, const double* a4,
                              const double* a5, int a6, const double* a7, double* a8, bool* a9,
                              double* a10, double* a11, double* a12, double* a13) {
    (void)a3;
    (void)a6;
    const int npts = a1;
    int v14 = a1;
    const double* v13 = a2;
    const double* v52 = a5;
    double* v16 = a12;


    int v141 = -1;
    int v144 = -1;
    int v143 = -1;
    double devOut[3] = {0.0, 0.0, 0.0};
    double v17 = -1.0e19;
    double v133 = -1.0e19;
    double v18 = 1.0e19;
    const double v170 = 1.0e19;
    P3 v139 = {0.0, 0.0, 0.0};
    P3 v185 = {0.0, 0.0, 0.0};
    P3 v173 = {0.0, 0.0, 0.0};
    P3 v177 = {0.0, 0.0, 0.0};
    V3 v134 = {0.0, 0.0, 1.0};
    V3 v136 = {0.0, 0.0, 0.0};
    P3 v188 = {0.0, 0.0, 0.0};
    P3 v190 = {0.0, 0.0, 0.0};
    P3 v147 = {0.0, 0.0, 0.0};
    P3 v148 = {0.0, 0.0, 0.0};
    double v138[2] = {0.0, 0.0};
    V3 v152 = {0.0, 0.0, 0.0};
    V3 v171 = {0.0, 0.0, 0.0};
    V3 v183 = {0.0, 1.0, 0.0};
    V3 v150 = {0.0, 0.0, 0.0};
    unsigned char v191[144];
    double M[16] = {0};
    double v192[36] = {0};
    double v187[3] = {0.0, 0.0, 0.0};
    double v142 = 0.0;
    double v179 = 0.0;
    double v175[3] = {a7[0], a7[1], a7[2]};
    double* v149 = nullptr;
    double* v50 = nullptr;
    void* v23 = nullptr;
    int iter = 0;
    bool boolTmp = false;
    double dummyD = 0.0;
    int v99 = -1;
    int v69 = -1;
    int v101 = -1;
    double v102 = 0.0;


    {
        double* q = reinterpret_cast<double*>(v191);
        memset(v191, 0, sizeof(v191));
        q[0] = 0.0; q[1] = 0.0; q[2] = 0.0; q[3] = 1.0;
        q[4] = 0.0; q[5] = 0.0; q[6] = 0.0; q[7] = 1.0;
        q[8] = 0.0; q[9] = 0.0; q[10] = 0.0; q[11] = 1.0;
    }

    *a9 = false;
    v16[0] = 0.0; v16[1] = 0.0; v16[2] = 0.0;
    a10[0] = 0.0; a10[1] = 0.0; a10[2] = 0.0;
    a11[0] = 0.0; a11[1] = 0.0; a11[2] = 0.0;
    for (int i = 0; i < 6; ++i) a13[i] = 0.0;


    v16[0] = -a4[0];
    v16[1] = -a4[1];
    v16[2] = -a4[2];

    while (true) {
        char v27 = 0;
        char v28 = 0;
        double v29 = 0.0;
        ARC_SPLINE_adjust_vec_on_pln(true, reinterpret_cast<V3*>(a8),
                                     reinterpret_cast<V3*>(v16));
        const double v31 = v16[0] * a8[2] - a8[0] * v16[2];
        const double v32 = a8[0] * v16[1] - v16[0] * a8[1];
        v150.x = v16[2] * a8[1] - v16[1] * a8[2];
        v150.y = v31;
        v150.z = v32;
        VEC3_unitize(reinterpret_cast<const V3*>(&v150.x), kUnitTol, &v179,
                     reinterpret_cast<V3*>(&v150.x));
        LSFIT_cre_local_csys(reinterpret_cast<P3*>(v175), reinterpret_cast<V3*>(&v150.x),
                             reinterpret_cast<V3*>(a8), reinterpret_cast<M4*>(M),
                             reinterpret_cast<M4*>(v192));

        v23 = SM_realloc(v23, static_cast<size_t>(24) * static_cast<size_t>(v14));
        if (v14 <= 0) break;
        {
            double* v34 = static_cast<double*>(v23);
            const double* v35 = v13;
            int v36 = static_cast<unsigned int>(a1);
            do {
                sub_18005E110(v187, const_cast<double*>(v35), v192);
                v34[0] = v187[0];
                v34[1] = v187[1];
                v34[2] = v187[2];
                if (!v27 || (!v28 && v34[0] > 0.0)) {

                    if (!(v34[1] > -1.0e-10))
                        v28 = 1;
                    else
                        v27 = 1;
                }
                v35 += 3;
                v34 += 3;
                --v36;
            } while (v36);
        }
        if (!v27 || !v28) break;

        {
            int v39 = 0;
            while (v39 < a1) {
                const double* src = static_cast<const double*>(v23) + 3 * v39;
                v152.x = src[0];
                v152.y = src[1];
                v152.z = src[2];
                v138[0] = v152.x;
                v138[1] = v152.y;
                VEC2_unitize(reinterpret_cast<const V2*>(v138), kUnitTol, &v142,
                             reinterpret_cast<V2*>(v138));
                if (v142 > *v52 + 1.0e-10) {
                    const double v43 = ARC_SPLINE_ask_angle_from_tan(v138[1], v138[0], 180);
                    if (v29 - 1.0e-10 > v43) {
                        v29 = v43;
                        const double v44 = v138[0] - *v52;
                        const double v45 = v44 * M[0] + M[4] * v138[1] + M[8] * 0.0 + M[12];
                        const double v46 = v44 * M[1] + M[5] * v138[1] + M[9] * 0.0 + M[13];
                        const double v47 = v44 * M[2] + M[6] * v138[1] + M[10] * 0.0 + M[14];
                        double v48 = v44 * M[3] + M[7] * v138[1] + M[11] * 0.0 + M[15];
                        if (v48 < kMinDen) {
                            if (v48 < 0.0)
                                v48 = fmin(-kMinDen, v48);
                            else
                                v48 = kMinDen;
                        }
                        v16[0] = v45 / v48;
                        v16[1] = v46 / v48;
                        v16[2] = v47 / v48;
                        VEC3_unitize(reinterpret_cast<const V3*>(v16), kUnitTol, &v142,
                                     reinterpret_cast<V3*>(v16));
                    }
                }
                ++v39;
            }
        }
        ++iter;
        v14 = a1;
        v13 = a2;
        if (iter >= 2) {
            ARC_SPLINE_adjust_vec_on_pln(true, reinterpret_cast<V3*>(a8),
                                     reinterpret_cast<V3*>(v16));
            break;
        }
    }
    v14 = a1;

    v50 = static_cast<double*>(SM_alloc(static_cast<size_t>(24) * static_cast<size_t>(v14)));
    v149 = v50;
    {
        int v51 = 0;
        while (v51 < v14) {
            const double* src = static_cast<const double*>(v23) + 3 * v51;
            v152.x = src[0];
            v152.y = src[1];
            v152.z = src[2];
            v138[0] = v152.x;
            v138[1] = v152.y;
            VEC2_unitize(reinterpret_cast<const V2*>(v138), kUnitTol, &v142,
                         reinterpret_cast<V2*>(v138));
            if (!(*v52 >= v142)) {
                const double v57 =
                    ARC_SPLINE_ask_inclination_angle_from_tan_2d(reinterpret_cast<const V2*>(v138));
                ARC_SPLINE_rotate_vector_around_axis(reinterpret_cast<V3*>(&v152.x),
                                                     reinterpret_cast<V3*>(&v134.x), -v57, false,
                                                     reinterpret_cast<V3*>(&v171.x));
                v50[3 * v51] = v171.x;
                v50[3 * v51 + 1] = v171.y;
                v50[3 * v51 + 2] = v171.z;
            } else {
                v50[3 * v51] = 0.0;
                v50[3 * v51 + 1] = 0.0;
                v50[3 * v51 + 2] = 0.0;
            }
            ++v51;
        }
    }

    LSFIT_line_to_points_3d(reinterpret_cast<P3*>(v50), v14,
                            reinterpret_cast<V3*>(&v183.x), &v144, &v143,
                            &v173, &v136, devOut,
                            reinterpret_cast<CSYS_s*>(v191));
    if (v134.y * v136.y + v134.x * v136.x + v134.z * v136.z < 0.0) {
        v136.x = -v136.x;
        v136.y = -v136.y;
        v136.z = -v136.z;
    }

    LSFIT_ask_dist_of_two_straight_lines(
        reinterpret_cast<P3*>(&v177.x), reinterpret_cast<V3*>(&v134.x),
        reinterpret_cast<P3*>(&v173.x), reinterpret_cast<V3*>(&v136.x), const_cast<double*>(v52),
        reinterpret_cast<P3*>(&v139.x), &dummyD, reinterpret_cast<P3*>(&v185.x), &dummyD, a9,
        &boolTmp);
    (void)boolTmp;
    double v59 = v139.z;
    double v60 = v139.y;
    double v61 = v139.x;

    if (!*a9) {

        int v62 = 0;
        const int v63 = a1;
        const double v64 = v134.y;
        const double v68 = v134.x;
        const double v67 = v134.z;
        const double v65 = *v52;
        int v100 = 0;
        bool runTail = false;
        if (a1 < 4) {
            v69 = -1;
            v99 = -1;
            v102 = -1.0e19;
            v18 = v170;
            v101 = -1;
            if (a1 > 0) {
                v133 = -1.0e19;
                v17 = -1.0e19;
                runTail = true;
            } else {
                v102 = v133;
            }
        } else {
            const double* v66 = v50 + 5;
            v69 = -1;
            int counter = 0;
            do {
                double v70 = v17;
                const double v71 = v18;

                const double v72a = ((*(v66 - 5) - v61) * v68 + (*(v66 - 4) - v60) * v64 +
                                     (*(v66 - 3) - v59) * v67);
                const double v73 =
                    (v60 - (v72a * v64 + v60)) * (v60 - (v72a * v64 + v60)) +
                    (v61 - (v72a * v68 + v61)) * (v61 - (v72a * v68 + v61)) +
                    (v59 - (v72a * v67 + v59)) * (v59 - (v72a * v67 + v59));
                const double v74 = sqrt(v73);
                double v72 = v72a;
                if (v65 >= v74) v72 = 0.0;
                if (v18 > v72) v18 = v72;
                int v75 = v62;
                if (v71 <= v72) v75 = v141;
                const double v76 = v18;
                double v77 = v133;
                if (v72 > v133) {
                    v77 = v72;
                    v133 = v72;
                }
                int v78 = v62;
                if (v72 <= v70) v78 = v69;
                const double v79 = v77;

                const double v80a = ((*(v66 - 2) - v61) * v68 + (*(v66 - 1) - v60) * v64 +
                                     (*v66 - v59) * v67);
                const double v81 =
                    (v60 - (v80a * v64 + v60)) * (v60 - (v80a * v64 + v60)) +
                    (v61 - (v80a * v68 + v61)) * (v61 - (v80a * v68 + v61)) +
                    (v59 - (v80a * v67 + v59)) * (v59 - (v80a * v67 + v59));
                const double v82 = sqrt(v81);
                double v80 = v80a;
                if (v65 >= v82) v80 = 0.0;
                if (v18 > v80) v18 = v80;
                int v83 = v62 + 1;
                int v84 = v62 + 1;
                if (v76 <= v80) v84 = v75;
                const double v85 = v18;
                double v86 = v133;
                if (v80 > v133) {
                    v86 = v80;
                    v133 = v80;
                }
                if (v80 <= v79) v83 = v78;
                const double v87 = v86;

                const double v88a = ((v66[1] - v61) * v68 + (v66[2] - v60) * v64 +
                                     (v66[3] - v59) * v67);
                const double v89 =
                    (v60 - (v88a * v64 + v60)) * (v60 - (v88a * v64 + v60)) +
                    (v61 - (v88a * v68 + v61)) * (v61 - (v88a * v68 + v61)) +
                    (v59 - (v88a * v67 + v59)) * (v59 - (v88a * v67 + v59));
                const double v90 = sqrt(v89);
                double v88 = v88a;
                if (v65 >= v90) v88 = 0.0;
                if (v18 > v88) v18 = v88;
                int v91 = v62 + 2;
                int v92 = v62 + 2;
                if (v85 <= v88) v92 = v84;
                const double v93 = v18;
                double v94 = v133;
                if (v88 > v133) {
                    v94 = v88;
                    v133 = v88;
                }
                if (v88 <= v87) v91 = v83;
                const double v95 = v94;

                const double v96a = ((v66[4] - v61) * v68 + (v66[5] - v60) * v64 +
                                     (v66[6] - v59) * v67);
                const double v97 =
                    (v60 - (v96a * v64 + v60)) * (v60 - (v96a * v64 + v60)) +
                    (v61 - (v96a * v68 + v61)) * (v61 - (v96a * v68 + v61)) +
                    (v59 - (v96a * v67 + v59)) * (v59 - (v96a * v67 + v59));
                const double v98 = sqrt(v97);
                double v96 = v96a;
                if (v65 >= v98) v96 = 0.0;
                if (v18 > v96) v18 = v96;
                v69 = v62 + 3;
                v99 = v62 + 3;
                if (v93 <= v96) v99 = v92;
                v141 = v99;
                v17 = v133;
                if (v96 > v133) {
                    v17 = v96;
                    v133 = v96;
                }
                if (v96 <= v95) v69 = v91;
                v101 = v69;
                v100 = counter + 4;
                counter += 4;
                v66 += 12;
                v62 += 4;
            } while (v62 < a1 - 3);
            if (v62 >= a1) {
                v102 = v133;
            } else {

                v69 = v99;
                runTail = true;
            }
        }
        if (runTail) {
            const double* v103 = &v50[3 * v100 + 2];
            int v109 = 0;
            do {
                const double v104 = v17;
                const double v105 = v18;
                const double v106a = ((*(v103 - 2) - v61) * v68 + (*(v103 - 1) - v60) * v64 +
                                      (*v103 - v59) * v67);
                const double v107 =
                    (v60 - (v106a * v64 + v60)) * (v60 - (v106a * v64 + v60)) +
                    (v61 - (v106a * v68 + v61)) * (v61 - (v106a * v68 + v61)) +
                    (v59 - (v106a * v67 + v59)) * (v59 - (v106a * v67 + v59));
                const double v108 = sqrt(v107);
                double v106 = v106a;
                if (v65 >= v108) v106 = 0.0;
                if (v18 > v106) v18 = v106;
                v99 = v62;
                if (v105 <= v106) v99 = v69;
                v17 = v133;
                if (v106 > v133) {
                    v17 = v106;
                    v133 = v106;
                }
                v109 = v62;
                if (v106 <= v104) v109 = v101;
                v103 += 3;
                ++v62;
                v69 = v99;
                v101 = v109;
            } while (v62 < v63);
            v69 = v109;
            v102 = v133;
        }


        const double v110 = v134.z;
        const double v111 = v134.x;
        const double v112 = *v52;
        LSFIT_ask_dist_pt_to_line_3d(reinterpret_cast<P3*>(&v50[3 * v99]),
                                     reinterpret_cast<P3*>(&v139.x),
                                     reinterpret_cast<V3*>(&v134.x), v112,
                                     reinterpret_cast<P3*>(&v188.x), &dummyD);
        LSFIT_ask_dist_pt_to_line_3d(reinterpret_cast<P3*>(&v50[3 * v69]),
                                     reinterpret_cast<P3*>(&v139.x),
                                     reinterpret_cast<V3*>(&v134.x), v112,
                                     reinterpret_cast<P3*>(&v190.x), &dummyD);
        LSFIT_ask_dist_pt_to_line_3d(reinterpret_cast<P3*>(&v188.x),
                                     reinterpret_cast<P3*>(&v173.x),
                                     reinterpret_cast<V3*>(&v136.x), v112,
                                     reinterpret_cast<P3*>(&v147.x), &dummyD);
        LSFIT_ask_dist_pt_to_line_3d(reinterpret_cast<P3*>(&v190.x),
                                     reinterpret_cast<P3*>(&v173.x),
                                     reinterpret_cast<V3*>(&v136.x), v112,
                                     reinterpret_cast<P3*>(&v148.x), &dummyD);

        const double v113 = v52[2];
        const double v114 = -v113;
        if (!(v18 > v113 || v114 > v102)) {
            const double ax = a8[0];
            const double ay = a8[1];
            const double az = a8[2];
            double v118, v119, v116v;
            if (fabs(v102) < fabs(v18)) {
                v61 = v114 * ax + v61;
                v60 = v114 * ay + v60;
                v59 = v114 * az + v59;
                v148.x = v61;
                v148.y = v60;
                v148.z = v59;
                v118 = v61 - v147.x;
                v116v = v60 - v147.y;
                v119 = v59 - v147.z;
            } else {
                v61 = v113 * ax + v61;
                v60 = v113 * ay + v60;
                v59 = v113 * az + v59;
                v147.x = v61;
                v147.y = v60;
                v147.z = v59;
                v118 = v61 - v148.x;
                v116v = v60 - v148.y;
                v119 = v59 - v148.z;
            }
            v136.x = v118;
            v136.y = v116v;
            v136.z = v119;
            if (v64 * v116v + v111 * v118 + v110 * v119 < 0.0) {
                v136.x = -v118;
                v136.y = -v116v;
                v136.z = -v119;
            }
        }
    }


    {
        const double v121 = v61 * M[0] + v60 * M[4] + v59 * M[8] + M[12];
        const double v122 = v61 * M[1] + v60 * M[5] + v59 * M[9] + M[13];
        const double v123 = v61 * M[2] + v60 * M[6] + v59 * M[10] + M[14];
        double v124 = v61 * M[3] + v60 * M[7] + v59 * M[11] + M[15];
        if (v124 < kMinDen) {
            if (v124 < 0.0)
                v124 = fmin(-kMinDen, v124);
            else
                v124 = kMinDen;
        }
        a10[0] = v121 / v124;
        a10[1] = v122 / v124;
        a10[2] = v123 / v124;
        ARC_SPLINE_transform_vec_3d(reinterpret_cast<V3*>(&v136.x), reinterpret_cast<M4*>(M), true,
                                    reinterpret_cast<V3*>(a11));
        if (!*a9) {
            sub_18005E110(v187, &v147.x, M);
            a13[0] = v187[0];
            a13[1] = v187[1];
            a13[2] = v187[2];
            sub_18005E110(v187, &v148.x, M);
            a13[3] = v187[0];
            a13[4] = v187[1];
            a13[5] = v187[2];
        }
    }
    if (v23) SM_free(v23);
    if (v50) SM_free(v50);
}
