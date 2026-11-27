










#include <math.h>

void h100(const double* a1, const double* a2, double* a3);
void vunt3(const double* a1, int* a2, double* a3);
void h806(const double* a1, const double* a2, const double* a3, int* a4);
void h605(const double* a1, const double* a2, const double* a3, const double* a4,
          int* a5, double* a6, double* a7);
void h110(const double* a1, double* a2);
void h053(const double* a1, const double* a2, double* a3);

void h611(const double* a1, const double* a2, const double* a3, int* a4, double* a5, double* a6)
{
    double v32 = 0.0001;
    double p[9];
    double dir[3];
    double v23, v24, v33, v34;
    double v14, v16, v22;
    double v30[11];
    int v31;
    int v8, v17, v18, v21;

    v33 = 0.0;
    v8 = 1;
    *a4 = 1;
    h100(a1, a3, &p[0]);
    h100(a1 + 3, a3, &p[3]);
    dir[0] = p[3] - p[0];
    dir[1] = p[4] - p[1];
    dir[2] = p[5] - p[2];
    vunt3(dir, &v31, dir);
    h806(&dir[2], &v33, &v32, &v31);
    if (v31)
    {
        h806(&p[2], a2 + 4, &v32, &v31);
        if (!v31)
            return;
        h605(&p[0], &p[3], a2 + 2, a2 + 5, a4, &p[0], &p[3]);
        if (*a4 == 1)
            return;
        if ((unsigned int)(*a4 - 2) < 2)
            goto LABEL_12;
    }
    v14 = (a2[4] - p[2]) / dir[2];
    p[0] = p[0] + dir[0] * v14;
    p[2] = p[2] + dir[2] * v14;
    p[1] = p[1] + dir[1] * v14;
    v24 = p[1] - a2[3];
    v23 = p[0] - a2[2];
    v16 = sqrt(v23 * v23 + v24 * v24);
    v34 = v16;
    h806(&v34, a2 + 5, &v32, &v31);
    if (!v31)
        return;
    *a4 = 2;
LABEL_12:
    h110(a3, v30);
    v17 = *a4;
    if (v17 >= 2)
    {
        v18 = 0;
        v21 = (int)(v17 - 1);
        do
        {
            v22 = p[v18 + 1] - a2[3];
            v23 = p[v18] - a2[2];
            v24 = v22;
            h053(&v24, &v23, &a6[v8 - 1]);
            p[v18 + 2] = a2[4];
            h100(&p[v18], v30, &a5[v18]);
            ++v8;
            v18 += 3;
            --v21;
        } while (v21);
    }
}
