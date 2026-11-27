


























#include <cmath>

int h0916(int a1, const double* a2, int a3, int a4, double a5, int a6, double* const a7);
int h0917(double a1, const double* a2, int a3, double a4);
int h0918(double* a1, const double* a2, int a3, int a4);

void h0926a(const int* a1, const double* a2, const double* a3, const double* a4,
            const double* a5, const int* a6, const double* a7, double** a8, double* a9)
{
    (void)a6;
    const int v9 = a1[1];
    int v11 = a1[5];
    const int v12 = a1[2];
    const int v13 = a1[4];
    const int v14 = a1[0];
    const int v15 = a1[3];

    int v16 = v9 - 1;
    if (a1[6] + 1 <= v9 - 1)
        v16 = a1[6] + 1;

    const int v96 = v12;
    const int v89 = v9;
    const int v87 = v13;
    const int v86 = v11;
    const int v95 = v16;

    int v20 = v16 + v11;
    if (!v12)
        v20 = v11;

    const int v94 = v14 + v13 + v20;
    const int v21 = v94 + v9;
    const int v22 = v94;
    const double v23 = a3[v94];

    const double* v24 = a5;
    bool v25;
    if (v13 > 0 || v11 > 0)
        v25 = std::fabs(*a5 - a3[v9 - 1]) < 1.0e-12;
    else
        v25 = false;

    int v26 = 0;
    const int v93 = v14;
    int v84 = 0;
    int v88 = 0;

    if (v94 > 0)
    {
        const int v28 = v15;
        int v29 = 0;
        int v97 = 0;
        int v30 = 0;
        int v98 = 0;
        int v31 = 0;
        const int v100 = v9;
        int v32 = 0;
        int v85 = 0;
        int v92 = 0;
        int v90 = 0;

        while (true)
        {
            int v34;
            int v91;
            int v43;
            double v44;

            if (v25)
            {
                v34 = 1;
                v91 = 1;
                for (int i = 0; i < v28; ++i)
                    a9[v31 + i] = a7[v32 + i];
                v43 = 1;
                v44 = *v24;
                v25 = false;
                const double* v45 = v24 + 1;
                v90 += v28;
                ++v88;
                a5 = v45;
                if (v88 < v87 + v86 && std::fabs(*v45 - v23) < 1.0e-12)
                    v25 = (v26 == v94 - 1);
            }
            else
            {
                v34 = 0;
                v91 = 0;
                v25 = false;
                v43 = 0;
                v44 = a4[v30];
                for (int i = 0; i < v28; ++i)
                    a9[v31 + i] = a2[v29 + i];
                ++v30;
                v84 = v26 + 1;
                v85 = v28 + v29;
                v98 = v30;
                if (v87 + v86 > v88 && v30 < v93)
                {
                    if (std::fabs(a4[v30] - v23) < 1.0e-12 && std::fabs(*v24 - v23) < 1.0e-12)
                        v25 = true;
                    if (std::fabs(*v24 - a4[v30]) < 1.0e-12)
                        v25 = true;
                }
            }

            const double v53 = (v44 == v23) ? v44 + -5.0e-13 : v44;
            double v99 = v53;
            const int v54 = v34 ? h0918(&v99, a3, v21, v9) : h0917(v53, a3, v21, 0.00001);

            if (v9 > 0)
            {
                int v55 = v89;
                int v56 = 0;
                const int v57 = v54;
                int v58 = v54 - (v89 - 1);
                double v101[32];
                while (!h0916(v21, a3, v58, v55, v44, v91, v101))
                {
                    const int v59 = v57 + v56 - (v89 - 1);
                    ++v58;
                    ++v56;
                    a8[v97][v59] = v101[v43];
                    v55 = v89;
                    if (v56 >= v100)
                    {
                        v30 = v98;
                        v31 = v92;
                        goto LABEL_52;
                    }
                }
                return;
            }

        LABEL_52:
            v31 += v28;
            v24 = a5;
            v32 = v90;
            v29 = v85;
            v26 = v84;
            v92 = v31;
            if (++v97 >= v94)
            {
                v11 = v86;
                break;
            }
        }
    }


    if (!v96)
        return;
    const int v60 = v16;
    if (v60 <= 0)
        return;
    for (int j = 0; j < v60; ++j)
    {
        double* row = a8[v14 + v13 + v11 + j];
        row[j] = 9.0;
        row[j + (v94 - v16)] = -9.0;
    }
}
