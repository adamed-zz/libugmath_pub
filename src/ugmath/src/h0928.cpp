







#include <cstdlib>


void* SM_alloc(size_t n);
void* SM_calloc(size_t n, size_t sz);
void SM_free(void* p);
extern "C" __int64 sub_1800357C0(int* a1, const double* a2, double* a3, double* a4,
                                 const int* a5, int* n, void** out);
int h126a(double** ab, int n, double** rows);

int h0928(const int* a1, const double* a2, const double* a3, const double* a4,
          const int* a5, double*** a6)
{
    int v15 = 0;
    void* v16 = 0;
    sub_1800357C0((int*)a1, a2, (double*)a3, (double*)a4, a5, &v15, &v16);
    int n = v15;
    unsigned __int64 v7 = 8ull * n;
    double** v8 = (double**)SM_alloc(v7);
    *v8 = (double*)SM_calloc((size_t)n * n, 8);
    if (n > 1)
    {
        for (int i = 1; i < n; ++i)
            v8[i] = (double*)((char*)v8[i - 1] + v7);
    }
    void** v12 = (void**)v16;
    unsigned int v13 = (unsigned int)h126a((double**)v16, n, v8);
    if (v12)
        SM_free(*v12);
    SM_free(v12);
    if (v13)
    {
        SM_free(*v8);
        SM_free(v8);
        return (int)v13;
    }
    *a6 = v8;
    return 0;
}
