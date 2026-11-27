









#include <cstring>

static void B6PutQ(double* p, long long v) { memcpy(p, &v, 8); }

#define B6_X(i) E[5 + (i)]
#define B6_Y(i) E[105 + (i)]

void em0916(double* a1, int* a2, int* a3, double* a4, int* a5, double* a6, double* a7) {
    double E[205];
    int v7 = *a3;
    int v107 = 0;

    for (int i = 0; i < v7; i++)
        v107 += a2[i];


    {
        int v25 = 1;
        int v28 = 1;
        int* v26 = a2;
        for (int v27 = 1; v27 <= v7; v27++, v26++) {
            int v30 = *v26 + 1;
            if (v30 >= 1) {
                for (int c = 0; c < v30; c++)
                    a6[v28 - 1 + c] = a1[v25 - 1];
                v28 += v30;
            }
            v25 += *v26;
        }
    }

    int* v11 = a2;
    int* v108 = a2;
    int v37 = 1;
    int v109 = 1;
    int v38 = v107;
    int v39 = *v11;
    int v99 = v107 - *a5;
    int v40 = v39 + 1;
    int v98 = v39 + 1;
    int v104 = (int)v7 + v99 - 1;
    if (v104 >= 1) {
        int v41 = 8;
        int v101 = 8;
        int v42 = 1;
        int v100 = 1;
        double* v102 = a7 + 2;


        B6PutQ(E + 0, (long long)v100);
        B6PutQ(E + 1, (long long)v101);
        B6PutQ(E + 2, (long long)(unsigned long long)(size_t)v102);
        B6PutQ(E + 3, (long long)(unsigned long long)(size_t)a4);
        B6PutQ(E + 4, (long long)v104);
        do {
            if (v37 > v40) {
                v108 = v11 + 1;
                v39 += v11[1];
                v98 = v11[1] + v40 + 1;
            }
            int v43 = *a5;
            int v44 = v43;

            for (int j = 0; j < v43; j++) {
                for (int t = 0; t < 4; t++) {
                    B6_X(4 * j + t) = 0.0;
                    B6_Y(4 * j + t) = 0.0;
                }
            }
            int v47 = v39;
            int v48 = v43 - v39 + 1;
            int v49 = (v48 <= 1) ? 1 : v48;
            int v50 = v38 - v39;
            if (v43 <= v50) v50 = v43;
            int v51 = v49;
            int v52 = v50;
            if (v49 <= v50) {
                int cnt = v52 - v51 + 1;
                for (int k = 0; k < cnt; k++) {
                    int dst = 4 * (v49 - 1) + 4 * k;
                    int src = 4 * (v49 + v39 - v43) - 4 + 4 * k;
                    for (int t = 0; t < 4; t++)
                        B6_Y(dst + t) = a4[src + t];
                    for (int t = 0; t < 4; t++)
                        B6_X(dst + t) = B6_Y(dst + t);
                }
                v48 = v43 - v39 + 1;
                v42 = v100;
            }
            int v58 = v43 - 1;
            int v59 = v43 - 1;
            if (v59 >= 1) {
                int v60 = 2 * v43;
                double* v61 = a6 + v58 + v42;


                B6PutQ(E + 0, (long long)v100);
                B6PutQ(E + 1, (long long)v101);
                B6PutQ(E + 2, (long long)(unsigned long long)(size_t)v102);
                B6PutQ(E + 3, -((long long)(size_t)a6 + v41));
                B6PutQ(E + 4, (long long)v104);
                do {
                    double v62 = v61[-1];
                    double v63 = v61[0];
                    int v64 = v99 + v60 - v58 - v39;
                    if (v43 <= v64) v64 = v43;
                    int v65 = v64;
                    int v66 = v39;
                    if (v43 + 1 - v58 >= v48) v66 = v58;
                    int v67 = v43 - v66 + 1;
                    if (v64 >= v67) {
                        int v68 = v47 - v44;
                        int v71i = v65 - 1 + v68;
                        double* v71 = a1 + v71i;
                        int v72 = v65 - v67 + 1;
                        int v69 = 32 * v65 - 32;
                        do {
                            int idx = v69 >> 3;
                            double v73 = a1[v71i + v58];
                            double p71 = *v71;
                            double v74 = v63 - p71;
                            double v75 = v73 - v63;
                            double v76 = v73 - p71;
                            double v77 = v62 - p71;
                            --v71;
                            --v71i;
                            double v78 = v73 - v62;
                            double v80 = v75 * E[103 + idx];
                            double v81 = v78 * E[2 + idx];
                            double v82 = (v75 * E[101 + idx] + v74 * E[105 + idx]) / v76;
                            double v83 = v74 * E[107 + idx];
                            double v84 = (v75 * E[102 + idx] + v74 * E[106 + idx]) / v76;
                            double v85 = v75 * E[104 + idx] + v74 * E[108 + idx];
                            double v86 = (v80 + v83) / v76;
                            double v87 = v85 / v76;
                            double v88 = (v78 * E[1 + idx] + v77 * E[5 + idx]) / v76;
                            double v89 = v81 + v77 * E[6 + idx];
                            double v92 = v77 * E[7 + idx];
                            double v91 = v77 * E[8 + idx];
                            double v93 = v78 * E[3 + idx];
                            double v94 = (v78 * E[4 + idx] + v91) / v76;
                            E[105 + idx] = v82;
                            E[106 + idx] = v84;
                            E[107 + idx] = v86;
                            E[108 + idx] = v87;
                            E[5 + idx] = v88 + v82;
                            E[6 + idx] = v89 / v76 + v84;
                            E[7 + idx] = (v93 + v92) / v76 + v86;
                            E[8 + idx] = v94 + v87;
                            v69 -= 32;
                            --v72;
                        } while (v72);
                        v48 = v43 - v39 + 1;
                        v44 = v43;
                        v47 = v39;
                    }
                    --v58;
                    v60 = 2 * v43;
                    --v61;
                    --v59;
                } while (v59);
                v42 = v100;
                v41 = v101;
            }
            v11 = v108;
            v42++;
            v38 = v107;
            v41 += 8;
            int m = v43;
            double* v97 = v102;
            v100 = v42;
            v101 = v41;

            B6PutQ(E + 1, (long long)v101);
            double dm = (double)v43;
            v97[-2] = E[1 + 4 * m] / dm;
            v97[-1] = E[2 + 4 * m] / dm;
            v97[0] = E[3 + 4 * m] / dm;
            v97[1] = E[4 + 4 * m] / dm;
            v37 = ++v109;
            v40 = v98;
            v102 = v97 + 4;
            B6PutQ(E + 2, (long long)(unsigned long long)(size_t)v102);
        } while (v42 <= v104);
    }
}
