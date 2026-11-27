







#include <math.h>
#include <string.h>
#include <float.h>








struct BCURVE_DATA
{
    double* nodes;
    double* knots;
    int field_10;
    int field_14;
    int field_18;
    int field_1c;
};

void e4322(int* a1, int* a2, double* a3, double* a4, int* a5);
void e0925(int* a1, double* a2, double* a3, double* a4);
void em0912(int* a1, double* a2, double* a3, double* a4, double* a5);
void em0926(int* a1, double* a2, int* a3, double* a4);
void k71433(double* a1, double* a2, int* a3);
double EQ_ask_number_tolerance();

void bc_xyz_box(BCURVE_DATA* a1, double* a2, double* a3)
{
    double* v53 = a3;
    int v3 = a1->field_14;
    int v6 = v3 + a1->field_10;
    double v7 = DBL_MAX;
    double v10 = -DBL_MAX;
    double v11 = DBL_MAX;
    double v12 = -DBL_MAX;
    double v13 = DBL_MAX;
    double v14 = -DBL_MAX;
    int v41 = v3 - 1;
    double* v46 = a1->nodes;
    double* v9 = a1->knots;
    int v43[3];
    v43[0] = 3;
    v43[1] = 0;
    v43[2] = 0;
    int v52 = v3;
    int v40 = v6;
    int v39;


    double v47[64];
    double v48[100];
    double v49[100];


    double v50buf[824];

    if (a1->field_1c == 0)
    {
        v39 = 1;
        v47[0] = a2[0];
        v47[1] = a2[1];
    }
    else
    {
        k71433(a2, v47, &v39);
        if (v39 <= 0)
            goto LABEL_36;
    }
    {
        double* v16 = &v47[1];
        int v17 = 0;
        int v18 = 0;
        int v19 = 0;
        int v42 = 0;
        for (;;)
        {
            int v38;
            int v54;
            e4322(&v52, &v40, v9, &v47[v17], &v38);
            e4322(&v52, &v40, v9, &v47[v17 + 1], &v54);
            int v20 = v52;
            int v21 = v38 - v52 - 1;
            v38 = v21;
            v54 += -1 - v52;
            if (v21 > v54)
                goto LABEL_34;
            {
                double* v22 = v46;
                int v23 = 4 * v21;
                do
                {
                    double v45[2];
                    double v44[2];
                    double v26;
                    v20 = v52;
                    v45[0] = v9[v21 - 1 + v20];
                    v45[1] = v9[v21 + v20];
                    if (EQ_ask_number_tolerance() >= fabs(v45[1] - v45[0]))
                        goto LABEL_31;
                    e0925(&v41, &v9[v21], (double*)((char*)v22 + 8LL * v23), v48);
                    if (v21 == v38)
                    {
                        double v24 = *v16;
                        double v25 = *(v16 - 1);
                        v44[0] = v25;
                        if (v45[1] > v24 || v38 == v54)
                        {
                            v44[1] = v24;
                            v26 = v24 - v25;
                        }
                        else
                        {
                            v44[1] = v45[1];
                            v26 = v45[1] - v25;
                        }
                    }
                    else
                    {
                        if (v21 != v54)
                        {
                            v44[0] = v45[0];
                            v44[1] = v45[1];
                            if (4 * v52 > 0)
                                memcpy(v49, v48, 32LL * v52);
                            goto LABEL_22;
                        }
                        {
                            double v27 = *(v16 - 1);
                            if (v27 <= v45[0])
                            {
                                v44[0] = v45[0];
                                v27 = v45[0];
                            }
                            else
                            {
                                v44[0] = *(v16 - 1);
                            }
                            v44[1] = *v16;
                            v26 = v44[1] - v27;
                        }
                    }
                    if (EQ_ask_number_tolerance() >= fabs(v26))
                        goto LABEL_31;
                    em0912(&v41, v45, v48, v44, v49);
                LABEL_22:
                    em0926(&v52, v49, v43, v50buf);
                    {
                        double* v28 = v50buf + 1;
                        long long v29 = 8;
                        do
                        {
                            if (v52 > 0)
                            {
                                double* v30 = v28;
                                int v31 = v52;
                                do
                                {
                                    double v32 = v30[2];
                                    double v33 = *(v30 - 1) / v32;
                                    double v34 = *v30 / v32;
                                    double v35 = v30[1] / v32;
                                    if (v19)
                                    {
                                        v33 = fmax(v33, v10);
                                        v7 = fmin(*(v30 - 1) / v32, v7);
                                        double v36 = fmin(v34, v11);
                                        v34 = fmax(v34, v12);
                                        v11 = v36;
                                        double v37 = fmin(v35, v13);
                                        v35 = fmax(v35, v14);
                                        v13 = v37;
                                    }
                                    else
                                    {
                                        v19 = 1;
                                        v7 = *(v30 - 1) / v32;
                                        v11 = *v30 / v32;
                                        v13 = v30[1] / v32;
                                    }
                                    v30 += 4;
                                    v14 = v35;
                                    v12 = v34;
                                    v10 = v33;
                                    --v31;
                                } while (v31);
                            }
                            v28 += 4 * v52;
                            --v29;
                        } while (v29);
                    }
                LABEL_31:
                    ++v21;
                    v23 += 4;
                } while (v21 <= v54);
            }
        LABEL_34:
            ++v18;
            v17 += 2;
            v16 += 2;
            v42 = v18;
            if (v18 >= v39)
            {
                v53 = a3;
                goto LABEL_36;
            }
        }
    }
LABEL_36:
    a3[0] = v7;
    a3[1] = v11;
    a3[2] = v13;
    a3[3] = v10;
    a3[4] = v12;
    a3[5] = v14;
}
