

















#include <cmath>

void e0924(int a1, int a2, double* a3, int* a4)
{
    double v4 = a3[0];
    int v5 = 1;
    *a4 = 0;
    unsigned int v8 = 1;
    double v9 = a3[a1];
    double v10 = a3[a2 - a1];
    if (a2 <= 1)
        return;

#define E0924_STEP(cur, prev)                                                              \
    {                                                                                      \
        double v15 = fabs((cur) - v4);                                                     \
        int v16 = v15 < 1.0e-10;                                                           \
        if (v16)                                                                           \
        {                                                                                  \
            ++v5;                                                                          \
        }                                                                                  \
        else                                                                               \
        {                                                                                  \
            v4 = (cur);                                                                    \
            int v17 = fabs((prev) - v9) < 1.0e-10;                                         \
            int v18 = !(fabs((prev) - v10) < 1.0e-10);                                       \
            if (!v17 && v18 && v5 > *a4)                                                   \
                *a4 = v5;                                                                  \
            v5 = 1;                                                                        \
        }                                                                                  \
    }

    if (a2 > 4)
    {
        unsigned int v13 = ((unsigned int)(a2 - 5) >> 2) + 1;
        unsigned __int64 v12 = (unsigned __int64)v13;
        v8 = 4 * v13 + 1;
        double* v11 = a3 + 2;
        do
        {
            E0924_STEP(v11[-1], v11[-2]);
            E0924_STEP(v11[0], v11[-1]);
            E0924_STEP(v11[1], v11[0]);
            E0924_STEP(v11[2], v11[1]);
            v11 += 4;
            --v12;
        } while (v12);
        if (v8 >= a2)
            return;
    }
    double* v27 = a3 + v8;
    unsigned int v28 = (unsigned int)(a2 - v8);
    do
    {
        E0924_STEP(v27[0], v27[-1]);
        ++v27;
        --v28;
    } while (v28);
#undef E0924_STEP
}
