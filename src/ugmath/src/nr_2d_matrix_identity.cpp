


















#include <cstring>

void NR_2d_matrix_identity(double **a, int n)
{
    __int64 count = n;
    if (count > 0)
    {
        double **p = a;
        do
        {
            double *row = *p;
            if (n > 0)
                memset(row, 0, n * sizeof(double));
            double **prev = p++;
            *(double *)((char *)row + ((char *)prev - (char *)a)) = 1.0;
        } while (--count);
    }
}
