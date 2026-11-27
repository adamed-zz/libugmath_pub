
















#pragma once


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



double EQ_ask_length_tolerance();
double EQ_ask_length_squared_tolerance();


int VEC3_unitize(const UGS::Math::Vector3* u, double tol, double* len_out,
                 UGS::Math::Vector3* out);


#include <cmath>

extern "C" __int64 sub_18001FDC0(const double* a1, const double* a2, const double* a3,
                                 double* a4, double* a5, UGS::Math::Vector3* a6)
{
    double v14 = *a1;
    double v13 = a1[1];
    double v8 = a1[2];
    double v11 = *a2;
    double v15 = a2[1];
    double v12 = a2[2];
    double v10 = *a3;
    double v6 = a3[1];
    double v9 = a3[2];
    double v31 = 1.0;
    UGS::Math::Vector3 v29 = {0.0, 0.0, 0.0};
    double v16 = v13 * v15 + v14 * v11 + v8 * v12;
    double v17 = v10 * v14 + v6 * v13 + v9 * v8;
    double v18 = v10 * v10 + v6 * v6 + v9 * v9;
    double v19 = v10 * v11 + v6 * v15 + v9 * v12;
    double v20 = v15 * v15 + v11 * v11 + v12 * v12;
    if (!(EQ_ask_length_squared_tolerance() >= fabs(v20)))
    {
        double v21 = v18 - v19 / v20 * v19;
        if (!(EQ_ask_length_squared_tolerance() >= fabs(v21)))
        {
            double* v22 = a5;
            UGS::Math::Vector3* v23 = a6;
            double v24 = (v17 - v19 / v20 * v16) / v21;
            *a5 = v24;
            double v25 = (v16 - v24 * v19) / v20;
            *a4 = v25;
            if (!v23)
                return 0;
            v23->x = v25 * *a2 + *a3 * *v22;
            v23->y = a3[1] * *v22 + a2[1] * *a4;
            v23->z = a3[2] * *v22 + a2[2] * *a4;
            double v26 = EQ_ask_length_tolerance();
            VEC3_unitize(v23, v26, &v31, &v29);
            double v27 = fabs(v31);
            if (!(EQ_ask_length_tolerance() >= v27))
            {
                *a4 = *a4 / v31;
                *v22 = *v22 / v31;
                *v23 = v29;
                return 0;
            }
        }
    }
    return 1;
}
