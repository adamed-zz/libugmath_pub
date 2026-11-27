















#include <cmath>

double EQ_ask_number_tolerance();

void e4322(int* a1, int* a2, double* a3, double* a4, int* a5)
{
    double v9 = EQ_ask_number_tolerance();
    __int64 v10 = *a1;
    double v11 = v9;
    double v12 = *a4;
    int v13 = *a2 - (int)v10;
    int v14 = (int)v10 + 1;
    int v15 = v13 + 1;
    int* v16;
    if (a3[v10] >= *a4)
    {
        v16 = a5;
        *v16 = v14;
        if (v9 >= fabs(a3[v10 - 1] - a3[v10]))
        {
            int v17 = (int)v10 + 2;
            __int64 v18 = (__int64)v17;
            __int64 v19 = (__int64)v13 + 1;
            if (v18 <= v19)
            {
                double* v20 = &a3[v17 - 1];
                while (v18 <= v19)
                {
                    if (fabs(*(v20 - 1) - *v20) > v9)
                    {
                        *v16 = v17;
                        return;
                    }
                    ++v17;
                    ++v18;
                    ++v20;
                }
            }
        }
        goto LABEL_39;
    }
    if (v12 > a3[v13])
    {
        v16 = a5;
        __int64 v21 = v13;
        *v16 = v15;
        double v22 = a3[v13 - 1];
        double* v23 = &a3[v13 - 1];
        __int64 v26 = (__int64)((int)v10 + 2);
        if (!(v9 >= fabs(v22 - a3[v13])) || v13 < v26)
            goto LABEL_39;
        do
        {
            double v24 = *(v23 - 1);
            if (fabs(v24 - v22) > v9)
            {
                *v16 = v13;
                return;
            }
            --v13;
            --v21;
            --v23;
            v22 = v24;
        } while (v21 >= v26);
        goto LABEL_39;
    }
    {
        int est = (int)((double)*a2 * v12);
        if (est + 1 >= v14)
            v10 = (int)est;
        if ((int)v10 + 1 <= v15)
            v13 = (int)v10;
        int v25 = v13 + 1;
        __int64 v26 = v25 - 1;
        double v27 = v12 - a3[v26];
        double* v28 = &a3[v26];
        if (v11 >= fabs(v27))
        {
            do
            {
                if (v25 <= v14)
                    break;
                --v28;
                --v25;
            } while (v11 >= fabs(v12 - *v28));
        }
        v16 = a5;
        int v29 = v25 - 1;
        __int64 v30 = (__int64)v25 - 1;
        double* v31 = &a3[v30 - 1];
        *v16 = v25;
        if (*v31 >= *a4)
        {
            *v16 = *a1 + 1;
            int v32 = *a1 + 1;
            if (v25 > v32)
            {
                while (!(*a4 > *(v31 - 1)) || !(*v31 >= *a4))
                {
                    --v29;
                    --v30;
                    --v31;
                    if (v30 < (__int64)v32)
                        goto LABEL_39;
                }
                *v16 = v29;
            }
        }
        else
        {
            if (*a4 > a3[v25 - 1])
            {
                *v16 = *a2 - *a1 + 1;
                int v35 = *a2 - *a1;
                if (v25 <= v35)
                {
                    int v34 = v25;
                    while (!(*a4 > a3[v34 - 1]) || !(a3[v34] >= *a4))
                    {
                        ++v25;
                        if (++v34 > v35)
                            goto LABEL_39;
                    }
                    *v16 = v25 + 1;
                }
            }
        }
        goto LABEL_39;
    }
LABEL_39:
    {
        int v37 = *v16;
        if (v11 >= fabs(a3[v37 - 2] - a3[v37 - 1]))
        {
            int v38;
            do
            {
                if (v37 <= *a1 + 1)
                    break;
                v38 = v37;
                *v16 = v37 - 1;
                v37 = v37 - 1;
            } while (v11 >= fabs(a3[v38 - 3] - a3[v37 - 1]));
        }
    }
}
