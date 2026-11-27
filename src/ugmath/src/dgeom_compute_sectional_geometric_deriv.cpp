







#include <math.h>

namespace UGS { namespace Math { struct Vector3 { double x, y, z; }; } }


int VEC3_unitize(UGS::Math::Vector3 const* u, double tolerance, double* magnitude,
                 UGS::Math::Vector3* result);

int DGEOM_compute_sectional_geometric_deriv(double* const a1, double* const a2,
                                            double* const a3_, int a4,
                                            double* const a5)
{
    UGS::Math::Vector3* a3 = (UGS::Math::Vector3*)a3_;
    const double* p = a3_;


    double v84;
    double v85;
    double v86;
    double v87;
    UGS::Math::Vector3 v88;
    double v90;
    double v91;
    double v92;
    double v93;
    double v94;
    double v95;
    double v96;
    double v97;
    double v98;
    double v99;

    a5[0] = a1[0];
    a5[1] = a1[1];
    a5[2] = a1[2];
    if (a4 == 0)
        return 0;

    if (!VEC3_unitize(a3, 1.0e-10, &v84, a3))
        return -2;

    v88.x = a2[1] * p[2] - a2[2] * p[1];
    v88.y = a2[2] * p[0] - p[2] * a2[0];
    v88.z = p[1] * a2[0] - a2[1] * p[0];
    if (!VEC3_unitize(&v88, 1.0e-10, &v84, &v88))
        return -2;

    a5[3] = v88.x;
    a5[4] = v88.y;
    a5[5] = v88.z;
    if (a4 == 1)
        return 0;


    v98 = a2[0] * p[0] + a2[1] * p[1] + a2[2] * p[2];
    v99 = 1.0 - v98 * v98;
    if (fabs(v99) < 1.0e-10)
        return -2;


    {
        double v18 = a1[3];
        double v20 = a1[4];
        double v22 = a1[5];
        double v19 = a1[6];
        double v21 = a1[7];
        double v23 = a1[8];
        double v14 = v88.x;
        double v24 = v14 * v18;
        double v28 = v14 * v19 + v88.y * v21 + v88.z * v23;
        double v29 = v24 + v88.y * v20 + v88.z * v22;
        v94 = v18 * v18 + v20 * v20 + v22 * v22;
        v92 = v19 * v18 + v21 * v20 + v23 * v22;
        v91 = v19 * v19 + v21 * v21 + v23 * v23;
        v93 = v91 * v94 - v92 * v92;
        if (fabs(v93) < 1.0e-10)
            return -2;
        v87 = (v29 * v91 - v28 * v92) / v93;
        v86 = (v28 * v94 - v29 * v92) / v93;
    }

    v96 = (a2[0] * a1[9] + a2[1] * a1[10] + a2[2] * a1[11]) * v87;
    v95 = a2[0] * a1[12] + a2[1] * a1[13] + a2[2] * a1[14];
    v97 = (a2[0] * a1[15] + a2[1] * a1[16] + a2[2] * a1[17]) * v86;
    {
        double v43 = (v95 + v95) * v87 * v86 + v96 * v87 + v97 * v86;
        v90 = (a2[0] - v98 * p[0]) * v43 / v99;
        a5[6] = v90;
        a5[7] = (a2[1] - v98 * p[1]) * v43 / v99;
        a5[8] = (a2[2] - v98 * p[2]) * v43 / v99;
    }
    if (a4 == 2)
        return 0;

    {
        v84 = a5[7];
        v85 = v84 * a1[4] + a1[3] * v90 + a5[8] * a1[5];
        double v59 = a1[12] * a1[3] + a1[13] * a1[4] + a1[14] * a1[5];
        double v60 = (a1[9] * a1[3] + a1[10] * a1[4] + a1[11] * a1[5]) * v87 * v87;
        double v66 = v85 - v60 - (v59 + v59) * v87 * v86;
        double v68 = v66 - (a1[15] * a1[3] + a1[16] * a1[4] + a1[17] * a1[5]) * v86 * v86;
        double v70 = a1[12] * a1[6] + a1[13] * a1[7] + a1[14] * a1[8];
        double v71 = v84 * a1[7] + a1[6] * v90 + a5[8] * a1[8];
        double v72 = a1[9] * a1[6] + a1[10] * a1[7] + a1[11] * a1[8];
        double v73 = v84 * v84 + v90 * v90 + a5[8] * a5[8];
        double v75 = v71 - v72 * v87 * v87 - (v70 + v70) * v87 * v86
                   - (a1[15] * a1[6] + a1[16] * a1[7] + a1[17] * a1[8]) * v86 * v86;

        double vA = (v68 * v91 - v75 * v92) / v93;
        double vB = (v75 * v94 - v68 * v92) / v93;
        double v79 = 3.0 * ((vA * v86 + vB * v87) * v95 + v96 * vA + v97 * vB)
                   + (a2[0] * a1[18] + a2[1] * a1[19] + a2[2] * a1[20]) * v87 * v87 * v87
                   + (a2[0] * a1[27] + a2[1] * a1[28] + a2[2] * a1[29]) * v86 * v86 * v86
                   + 3.0 * (a2[0] * a1[21] + a2[1] * a1[22] + a2[2] * a1[23]) * v87 * v87 * v86
                   + 3.0 * (a2[0] * a1[24] + a2[1] * a1[25] + a2[2] * a1[26]) * v87 * v86 * v86;

        double v80 = (a2[0] - v98 * p[0]) * v79 / v99 - v73 * a5[3];
        double v81 = v73 * a5[4];
        double v82 = v73 * a5[5];
        a5[9] = v80;
        a5[10] = (a2[1] - v98 * p[1]) * v79 / v99 - v81;
        a5[11] = (a2[2] - v98 * p[2]) * v79 / v99 - v82;
    }
    return 0;
}
