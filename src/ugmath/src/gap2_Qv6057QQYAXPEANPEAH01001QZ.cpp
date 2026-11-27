#include <cmath>
#include <xmmintrin.h>
#include <emmintrin.h>

void h805(const double* a, const double* b, const int* mode, int* out);
void vcru3(const double* a, const double* b, int* ok, double* out);
void vunt3(const double* a, int* ok, double* out);

void v6057(double* a1, int* a2, double* a3, int* a4, double* a5, double* a6, int* a7)
{
    int* v7;
    bool v10;
    double v11, v12, v13, v14, v15, v16;
    __m128d v17;
    double v18, v19, v20;
    double* v21;
    double* v22;
    double v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34;
    double v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47;
    double* v48;
    double* v49;
    double* v50;
    double* v51;
    double v52, v53, v54, v55, v56, v57, v58, v59, v60, v61, v62, v63, v64;
    __int64 v65;
    double* v66;
    double v67, v68, v69, v70, v71, v72, v73, v74;
    double v75, v76, v83, v87, v88;




    double v77[3];
    double v80[3];
    double v84[3];
    double v89, v90, v91;
    int v92, v93;

    v7 = a7;
    *a4 = 0;
    v10 = *a2 == 1;
    v11 = a3[2];
    v12 = *a3;
    v13 = *a1 - *a3;
    v14 = a3[1];
    v15 = a1[1] - v14;
    v16 = a1[2] - v11;
    v17 = _mm_set_sd(1.0);
    v77[2] = v16;
    v76 = 1.0;
    v87 = 0.0;
    v77[0] = v13;
    v77[1] = v15;
    v93 = 1;
    v92 = 0;
    if (v10)
    {
        vcru3(a3 + 3, v77, &v92, v84);
        if (!v92)
            goto LABEL_31;
        vcru3(v84, a3 + 3, &v92, v80);
        v18 = a3[6] / (v80[0] * v77[0] + v80[1] * v77[1] + v80[2] * v77[2]);
        v19 = fabs(v18);
        v83 = v19;
        h805(&v83, &v76, &v93, &v92);
        if (v92 == 1)
        {
            v75 = 0.0;
            v20 = 0.0;
LABEL_10:
            v21 = a6;
            v22 = a5;
            v23 = v20 * v84[2] + v80[2] * v18;
            v24 = v20 * v84[1] + v80[1] * v18;
            *(double*)a6 = v20 * v84[0] + v80[0] * v18;
            v21[1] = v24;
            v21[2] = v23;
            v25 = a3[6];
            v26 = v25 * v21[1] + v76 * a3[1];
            v27 = v76 * *a3 + v25 * *v21;
            v28 = v25 * v21[2] + v76 * a3[2];
            *v22 = v27;
            v22[1] = v26;
            v22[2] = v28;
            ++*a4;
            h805(&v75, &v87, &v93, &v92);
            if (!v92)
            {
                v29 = -v75 * v84[1] + v80[1] * v18;
                v30 = -v75 * v84[2] + v80[2] * v18;
                v21[3] = -v75 * v84[0] + v80[0] * v18;
                v21[4] = v29;
                v21[5] = v30;
                v31 = a3[6];
                v32 = v31 * v21[4] + v76 * a3[1];
                v33 = v76 * *a3 + v31 * v21[3];
                v34 = v31 * v21[5] + v76 * a3[2];
                v22[3] = v33;
                v22[4] = v32;
                v22[5] = v34;
                ++*a4;
            }
            goto LABEL_29;
        }



        if (!(v19 > 1.0))
        {
            v17.m128d_f64[0] = 1.0 - v18 * v18;
            v20 = v17.m128d_f64[0] < 0.0 ? sqrt(v17.m128d_f64[0])
                                         : _mm_sqrt_pd(v17).m128d_f64[0];
            v75 = v20;
            if (v20 >= 0.0)
                goto LABEL_10;
        }
    }
    else
    {
        v35 = a3[3];
        v36 = a3[5];
        v37 = a3[4] * v15 + v35 * v13 + v36 * v16;
        v38 = v35 * v37 + v12;
        v89 = a3[4] * v37 + v14;
        v90 = v36 * v37 + v11;
        v91 = v38;
        h805(a3 + 6, &v87, &v93, &v92);
        if (v92 == 1)
        {
            v39 = *a3;
            v40 = a3[1];
            v88 = a3[2];
            v41 = sin(a3[7]) * fabs(v37);
            v42 = v41 / cos(a3[7]);
        }
        else
        {
            v43 = cos(a3[7]) * a3[6];
            v44 = v43 / sin(a3[7]);
            v40 = v44 * a3[4] + v76 * a3[1];
            v39 = v44 * a3[3] + v76 * *a3;
            v45 = v44 * a3[5] + v76 * a3[2];
            v42 = (v44 - v37) * a3[6] / v44;
            v38 = v91;
            v88 = v45;
        }
        vcru3(a3 + 3, v77, &v92, v84);
        if (!v92)
            goto LABEL_31;
        vcru3(v84, a3 + 3, &v92, v80);
        v46 = v42 / (v80[0] * v77[0] + v80[1] * v77[1] + v80[2] * v77[2]);
        v83 = fabs(v46);
        h805(&v83, &v76, &v93, &v92);
        if (v92 == 1)
        {
            v75 = 0.0;
            v47 = 0.0;
        }
        else
        {
            if (fabs(v46) > 1.0)
                goto LABEL_29;
            v17.m128d_f64[0] = 1.0 - v46 * v46;
            v47 = v17.m128d_f64[0] < 0.0 ? sqrt(v17.m128d_f64[0])
                                         : _mm_sqrt_pd(v17).m128d_f64[0];
            v75 = v47;



            if (!(v47 >= 0.0))
                goto LABEL_29;
        }
        v48 = a5;
        v49 = a6;
        v50 = (double*)a6;
        v51 = a6;
        v52 = v88;
        v53 = v88;
        v54 = v80[0] * v46 + v47 * v84[0];
        v55 = v80[2] * v46 + v47 * v84[2];
        v56 = v90 * v76;
        v57 = v80[1] * v46 + v47 * v84[1];
        v58 = v89 * v76;
        v77[0] = v54;
        v77[2] = v55;
        v77[1] = v57;
        *a5 = v42 * v54 + v38 * v76;
        v48[1] = v42 * v57 + v58;
        v59 = v56 + v42 * v55;
        v48[2] = v59;
        v60 = v53 - v59;
        v61 = v39 - *v48;
        v62 = v40 - v48[1];
        v63 = v62 * v62 + v61 * v61 + v60 * v60;
        v64 = -(v54 * v61 + v62 * v57 + v55 * v60);
        v83 = v64;
        *(double*)v51 = v54 * v63 + v64 * v61;
        *((double*)v51 + 1) = v63 * v57 + v64 * v62;
        *((double*)v51 + 2) = v64 * v60 + v55 * v63;
        vunt3(v51, &v92, v50);
        if (v92)
        {
            ++*a4;
            v65 = 4;
        }
        else
        {
            v65 = 1;
        }
        h805(&v75, &v87, &v93, &v92);
        if (!v92)
        {
            v75 = -v75;
            v66 = (double*)((char*)v49 + v65 * 8 - 8);
            v77[0] = v75 * v84[0] + v80[0] * v46;
            v77[1] = v75 * v84[1] + v80[1] * v46;
            v77[2] = v75 * v84[2] + v80[2] * v46;
            v67 = v42 * v77[1] + v89 * v76;
            v68 = v42 * v77[2] + v90 * v76;
            v69 = v52 - v68;
            v48[v65 - 1] = v42 * v77[0] + v91 * v76;
            v48[v65] = v67;
            v48[v65 + 1] = v68;
            v70 = v39 - v48[v65 - 1];
            v71 = v40 - v48[v65];
            v72 = v71 * v71 + v70 * v70 + v69 * v69;
            v83 = -(v71 * v77[1] + v70 * v77[0] + v69 * v77[2]);
            v73 = v83 * v71 + v77[1] * v72;
            v74 = v83 * v69 + v77[2] * v72;
            *v66 = v83 * v70 + v77[0] * v72;
            *(double*)((char*)v49 + v65 * 8) = v73;
            v66[2] = v74;
            vunt3((double*)v66, &v92, v66);
            if (v92)
                ++*a4;
        }
    }
LABEL_29:
    if (*a4)
    {
        *v7 = 1;
        return;
    }
LABEL_31:
    *v7 = 2;
}
