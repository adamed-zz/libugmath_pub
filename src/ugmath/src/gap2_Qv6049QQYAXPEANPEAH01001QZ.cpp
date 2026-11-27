#include <cmath>
#include <xmmintrin.h>
#include <emmintrin.h>

void h805(const double* a, const double* b, const int* mode, int* out);
void vcru3(const double* a, const double* b, int* ok, double* out);

void v6049(double* a1, int* a2, double* a3, int* a4, double* a5, double* a6, int* a7)
{
    int v7;
    __m128d v9;
    double* v11;
    bool v12;
    double v13, v14, v15, v16, v17, v18, v19, v20, v21, v22;
    double* v23;
    double* v24;
    double v25, v26, v27;
    __m128d v28;
    double v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40;
    double v41, v42, v43, v44, v45, v46, v47, v48;
    double v49, v50, v51, v55, v62, v63;




    double v52[3];
    double v56[3];
    double v59[3];
    int v64, v65;

    v7 = 0;
    v9 = _mm_set_sd(1.0);
    v11 = a1;
    *a4 = 0;
    v12 = *a2 == 1;
    v63 = 0.0;
    v50 = 1.0;
    v65 = 1;
    v64 = 0;
    if (v12)
    {
        v55 = fabs(a3[4] * a1[4] + a1[3] * a3[3] + a3[5] * a1[5]);
        h805(&v55, &v50, &v65, &v64);
        if (v64 != 1)
        {
            *a7 = 2;
            return;
        }
        v13 = a3[1] - v11[1];
        v59[0] = *a3 - *v11;
        v14 = a3[2] - v11[2];
        v59[1] = v13;
        v59[2] = v14;
        vcru3(v11 + 3, v59, &v64, v56);
        if (!v64)
            goto LABEL_31;
        vcru3(v56, v11 + 3, &v64, v52);
        v15 = v11[1];
        v16 = v11[2];
        v17 = a3[6];
        v18 = v52[0] * v59[0] + v52[1] * v59[1] + v52[2] * v59[2];
        v19 = v11[6];
    }
    else
    {
        v20 = a1[1] - a3[1];
        v59[0] = *a1 - *a3;
        v21 = a1[2] - a3[2];
        v59[1] = v20;
        v59[2] = v21;
        vcru3(a1 + 3, v59, &v64, v56);
        if (!v64)
            goto LABEL_31;
        vcru3(v56, v11 + 3, &v64, v52);
        v15 = a3[1];
        v16 = a3[2];
        v17 = v11[6];
        v11 = a3;
        v18 = v52[0] * v59[0] + v52[1] * v59[1] + v52[2] * v59[2];
        v19 = a3[3];
    }
    v22 = *v11;
    v51 = v19;
    v62 = v17;
    h805(&v51, &v62, &v65, &v64);
    v23 = a6;
    v24 = a5;
    if (v64 == 1)
    {
        v49 = 1.0;
        v25 = 0.0;
        v26 = 1.0;
        goto LABEL_18;
    }
    v25 = v51 / (v62 * v18 / (v51 - v62) + v18);
    v27 = fabs(v25);
    v55 = v27;
    h805(&v55, &v50, &v65, &v64);
    if (v64 == 1)
    {
        v49 = 0.0;
        v26 = 0.0;
LABEL_18:
        v7 = 4;
        v29 = v52[1] * v25 + v56[1] * v26;
        v30 = v52[2] * v25 + v56[2] * v26;
        *v23 = v52[0] * v25 + v56[0] * v26;
        v23[1] = v29;
        v23[2] = v30;
        v31 = v51 * v23[1] + v15 * v50;
        v32 = v16 * v50 + v51 * v23[2];
        *v24 = v22 * v50 + v51 * *v23;
        v24[1] = v31;
        v24[2] = v32;
        ++*a4;
        h805(&v49, &v63, &v65, &v64);
        if (!v64)
        {
            v7 = 7;
            v33 = v56[1] * -v49;
            v49 = -v49;
            v34 = v52[1] * v25 + v33;
            v35 = v52[2] * v25 + v56[2] * v49;
            v23[3] = v52[0] * v25 + v56[0] * v49;
            v23[4] = v34;
            v23[5] = v35;
            v36 = v15 * v50 + v51 * v23[4];
            v37 = v51 * v23[5] + v16 * v50;
            v24[3] = v22 * v50 + v51 * v23[3];
            v24[4] = v36;
            v24[5] = v37;
            ++*a4;
        }
        goto LABEL_20;
    }
    if (v27 > 1.0)
    {
        v49 = -1.0;
        goto LABEL_20;
    }
    v28 = _mm_set_pd(0.0, 1.0 - v25 * v25);
    if (v28.m128d_f64[0] < 0.0)
        v26 = sqrt(v28.m128d_f64[0]);
    else
        v26 = _mm_sqrt_pd(v28).m128d_f64[0];
    v49 = v26;
    if (v26 >= 0.0)
        goto LABEL_18;
LABEL_20:
    v38 = v51 / (v18 - v62 * v18 / (v62 + v51));
    v39 = fabs(v38);
    v55 = v39;
    h805(&v55, &v50, &v65, &v64);
    if (v64 == 1)
    {
        v49 = 0.0;
        v40 = 0.0;
LABEL_27:
        v41 = v52[1] * v38 + v56[1] * v40;
        v42 = v52[2] * v38 + v56[2] * v40;
        v23[v7 - 1] = v52[0] * v38 + v56[0] * v40;
        v23[v7] = v41;
        v23[v7 + 1] = v42;
        v43 = v51 * v23[v7] + v15 * v50;
        v44 = v16 * v50 + v42 * v51;
        v24[v7 - 1] = v51 * v23[v7 - 1] + v22 * v50;
        v24[v7] = v43;
        v24[v7 + 1] = v44;
        ++*a4;
        h805(&v49, &v63, &v65, &v64);
        if (!v64)
        {
            v49 = -v49;
            v45 = v52[1] * v38 + v56[1] * v49;
            v46 = v52[2] * v38 + v56[2] * v49;
            v23[v7 + 2] = v52[0] * v38 + v56[0] * v49;
            v23[v7 + 3] = v45;
            v23[v7 + 4] = v46;
            v47 = v15 * v50 + v51 * v23[v7 + 3];
            v48 = v16 * v50 + v46 * v51;
            v24[v7 + 2] = v22 * v50 + v51 * v23[v7 + 2];
            v24[v7 + 3] = v47;
            v24[v7 + 4] = v48;
            ++*a4;
        }
        goto LABEL_29;
    }
    if (v39 <= 1.0)
    {
        v9.m128d_f64[0] = 1.0 - v38 * v38;
        v40 = v9.m128d_f64[0] < 0.0 ? sqrt(v9.m128d_f64[0]) : _mm_sqrt_pd(v9).m128d_f64[0];
        v49 = v40;
        if (v40 >= 0.0)
            goto LABEL_27;
    }
LABEL_29:
    if (*a4)
    {
        *a7 = 1;
        return;
    }
LABEL_31:
    *a7 = 3;
}
