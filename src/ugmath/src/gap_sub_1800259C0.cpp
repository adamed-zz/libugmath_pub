







#define B6_PX(k) (*(const double*)(a3 + 24LL * (k)))
#define B6_PY(k) (*(const double*)(a3 + 24LL * (k) + 8))
#define B6_PZ(k) (*(const double*)(a3 + 24LL * (k) + 16))

extern "C" char sub_1800259C0(int a1, int* a2, const unsigned char* a3,
                              const double* a4, int a5, int a6, int a7) {
    if (a1 <= 0)
        return 0;
    int* v11 = &a2[a5];
    int* v12 = &a2[a6];
    int* v10 = &a2[a7];
    int v7 = 0;
    int* v9 = a2;
    while (1) {
        if (!(v7 == a5 || v7 == a6 || v7 == a7)) {
        const int idx9 = *v9;
        const int idx11 = *v11;
        const int idx12 = *v12;
        const int idx10 = *v10;

        {
            double v13 = B6_PZ(idx11) - B6_PZ(idx12);
            double v14 = B6_PX(idx12);
            double v15 = B6_PX(idx11) - v14;
            double v16 = B6_PZ(idx12) - B6_PZ(idx9);
            double v17 = B6_PY(idx11) - B6_PY(idx12);
            double v18 = B6_PY(idx12) - B6_PY(idx9);
            double v19 = v14 - B6_PX(idx9);
            double v21 = (v16 * v17
                          - v18 * v13
                          + 0.0
                          + (B6_PZ(idx9) - B6_PZ(idx11)) * v18
                          - (B6_PY(idx9) - B6_PY(idx11)) * v16
                          + (B6_PY(idx9) - B6_PY(idx11)) * v13
                          - (B6_PZ(idx9) - B6_PZ(idx11)) * v17) * a4[0];
            double v22 = v21
                         + (v19 * v13
                            - v16 * v15
                            + 0.0
                            + (B6_PX(idx9) - B6_PX(idx11)) * v16
                            - (B6_PZ(idx9) - B6_PZ(idx11)) * v19
                            + (B6_PZ(idx9) - B6_PZ(idx11)) * v15
                            - (B6_PX(idx9) - B6_PX(idx11)) * v13) * a4[1];
            double v23 = v18 * v15
                         - v19 * v17
                         + 0.0
                         + (B6_PY(idx9) - B6_PY(idx11)) * v19
                         - (B6_PX(idx9) - B6_PX(idx11)) * v18
                         + (B6_PX(idx9) - B6_PX(idx11)) * v17
                         - (B6_PY(idx9) - B6_PY(idx11)) * v15;
            double v24 = B6_PY(idx9);
            double v25 = B6_PZ(idx9);
            double v26 = B6_PX(idx9);
            double v27 = B6_PX(idx10);
            double v28 = B6_PZ(idx10);
            double v29 = v28 - v25;
            double v30 = v25 - B6_PZ(idx12);
            double v31 = B6_PX(idx12) - v27;
            double v32 = v27 - v26;
            double v33 = v26 - B6_PX(idx12);
            double v34 = B6_PZ(idx12) - v28;
            double v35 = B6_PY(idx10);
            double v36 = B6_PY(idx12) - v35;
            int v37 = (v22 + a4[2] * v23 > 0.0) ? 1 : 0;
            double v38 = v35 - v24;
            double v39 = v24 - B6_PY(idx12);
            double v40 = (v29 * v36 - v38 * v34 + 0.0 + v30 * v38
                          - v39 * v29 + v39 * v34 - v30 * v36) * a4[0];
            double v41 = v32 * v34 - v29 * v31 + 0.0 + v33 * v29
                         - v30 * v32 + v30 * v31 - v33 * v34;
            double v42 = (v38 * v31 - v32 * v36 + 0.0 + v39 * v32
                          - v33 * v38 + v33 * v36 - v39 * v31) * a4[2];
            int v43 = v37 + 1;
            double v44 = B6_PZ(idx11);
            double v45 = B6_PY(idx9);
            double v46 = v28 - v44;
            double v47 = v40 + v41 * a4[1];
            double v48 = B6_PX(idx11);
            double v49 = B6_PX(idx10) - v48;
            double v50 = v47 + v42;
            double v51 = B6_PX(idx9);
            double v52 = v48 - v51;
            bool v53 = v50 <= 0.0;
            double v54 = B6_PZ(idx9);
            double v55 = B6_PY(idx11);
            double v56 = v44 - v54;
            double v57 = v35 - v55;
            double v58 = v55 - v45;
            if (v53)
                v43 = v37;
            double v59 = v54 - v28;
            double v62 = v45 - v35;
            int v60 = v43 + 1;
            double v63 = v51 - B6_PX(idx10);


            double t61a = (v56 * v57 - v58 * v46)
                        + (v59 * v58 - v62 * v56);
            double t61b = (v62 * v46 - v59 * v57);
            double t62a = (v52 * v46 - v56 * v49)
                        + (v63 * v56 - v59 * v52);
            double t62b = (v59 * v49 - v63 * v46);
            double t63a = (v58 * v49 - v52 * v57)
                        + (v62 * v52 - v63 * v58);
            double t63b = (v63 * v57 - v62 * v49);
            double v61expr =
                ((t61a + t61b) * a4[0]
                 + (t62a + t62b) * a4[1])
                + (t63a + t63b) * a4[2];
            if (v61expr <= 0.0)
                v60 = v43;
            if (v60 == 3)
                return 1;
        }
        }

        ++v7;
        ++v9;
        if (v7 >= a1)
            return 0;
    }
}
