






#include <math.h>
#include <cstring>

double EQ_ask_number_tolerance();
void em0911(int* a1, double* a2, double* a3, double* a4, double* a5);
void h804(double* a1, const double* a2, const int* a3, int* a4);

void em0912(int* a1, double* a2, double* a3, double* a4, double* a5) {
    int v5;
    double v9, v11, v12, v13, v14, v15, v16, v17, v18;
    int v19;
    double v20, v21;
    double* v22;
    double v23, v24, v25, v26, v27, v28;
    double *v29, *v30, *v31;
    double v32, v33;
    double v35[99];
    double v34[100];
    int v37;
    int v36;
    double v38;

    v5 = *a1;
    v9 = fabs(*a4 - *a2);
    v36 = 0;
    if (EQ_ask_number_tolerance() >= v9) {
        v11 = fabs(a4[1] - a2[1]);
        if (EQ_ask_number_tolerance() >= v11) {
            memcpy(a5, a3, 8LL * (4 * v5 + 4));
            return;
        }
    }
    v12 = fabs(*a4 - *a2);
    if (EQ_ask_number_tolerance() >= v12 ||
        ((v13 = fabs(*a4 - a2[1])), EQ_ask_number_tolerance() >= v13)) {
        v19 = 4 * v5 + 4;
        v20 = fabs(*a4 - *a2);
        v21 = EQ_ask_number_tolerance();
        if (v21 >= v20)
            memcpy(v34, a3, 8LL * v19);
        else
            memcpy(v35, a3, 8LL * v19);
    } else {
        v14 = *a4;
        v15 = *a2;
        v16 = a2[1];
        if (*a2 <= *a4) {
            v18 = v16 - v15;
            if (v14 <= v16)
                v17 = (v14 - v15) / v18;
            else
                v17 = (v14 - v16) / v18 + 1.0;
        } else {
            v17 = (v14 - v15) / (v16 - v15);
        }
        v38 = v17;
        em0911(a1, a3, &v38, v35, v34);
        v19 = 4 * v5 + 4;
    }
    v38 = *a4;
    h804(&v38, a2, &v36, &v37);
    if (v37 == 1) {
        v23 = fabs(a4[1] - *a2);
        if (EQ_ask_number_tolerance() >= v23) {
            memcpy(a5, v35, 8LL * v19);
            return;
        }
        v24 = fabs(a4[1] - a2[1]);
        if (!(EQ_ask_number_tolerance() >= v24))
            goto LABEL_19;
        goto LABEL_25;
    }
    if (v37 < 4) {
        v32 = fabs(a4[1] - a2[1]);
        if (!(EQ_ask_number_tolerance() >= v32)) {
LABEL_19:
            v25 = a2[1];
            v26 = a4[1];
            v27 = v25 - *a4;
            if (v25 <= v26)
                v28 = (v26 - v25) / v27 + 1.0;
            else
                v28 = (v26 - *a4) / v27;
            v29 = a5;
            v30 = v35;
            v38 = v28;
            v31 = v34;
            goto LABEL_31;
        }
LABEL_25:
        memcpy(a5, v34, 8LL * v19);
        return;
    }
    if (v37 == 4) {
        v33 = a2[1];
    } else {
        if (v37 != 5)
            return;
        v33 = *a4;
    }
    v31 = v35;
    v30 = a5;
    v29 = v34;
    v38 = (a4[1] - v33) / (v33 - *a2) + 1.0;
LABEL_31:
    em0911(a1, v31, &v38, v29, v30);
}
