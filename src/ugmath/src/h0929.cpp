









#include <cstdlib>



void* SM_calloc(size_t n, size_t sz);
void SM_free(void* p);
extern "C" __int64 sub_180036070(int* a1, const double* a2, const double* a3, void** a4);
void sub_180037EC0(int n1, int n2, int a1_3, double* mat, double** out, double* rhs);

int h0929(int* const a1, double* const a2, double* const a3, double** a4, double* a5)
{
    int v7;
    if (a1[2])
    {
        int v6 = a1[1] - 1;
        if (a1[6] + 1 <= v6)
            v6 = a1[6] + 1;
        v7 = a1[5] + v6;
    }
    else
    {
        v7 = a1[5];
    }
    int v8 = a1[4] + a1[0];
    void* v12 = 0;
    int v9 = a1[3];
    int v10 = v7 + v8;
    sub_180036070(a1, a2, a3, &v12);
    sub_180037EC0(v10, v10, v9, static_cast<double*>(v12), a4, a5);
    SM_free(v12);
    return 0;
}
