














#include <math.h>

void __cdecl MC_solve_3(double (* const a)[4], double * const x);

void __cdecl MC_axis_plane_x(double * const a1, double * const a2,
                             double * const a3, double a4,
                             double * const a5)
{
    double m[3][4];
    int i;

    m[0][0] = a3[0];
    m[0][1] = a3[1];
    m[0][2] = a3[2];
    m[0][3] = a4;

    i = 0;
    if (fabs(a1[1]) > fabs(a1[0]))
        i = 1;
    if (fabs(a1[2]) > fabs(a1[i]))
        i = 2;

    switch (i)
    {
    case 0:

        m[1][0] = -a1[2];
        m[1][1] = 0.0;
        m[1][2] = a1[0];
        m[1][3] = a1[0] * a2[2] - a2[0] * a1[2];
        m[2][0] = a1[1];
        m[2][1] = -a1[0];
        m[2][2] = 0.0;
        m[2][3] = a2[0] * a1[1] - a1[0] * a2[1];
        break;
    case 1:

        m[1][0] = 0.0;
        m[1][1] = a1[2];
        m[1][2] = -a1[1];
        m[1][3] = a2[1] * a1[2] - a2[2] * a1[1];
        m[2][0] = a1[1];
        m[2][1] = -a1[0];
        m[2][2] = 0.0;
        m[2][3] = a1[1] * a2[0] - a1[0] * a2[1];
        break;
    default:

        m[1][0] = 0.0;
        m[1][1] = a1[2];
        m[1][2] = -a1[1];
        m[1][3] = a1[2] * a2[1] - a1[1] * a2[2];
        m[2][0] = -a1[2];
        m[2][1] = 0.0;
        m[2][2] = a1[0];
        m[2][3] = a2[2] * a1[0] - a1[2] * a2[0];
        break;
    }

    MC_solve_3(m, a5);
}
