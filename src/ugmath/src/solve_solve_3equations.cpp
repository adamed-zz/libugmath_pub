












#include <intrin.h>

int SOLVE_solve_3equations(double (*const a)[3], double *const b, double *const x)
{
    const double a07 = a[0][7];
    const double a05 = a[0][5];
    const double a00 = a[0][0];
    const double a08 = a[0][8];
    const double a04 = a[0][4];
    const double a02 = a[0][2];
    const double a01 = a[0][1];
    const double v9  = a04 * a08 - a05 * a07;
    const double v10 = a01 * a08 - a02 * a07;
    const double a06 = a[0][6];
    const double v11 = a01 * a05 - a02 * a04;
    const double a03 = a[0][3];
    _ReadWriteBarrier();
    const double a0r = a[0][0];
    const double a6r = a[0][6];
    const double det = a0r * v9 - a03 * v10 + a6r * v11;
    if (det == 0.0)
        return 1;
    const double b0 = b[0];
    const double b1 = b[1];
    const double b2 = b[2];
    x[0] = (b0 * v9 - b1 * v10 + b2 * v11) / det;
    x[1] = ((a6r * a05 - a03 * a08) * b0
          + (a08 * a00 - a06 * a02) * b1
          + (a03 * a02 - a00 * a05) * b2) / det;
    x[2] = ((a6r * a01 - a0r * a07) * b1
          + (a03 * a07 - a06 * a04) * b0
          + (a0r * a04 - a03 * a01) * b2) / det;
    return 0;
}
