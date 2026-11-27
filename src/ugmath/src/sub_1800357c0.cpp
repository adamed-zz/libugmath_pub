










#include <cstddef>

void* SM_alloc(size_t n);
void* SM_calloc(size_t n, size_t m);
void  SM_free(void* p);

int  h0917(double x, const double* knots, int n, double tol);
int  h0918(double* x, const double* knots, int n, int m);
int  h0916(int n, const double* knots, int start, int order, double t, int span, double* const out);

extern "C" __int64 sub_1800357C0(int* a1, const double* a2, double* a3, double* a4,
                                 int* a5, int* a6, double*** a7)
{
    int v7 = a1[1];
    int v9 = a1[4];
    int v11 = a1[5];
    int v13 = a1[2];
    __int64 v14 = *a1;
    int v15 = a1[6];
    int v16 = v7 - 1;
    int v17 = v15 + 1;
    if (v17 <= v7 - 1)
        v16 = v17;
    int v18 = v11 + v16;
    if (!v13)
        v18 = v11;
    int v58 = (int)v14 + v9 + v18;
    int v19 = v58 + v7;
    double v20 = a2[v58];
    *a6 = v58;
    void** v21 = (void**)SM_alloc(8ll * v58);
    void** v70 = v21;
    v21[0] = SM_calloc((size_t)(int)(v58 * v58), 8u);
    if (v58 > 1)
    {
        for (__int64 v22 = 1; v22 < v58; ++v22)
            v21[v22] = (char*)v21[v22 - 1] + 8 * v58;
    }
    double v67[30];
    if ((int)v14 > 0)
    {
        __int64 v65 = (char*)v21 - (char*)a3;
        for (__int64 v66 = 0; v66 < v14; ++v66)
        {
            double v62 = *a3;
            double v24 = v62;
            if (v62 == v20)
            {
                v24 = v62 + -5.0e-13;
                v62 = v62 + -5.0e-13;
            }
            int v25 = h0917(v24, a2, v19, 0.00001);
            int v26 = v25 - (v7 - 1);
            if (v26 < 0)
                goto FAIL;
            __int64 v27 = v26;
            __int64 v28 = v25;
            if (v26 <= v25)
            {
                int nRc;
                do
                {
                    nRc = h0916(v19, a2, v26, v7, *a3, 0, v67);
                    if (nRc)
                        goto FAIL;
                    ++v26;
                    *(double*)(*(__int64*)((char*)a3 + (size_t)v65) + 8 * v27++) = v67[0];
                    if (v27 > v28)
                        break;
                } while (true);
            }
            ++a3;
        }
    }
    if (v11 + v9 > 0)
    {
        __int64 v23 = v14;
        __int64 v65 = (char*)v21 + 8 * v23 - (char*)a4;
        __int64 v29 = 0;
        for (;;)
        {
            double v62 = *a4;
            if (v62 == v20)
                v62 = v62 + -5.0e-13;
            int v30 = h0918(&v62, a2, v19, v7);
            int v31 = v30 - (v7 - 1);
            __int64 v32 = v30;
            __int64 v33 = v31;
            if (v31 <= v30)
            {
                int nRc;
                do
                {
                    nRc = h0916(v19, a2, v31, v7, *a4, a5[v29], v67);
                    if (nRc)
                        goto FAIL;
                    ++v31;
                    *(double*)(*(__int64*)((char*)a4 + (size_t)v65) + 8 * v33++) =
                        v67[a5[v29]];
                    if (v33 > v32)
                        break;
                } while (true);
            }
            ++v29;
            ++a4;
            if (v29 >= v11 + v9)
                break;
        }
    }
    {
        void** v35 = v70;
        if (v13)
        {
            __int64 v36 = v16;
            int v37 = v58 - v16;
            for (__int64 m = 0; m < v36; ++m)
            {
                double* row = (double*)v35[v14 + v9 + v11 + m];
                row[m] = 9.0;
                row[v37 + m] = -9.0;
            }
        }
        *a7 = (double**)v35;
    }
    return 0;
FAIL:
    SM_free(*(void**)v70);
    SM_free(v70);
    return 2;
}
