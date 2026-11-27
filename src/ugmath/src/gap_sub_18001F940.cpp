










#include <cmath>

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

extern "C" __int64 sub_18001F940(const double* a1, const double* a2, const double* a3,
                                 const double* a4, const double* a5, const double* a6, int a7,
                                 const double* a8, double* a9)
{
    (void)a7;


    double s99;
    double c13;
    Vector3 v103;
    __int64 result = sub_18001FDC0(a6, a1, a2, &s99, &c13, &v103);
    if ((int)result)
        return result;

    double v14 = a8[1];
    double v15 = a8[2];
    double v16 = *a2;
    double v17 = *a1 * *a8 + v14 * a1[1] + v15 * a1[2];
    double v18 = *a2 * *a8 + a2[1] * v14 + a2[2] * v15;
    double v19 = *a3 * *a8 + a3[1] * v14 + a3[2] * v15;
    double v20 = *a4 * *a8 + a4[1] * v14 + a4[2] * v15;
    double v21 = *a5 * *a8 + a5[1] * v14 + a5[2] * v15;


    double v22, v23, v24, v25;
    if (fabs(v17) > fabs(v18))
    {

        v22 = 1.0;
        v23 = 0.0;
        v24 = -v18 / v17;
        v25 = -((v24 * v19 + v20) * v24 + (v24 * v20 + v21)) / v17;
    }
    else
    {

        v22 = -v17 / v18;
        v23 = -((v22 * v21 + v20) * v22 + (v22 * v20 + v19)) / v18;
        v24 = 1.0;
        v25 = 0.0;
    }

    double v26 = (v24 + v24) * v22;
    double v27 = *a1 * v25 + v16 * v23;
    double v28 = *a1 * v24 + v16 * v22;
    double v29 = a1[1];
    double v30 = v29 * v25;

    double v31 = v24 * v24 * *a3 + *a4 * v26 + v22 * v22 * *a5 + v27;
    double v32 = v29 * v24 + a2[1] * v22;

    double v33 = v24 * v24 * a3[1] + a4[1] * v26 + v22 * v22 * a5[1] + (v30 + a2[1] * v23);
    double v34 = a1[2];
    double v35 = a2[2] * v22 + v34 * v24;

    double v36 = v24 * v24 * a3[2] + a4[2] * v26 + v22 * v22 * a5[2] + (a2[2] * v23 + v34 * v25);
    double v37 = v28 * v28 + v32 * v32 + v35 * v35;
    double v38 = sqrt(v37);

    double v39 = -(v28 * v31 + v32 * v33 + v36 * v35) * (1.0 / v38) * (1.0 / v38) *
                 (1.0 / v38) * (1.0 / v38);
    *a9 = 1.0 / v38 * v31 * (1.0 / v38) + v28 * v39;
    a9[2] = v36 * (1.0 / v38) * (1.0 / v38) + v35 * v39;
    a9[1] = 1.0 / v38 * v33 * (1.0 / v38) + v39 * v32;
    return 0;
}
