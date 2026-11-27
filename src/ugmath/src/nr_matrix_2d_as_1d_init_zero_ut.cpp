



#include <string.h>



void NR_matrix_2d_as_1d_init_zero_ut(double *a, int n)
{
    if (n > 0)
    {
        __int64 i = 1;
        __int64 off = 0;
        __int64 bound = n;
        __int64 count = (unsigned int)n;
        do
        {
            if (i < bound)
                memset(&a[off + i], 0, 8 * (bound - i));
            off += bound;
            ++i;
            --count;
        } while (count);
    }
}
