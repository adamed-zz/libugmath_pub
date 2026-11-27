






















#pragma once
#include <cstddef>


void* SM_alloc(size_t n);
void* SM_alloc(size_t n, size_t m);
void* SM_calloc(size_t n, size_t m);
void  SM_free(void* p);


int  ext_merrorlevel();
void ext_merrorflush();
void ext_msetup_banded(int n, int m, double*** a, double** b);
void ext_mdecompose_banded(double** a, int n, int m);
void ext_msolve_banded(double** a, int n, int m, double* b);
void ext_mdispose_banded(double*** a, double** b);
void ext_bandec(double** a, int n, int m1, int m2, double** al, int* indx, double* d);
void ext_banbks(double** a, int n, int m1, int m2, double** al, int* indx, double* b);
int  ext_SOLVE_lu_solver(double** a, double** b, int n, int m);
int  ext_knot_seq_order_4(const int* a1, const double* a3, const double* a4, int* a7, double* a8);
void ext_h0926a2(const int* a1, const double* a2, const double* a3, const double* a4,
                 const double* a5, const int* a6, const double* a7, double** a8, double* a9);
void ext_h0926a(const int* a1, const double* a2, const double* a3, const double* a4,
                const double* a5, const int* a6, const double* a7, double** a8, double* a9);
void ext_h0926(const int* a1, const double* a2, const double* a3, const double* a4,
               const int* a5, double* a6);
int  ext_h0914(const int* a1, const double* a2, const double* a3, int* a4, double* a5);
void ext_h0927(const int* a1, const double* a2, const double* a3, double* a4);
void ext_h805(const double* a1, const double* a2, const int* a3, int* a4);
int  ext_em0928(const int* a1, const int* a2, const double* a3);
double ext_h128(double a, double b);
int  ext_h553(const double* a1, const double* a2, const double* a3,
              const double* a4, const double* a5, const double* a6,
              const int* a7, double* a8);
void ext_e0925(int* a1, double* a2, double* a3, double* a4);
int  ext_eqz(const double* a, const double* b, const int* mode);


int  h0917(double x, const double* knots, int n, double tol);
int  h0918(double* x, const double* knots, int n, int m);
int  h0914(const int* a1, const double* a2, const double* a3, int* a4, double* a5);
int  h0913a(const int* a1, const double* a2, const double* a3, const double* a4,
            const int* a5, const double* a6, const double* a7, double* a8);
int  h0913b(const int* a1, const double* a2, const double* a3, const double* a4,
            const int* a5, const double* a6, const double* a7, double* a8);
void h0926(const int* a1, const double* a2, const double* a3, const double* a4,
           const int* a5, double* a6);
void h0926a(const int* a1, const double* a2, const double* a3, const double* a4,
            const double* a5, const int* a6, const double* a7, double** a8, double* a9);
int  h0916(int a1, const double* a2, int a3, int a4, double a5, int a6, double* const a7);
int  h0913(const int* a1, const double* a2, const double* a3, const double* a4,
           const int* a5, const double* a6, int* a7, double* a8, double* a9);
int  h0925(const int* a1, const double* a2, const double* a3, int* a4, double* a5, double* a6);
int  h0925_chk(int a1, double* a2, const double* a3);


extern "C" void* g_b6_raw_base;

#include <cmath>
#include <cstring>
#include <emmintrin.h>



static inline double b6_maxsd(double a, double b)
{
    return _mm_cvtsd_f64(_mm_max_sd(_mm_set_sd(a), _mm_set_sd(b)));
}
static inline double b6_minsd(double a, double b)
{
    return _mm_cvtsd_f64(_mm_min_sd(_mm_set_sd(a), _mm_set_sd(b)));
}

int h0914(const int* a1, const double* a2, const double* a3, int* a4, double* a5)
{
    const int v7 = a1[1];
    const int v10 = a1[2];
    const int v11 = a1[4];
    const int v12 = a1[5];
    const int v13 = a1[6];
    const int v5 = a1[7];
    const int v9 = a1[0];
    const int v159 = v7 - 1;
    const int v157 = v9;
    const int v161 = v7;
    const int v151 = v10;
    int v14 = v5 + 1;

    if (v5 == 0 && v7 == 2)
    {

        const int v16 = (v10 != 0) ? (v9 + 1) : v9;
        const long long v18 = v16;
        int v17 = 1;
        *a4 = v16 + 2;
        *a5 = *a2;
        long long v8 = 0;
        if (v16 < 4)
        {
            if (v16 > 0)
            {
                long long v22 = 1;
                double* v23 = &a5[v22];
                for (v8 = 0; v8 < v18; ++v8)
                    *v23++ = a2[v8];
                v17 += (int)(v18 - 0);
            }
        }
        else
        {
            const long long v20 = ((unsigned long long)(v16 - 4) >> 2) + 1;
            v8 = 4 * v20;
            const long long v22 = 4 * v20 + 1;
            v17 = (int)v22;
            double* v21 = a5 + 2;
            for (long long i = 0; i < v20; ++i)
            {
                *(v21 - 1) = a2[4 * i + 0];
                *v21 = a2[4 * i + 1];
                v21[1] = a2[4 * i + 2];
                v21[2] = a2[4 * i + 3];
                v21 += 4;
            }
            if (v8 < v18)
            {
                double* v23 = &a5[v22];
                long long j = v8;
                for (; j < v18; ++j)
                    *v23++ = a2[j];
                v17 += (int)(v18 - v8);
            }
        }
        a5[v17] = a2[v9 - 1];
        if (v10 != 0)
        {
            const double v25 = a5[2] - a5[1];
            a5[0] = a5[1] - (a5[v18] - a5[v18 - 1]);
            a5[v18 + 1] = v25 + a5[v18];
        }
        return 0;
    }
    if (v5 != 0)
        v14 = v5 + 1;
    else
        v14 = v7 - 1;


    const int v152 = (v14 <= v7 - 1) ? v14 : (v7 - 1);
    const int v27 = (v10 != 0) ? (v13 + v152) : v13;
    const int v155 = v9 + v11 + v12 + v27;
    *a4 = v155 + v7;
    double* v28 = (double*)SM_calloc((size_t)(long long)v155, 8);
    const int v29 = v11 + v13 + v12;
    long long v30 = 1;
    int v31 = 1;
    int v32 = 0;
    *v28 = *a2;

    {
        long long v33 = 1;
        long long v37 = 0;
        bool tail = true;
        if (v29 >= 4)
        {
            const double* v34 = a3 + 2;
            const unsigned v35 = ((unsigned)(v29 - 4) >> 2) + 1;
            long long v36 = v35;
            v32 = 4 * (int)v35;
            v37 = 4LL * v35;
            do
            {
                double v38 = *a2;
                const double v39 = *(v34 - 2);
                if (std::fabs(*a2 - v39) <= 1.0e-10) { v28[v33] = v39; ++v31; v38 = *a2; ++v33; }
                const double v40 = *(v34 - 1);
                if (std::fabs(v38 - v40) <= 1.0e-10) { v28[v33] = v40; ++v31; v38 = *a2; ++v33; }
                if (std::fabs(v38 - *v34) <= 1.0e-10) { v28[v33] = *v34; ++v31; v38 = *a2; ++v33; }
                const double v41 = v34[1];
                if (std::fabs(v38 - v41) <= 1.0e-10) { ++v31; v28[v33++] = v41; }
                v34 += 4;
                --v36;
            } while (v36);
            if (v32 >= v29)
                tail = false;
        }
        else
        {
            if (v29 <= 0)
                tail = false;
        }
        if (tail)
        {
            double* v42 = &v28[v33];
            const double* v43 = &a3[v37];
            do
            {
                if (std::fabs(*a2 - *v43) <= 1.0e-10)
                {
                    ++v31;
                    *v42++ = *v43;
                }
                ++v43;
                ++v32;
            } while (v32 < v29);
        }
    }


    int v44 = 0;
    if (v151 != 0)
    {
        v44 = (v31 + v152) / 2;
        const int v45 = v152 + v31 - v44;
        v31 = 0;
        int v63 = 0;
        if (v45 >= 4)
        {
            double* v46 = v28 + 2;
            unsigned v47 = ((unsigned)(v45 - 4) >> 2) + 1;
            long long v48 = v47;
            v63 = 4 * (int)v47;
            do
            {
                *(v46 - 2) = *a2;
                v46 += 4;
                *(v46 - 5) = *a2;
                *(v46 - 4) = *a2;
                *(v46 - 3) = *a2;
                --v48;
            } while (v48);
            if (v63 >= v45)
                v31 = v45;
        }
        if (v31 != v45 && v45 > 0)
        {
            double* v50 = &v28[v63];
            int v51 = v45 - v63;
            v31 = v45;
            do
            {
                *v50++ = *a2;
                --v51;
            } while (v51);
        }
    }


    const long long v52 = v157;
    if (v157 > 1)
    {
        long long v53 = v31;
        do
        {
            ++v31;
            v28[v53] = a2[v30];
            int v54 = 0;
            ++v53;
            long long v55 = 0;
            if (v29 >= 4)
            {
                const double* v56 = a3 + 2;
                const unsigned v57 = ((unsigned)(v29 - 4) >> 2) + 1;
                long long v58 = v57;
                v54 = 4 * (int)v57;
                v55 = 4LL * v57;
                do
                {
                    const double v59 = *(v56 - 2);
                    if (std::fabs(v28[v53 - 1] - v59) <= 1.0e-10) { ++v31; v28[v53++] = v59; }
                    const double v60 = *(v56 - 1);
                    if (std::fabs(v28[v53 - 1] - v60) <= 1.0e-10) { ++v31; v28[v53++] = v60; }
                    if (std::fabs(v28[v53 - 1] - *v56) <= 1.0e-10) { ++v31; v28[v53++] = *v56; }
                    const double v61 = v56[1];
                    if (std::fabs(v28[v53 - 1] - v61) <= 1.0e-10) { ++v31; v28[v53++] = v61; }
                    v56 += 4;
                    --v58;
                } while (v58);
            }
            if (v54 < v29)
            {
                const double* v62 = &a3[v55];
                do
                {
                    if (std::fabs(v28[v53 - 1] - *v62) <= 1.0e-10)
                    {
                        ++v31;
                        v28[v53++] = *v62;
                    }
                    ++v62;
                    ++v54;
                } while (v54 < v29);
            }
            ++v30;
        } while (v30 < v157);
    }

    if (v151 != 0)
    {
        int v63 = 0;
        if (v44 >= 4)
        {
            long long v64 = v31;
            unsigned v65 = ((unsigned)(v44 - 4) >> 2) + 1;
            long long v66 = v65;
            double* v67 = &v28[v64 + 2];
            v63 = 4 * (int)v65;
            do
            {
                *(v67 - 2) = a2[v157];
                v67 += 4;
                *(v67 - 5) = a2[v157];
                *(v67 - 4) = a2[v157];
                *(v67 - 3) = a2[v157];
                --v66;
            } while (v66);
        }
        if (v63 < v44)
        {
            double* v69 = &v28[v31 + v63];
            int v70 = v44 - v63;
            do
            {
                *v69++ = a2[v157];
                --v70;
            } while (v70);
        }
    }


    const int v71 = v155;
    int v72 = v161 - v152;
    const int v156 = v72;
    const int v73 = (v155 - v152) / (v161 - v152);
    int v74 = v161;
    int v75 = v73 + 1;
    if (v155 - v152 <= v73 * (v161 - v152))
        v75 = v73;
    const int v158 = v75;
    if (v75 > 1)
    {
        const int v160 = v75 - 1;
        const int v76 = (*a4 - 2 * v161) / (v75 - 1);
        const int v77 = (*a4 - 2 * v161) % (v75 - 1);
        int* v80 = (int*)SM_calloc((size_t)(long long)v160, 4);
        for (int i = 0; i < v160; ++i)
            v80[i] = v76;
        for (int i = 0; i < v77; ++i)
            ++v80[i];
        double* v92 = (double*)SM_calloc((size_t)(long long)(v158 + 1), 8);
        int v90 = v160;
        int v91 = 0;
        int v93 = 0;
        int v153 = 0;
        if (v160 <= 0)
        {
            v92[v160] = 1.0;
        }
        else
        {
            int v94 = 0;
            int v95 = v161;
            do
            {
                if (v93)
                    v91 += v80[v94 - 1];
                v92[v94] = 0.0;
                int v96 = v80[v94];
                double v97 = 0.0;
                int v98 = 0;
                if (v95 - v96 > 0)
                {
                    int v99 = 0;
                    do
                    {
                        ++v98;
                        const int v100 = v91 - v99++;
                        v97 = v97 + v28[v161 - 1 + v100];
                        v92[v94] = v97;
                        v96 = v80[v94];
                    } while (v98 < v161 - v96);
                    v90 = v160;
                    v95 = v161;
                }
                v93 = ++v153;
                v92[v94++] = v97 / (double)(v95 - v96);
            } while (v94 < v90);

            long long v101 = 0;
            int v102 = 0;
            v92[v90] = 1.0;
            int v103 = 0;
            double v104 = *v92;
            int v154 = 0;
            do
            {
                const double v105 = v92[v101];
                const double v106 = v92[v101 + 1] - v105;
                if (v103 > 0)
                    v102 += v80[v101 - 1];
                if (std::fabs(v92[v101] * 2048.0 - (double)(int)(v92[v101] * 2048.0)) > 0.00000001)
                {
                    double v107 = v105 - v104 * 0.25;
                    double v108 = v106 * 0.25 + v105;
                    double v109 = b6_maxsd(v28[v102 + v80[v101]], v107);
                    double v110 = b6_minsd(v28[v95 - 1 + v102], v108);
                    if (v109 >= v110)
                    {
                        v109 = v107;
                        v110 = v108;
                    }
                    const double v111 = ext_h128(v109, v110);
                    v103 = v154;
                    v90 = v160;
                    v95 = v161;
                    v92[v101] = v111;
                }
                ++v103;
                ++v101;
                v154 = v103;
                v104 = v106;
            } while (v101 < v90);

            long long v112 = v161;
            const int* v113 = v80;
            const double* v114 = v92;
            int v115 = v90;
            do
            {
                for (int i = 0; i < v113[0]; ++v112)
                {
                    ++i;
                    a5[v112] = *v114;
                }
                ++v114;
                ++v113;
                --v115;
            } while (v115);
        }
        SM_free(v80);
        SM_free(v92);
        v74 = v161;
        v72 = v156;
    }


    long long v146 = 0;
    if (v151 == 0)
    {
        int v8 = 0;
        if (v74 >= 4)
        {
            double* v147 = a5 + 2;
            do
            {
                v146 += 4;
                *(v147 - 2) = *a2;
                v147 += 4;
                a5[*a4 - v8 - 1] = a2[v52 - 1];
                *(v147 - 5) = *a2;
                a5[*a4 - v8 - 2] = a2[v52 - 1];
                *(v147 - 4) = *a2;
                a5[*a4 - v8 - 3] = a2[v52 - 1];
                *(v147 - 3) = *a2;
                const int v148 = *a4 - v8;
                v8 = v8 + 4;
                a5[v148 - 4] = a2[v52 - 1];
            } while (v146 < v74 - 3);
        }
        for (; v146 < v74;)
        {
            a5[v146++] = *a2;
            const int v149 = *a4 - v8;
            v8 = v8 + 1;
            a5[v149 - 1] = a2[v52 - 1];
        }
        SM_free(v28);
        return 0;
    }


    long long v116 = 0;
    if (v72 >= 4)
    {
        double* v117 = &a5[v159 - 2];
        unsigned long long v118 = ((unsigned long long)(v72 - 4) >> 2) + 1;
        v116 = 4 * (long long)v118;
        do
        {
            v117[2] = *a2;
            v117 -= 4;
            v117[5] = *a2;
            v117[4] = *a2;
            v117[3] = *a2;
            --v118;
        } while (v118);
    }
    if (v116 < v72)
    {
        double* v119 = &a5[v159 - v116];
        long long v120 = v72 - v116;
        do
        {
            *v119-- = *a2;
            --v120;
        } while (v120);
    }
    {
        long long v121 = 0;
        const int v122 = v71;
        if (v72 >= 4)
        {
            double* v123 = &a5[v71 + 2];
            unsigned long long v124 = ((unsigned long long)(v72 - 4) >> 2) + 1;
            v121 = 4 * (long long)v124;
            do
            {
                *(v123 - 2) = a2[v52];
                v123 += 4;
                *(v123 - 5) = a2[v52];
                *(v123 - 4) = a2[v52];
                *(v123 - 3) = a2[v52];
                --v124;
            } while (v124);
        }
        if (v121 < v72)
        {
            double* v125 = &a5[v122 + v121];
            long long v126 = v72 - v121;
            do
            {
                *v125++ = a2[v52];
                --v126;
            } while (v126);
        }
    }


    {
        const int v127 = v159 - v72;
        const int v128 = v71 + v72;
        if (v127 >= 0)
        {
            long long v129 = 0;
            const bool back_unrolled = (v127 >= 3);
            if (back_unrolled)
            {
                double* v130 = &a5[v159 + 1];
                const long long v131 = (long long)v128 - (long long)v159;
                unsigned long long v132 = ((unsigned long long)(v127 + 1LL)) >> 2;
                v129 = 4 * (long long)v132;
                do
                {
                    const double v133 = v130[v131 - 2] + *v130 - *(v130 - 1);
                    v130[v131 - 1] = v133;
                    const double v134 = v133 + v130[1] - *v130;
                    v130[v131] = v134;
                    const double v135 = v134 + v130[2] - v130[1];
                    v130[v131 + 1] = v135;
                    v130[v131 + 2] = v135 + v130[3] - v130[2];
                    v130 += 4;
                    --v132;
                } while (v132);
            }
            if (v129 <= v127)
            {
                double* v137 = &a5[(long long)v128 + v129];
                long long v138 = v127 - v129 + 1;
                do
                {
                    *v137 = v137[v159 - ((long long)v128 - 1LL)] + *(v137 - 1)
                          - v137[v159 - ((long long)v128 - 1LL) - 1];
                    ++v137;
                    --v138;
                } while (v138);
            }
            const int v136 = v127 + 1;
            int v8 = 0;
            if (back_unrolled)
            {
                const long long v139 = (long long)v136 - (long long)v71;
                double* v140 = &a5[v71 - 1];
                unsigned long long v141 = ((unsigned long long)(v127 + 1LL)) >> 2;
                v8 = (int)(4 * (long long)v141);
                do
                {
                    const double v142 = v140[v139 + 1] - (v140[1] - *v140);
                    v140[v139] = v142;
                    const double v143 = v142 - (*v140 - *(v140 - 1));
                    v140[v139 - 1] = v143;
                    const double v144 = v143 - (*(v140 - 1) - *(v140 - 2));
                    v140[v139 - 2] = v144;
                    v140[v139 - 3] = v144 - (*(v140 - 2) - *(v140 - 3));
                    v140 -= 4;
                    --v141;
                } while (v141);
                if (v8 > v127)
                    goto free28;
            }
            {
                double* v145 = &a5[(long long)v136 - v8 - 1];
                do
                {
                    ++v8;
                    *v145 = v145[1] - (v145[v71 - (long long)v136 + 1] - v145[v71 - (long long)v136]);
                    --v145;
                } while (v8 <= v127);
            }
        }
    }
free28:
    SM_free(v28);
    return 0;
}
