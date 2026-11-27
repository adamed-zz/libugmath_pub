











extern void em0200(const double* a1, const double* a2, double* a3, double* a4, double* a5);
extern void h0747(const double* a1, const double* a2, const double* a3, const double* a4,
                  double* a5);
extern void h805(const double* a1, const double* a2, const int* a3, int* a4);

void h0731(const double* a1, const double* a2, int* a3)
{
    int mode = 0;
    double zero = 0.0;
    int i = 0;
    double v15, v14, v13, v17[2], v12;
    double v10 = 0.0;
    int v18;
    for (;;) {
        int next = i + 2;
        int j = 0;
        if (i != 6)
            j = i + 2;
        em0200(&a1[i], &a1[j], &v15, &v14, &v13);
        int k = 0;
        if (j != 6)
            k = j + 2;
        h0747(&v15, &v14, &v13, &a1[k], v17);
        h0747(&v15, &v14, &v13, a2, &v12);
        h805(&v12, &zero, &mode, &v18);
        if (v18 == 1)
            goto inside;
        v10 = v12 * v17[0];
        if (v10 < 0.0) {
            h0747(&v15, &v14, &v13, a2 + 2, &v12);
            h805(&v12, &zero, &mode, &v18);
            if (v18 == 1)
                goto inside;
            v10 = v12 * v17[0];
            if (v10 < 0.0) {
                h0747(&v15, &v14, &v13, a2 + 4, &v12);
                h805(&v12, &zero, &mode, &v18);
                if (v18 == 1)
                    goto inside;
                v10 = v12 * v17[0];
                if (v10 < 0.0) {
                    h0747(&v15, &v14, &v13, a2 + 6, &v12);
                    h805(&v12, &zero, &mode, &v18);
                    if (v18 == 1)
                        goto inside;
                    v10 = v12 * v17[0];
                    if (v10 < 0.0)
                        break;
                }
            }
        }
        if (v10 != 0.0) {
            i = next;
            if (next < 8)
                continue;
        }
    inside:
        *a3 = 1;
        return;
    }
    *a3 = 0;
}
