




#include <cstdint>
#include <emmintrin.h>
#include <cstdarg>
#include <cstring>

extern "C" __int64 sub_18008E820(__int64 a1, __int64 a2, __m128i* a3, __int64* a4,
                                   __int64 a5, __int64 a6, ...)
{


  va_list ap;
  va_start(ap, a6);
  double a7 = va_arg(ap, double);
  va_end(ap);
  __int64 v7;
  __int64 v8;
  double v9;
  __int64 *v10;
  __int64 v12;
  __int64 v13;
  unsigned __int64 v14;
  unsigned __int64 v15;
  __int64 v16;
  signed __int64 result;
  signed __int64 v18;
  __int64 v19;
  __int64 v20;
  __int64 v21;
  __int64 v22;
  double *v23;
  __int64 v24;
  __int64 v25;
  __m128d v26;
  __m128d v27;
  __m128d v28;
  __m128d v29;
  __m128d v30;
  __m128d v31;
  __m128d v32;
  __m128d v33;
  __m128d *v34;
  __int64 v35;
  __m128d v36;
  __m128d v37;
  double v38;
  double v39;
  double v40;
  double v41;
  double v42;
  double v43;
  double v44;
  double v45;
  __int64 v46;
  __int64 v47;
  double *v48;
  __int64 v49;
  __int64 v50;
  __int64 v51;
  __int64 v52;
  __int64 v53;
  unsigned __int64 v54;
  double v55;
  double v56;
  double v57;
  double v58;
  double v59;
  double v60;
  double v61;
  double v62;
  double v63;
  __int64 v64;
  double *v65;
  __int64 v66;
  double v67;
  double v68;
  double v69;
  double v70;
  unsigned __int64 v71;
  unsigned __int64 v72;
  __int64 v73;
  double *v74;
  __int64 v75;
  __int64 v76;
  __m128d v77;
  __m128d v78;
  __m128d v79;
  __m128d v80;
  __int64 v81;
  __m128d *v82;
  __m128d v83;
  __m128d v84;
  double v85;
  double v86;
  double v87;
  double v88;
  __int64 v89;
  __int64 v90;
  double *v91;
  __int64 v92;
  unsigned __int64 v93;
  double v94;
  double v95;
  double v96;
  double v97;
  double v98;
  double v99;
  double v100;
  double v101;
  __int64 v102;
  double *v103;
  __int64 v104;
  double v105;
  double v106;
  unsigned __int64 v107;
  __int64 v108;
  double *v109;
  __int64 v110;
  __m128d v111;
  __m128d v112;
  __int64 v113;
  __m128d *v114;
  __m128d v115;
  __m128d v116;
  double v117;
  double v118;
  __int64 v119;
  __int64 v120;
  double *v121;
  unsigned __int64 v122;
  double v123;
  double v124;
  double v125;
  double v126;
  double v127;
  double v128;
  double v129;
  double v130;
  double v131;
  double v132;
  double v133;
  __int64 v134;
  double *v135;
  __int64 v136;
  double v137;
  double v138;
  double v139;
  unsigned __int64 v140;
  __int64 v141;
  signed __int64 v142;
  double *v143;
  __int64 v144;
  __m128d v145;
  __m128d *v146;
  __int64 v147;
  __m128d v148;
  __m128d v149;
  double v150;
  __int64 v151;
  __int64 v152;
  double *v153;
  double v154;
  double v155;
  double v156;
  double v157;
  double *v158;
  double v159;
  __int64 v160;
  __int64 v161;
  __int64 v162;
  __int64 v163;
  signed __int64 v164;
  signed __int64 v165;
  signed __int64 v166;
  __int64 v167;
  unsigned __int64 v168;
  __m128i v169;
  __int64 v171;
  __int64 v172;
  unsigned __int64 v173;
  __int64 v174;

  v171 = a2;
  v7 = a1 - 7;
  v8 = a6;
  v9 = a7;
  v10 = a4;
  v12 = 0;
  v169 = *a3;
  v13 = ((long long*)a3)[0];
  v14 = (unsigned long long)_mm_cvtsi128_si64(_mm_srli_si128(*(__m128i*)a3, 8));
  v15 = v14;
  v16 = v14;
  if ( 8 * v14 <= 0x7D00 )
    v12 = v7;
  result = a1 - 3;
  v162 = v12;
  v18 = 0;
  v165 = a1 - 3;
  v166 = a1 - 1;
  v164 = 0;
  if ( v12 > 0 )
  {
    v19 = 0;
    v20 = 2 * a6;
    v21 = -2 * a6;
    v168 = v14 << 6;
    v22 = -a6;
    v23 = (double *)(16 * a6 + a5);
    v24 = 8 * v14;
    v160 = 0;
    v172 = 8 * v14;
    v163 = 8 * (2 - v14);
    v167 = -8LL * v14;
    do
    {
      v25 = 0;
      v26 = _mm_setzero_pd();
      v27 = _mm_setzero_pd();
      v28 = _mm_setzero_pd();
      v29 = _mm_setzero_pd();
      v30 = _mm_setzero_pd();
      v31 = _mm_setzero_pd();
      v32 = _mm_setzero_pd();
      v33 = _mm_setzero_pd();
      if ( a2 >= 2 )
      {
        v34 = (__m128d *)(v24 + v13 + 8 * (v15 - 2) + v163);
        v35 = 2;
        do
        {
          v36 = _mm_loadu_pd((const double *)((char *)v34 + *a4 - v172 - v13));
          v25 += 2;
          v35 += 2;
          v26 = _mm_add_pd(v26, _mm_mul_pd(_mm_loadu_pd((const double *)((char *)v34 - 8 * v15)), v36));
          v27 = _mm_add_pd(v27, _mm_mul_pd(v36, _mm_loadu_pd((const double *)v34)));
          v28 = _mm_add_pd(v28, _mm_mul_pd(_mm_loadu_pd((const double *)((char *)v34 + 8 * v15)), v36));
          v29 = _mm_add_pd(v29, _mm_mul_pd(_mm_loadu_pd((const double *)&v34[v15]), v36));
          v30 = _mm_add_pd(v30, _mm_mul_pd(_mm_loadu_pd((const double *)((char *)v34 + 24 * v15)), v36));
          v31 = _mm_add_pd(v31, _mm_mul_pd(_mm_loadu_pd((const double *)&v34[2 * v15]), v36));
          v32 = _mm_add_pd(v32, _mm_mul_pd(_mm_loadu_pd((const double *)((char *)v34 + 40 * v15)), v36));
          v37 = _mm_loadu_pd((const double *)&v34[3 * v15]);
          ++v34;
          v33 = _mm_add_pd(v33, _mm_mul_pd(v37, v36));
        }
        while ( v35 <= a2 );
        v8 = a6;
        v16 = v15;
        v24 = v172;
        v10 = a4;
        v19 = v160;
        v21 = -2 * a6;
        v20 = 2 * a6;
        v22 = -a6;
      }
      v38 = _mm_cvtsd_f64(_mm_add_sd(v26, _mm_unpackhi_pd(v26, v26)));
      v39 = _mm_cvtsd_f64(_mm_add_sd(v27, _mm_unpackhi_pd(v27, v27)));
      v40 = _mm_cvtsd_f64(_mm_add_sd(v28, _mm_unpackhi_pd(v28, v28)));
      v41 = _mm_cvtsd_f64(_mm_add_sd(v29, _mm_unpackhi_pd(v29, v29)));
      v42 = _mm_cvtsd_f64(_mm_add_sd(v30, _mm_unpackhi_pd(v30, v30)));
      v43 = _mm_cvtsd_f64(_mm_add_sd(v31, _mm_unpackhi_pd(v31, v31)));
      v44 = _mm_cvtsd_f64(_mm_add_sd(v32, _mm_unpackhi_pd(v32, v32)));
      v45 = _mm_cvtsd_f64(_mm_add_sd(v33, _mm_unpackhi_pd(v33, v33)));
      if ( v25 < a2 )
      {
        v46 = *v10;
        if ( a2 - v25 < 4 )
          goto LABEL_14;
        v47 = v46 - v167 - v24 - v13;
        v48 = (double *)(v13 + 8 * (v25 + v19 + 2));
        v49 = v46 - v163 - v24 - v13;
        v51 = 6 * v15;
        v52 = 7 * v15;
        v54 = ((unsigned __int64)(a2 - v25 - 4) >> 2) + 1;
        v25 += 4 * v54;
        do
        {
          v38 = *(double *)((char *)v48 + v47 - 8) * *(v48 - 1)
              + *(double *)((char *)v48 + v49) * *(v48 - 2)
              + v38
              + *(double *)((char *)v48 + v47) * *v48
              + *(double *)((char *)v48 + v47 + 8) * v48[1];
          v39 = *(double *)((char *)v48 + v47 - 8) * v48[v16 - 1]
              + *(double *)((char *)v48 + v49) * v48[v15 - 2]
              + v39
              + *(double *)((char *)v48 + v47) * v48[v16]
              + *(double *)((char *)v48 + v47 + 8) * v48[v16 + 1];
          v40 = *(double *)((char *)v48 + v47 - 8) * v48[2 * v15 - 1]
              + *(double *)((char *)v48 + v49) * v48[2 * v15 - 2]
              + v40
              + *(double *)((char *)v48 + v47) * v48[2 * v15]
              + *(double *)((char *)v48 + v47 + 8) * v48[2 * v15 + 1];
          v41 = *(double *)((char *)v48 + v47 - 8) * v48[3 * v15 - 1]
              + *(double *)((char *)v48 + v49) * v48[3 * v15 - 2]
              + v41
              + *(double *)((char *)v48 + v47) * v48[3 * v15]
              + *(double *)((char *)v48 + v47 + 8) * v48[3 * v15 + 1];
          v50 = 4 * v15;
          v42 = *(double *)((char *)v48 + v47 - 8) * v48[v50 - 1]
              + *(double *)((char *)v48 + v49) * v48[v50 - 2]
              + v42
              + *(double *)((char *)v48 + v47) * v48[v50]
              + *(double *)((char *)v48 + v47 + 8) * v48[v50 + 1];
          v53 = 5 * v15;
          v43 = *(double *)((char *)v48 + v47 - 8) * v48[v53 - 1]
              + *(double *)((char *)v48 + v49) * v48[v53 - 2]
              + v43
              + *(double *)((char *)v48 + v47) * v48[v53]
              + *(double *)((char *)v48 + v47 + 8) * v48[v53 + 1];
          v55 = *(double *)((char *)v48 + v47 - 8) * v48[v51 - 1] + *(double *)((char *)v48 + v49) * v48[v51 - 2] + v44;
          v56 = *(double *)((char *)v48 + v47 - 8) * v48[v52 - 1];
          v57 = *(double *)((char *)v48 + v47);
          v58 = v57 * v48[v52];
          v59 = *(double *)((char *)v48 + v47 + 8);
          v60 = v57 * v48[6 * v15];
          v61 = *(double *)((char *)v48 + v49) * v48[v52 - 2] + v45;
          v62 = v59 * v48[v52 + 1];
          v63 = v59 * v48[v51 + 1];
          v48 += 4;
          v44 = v55 + v60 + v63;
          v45 = v61 + v56 + v58 + v62;
          --v54;
        }
        while ( v54 );
        a2 = v171;
        v13 = ((long long*)&v169)[0];
        v18 = v164;
        v8 = a6;
        v24 = v172;
        v9 = a7;
        if ( v25 < v171 )
        {
LABEL_14:
          v64 = v46 - v172 - v13;
          v65 = (double *)(v13 + 8 * (v15 + v25 + v160));
          v66 = a2 - v25;
          do
          {
            v67 = *(double *)((char *)v65 + v64);
            v38 = v38 + v67 * v65[-v15];
            v39 = v39 + v67 * *v65;
            v40 = v40 + v67 * v65[v15];
            v41 = v41 + v67 * v65[2 * v15];
            v68 = v67 * v65[4 * v15];
            v42 = v42 + v67 * v65[3 * v15];
            v69 = v67 * v65[5 * v15];
            v70 = v67 * v65[6 * v15];
            ++v65;
            v43 = v43 + v68;
            v44 = v44 + v69;
            v45 = v45 + v70;
            --v66;
          }
          while ( v66 );
          v8 = a6;
          v24 = v172;
        }
        v22 = -a6;
        v20 = 2 * a6;
        v21 = -2 * a6;
        v19 = v160;
      }
      v24 += v168;
      v10 = a4;
      v18 += 8LL;
      v19 += v16 * 8;
      v164 = v18;
      v160 = v19;
      v172 = v24;
      v23[v21] = v38 * v9 + v23[v21];
      v23[v22] = v39 * v9 + v23[v22];
      *v23 = v40 * v9 + *v23;
      v23[v8] = v41 * v9 + v23[v8];
      v23[v20] = v42 * v9 + v23[v20];
      v23[3 * v8] = v43 * v9 + v23[3 * v8];
      v23[4 * a6] = v44 * v9 + v23[4 * a6];
      v23[5 * v8] = v45 * v9 + v23[5 * v8];
      v23 += 8 * a6;
    }
    while ( v18 < v162 );
    result = v165;
  }
  if ( v18 < result )
  {
    v71 = v13 + 8 * (v15 - 2);
    v72 = v18 * v15;
    v73 = 8 * v18 * v15;
    v173 = v18 * v15;
    v161 = v73;
    v74 = (double *)(a5 + 8 * v8 * v18);
    result = 16 * v8;
    v75 = 3 * v8;
    do
    {
      v76 = 0;
      v77 = _mm_setzero_pd();
      v78 = _mm_setzero_pd();
      v79 = _mm_setzero_pd();
      v80 = _mm_setzero_pd();
      if ( a2 >= 2 )
      {
        v81 = 2;
        v82 = (__m128d *)(v73 + v71 + 16);
        do
        {
          v83 = _mm_loadu_pd((const double *)((char *)v82 + *v10 - v73 - v16 * 8 - v13));
          v76 += 2;
          v81 += 2;
          v77 = _mm_add_pd(v77, _mm_mul_pd(_mm_loadu_pd((const double *)((char *)v82 - 8 * v15)), v83));
          v78 = _mm_add_pd(v78, _mm_mul_pd(_mm_loadu_pd((const double *)v82), v83));
          v79 = _mm_add_pd(v79, _mm_mul_pd(_mm_loadu_pd((const double *)((char *)v82 + 8 * v15)), v83));
          v84 = _mm_loadu_pd((const double *)&v82[v15]);
          ++v82;
          v80 = _mm_add_pd(v80, _mm_mul_pd(v84, v83));
        }
        while ( v81 <= a2 );
        v72 = v173;
        result = 16 * v8;
        v75 = 3 * v8;
      }
      v85 = _mm_cvtsd_f64(_mm_add_sd(v77, _mm_unpackhi_pd(v77, v77)));
      v86 = _mm_cvtsd_f64(_mm_add_sd(v78, _mm_unpackhi_pd(v78, v78)));
      v87 = _mm_cvtsd_f64(_mm_add_sd(v79, _mm_unpackhi_pd(v79, v79)));
      v88 = _mm_cvtsd_f64(_mm_add_sd(v80, _mm_unpackhi_pd(v80, v80)));
      if ( v76 < a2 )
      {
        v89 = *v10;
        if ( a2 - v76 < 4 )
          goto LABEL_31;
        v90 = v89 - v73 - v13;
        v91 = (double *)(v13 + 8 * (v76 + v72 + 2));
        v92 = v89 - v161 - v13;
        v93 = ((unsigned __int64)(a2 - v76 - 4) >> 2) + 1;
        v76 += 4 * v93;
        do
        {
          v85 = *(double *)((char *)v91 + v90 - 8) * *(v91 - 1)
              + *(double *)((char *)v91 + v92 - 16) * *(v91 - 2)
              + v85
              + *(double *)((char *)v91 + v90) * *v91
              + *(double *)((char *)v91 + v90 + 8) * v91[1];
          v94 = *(double *)((char *)v91 + v90 - 8) * v91[2 * v15 - 1]
              + *(double *)((char *)v91 + v92 - 16) * v91[2 * v15 - 2]
              + v87;
          v95 = *(double *)((char *)v91 + v90);
          v96 = v95 * v91[3 * v15];
          v97 = v95 * v91[2 * v15];
          v86 = *(double *)((char *)v91 + v90 - 8) * v91[v16 - 1]
              + *(double *)((char *)v91 + v92 - 16) * v91[v15 - 2]
              + v86
              + *(double *)((char *)v91 + v90) * v91[v16]
              + *(double *)((char *)v91 + v90 + 8) * v91[v16 + 1];
          v98 = *(double *)((char *)v91 + v90 + 8);
          v99 = v98 * v91[3 * v15 + 1];
          v100 = v98 * v91[2 * v15 + 1];
          v101 = *(double *)((char *)v91 + v92 - 16) * v91[3 * v15 - 2]
               + v88
               + *(double *)((char *)v91 + v90 - 8) * v91[3 * v15 - 1]
               + v96;
          v91 += 4;
          v87 = v94 + v97 + v100;
          v88 = v101 + v99;
          --v93;
        }
        while ( v93 );
        v73 = v161;
        if ( v76 < a2 )
        {
LABEL_31:
          v102 = v89 - v73 - v16 * 8 - v13;
          v103 = (double *)(v13 + 8 * (v173 + v76 + v15));
          v104 = a2 - v76;
          do
          {
            v85 = v85 + *(double *)((char *)v103 + v102) * v103[-v15];
            v105 = *(double *)((char *)v103 + v102) * v103[v15];
            v106 = *(double *)((char *)v103 + v102) * v103[2 * v15];
            v86 = v86 + *(double *)((char *)v103 + v102) * *v103;
            ++v103;
            v87 = v87 + v105;
            v88 = v88 + v106;
            --v104;
          }
          while ( v104 );
        }
        result = 16 * v8;
        v72 = v173;
        v75 = 3 * v8;
        v9 = a7;
      }
      v73 += 32 * v15;
      v10 = a4;
      v71 = v13 + 8 * (v15 - 2);
      v72 += 4 * v15;
      v18 += 4LL;
      v173 = v72;
      v161 = v73;
      *v74 = v85 * v9 + *v74;
      v74[v8] = v86 * v9 + v74[v8];
      *(double *)((char *)v74 + result) = v87 * v9 + *(double *)((char *)v74 + result);
      v74[v75] = v88 * v9 + v74[v75];
      v74 += 4 * v8;
    }
    while ( v18 < v165 );
  }
  if ( v18 < v166 )
  {
    v107 = v18 * v15;
    v108 = 8 * v18 * v15;
    v109 = (double *)(a5 + 8 * v8 * v18);
    result = v13 + 8 * (v15 - 2);
    do
    {
      v110 = 0;
      v111 = _mm_setzero_pd();
      v112 = _mm_setzero_pd();
      if ( a2 >= 2 )
      {
        v113 = 2;
        v114 = (__m128d *)(v108 + result + 16);
        do
        {
          v115 = _mm_loadu_pd((const double *)((char *)v114 + *a4 - v108 - v16 * 8 - v13));
          v110 += 2;
          v113 += 2;
          v111 = _mm_add_pd(v111, _mm_mul_pd(_mm_loadu_pd((const double *)((char *)v114 - 8 * v15)), v115));
          v116 = _mm_loadu_pd((const double *)v114);
          ++v114;
          v112 = _mm_add_pd(v112, _mm_mul_pd(v115, v116));
        }
        while ( v113 <= a2 );
      }
      v117 = _mm_cvtsd_f64(_mm_add_sd(v111, _mm_unpackhi_pd(v111, v111)));
      v118 = _mm_cvtsd_f64(_mm_add_sd(v112, _mm_unpackhi_pd(v112, v112)));
      if ( v110 < a2 )
      {
        v119 = *a4;
        if ( a2 - v110 < 4 )
          goto LABEL_45;
        v120 = v119 - v108 - v13;
        v121 = (double *)(v13 + 8 * (v107 + v110 + 2));
        v122 = ((unsigned __int64)(a2 - v110 - 4) >> 2) + 1;
        v110 += 4 * v122;
        do
        {
          v123 = *(double *)((char *)v121 + v119 - v108 - v13 - 16);
          v124 = *(double *)((char *)v121 + v120);
          v125 = *(double *)((char *)v121 + v120 + 8);
          v126 = v124 * v121[v16];
          v127 = v123 * v121[v15 - 2] + v118;
          v128 = v124 * *v121;
          v129 = v125 * v121[v16 + 1];
          v130 = v123 * *(v121 - 2) + v117;
          v131 = v125 * v121[1];
          v132 = *(double *)((char *)v121 + v120 - 8) * *(v121 - 1);
          v133 = *(double *)((char *)v121 + v120 - 8) * v121[v16 - 1];
          v121 += 4;
          v117 = v132 + v130 + v128 + v131;
          v118 = v127 + v133 + v126 + v129;
          --v122;
        }
        while ( v122 );
        if ( v110 < a2 )
        {
LABEL_45:
          v134 = v119 - v108 - v16 * 8 - v13;
          v135 = (double *)(v13 + 8 * (v15 + v107 + v110));
          v136 = a2 - v110;
          do
          {
            v137 = *(double *)((char *)v135 + v134);
            v138 = v137 * *v135;
            v139 = v137 * v135[-v15];
            ++v135;
            v118 = v118 + v138;
            v117 = v117 + v139;
            --v136;
          }
          while ( v136 );
        }
        v9 = a7;
      }
      v108 += 16 * v15;
      v107 += 2 * v15;
      result = v13 + 8 * (v15 - 2);
      v18 += 2LL;
      *v109 = v117 * v9 + *v109;
      v109[v8] = v118 * v9 + v109[v8];
      v109 += 2 * v8;
    }
    while ( v18 < v166 );
  }
  if ( v18 < a1 )
  {
    v174 = 8 * v8;
    v140 = v18 * v15;
    result = v8 * v18;
    v141 = 8 * v18 * v15;
    v142 = a1 - v18;
    v143 = (double *)(a5 + 8 * result);
    do
    {
      v144 = 0;
      v145 = _mm_setzero_pd();
      if ( a2 >= 2 )
      {
        v146 = (__m128d *)*a4;
        v147 = 2;
        result = v13 + v141 - *a4;
        do
        {
          v148 = _mm_loadu_pd((const double *)((char *)v146 + result));
          v144 += 2;
          v147 += 2;
          v149 = _mm_loadu_pd((const double *)v146);
          ++v146;
          v145 = _mm_add_pd(v145, _mm_mul_pd(v148, v149));
        }
        while ( v147 <= a2 );
      }
      v150 = _mm_cvtsd_f64(_mm_add_sd(v145, _mm_unpackhi_pd(v145, v145)));
      if ( v144 < a2 )
      {
        v151 = *a4;
        if ( a2 - v144 < 4 )
          goto LABEL_59;
        v152 = v151 - v141 - v13;
        v153 = (double *)(v13 + 8 * (v144 + v140 + 2));
        result = ((unsigned __int64)(a2 - v144 - 4) >> 2) + 1;
        v144 += 4 * result;
        do
        {
          v154 = *(double *)((char *)v153 + v152) * *v153;
          v155 = *(double *)((char *)v153 + v151 - v141 - v13 - 16) * *(v153 - 2) + v150;
          v156 = *(double *)((char *)v153 + v152 - 8) * *(v153 - 1);
          v157 = *(double *)((char *)v153 + v152 + 8) * v153[1];
          v153 += 4;
          v150 = v156 + v155 + v154 + v157;
          --result;
        }
        while ( result );
        if ( v144 < a2 )
        {
LABEL_59:
          v158 = (double *)(v151 + 8 * v144);
          result = a2 - v144;
          do
          {
            v159 = *(double *)((char *)v158 + v13 + v141 - v151) * *v158;
            ++v158;
            v150 = v150 + v159;
            --result;
          }
          while ( result );
        }
      }
      v140 += v15;
      v141 += v16 * 8;
      *v143 = v150 * v9 + *v143;
      v143 = (double *)((char *)v143 + v174);
      --v142;
    }
    while ( v142 );
  }
  return result;
}
