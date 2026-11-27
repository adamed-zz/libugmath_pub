








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
};

void* SM_alloc(size_t n);
void* SM_calloc(size_t n, size_t m);
void  SM_free(void* p);

int  h0929(int* const a1, double* const a2, double* const a3, double** a4, double* a5);
extern "C" __int64 sub_180036800(int* desc, const double* a2, const double* a3,
                      double** lu, int* indx, double* a6);
extern "C" void sub_180035060(int* a1, const double* a2, const double* a3,
                   __int64* a4, double* a5);
void banbks(double** a, int n, int m1, int m2, double** al, int* indx, double* b);

int h0929a2(int* const a1, double* const a2, double* const a3,
                Solver_data_s& a4, double* a5)
{
    int v5 = a4.method;
    Solver_data_s* v6 = &a4;
    if (!v5)
        return h0929(a1, a2, a3, a4.dense, a5);
    if (v5 == 1)
        return sub_180036800(a1, a2, a3, a4.lu, a4.indx, a5);

    int v45 = a4.band_m;
    int v49[8];
    v49[0] = a1[0];
    v49[1] = a1[1];
    v49[4] = a1[4];
    int v10 = a4.m_size;
    v49[5] = a1[5];
    int v11 = a1[3];
    int v12 = a1[2];
    v49[7] = a1[6];
    v49[2] = v12;
    v49[3] = v11;
    v49[6] = 0;
    char* v47 = (char*)SM_calloc((size_t)((int)v11 * (int)v10), 8u);
    sub_180035060(v49, a2, a3, (__int64*)v6, (double*)v47);
    int v13 = 0;
    double* v48 = (double*)SM_alloc(8 * (size_t)v10);
    double* v14 = v48;
    if (v11 > 0)
    {
        __int64 v15 = 0;
        __int64 v16 = v11;
        __int64 v46 = 0;
        do
        {
            int v17 = 0;
            __int64 v18 = 0;
            if (v10 >= 4)
            {
                double* v19 = v14 + 2;
                __int64 v20 = v13 + 2 * v11;
                __int64 v21 = v15 + v16 - v20;
                __int64 v22 = v46 - v20;
                double* v23 = (double*)&v47[8 * v20];
                __int64 v24 = v11 + v13 + 2 * v11 - v20;
                unsigned int v25 = ((unsigned int)(v10 - 4) >> 2) + 1;
                __int64 v26 = v25;
                v17 = 4 * v25;
                v18 = 4LL * v25;
                do
                {
                    *(v19 - 2) = v23[v22];
                    v19 += 4;
                    *(v19 - 5) = v23[v21];
                    *(v19 - 4) = *v23;
                    double v27 = v23[v24];
                    v23 += 4 * v11;
                    *(v19 - 3) = v27;
                    --v26;
                } while (v26);
                v14 = v48;
                v16 = v11;
                v6 = &a4;
            }
            if (v17 < v10)
            {
                double* v28 = &v14[v18];
                __int64 v29 = (unsigned int)(v10 - v17);
                char* v30 = &v47[8 * v13 + 8 * v11 * v17];
                do
                {
                    __int64 v31 = *(__int64*)v30;
                    v30 += 8 * v16;
                    *(__int64*)v28++ = v31;
                    --v29;
                } while (v29);
            }
            banbks(v6->banded, v10, v45, v45, v6->al, v6->indx, v14);
            int v32 = 0;
            __int64 v33 = 0;
            if (v10 >= 4)
            {
                int v34 = 2;
                double* v35 = v14 + 2;
                v33 = 4LL * (((unsigned int)(v10 - 4) >> 2) + 1);
                do
                {
                    unsigned int v36;
                    if (v12 == 1)
                    {
                        if ((v32 & 1) != 0)
                            v36 = v10 - (v34 - 1) / 2;
                        else
                            v36 = (unsigned int)v32 >> 1;
                    }
                    else
                    {
                        v36 = v32;
                    }
                    a5[(int)(v13 + v11 * v36)] = *(v35 - 2);
                    int v37 = v34 - 1;
                    unsigned int v38, v39, v40;
                    if (v12 == 1)
                    {
                        if ((v37 & 1) != 0)
                            v38 = v10 - v34 / 2;
                        else
                            v38 = (unsigned int)(v34 - 1) >> 1;
                        a5[(int)(v13 + v38 * v11)] = *(v35 - 1);
                        if ((v34 & 1) != 0)
                            v39 = v10 - (v34 + 1) / 2;
                        else
                            v39 = (unsigned int)v34 >> 1;
                        a5[(int)(v13 + v39 * v11)] = *v35;
                        if (((((unsigned char)v34) + 1) & 1) != 0)
                            v40 = v10 - (v34 + 2) / 2;
                        else
                            v40 = (unsigned int)(v34 + 1) >> 1;
                    }
                    else
                    {
                        a5[v13 + v37 * v11] = *(v35 - 1);
                        a5[v13 + v11 * v34] = *v35;
                        v40 = (unsigned int)(v34 + 1);
                    }
                    double v41 = v35[1];
                    v32 += 4;
                    v35 += 4;
                    v34 += 4;
                    a5[(int)(v13 + v11 * v40)] = v41;
                } while (v32 < v10 - 3);
            }
            if (v32 < v10)
            {
                double* v42 = &v14[v33];
                do
                {
                    unsigned int v43;
                    if (v12 == 1)
                    {
                        if ((v32 & 1) != 0)
                            v43 = v10 - (v32 + 1) / 2;
                        else
                            v43 = (unsigned int)v32 >> 1;
                    }
                    else
                    {
                        v43 = v32;
                    }
                    double v44 = *v42;
                    ++v32;
                    ++v42;
                    a5[(int)(v13 + v11 * v43)] = v44;
                } while (v32 < v10);
            }
            ++v13;
            v15 = v46 + 1;
            v16 = v11;
            ++v46;
        } while (v13 < v11);
    }
    SM_free(v14);
    SM_free(v47);
    return 0;
}
