
































#include <cstring>

int h0916(int a1, const double* a2, int a3, int a4, double a5, int a6, double* const a7);
int h0917(double a1, const double* a2, int a3, double a4);
int h0918(double* a1, const double* a2, int a3, int a4);

void h0926(const int* a1, const double* a2, const double* a3, const double* a4,
           const int* a5, double* a6)
{
    const int v13 = a1[0];
    const int v6 = a1[1];
    const int v10 = a1[2];
    const int v8 = a1[4];
    const int v12 = a1[5];
    const int v14 = a1[6];
    const int v15 = a1[7];

    int v16 = v6 - 1;
    if (v15 + 1 <= v6 - 1)
        v16 = v15 + 1;
    const int v47 = v16;
    const int v41 = v6 - 1;

    int v18 = v14;
    if (v10)
        v18 = v14 + v16;

    const int v42 = v8 + v14 + v12;
    const int v40 = v13 + v8 + v12 + v18;
    const int v19 = v40 + v6;
    const double v20 = a2[v40];

    if (v40 * v40 > 0)
        memset(a6, 0, 8ull * (unsigned long long)(long long)(v40 * v40));

    double v50[30];

    if (v13 > 0)
    {
        int v22 = 0;
        for (int i = 0; i < v13; ++i)
        {
            double v24 = *a3;
            if (v24 == v20)
                v24 = v24 + -5.0e-13;
            const int v25 = h0917(v24, a2, v19, 0.00001);
            if (v6 > 0)
            {
                int v26 = v25 - v41;
                int v27 = 0;
                double* v28 = &a6[v22 * v40 - v41 + v25];
                while (!h0916(v19, a2, v26, v6, *a3, 0, v50))
                {
                    ++v26;
                    *v28 = v50[0];
                    ++v27;
                    ++v28;
                    if (v27 >= v6)
                        goto knot_done;
                }
                return;
            }
        knot_done:
            ++v22;
            ++a3;
        }
    }

    if (v42 > 0)
    {
        int v30 = v13;
        for (int j = 0; j < v42; ++j)
        {
            double v45 = *a4;
            if (v45 == v20)
                v45 = v45 + -5.0e-13;
            const int v31 = h0918(&v45, a2, v19, v6);
            if (v6 > 0)
            {
                int v33 = v31 - v41;
                int v32 = 0;
                double* v34 = &a6[v30 * v40 - v41 + v31];
                while (!h0916(v19, a2, v33, v6, *a4, *a5, v50))
                {
                    ++v33;
                    ++v32;
                    *v34++ = v50[*a5];
                    if (v32 >= v6)
                        goto parm_done;
                }
                return;
            }
        parm_done:
            ++v30;
            ++a4;
            ++a5;
        }
    }

    if (v10)
    {
        const int v35 = v47;
        if (v35 > 0)
        {
            const int v36 = v13 + v12 + v8;
            for (int i = 0; i < v35; ++i)
            {
                const int v37 = i + v40 * (v36 + i);
                a6[v37] = 9.0;
                a6[v37 + v40 - v35] = -9.0;
            }
        }
    }
}
