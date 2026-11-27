





#include <cstring>

struct BCDF_s;

double* BCDF_return_param_array(struct BCDF_s* a1, int* a2);
void BCDF_copy_single_3d_point(struct BCDF_s* a1, int a2, double* const a3);
int SOLVE_solve_3equations(double (*const a1)[3], double* const a2, double* const a3);

extern "C" void sub_1800131F0(struct BCDF_s* a1, int a2, int a3, double* a4)
{
    __int64 v4 = a2;
    int v39;
    double* v8 = BCDF_return_param_array(a1, &v39);

    struct alignas(16) LocalFrame
    {
        double m[3][3];
        double pad;
        double c1[3];
        double rhs[3];
        double sol[3];
        double c2[3];
        double c0[3];
        double p0[3];
        double p1[3];
        double p2[3];
    } L;

    BCDF_copy_single_3d_point(a1, (int)(v4 - 1), L.p0);
    BCDF_copy_single_3d_point(a1, (int)v4, L.p1);
    BCDF_copy_single_3d_point(a1, (int)(v4 + 1), L.p2);

    double v9 = v8[v4 - 1];
    double v10 = v8[v4];
    double v11 = v8[v4 + 1];

    __int64 v13;

    L.m[0][0] = v9 * v9;
    L.m[0][1] = v9;
    L.m[0][2] = 1.0;
    L.m[1][0] = v10 * v10;
    L.m[1][1] = v10;
    L.m[1][2] = 1.0;
    L.m[2][0] = v11 * v11;
    L.m[2][1] = v11;
    L.m[2][2] = 1.0;

    for (v13 = 0; v13 < 24; v13 += 8)
    {
        double v14 = *(double*)((char*)L.p1 + v13);
        L.rhs[0] = *(double*)((char*)L.p0 + v13);
        L.rhs[2] = *(double*)((char*)L.p2 + v13);
        L.rhs[1] = v14;
        if ((unsigned int)SOLVE_solve_3equations((double (*const)[3])L.m, L.rhs, L.sol))
            goto copy_out;
        double v15 = L.sol[1];
        *(double*)((char*)L.c2 + v13) = L.sol[0];
        *(double*)((char*)L.c0 + v13) = L.sol[2];
        *(double*)((char*)L.c1 + v13) = v15;
    }

    if (a3 >= 0)
    {
        L.m[0][0] = (v10 * L.c2[0] + L.c1[0]) * v10 + L.c0[0];
        L.m[0][1] = (L.c2[1] * v10 + L.c1[1]) * v10 + L.c0[1];
        L.m[0][2] = (L.c2[2] * v10 + L.c1[2]) * v10 + L.c0[2];
    }
    if (a3 >= 1)
    {
        L.m[1][0] = (L.c2[0] + L.c2[0]) * v10 + L.c1[0];
        L.m[1][1] = (L.c2[1] + L.c2[1]) * v10 + L.c1[1];
        L.m[1][2] = (L.c2[2] + L.c2[2]) * v10 + L.c1[2];
    }
    if (a3 >= 2)
    {
        L.m[2][0] = L.c2[0] + L.c2[0];
        L.m[2][1] = L.c2[1] + L.c2[1];
        L.m[2][2] = L.c2[2] + L.c2[2];
    }

copy_out:


    __int64 v17 = (int)(3 * a3);
    if (v17 > 0)
        memcpy(a4, &L.m[1][0], 8 * v17);
}
