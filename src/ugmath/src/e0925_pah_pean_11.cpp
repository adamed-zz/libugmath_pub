










#include <cstring>

void e0925(int *a1, double *a2, double *a3, double *a4)
{
    __int64 v4 = *a1;
    if (a4 != a3)
        memcpy(a4, a3, 8LL * (4 * (int)v4 + 4));
    double v7 = a2[v4];
    __int64 v8 = 0;
    __int64 v9 = (int)v4 - 1;
    int v10 = 0;
    __int64 v130 = v4 - 1;
    if ((int)v4 - 1 > 0)
    {
        __int64 v11 = 8 * v4 + 16;
        __int64 v12 = 0;
        double *v13 = a2 + 1;
        do
        {
            int v14 = 0;
            __int64 v15 = 0;
            int v16 = (int)(v4 - v10 - 1);
            if (v16 >= 4)
            {
                double v17 = a4[2];
                double *v18 = a4 + 2;
                unsigned int v19 = ((unsigned int)(v4 - v10 - 5) >> 2) + 1;
                double *v20 = v13;
                __int64 v21 = v19;
                v14 = 4 * v19;
                v15 = 4LL * v19;
                do
                {
                    double v22 = v18[2];
                    double v23 = *(double *)((char *)v20 + v11 - 16) - *v20;
                    double v24 = (v7 - *v20) / v23;
                    double v25 = (*(double *)((char *)v20 + v11 - 16) - v7) / v23;
                    double v26 = v17 * v25;
                    *(v18 - 2) = v22 * v24 + v25 * *(v18 - 2);
                    double v27 = v25;
                    double v28 = v25 * v18[1];
                    double v29 = v18[3];
                    double v30 = v18[4];
                    double v31 = v18[6];
                    *(v18 - 1) = v27 * *(v18 - 1) + v29 * v24;
                    *v18 = v26 + v30 * v24;
                    double v32 = v18[5];
                    v18[1] = v28 + v32 * v24;
                    double v33 = *(double *)((char *)v20 + v11 - 8);
                    double v34 = v33 - v7;
                    double v35 = v33 - v20[1];
                    double v36 = (v7 - v20[1]) / v35;
                    double v37 = v34 / v35;
                    v18[2] = v31 * v36 + v22 * v37;
                    double v38 = v18[7];
                    double v39 = v18[9];
                    double v40 = v38 * v36 + v29 * v37;
                    double v41 = v18[8];
                    v18[3] = v40;
                    v18[4] = v41 * v36 + v30 * v37;
                    double v42 = v39 * v36 + v32 * v37;
                    double v43 = v18[10];
                    v18[5] = v42;
                    double v44 = *(double *)((char *)v20 + v11);
                    double v45 = v44 - v7;
                    double v46 = v44 - v20[2];
                    double v47 = (v7 - v20[2]) / v46;
                    double v48 = v45 / v46;
                    v18[6] = v43 * v47 + v31 * v48;
                    double v49 = v18[11];
                    double v50 = v18[13];
                    double v51 = v49 * v47 + v38 * v48;
                    double v52 = v18[12];
                    v18[7] = v51;
                    v18[8] = v52 * v47 + v41 * v48;
                    v18[9] = v50 * v47 + v39 * v48;
                    double v53 = v7 - v20[3];
                    double v54 = *(double *)((char *)v20 + v11 + 8);
                    double v55 = v54 - v20[3];
                    v20 += 4;
                    double v56 = v53 / v55;
                    double v57 = (v54 - v7) / v55;
                    v18[10] = v56 * v18[14] + v43 * v57;
                    v17 = v18[16];
                    double v58 = v17 * v56;
                    double v59 = v56 * v18[15] + v49 * v57;
                    double v60 = v56 * v18[17] + v50 * v57;
                    v18[11] = v59;
                    v18[12] = v52 * v57 + v58;
                    v18[13] = v60;
                    v18 += 16;
                    --v21;
                }
                while (v21);
                v9 = (int)v4 - 1;
            }
            if (v14 < v16)
            {
                double *v61 = &a4[4 * v15 + 1];
                __int64 v62 = (unsigned int)(v16 - v14);
                double v63 = *v61;
                double *v64 = &a2[v12 + 1 + v15];
                do
                {
                    double v65 = *(double *)((char *)v64 + v11 - 16);
                    double v66 = v65 - *v64;
                    double v67 = v7 - *v64++;
                    double v68 = v67 / v66;
                    double v69 = (v65 - v7) / v66;
                    double v70 = v61[4] * v68;
                    *(v61 - 1) = v68 * v61[3] + v69 * *(v61 - 1);
                    double v71 = v68 * v61[5];
                    double v72 = v70 + v63 * v69;
                    double v73 = v68 * v61[6];
                    v63 = v61[4];
                    *v61 = v72;
                    double v74 = v73 + v69 * v61[2];
                    v61[1] = v71 + v69 * v61[1];
                    v61[2] = v74;
                    v61 += 4;
                    --v62;
                }
                while (v62);
            }
            ++v10;
            ++v12;
            ++v13;
            v11 -= 8;
        }
        while (v12 < v9);
        int v75 = (int)v4 - 1;
        double v76 = a2[v4 + 1] - v7;
        int v77 = 1;
        do
        {
            int v78 = (int)v4;
            __int64 v79 = v4;
            if ((int)v4 > v77)
            {
                bool do_scalar = false;
                if (v75 < 4)
                    do_scalar = true;
                else
                {
                double *v80 = &a4[4 * v4 + 2];
                double v81 = *v80;
                double *v82 = &a2[2 * v4 - v8 - 2];
                __int64 v83 = ((unsigned int)(v4 - v77 - 4) >> 2) + 1;
                v78 = (int)(v4 - 4 * v83);
                v79 = v4 - 4 * v83;
                do
                {
                    double v84 = *(v80 - 6);
                    double v85 = v82[2];
                    double v86 = v85 - a2[v4 + 1];
                    double v87 = v85 - v7;
                    double v88 = v86 / v87;
                    *(v80 - 2) = v76 / v87 * *(v80 - 2) + v84 * v88;
                    double v89 = v76 / v87 * v80[1];
                    double v90 = *(v80 - 5);
                    double v91 = *(v80 - 4);
                    double v92 = *(v80 - 3);
                    double v93 = *(v80 - 10);
                    *(v80 - 1) = v90 * v88 + v76 / v87 * *(v80 - 1);
                    *v80 = v91 * v88 + v81 * (v76 / v87);
                    v80[1] = v92 * v88 + v89;
                    double v94 = v82[1];
                    double v95 = v94 - a2[v4 + 1];
                    double v96 = v94 - v7;
                    double v97 = v95 / v96;
                    *(v80 - 6) = v93 * v97 + v84 * (v76 / v96);
                    double v98 = *(v80 - 9);
                    double v99 = *(v80 - 7);
                    double v100 = v98 * v97 + v90 * (v76 / v96);
                    double v101 = *(v80 - 8);
                    *(v80 - 5) = v100;
                    *(v80 - 4) = v101 * v97 + v91 * (v76 / v96);
                    *(v80 - 3) = v99 * v97 + v92 * (v76 / v96);
                    double v102 = *v82 - v7;
                    double v103 = v76 / v102;
                    double v104 = (*v82 - a2[v4 + 1]) / v102;
                    double v105 = *(v80 - 14);
                    *(v80 - 10) = v105 * v104 + v93 * v103;
                    double v106 = *(v80 - 13);
                    double v107 = *(v80 - 12);
                    double v108 = *(v80 - 11);
                    *(v80 - 9) = v98 * v103 + v106 * v104;
                    *(v80 - 8) = v101 * v103 + v107 * v104;
                    *(v80 - 7) = v99 * v103 + v108 * v104;
                    double v109 = *(v82 - 1);
                    v82 -= 4;
                    double v110 = v109 - v7;
                    double v111 = v76 / (v109 - v7);
                    double v112 = (v109 - a2[v4 + 1]) / (v109 - v7);
                    *(v80 - 14) = v112 * *(v80 - 18) + v105 * (v76 / v110);
                    v81 = *(v80 - 16);
                    double v113 = v81 * v112;
                    double v114 = v112 * *(v80 - 17) + v106 * v111;
                    double v115 = v112 * *(v80 - 15) + v108 * v111;
                    *(v80 - 13) = v114;
                    *(v80 - 12) = v107 * v111 + v113;
                    *(v80 - 11) = v115;
                    v80 -= 16;
                    --v83;
                }
                while (v83);
                if (v78 > v77)
                    do_scalar = true;
                }
                if (do_scalar)
                {
                    double *v116 = &a4[4 * v79 + 1];
                    __int64 v117 = (unsigned int)(v78 - v77);
                    double v118 = *v116;
                    double *v119 = &a2[v4 + v79 - v8];
                    do
                    {
                        double v120 = *v119;
                        double v121 = *v119-- - v7;
                        double v122 = (v120 - a2[v4 + 1]) / v121;
                        double v123 = v76 / v121;
                        double v124 = v122 * *(v116 - 5) + v76 / v121 * *(v116 - 1);
                        double v125 = *(v116 - 4) * v122;
                        *(v116 - 1) = v124;
                        double v126 = v122 * *(v116 - 3);
                        double v127 = v125 + v118 * v123;
                        double v128 = v122 * *(v116 - 2);
                        v118 = *(v116 - 4);
                        *v116 = v127;
                        double v129 = v128 + v123 * v116[2];
                        v116[1] = v126 + v123 * v116[1];
                        v116[2] = v129;
                        v116 -= 4;
                        --v117;
                    }
                    while (v117);
                }
                v75 = (int)v130;
            }
            --v75;
            ++v77;
            ++v8;
            v130 = v75;
        }
        while (v8 < v9);
    }
}
