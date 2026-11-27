

















#include <cstddef>
#include <cstdint>
#include <cmath>

__declspec(dllimport) void* __cdecl SM_alloc(size_t);
__declspec(dllimport) void __cdecl SM_free(void*);

struct hungarian_problem_t
{
    int num_rows;
    int num_cols;
    double** rows;
    int* other;
    double cost;
};


static __forceinline double mn(double x, double m)
{
    return x < m ? x : m;
}

int hungarian_solve(hungarian_problem_t* a1)
{
    double total = 0.0;
    int num_cols = a1->num_cols;
    __int64 num_rows = a1->num_rows;

    int* row_assign = (int*)SM_alloc(4 * num_rows);
    int* free_rows = (int*)SM_alloc(4LL * a1->num_rows);
    double* u = (double*)SM_alloc(8LL * a1->num_rows);
    int* prev = (int*)SM_alloc(4LL * a1->num_rows);
    int* col_assign = (int*)SM_alloc(4LL * a1->num_cols);
    int* col_way = (int*)SM_alloc(4LL * a1->num_cols);
    double* v = (double*)SM_alloc(8LL * a1->num_cols);
    double* slack = (double*)SM_alloc(8LL * a1->num_cols);

    for (int i = 0; i < a1->num_rows; ++i)
    {
        row_assign[i] = 0;
        free_rows[i] = 0;
        u[i] = 0.0;
        prev[i] = 0;
    }
    for (int j = 0; j < a1->num_cols; ++j)
    {
        col_assign[j] = 0;
        col_way[j] = 0;
        v[j] = 0.0;
        slack[j] = 0.0;
    }


    if (num_cols > 0)
    {
        for (__int64 j = 0; j < num_cols; ++j)
        {
            double m = a1->rows[0][j];
            if (num_rows > 1)
            {
                for (__int64 i = 1; i < num_rows; ++i)
                    m = mn(a1->rows[i][j], m);
            }
            total = total + m;
            if (!(1.0e-10 >= fabs(m)))
            {
                for (__int64 i = 0; i < num_rows; ++i)
                    a1->rows[i][j] = a1->rows[i][j] - m;
            }
        }
    }

    for (int j = 0; j < num_cols; ++j)
    {
        col_assign[j] = -1;
        col_way[j] = -1;
        v[j] = 0.0;
        slack[j] = 2147483647.0;
    }


    int free_count = 0;
    if (num_rows > 0)
    {
        __int64 nfree = 0;
        for (__int64 i = 0; i < num_rows; ++i)
        {
            double m = a1->rows[i][0];
            if (num_cols > 1)
            {
                for (__int64 j = 1; j < num_cols; ++j)
                    m = mn(a1->rows[i][j], m);
            }
            u[i] = m;
            int found = 0;
            if (num_cols > 0)
            {
                for (__int64 j = 0; j < num_cols; ++j)
                {
                    if (!(1.0e-10 >= fabs(m - a1->rows[i][j])) || col_assign[j] >= 0)
                        continue;
                    row_assign[i] = (int)j;
                    col_assign[j] = (int)i;
                    found = 1;
                    break;
                }
            }
            if (!found)
            {
                ++free_count;
                row_assign[i] = -1;
                free_rows[nfree++] = (int)i;
            }
        }
    }

    if (free_count != 0)
    {
        int remaining = free_count;
        __int64 q = 0;
        __int64 qn = free_count;
        int row0;
        int col0;

        for (;;)
        {
            for (;;)
            {
                while (q < qn)
                {
                    int r = free_rows[q];
                    if (num_cols <= 0)
                    {
                        ++q;
                        continue;
                    }
                    double ur = u[r];
                    int hit = 0;
                    for (int j = 0; j < num_cols; ++j)
                    {
                        double s = slack[j];
                        if (1.0e-10 >= fabs(s))
                            continue;
                        double cur = a1->rows[r][j] - ur + v[j];
                        if (!(s > cur))
                            continue;
                        if (!(1.0e-10 >= fabs(cur)))
                        {
                            slack[j] = cur;
                            prev[j] = r;
                            continue;
                        }
                        if (col_assign[j] < 0)
                        {
                            row0 = r;
                            col0 = j;
                            hit = 1;
                            break;
                        }
                        slack[j] = 0.0;
                        col_way[j] = r;
                        free_rows[qn++] = col_assign[j];
                    }
                    if (hit)
                        goto found;
                    ++q;
                }

                {
                    double delta = 2147483647.0;
                    for (int j = 0; j < num_cols; ++j)
                        if (!(1.0e-10 >= fabs(slack[j])))
                            delta = mn(slack[j], delta);
                    for (__int64 t = 0; t < qn; ++t)
                    {
                        int r = free_rows[t];
                        u[r] = delta + u[r];
                    }
                    if (num_cols <= 0)
                        continue;
                    int hit = 0;
                    for (int j = 0; j < num_cols; ++j)
                    {
                        if (1.0e-10 >= fabs(slack[j]))
                        {
                            v[j] = delta + v[j];
                            continue;
                        }
                        double s = slack[j] - delta;
                        slack[j] = s;
                        if (!(1.0e-10 >= fabs(s)))
                            continue;
                        int prow = prev[j];
                        if (col_assign[j] >= 0)
                        {
                            col_way[j] = prow;
                            free_rows[qn++] = col_assign[j];
                            continue;
                        }
                        for (int t = j + 1; t < num_cols; ++t)
                            if (1.0e-10 >= fabs(slack[t]))
                                v[t] = delta + v[t];
                        row0 = prow;
                        col0 = j;
                        hit = 1;
                        break;
                    }
                    if (!hit)
                        continue;
                    break;
                }
            }
        found:

            for (;;)
            {
                int old = row_assign[row0];
                row_assign[row0] = col0;
                col_assign[col0] = row0;
                if (old < 0)
                    break;
                row0 = col_way[old];
                col0 = old;
            }

            if (--remaining == 0)
                break;


            free_count = 0;
            for (int t = 0; t < num_cols; ++t)
            {
                col_way[t] = -1;
                slack[t] = 2147483647.0;
            }
            __int64 nfree = 0;
            for (__int64 t = 0; t < num_rows; ++t)
                if (row_assign[t] < 0)
                {
                    ++free_count;
                    free_rows[nfree++] = (int)t;
                }
            q = 0;
            qn = free_count;
        }
    }


    for (__int64 i = 0; i < num_rows; ++i)
        a1->other[i] = row_assign[i];
    for (__int64 j = 0; j < num_rows; ++j)
    {
        for (int t = 0; t < num_cols; ++t)
            a1->rows[j][t] = a1->rows[j][t] - u[j] + v[t];
    }
    for (__int64 i = 0; i < num_rows; ++i)
        total = total + u[i];
    for (int t = 0; t < num_cols; ++t)
        total = total - v[t];
    a1->cost = total;

    SM_free(slack);
    SM_free(v);
    SM_free(col_way);
    SM_free(col_assign);
    SM_free(prev);
    SM_free(u);
    SM_free(free_rows);
    SM_free(row_assign);
    return 0;
}
