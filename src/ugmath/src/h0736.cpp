









void h0736(const double* a1, double* a2)
{
    double v2;
    double v3;
    double v4;
    double v5;
    double v6;
    double v7;
    double v8;
    double v9;
    double v10;
    double v11;

    *a2 = *a1;
    a2[1] = *a1;
    a2[2] = a1[1];
    a2[3] = a1[1];
    v2 = *a2;
    v3 = a1[2];
    if (*a2 > v3) {
        *a2 = v3;
        v2 = v3;
        v3 = a1[2];
    }
    v4 = a2[1];
    if (v3 > v4) {
        a2[1] = v3;
        v4 = v3;
    }
    v5 = a1[3];
    v6 = a2[2];
    if (v6 > v5) {
        a2[2] = v5;
        v6 = v5;
        v5 = a1[3];
    }
    v7 = a2[3];
    if (v5 > v7) {
        a2[3] = v5;
        v7 = v5;
    }
    v8 = a1[4];
    if (v2 > v8) {
        *a2 = v8;
        v2 = v8;
        v8 = a1[4];
    }
    if (v8 > v4) {
        a2[1] = v8;
        v4 = v8;
    }
    v9 = a1[5];
    if (v6 > v9) {
        a2[2] = v9;
        v6 = v9;
        v9 = a1[5];
    }
    if (v9 > v7) {
        a2[3] = v9;
        v7 = v9;
    }
    v10 = a1[6];
    if (v2 > v10) {
        *a2 = v10;
        v10 = a1[6];
    }
    if (v10 > v4)
        a2[1] = v10;
    v11 = a1[7];
    if (v6 > v11) {
        a2[2] = v11;
        v11 = a1[7];
    }
    if (v11 > v7)
        a2[3] = v11;
}
