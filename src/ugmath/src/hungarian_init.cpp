













#include <cstddef>
#include <cstdint>
#include <emmintrin.h>

__declspec(dllimport) void* __cdecl SM_alloc(size_t);

struct hungarian_problem_t
{
    int num_rows;
    int num_cols;
    void** rows;
    int* other;
};

int hungarian_init(hungarian_problem_t* a1, double** a2, int a3, int a4, int a5)
{
    __m128d v7 = _mm_setzero_pd();
    __int64 v8 = a4;
    __int64 v9 = a3;
    if ((unsigned)a5 > 1)
        return 10;
    int v11 = a4;
    if (a4 < a3)
        v11 = a3;
    a1->num_rows = v11;
    a1->num_cols = v11;
    __int64 v12 = 8LL * v11;
    a1->rows = (void**)SM_alloc(v12);
    a1->other = (int*)SM_alloc(v12);
    int v13 = 0;
    int v14 = a1->num_rows;
    __int64 v15 = v8;
    if (a1->num_rows > 0)
    {
        __int64 v16 = 0;
        do
        {
            void* v17 = SM_alloc(v12);
            int v18 = 0;
            a1->rows[v16] = v17;
            __int64 v19 = 0;
            a1->other[v16] = -1;
            if (a1->num_cols > 0)
            {
                double* v20 = (double*)a1->rows[v16];
                do
                {
                    double v21 = (v16 >= v9 || v19 >= v15) ? 0.0 : a2[v16][v19];
                    v20[v19] = v21;
                    ++v18;
                    v20 = (double*)a1->rows[v16];
                    double v22 = v20[v19++];
                    v7 = _mm_max_sd(_mm_set_sd(v22), v7);
                } while (v18 < a1->num_cols);
            }
            v14 = a1->num_rows;
            ++v13;
            ++v16;
        } while (v13 < a1->num_rows);
    }
    if (a5 == 1)
    {
        int v23 = 0;
        if (v14 > 0)
        {
            __int64 v24 = 0;
            do
            {
                int v25 = 0;
                if (a1->num_cols > 0)
                {
                    __int64 v26 = 0;
                    do
                    {
                        ++v25;
                        *(double*)(*(uint64_t*)(v24 + (uint64_t)a1->rows) + v26) =
                            _mm_cvtsd_f64(v7) -
                            *(double*)(*(uint64_t*)(v24 + (uint64_t)a1->rows) + v26);
                        v26 += 8;
                    } while (v25 < a1->num_cols);
                }
                ++v23;
                v24 += 8;
            } while (v23 < a1->num_rows);
        }
    }
    return 0;
}
