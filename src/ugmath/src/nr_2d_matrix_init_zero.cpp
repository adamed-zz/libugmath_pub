






#include <cstring>

void NR_2d_matrix_init_zero(double **a, int rows, int cols)
{
    if (rows > 0)
    {
        __int64 i = 0;
        do
        {
            if (cols > 0)
                memset(a[i], 0, cols * sizeof(double));
            ++i;
        } while (i < rows);
    }
}
