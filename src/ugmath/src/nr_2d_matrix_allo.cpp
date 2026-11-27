
















__declspec(dllimport) void* SM_alloc(unsigned __int64 size);

double** NR_2d_matrix_allo(int a1, int a2, double** a3)
{
    __int64 v4 = a2;
    __int64 v5 = a1;
    if (!*a3)
    {
        int sz = (int)v5 * (int)v4;
        *a3 = (double*)SM_alloc(8LL * sz);
    }
    double** result = (double**)SM_alloc(8 * v5);
    result[0] = *a3;
    if (v5 > 1)
    {
        __int64 i = 1;
        do
        {
            result[i] = &result[i - 1][a2];
            ++i;
        } while (i < v5);
    }
    return result;
}
