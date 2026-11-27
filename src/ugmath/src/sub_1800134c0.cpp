










#include <cstring>

struct BCDF_s;

int BCDF_return_num_of_points(struct BCDF_s* a1);
double* BCDF_return_param_array(struct BCDF_s* a1, int* a2);
void BCDF_copy_single_3d_point(struct BCDF_s* a1, int a2, double* const a3);
int SOLVE_solve_3equations(double (*const a1)[3], double* const a2, double* const a3);

extern "C" void sub_1800134C0(struct BCDF_s* a1, int a2, double* a3)
{
    int v6 = BCDF_return_num_of_points(a1);
    int v7 = v6 - 2;
    int v40;
    double* v8 = BCDF_return_param_array(a1, &v40);

    struct alignas(16) LocalFrame
    {
        double m00, m01, m02;
        double m10, m11, m12;
        double m20, m21, m22;
        double pad;
        double c1[3];
        double rhs[3];
        double sol[3];
        double c2[3];
        double c0[3];
        double pn2[3];
        double p0[3];
        double p1[3];
    } L;

    BCDF_copy_single_3d_point(a1, v6 - 2, L.pn2);
    BCDF_copy_single_3d_point(a1, 0, L.p0);
    BCDF_copy_single_3d_point(a1, 1, L.p1);

    double v9 = v8[0];
    double v11 = v8[1];
    double v12 = v8[v7] - v8[v6 - 1];

    __int64 v13;


    L.m11 = v9;
    L.m21 = v11;
    L.m01 = v12;
    L.m02 = 1.0;
    L.m12 = 1.0;
    L.m00 = L.m01 * L.m01;
    L.m22 = 1.0;
    L.m10 = v9 * v9;
    L.m20 = v11 * v11;

    for (v13 = 0; v13 < 24; v13 += 8)
    {
        double v14 = *(double*)((char*)L.p0 + v13);
        L.rhs[0] = *(double*)((char*)L.pn2 + v13);
        L.rhs[2] = *(double*)((char*)L.p1 + v13);
        L.rhs[1] = v14;
        if ((unsigned int)SOLVE_solve_3equations((double (*const)[3])&L.m00, L.rhs, L.sol))
            goto copy_out;
        double v15 = L.sol[1];
        *(double*)((char*)L.c2 + v13) = L.sol[0];
        *(double*)((char*)L.c0 + v13) = L.sol[2];
        *(double*)((char*)L.c1 + v13) = v15;
    }

    if (a2 >= 0)
    {
        L.m00 = (L.c2[0] * v9 + L.c1[0]) * v9 + L.c0[0];
        L.m01 = (L.c2[1] * v9 + L.c1[1]) * v9 + L.c0[1];
        L.m02 = (L.c2[2] * v9 + L.c1[2]) * v9 + L.c0[2];
    }
    if (a2 >= 1)
    {
        L.m10 = (L.c2[0] + L.c2[0]) * v9 + L.c1[0];
        L.m11 = (L.c2[1] + L.c2[1]) * v9 + L.c1[1];
        L.m12 = (L.c2[2] + L.c2[2]) * v9 + L.c1[2];
    }
    if (a2 >= 2)
    {
        L.m20 = L.c2[0] + L.c2[0];
        L.m21 = L.c2[1] + L.c2[1];
        L.m22 = L.c2[2] + L.c2[2];
    }

copy_out:
    __int64 v18 = (int)(unsigned int)(3 * a2);
    __int64 v17 = 0;
    for (; v17 <= v18 - 4; v17 += 4)
    {
        *(unsigned __int64*)(a3 + v17 + 0) = *(unsigned __int64*)(&L.m10 + v17 + 0);
        *(unsigned __int64*)(a3 + v17 + 1) = *(unsigned __int64*)(&L.m10 + v17 + 1);
        *(unsigned __int64*)(a3 + v17 + 2) = *(unsigned __int64*)(&L.m10 + v17 + 2);
        *(unsigned __int64*)(a3 + v17 + 3) = *(unsigned __int64*)(&L.m10 + v17 + 3);
    }
    if (v17 < v18)
        memcpy(a3 + v17, &L.m10 + v17, 8 * (v18 - v17));
}
