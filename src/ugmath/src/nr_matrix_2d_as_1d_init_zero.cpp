












#include <cstring>

void NR_matrix_2d_as_1d_init_zero(double* p, int rows, int cols)
{
    if (rows > 0)
    {
        __int64 v4 = cols;
        __int64 v5 = (unsigned int)rows;
        __int64 v6 = 8LL * cols;
        do
        {
            if (v4 > 0)
                memset(p, 0, v4 << 3);
            p = reinterpret_cast<double*>(reinterpret_cast<char*>(p) + v6);
            --v5;
        } while (v5);
    }
}
