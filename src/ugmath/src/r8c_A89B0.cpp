




#include <math.h>

extern "C" __declspec(dllimport) int MACH__checking_level;
__declspec(dllimport) void ERROR_assertion_failed(const char*, int,
                                                             const char*, ...);
extern "C" char sub_1800A8730(int, int, int, const double*);

struct Tri {
    int a;
    int b;
    int c;
    int n0;
    int n1;
    int n2;
};

extern "C" char sub_1800A89B0(int a1, const double* a2, int a3, int* a4,
                              Tri* a5, int* a6) {
    int* v48 = a4;
    const int v7 = a1;
    char v9 = 1;
    const int v10 = a1 - 1;
    if (MACH__checking_level > 0 && *a4 >= a3) {
        ERROR_assertion_failed(
            (char*)"o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\ptf_poly_tri_fill.c",
            500, (char*)"%s", (char*)"(*itri) < num_tris");
        a4 = v48;
        v9 = 1;
    }
    if (v7 == 3) {
        const double v11 =
            (a2[5] - a2[1]) * (a2[2] - a2[0]) - (a2[3] - a2[1]) * (a2[4] - a2[0]);
        if (!(1.0e-10 >= fabs(v11)) && !(1.0e-10 > v11)) {
            Tri* t = a5 + *a4;
            t->a = 2;
            t->b = 0;
            t->c = 1;
            t->n0 = -1;
            t->n1 = -1;
            t->n2 = -1;
            if (a6) {
                t->n2 = *a6;
                *a6 = *a4;
            }
            ++*a4;
            return 1;
        }
        return 0;
    }
    int v15 = 1;
    const double* v16 = &a2[(v7 - 1) * 2];
    if (v10 <= 1) return v9;
    int v17 = 1;
    double v18, v19, v20, v21, v22, v23;
LABEL_scan:
    v18 = v16[1];
    v19 = a2[0] - *v16;
    v20 = a2[1] - v18;
    v21 = a2[2 * v17] - *v16;
    v22 = a2[2 * v17 + 1] - v18;
    v23 = v22 * v19 - v21 * v20;
    if (1.0e-10 >= fabs(v23)) {
        const int w24 = v15 + 1;
        ++v17;
        v15 = w24;
        if (v17 >= v7 - 1) return v9;
        goto LABEL_scan;
    }
    {
        int v24 = v15 + 1;
        const double v27 = v23 + v23;
        ++v17;
        const double v28 = v20 * v20 + v19 * v19;
        const double v29 = v22 * v22 + v21 * v21;
        const double v30 = (v29 * v19 - v28 * v21) / v27;
        const double v31 = (v28 * v22 - v29 * v20) / v27;
        const double v32 = v30 * v30;
        const double v33 = v31 * v31;
        const double v34 = v31 + *v16;
        const double v35 = v30 + v18;
        const double v36 = v32 + v33;
        if (1.0e-10 > v23) {
            v15 = v24;
            if (v17 >= v7 - 1) return v9;
            goto LABEL_scan;
        }
        if (v24 < v10) {
            const double v37 = v36 - 1.0e-10;
            const double* v38 = &a2[2 * v17];
            for (;;) {
                const double dx = *v38 - v34;
                const double dy = v38[1] - v35;
                if (v37 > dx * dx + dy * dy) {
                    const double v39 =
                        (v38[1] - v16[1]) * (a2[0] - *v16) -
                        (a2[1] - v16[1]) * (*v38 - *v16);
                    if (!(1.0e-10 >= fabs(v39)) && !(1.0e-10 > v39) &&
                        !sub_1800A8730(v24, v10, (int)v7, a2) &&
                        !sub_1800A8730(v24, 0, (int)v7, a2))
                        break;
                }
                ++v24;
                ++v17;
                v38 += 2;
                if (v24 >= v10) goto LABEL_23;
            }
            v9 = 0;
            v15 = v24;
            if (v17 >= v7 - 1) return v9;
            goto LABEL_scan;
        }
    }
LABEL_23: {
    const int v40 = *v48;
    *v48 = v40 + 1;
    Tri* t = a5 + v40;
    t->a = v10;
    t->b = 0;
    t->c = v15;
    t->n0 = -1;
    t->n1 = -1;
    t->n2 = -1;
    if (a6) {
        t->n2 = *a6;
        *a6 = v40;
    }
    if (v15 <= 1) {
        v9 = 1;
    } else {
        t->n0 = v40;
        v9 = sub_1800A89B0(v15 + 1, a2, a3, v48, a5, &t->n0);
        if (!v9) return 0;
    }
    if (v15 < (int)v7 - 2) {
        t->n1 = v40;
        const int v44 = *v48;
        v9 = sub_1800A89B0((int)v7 - v15, a2 + 2 * v15, a3, v48, a5, &t->n1);
        if (!v9) return 0;
        int v45 = *v48 - v44;
        if (v45 > 0) {
            int* v46 = reinterpret_cast<int*>(a5 + v44) + 2;
            do {
                *(v46 - 2) += v15;
                *(v46 - 1) += v15;
                *v46 += v15;
                v46 += 6;
                --v45;
            } while (v45);
        }
    }
    return v9;
    }
}
