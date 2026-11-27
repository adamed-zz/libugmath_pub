










#include <cstring>

void NR_matrix_2d_as_1d_init_zero_lt(double* p, int n)
{
    if (n > 0)
    {
        __int64 v3 = 0;
        __int64 v4 = 8LL * n;
        __int64 v5 = (unsigned int)n;
        do
        {
            if (v3 > 0)
                memset(p, 0, 8 * v3);
            ++v3;
            p = reinterpret_cast<double*>(reinterpret_cast<char*>(p) + v4);
            --v5;
        } while (v5);
    }
}
