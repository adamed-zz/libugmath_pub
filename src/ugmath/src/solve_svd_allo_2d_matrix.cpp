




















__declspec(dllimport) void *__cdecl SM_alloc(unsigned __int64 size);

double ** __cdecl SOLVE_svd_allo_2d_matrix(int a1, int a2)
{
    double **v5 = (double **)SM_alloc(8LL * (unsigned int)a1);
    if (v5)
    {
        int v6 = 0;
        if (a1 <= 0)
            return v5;
        unsigned __int64 v9 = 8LL * (unsigned int)a2;
        double **v8 = v5;
        do
        {
            void *v10 = SM_alloc(v9);
            *v8 = (double *)v10;
            if (!v10)
                return 0;
            ++v6;
            ++v8;
        } while (v6 < a1);
        return v5;
    }
    return 0;
}
