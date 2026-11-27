






#include <cmath>

int h0916(int a1, const double* a2, int a3, int a4, double a5, int a6, double* const a7)
{

    double B[25 * 25 + 8];
    double* const v82 = B + 1;

    int v7 = a6;
    int v8 = 0;
    double* v9 = a7;
    long long v11 = a4;
    long long v12 = a4;
    long long v80 = a4;
    if (a6 >= a4)
    {
        a7[a4] = 0.0;
        v7 = a4 - 1;
    }
    const double v14 = a2[a1 - 1];

    const double v15 = (!(std::fabs(a5 - v14) > 1.0e-10)) ? (v14 - 1.0e-10) : a5;


    for (int col = 0; col < a4; ++col)
    {
        const int i = a3 + col;

        if (!(v15 >= a2[i]) || !(a2[i + 1] > v15))
            B[col] = 0.0;
        else
            B[col] = 1.0;
    }

    const long long v30 = v7;
    const long long v79 = v7;
    if (a4 > 0)
    {


        for (long long col = 0; col < v11; ++col)
            for (long long row = 1; row <= v30; ++row)
                v82[25 * row - 1 + col] = v82[col - 1];
    }

    int v38 = 2;
    if (v11 >= 2)
    {
        int v39 = (int)v11 - 2;
        long long v40 = 2;
        int v87 = (int)v11 - 2;
        while (1)
        {
            int v41 = 0;
            long long v42;
            double* v43;
            double v44;
            long long v84;
            long long v78;
            int v45;
            double* v86;
            if (v30 < 0)
                goto LABEL_88;
            v42 = v39;
            v43 = v82;
            v44 = a2[a3 - 1 + v40] - a2[a3];
            v84 = 0;
            v78 = v30 + 1;
            v45 = (int)v11 + 1;
            v86 = v82;
            do
            {
                double v46;
                if (!(1.0e-10 >= std::fabs(v44)))
                    v46 = *(v43 - 1) / v44;
                else
                    v46 = 0.0;
                long long v47 = 0;
                if (v42 < 0)
                    goto LABEL_86;
                if (v42 < 3)
                    goto LABEL_78;
                {
                    int v48 = 2 * (int)v11;
                    do
                    {
                        long long v49 = v40 + a3 + v47;
                        long long v50 = a3 + v47;
                        double v51 = a2[v49] - a2[a3 + 1 + v47];
                        double v52;
                        if (!(1.0e-10 >= std::fabs(v51)))
                            v52 = *v43 / v51;
                        else
                            v52 = 0.0;
                        double v53;
                        if (v38 >= v45)
                            v53 = (double)(v48 - v41 - v38) * (v46 - v52);
                        else
                            v53 = (a2[v49] - a5) * v52 + (a5 - a2[v50]) * v46;
                        *(v43 - 1) = v53;

                        double v54 = a2[v50 + 2];
                        double v55 = a2[v49 + 1] - v54;
                        double v56;
                        if (!(1.0e-10 >= std::fabs(v55)))
                            v56 = v43[1] / v55;
                        else
                            v56 = 0.0;
                        int v57 = v48 - v41;
                        double v58;
                        if (v38 >= v45)
                            v58 = (double)(v57 - v38) * (v52 - v56);
                        else
                            v58 = (a2[v49 + 1] - a5) * v56 + (a5 - a2[v50 + 1]) * v52;
                        *v43 = v58;

                        double v59 = a2[v50 + 3];
                        double v60 = a2[v49 + 2] - v59;
                        double v61;
                        if (!(1.0e-10 >= std::fabs(v60)))
                            v61 = v43[2] / v60;
                        else
                            v61 = 0.0;
                        int v62 = v57 - v38;
                        double v63;
                        if (v38 >= v45)
                            v63 = (v56 - v61) * (double)v62;
                        else
                            v63 = (a2[v49 + 2] - a5) * v61 + (a5 - v54) * v56;
                        v43[1] = v63;

                        double v64 = a2[v49 + 3] - a2[v50 + 4];
                        if (!(1.0e-10 >= std::fabs(v64)))
                            v46 = v43[3] / v64;
                        else
                            v46 = 0.0;
                        double v65;
                        if (v38 >= v45)
                            v65 = (v61 - v46) * (double)v62;
                        else
                            v65 = (a2[v49 + 3] - a5) * v46 + (a5 - v59) * v61;
                        v43[2] = v65;

                        v47 += 4;
                        v43 += 4;
                    } while (v47 <= v42 - 3);
                }
                v43 = v86;
                if (v47 <= v42)
                {
                    v11 = a4;
                LABEL_78:
                    double* v66 = &v82[v47 - 1 + v84];
                    do
                    {
                        double v67 = a2[v40 + a3 + v47] - a2[a3 + 1 + v47];
                        double v68;
                        if (!(1.0e-10 >= std::fabs(v67)))
                            v68 = v66[1] / v67;
                        else
                            v68 = 0.0;
                        double v69;
                        if (v38 >= v45)
                            v69 = (double)(2 * (int)v11 - v41 - v38) * (v46 - v68);
                        else
                            v69 = (a2[v40 + a3 + v47] - a5) * v68 + (a5 - a2[a3 + v47]) * v46;
                        *v66 = v69;
                        ++v47;
                        ++v66;
                        v46 = v68;
                    } while (v47 <= v42);
                }
            LABEL_86:
                v84 += 25;
                v43 += 25;
                v11 = a4;
                ++v41;
                --v45;
                v86 = v43;
                bool last = (v78-- == 1);
                v8 = 0;
                if (last)
                    break;
            } while (true);

            v39 = v87;
            v12 = v80;
        LABEL_88:
            --v39;
            ++v38;
            ++v40;
            v87 = v39;
            if (v40 > v12)
            {
                v9 = a7;
                break;
            }
        }
    }

    if (v30 >= 0)
    {
        if (v30 < 3)
            goto LABEL_95;
        {
            unsigned long long v71 = (unsigned long long)(v30 + 1) >> 2;
            double* v72 = v82 + 24;
            double* v73 = v9 + 2;
            v8 = (int)(4 * v71);
            do
            {
                double v74 = *(v72 - 25);
                v72 += 100;
                *(v73 - 2) = v74;
                v73 += 4;
                *(v73 - 5) = *(v72 - 100);
                *(v73 - 4) = *(v72 - 75);
                *(v73 - 3) = *(v72 - 50);
                --v71;
            } while (v71);
            if (v8 > v30)
                return 0;
        }
    LABEL_95:
        double* v75 = &v82[25 * (long long)v8 - 1];
        do
        {
            double v76 = *v75;
            v75 += 25;
            v9[v8++] = v76;
        } while (v8 <= v30);
    }
    return 0;
}
