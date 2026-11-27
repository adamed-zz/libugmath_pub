

















#include <cstring>

void NR_matrix_2d_as_1d_identity(double* a, int n)
{
    if (n > 0)
    {
        double* diag = a;
        double* row = a;
        __int64 v4 = n;
        __int64 v5 = 8LL * (n + 1);
        __int64 v6 = 8LL * n;
        __int64 v7 = (unsigned int)n;
        do
        {
            if (v4 > 0)
                memset(row, 0, v4 << 3);
            *diag = 1.0;
            row = reinterpret_cast<double*>(reinterpret_cast<char*>(row) + v6);
            diag = reinterpret_cast<double*>(reinterpret_cast<char*>(diag) + v5);
            --v7;
        } while (v7);
    }
}
