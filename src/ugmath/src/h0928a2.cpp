









#include <cstddef>

struct Solver_data_s
{
    int version;
    int m_size;
    double** dense;
    double** lu;
    int band_m;
    int pad1c;
    double** banded;
    double** al;
    int* indx;
    char pad38[0x30];
    int method;
    void allocate(int n, int m);
};

void* SM_alloc(size_t n);
void  SM_free(void* p);

extern "C" __int64 sub_1800357C0(int* a1, const double* a2, double* a3, double* a4,
                      int* a5, int* a6, double*** a7);
extern "C" void    sub_180034540(int* a1, const double* a2, const double* a3, const double* a4,
                      const int* a5, Solver_data_s* a6);
int     h0928(const int* a1, const double* a2, const double* a3, const double* a4,
              const int* a5, double*** a6);
int     ludcmp_a(double** a, int n, int* indx, double* d);
void    bandec(double** a, int n, int m1, int m2, double** al, int* indx, double* d);

int h0928a2(const int* a1, const double* a2, const double* a3, const double* a4,
                const int* a5, Solver_data_s& a6)
{
    double v31d = 0.0;
    int v6 = a1[1];
    int v8 = a1[2];
    int v10 = a1[4];
    int v12 = a1[0];
    int v14 = a1[5];
    int v15 = v6 - 1;
    Solver_data_s* v16 = &a6;
    int v17 = a1[6] + 1;
    int v19;
    if (v8)
    {
        int v18 = v6 - 1;
        if (v17 <= v15)
            v18 = v17;
        v19 = v14 + v18;
    }
    else
    {
        v19 = v14;
    }
    int v20 = v19 + v10 + v12;
    int v21 = 2;
    if (a6.version >= 22120)
    {
        if (v8 == 1)
        {
            int v22 = v6 - 1;
            if (v17 <= v15)
                v22 = v17;
            if (v12 > 1)
            {
                int v23 = 0;
                while (a3[v23 + 1] > a3[v23])
                {
                    if (++v23 >= v12 - 1)
                        goto LABEL_17;
                }
                v21 = 1;
            }
        LABEL_17:
            if (v12 < v22)
            {
                a6.method = 1;
                goto LU_SOLVE;
            }
        }
    }
    else
    {
        v21 = 0;
    }
    a6.method = v21;
    if (!v21)
    {
        v16->m_size = v20;
        return h0928(a1, a2, a3, a4, a5, &v16->dense);
    }
    if (v21 == 1)
        goto LU_SOLVE;
    if (v8 == 1)
        v15 = 2 * v6 - 2;
    v16->allocate(v20, v15);
    {
        int v32[8];
        v32[0] = a1[0];
        v32[1] = a1[1];
        v32[2] = a1[2];
        v32[3] = a1[3];
        v32[4] = a1[4];
        v32[5] = a1[5];
        v32[6] = 0;
        v32[7] = a1[6];
        sub_180034540(v32, a2, a3, a4, a5, v16);
    }
    bandec(v16->banded, v20, v15, v15, v16->al, v16->indx, &v31d);
    return 0;

LU_SOLVE:
    v16->m_size = v20;
    {
        double** v33 = 0;
        int nCount = 0;
        double v31 = 0.0;
        sub_1800357C0((int*)a1, a2, (double*)a3, (double*)a4, (int*)a5, &nCount,
                      (double***)&v33);
        int v25 = nCount;
        int* v26 = (int*)SM_alloc(4ll * v25);
        int* v29 = v26;
        double** v28 = v33;
        unsigned int v30 = (unsigned int)ludcmp_a(v33, v25, v26, &v31);
        if (v30)
        {
            if (v28)
                SM_free(*v28);
            SM_free(v28);
            SM_free(v29);
            return (int)v30;
        }
        v16->lu = v28;
        v16->indx = v29;
        return 0;
    }
}
