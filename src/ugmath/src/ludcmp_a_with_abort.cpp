













#include <math.h>

__declspec(dllimport) void *SM_alloc(unsigned __int64, unsigned __int64);
__declspec(dllimport) void SM_free(void *);

int ludcmp_a_with_abort(double **a, int n, int *indx, double *d, bool (*abort_check)(void))
{
    int i, j, k, imax = -1;
    double big, dum, sum, temp;
    double vv_stack[16];
    double *vv = vv_stack;
    void *heap = 0;

    if (n > 16) {
        heap = SM_alloc(n, 8u);
        vv = (double *)heap;
    }
    *d = 1.0;
    for (i = 0; i < n; i++) {
        big = 0.0;
        for (j = 0; j < n; j++) {
            temp = fabs(a[i][j]);
            if (temp > big)
                big = temp;
        }
        if (big == 0.0)
            goto fail;
        vv[i] = 1.0 / big;
    }
    for (i = 0; i < n; i++) {
        if (abort_check && (i % 400) == 0 && abort_check())
            goto fail;
        for (j = 0; j < i; j++) {
            sum = a[j][i];
            for (k = 0; k < j; k++)
                sum -= a[j][k] * a[k][i];
            a[j][i] = sum;
        }
        big = 0.0;
        for (j = i; j < n; j++) {
            sum = a[j][i];
            for (k = 0; k < i; k++)
                sum -= a[j][k] * a[k][i];
            a[j][i] = sum;
            dum = vv[j] * fabs(sum);
            if (dum >= big) {
                big = dum;
                imax = j;
            }
        }
        if (i != imax) {
            for (k = 0; k < n; k++) {
                dum = a[imax][k];
                a[imax][k] = a[i][k];
                a[i][k] = dum;
            }
            *d = -*d;
            vv[imax] = vv[i];
        }
        indx[i] = imax;
        if (a[i][i] == 0.0)
            a[i][i] = 1.0e-20;
        if (i != n - 1) {
            dum = 1.0 / a[i][i];
            for (k = i + 1; k < n; k++)
                a[k][i] *= dum;
        }
    }
    SM_free(heap);
    return 0;
fail:
    SM_free(heap);
    return 1;
}
