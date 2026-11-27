








#include <cmath>
#include <cstring>

struct BCDF_s;

int BCDF_return_num_of_points(struct BCDF_s* a1);
double* BCDF_return_param_array(struct BCDF_s* a1, int* a2);
void BCDF_copy_single_3d_point(struct BCDF_s* a1, int a2, double* const a3);
void BCDF_copy_single_3d_slope(struct BCDF_s* a1, int a2, double* const a3, int* a4);
int BCDF_slope_at_point(struct BCDF_s* a1, int a2, int* a3);
void BCDF_CALC_mirror_slope(double* a1, double* a2, double* a3, double* a4);
int SOLVE_solve_3equations(double (*const a1)[3], double* const a2, double* const a3);

extern "C" void sub_1800137C0(struct BCDF_s* a1, int a2, double* a3)
{
    int v6 = BCDF_return_num_of_points(a1);
    int v7 = 3 * a2;
    int v71;
    double* v8 = BCDF_return_param_array(a1, &v71);
    if (v7 > 0)
        memset(a3, 0, 8LL * v7);

    double v53[3];
    double v56[3];
    BCDF_copy_single_3d_point(a1, 0, v53);
    BCDF_copy_single_3d_point(a1, 1, v56);

    if (v6 == 2)
    {
        double v9 = 1.0 / (v8[1] - v8[0]);
        double v10 = (v56[1] - v53[1]) * v9;
        a3[0] = (v56[0] - v53[0]) * v9;
        double v11 = v56[2] - v53[2];
        a3[1] = v10;
        a3[2] = v11 * v9;
        return;
    }

    __int64 v12 = 0;
    int v74;
    int v75;
    double v72[3];
    alignas(16) double m[3][3];

    if ((unsigned int)BCDF_slope_at_point(a1, 1, &v74))
    {
        BCDF_copy_single_3d_slope(a1, v74, v72, &v75);
        if (((v75 - 2) & 0xFFFFFFFC) != 0 || v75 == 3)
        {

            double A[3];
            double B[3];
            double C[3];
            double t0 = v8[0];
            double t[3] = {v8[0], v8[1], v8[1]};
            double mat[3][3] = {
                {t[0] * t[0], t[0], 1.0},
                {t[1] * t[1], t[1], 1.0},
                {t[2] + t[2], 1.0, 0.0},
            };
            __int64 k = 0;
            for (; k < 24; k += 8)
            {
                double rhs[3];
                double sol[3];
                rhs[0] = *(double*)((char*)v53 + k);
                rhs[1] = *(double*)((char*)v56 + k);
                rhs[2] = *(double*)((char*)v72 + k);
                if ((unsigned int)SOLVE_solve_3equations(mat, rhs, sol))
                    break;
                *(double*)((char*)A + k) = sol[0];
                *(double*)((char*)C + k) = sol[2];
                *(double*)((char*)B + k) = sol[1];
            }
            if (k >= 24)
            {
                if (a2 >= 0)
                {
                    m[0][0] = (A[0] * t0 + B[0]) * t0 + C[0];
                    m[0][1] = (A[1] * t0 + B[1]) * t0 + C[1];
                    m[0][2] = (A[2] * t0 + B[2]) * t0 + C[2];
                }
                if (a2 >= 1)
                {
                    m[1][0] = (A[0] + A[0]) * t0 + B[0];
                    m[1][1] = (A[1] + A[1]) * t0 + B[1];
                    m[1][2] = (A[2] + A[2]) * t0 + B[2];
                }
                if (a2 >= 2)
                {
                    m[2][0] = A[0] + A[0];
                    m[2][1] = A[1] + A[1];
                    m[2][2] = A[2] + A[2];
                }
            }
        }
        else
        {

            BCDF_CALC_mirror_slope(v72, v53, v56, &m[1][0]);
            double dy = v56[1] - v53[1];
            double dz = v56[2] - v53[2];
            double dx = v56[0] - v53[0];
            double c0 = m[1][2] * dy - m[1][1] * dz;
            double c1 = m[1][0] * dz - m[1][2] * dx;
            double c2 = m[1][1] * dx - m[1][0] * dy;
            double len = std::sqrt(c1 * c1 + c0 * c0 + c2 * c2);
            if (len >= 1.0e-10)
            {
                double inv = 1.0 / len;
                double nx = c0 * inv;
                double ny = c1 * inv;
                double nz = c2 * inv;
                m[2][0] = m[1][1] * nz - m[1][2] * ny;
                m[2][1] = m[1][2] * nx - m[1][0] * nz;
                m[2][2] = m[1][0] * ny - m[1][1] * nx;
            }
        }
    }
    else
    {

        double v73[3];
        BCDF_copy_single_3d_point(a1, 2, v73);
        double A[3];
        double B[3];
        double C[3];
        double t0 = v8[0];
        double t1 = v8[1];
        double t2 = v8[2];
        m[0][0] = t0 * t0;
        m[0][1] = t0;
        m[0][2] = 1.0;
        m[1][0] = t1 * t1;
        m[1][1] = t1;
        m[1][2] = 1.0;
        m[2][0] = t2 * t2;
        m[2][1] = t2;
        m[2][2] = 1.0;
        __int64 k = 0;
        for (; k < 24; k += 8)
        {
            double rhs[3];
            double sol[3];
            rhs[0] = *(double*)((char*)v53 + k);
            rhs[1] = *(double*)((char*)v56 + k);
            rhs[2] = *(double*)((char*)v73 + k);
            if ((unsigned int)SOLVE_solve_3equations(m, rhs, sol))
                break;
            *(double*)((char*)A + k) = sol[0];
            *(double*)((char*)C + k) = sol[2];
            *(double*)((char*)B + k) = sol[1];
        }
        if (k >= 24)
        {
            if (a2 >= 0)
            {
                m[0][0] = (A[0] * t0 + B[0]) * t0 + C[0];
                m[0][1] = (A[1] * t0 + B[1]) * t0 + C[1];
                m[0][2] = (A[2] * t0 + B[2]) * t0 + C[2];
            }
            if (a2 >= 1)
            {
                m[1][0] = (A[0] + A[0]) * t0 + B[0];
                m[1][1] = (A[1] + A[1]) * t0 + B[1];
                m[1][2] = (A[2] + A[2]) * t0 + B[2];
            }
            if (a2 >= 2)
            {
                m[2][0] = A[0] + A[0];
                m[2][1] = A[1] + A[1];
                m[2][2] = A[2] + A[2];
            }
        }
    }



    __int64 v17 = v7;
    if (v17 > 0)
        memcpy(a3, &m[1][0], 8 * v17);
}
