









#include <math.h>
#include <emmintrin.h>

extern void h270(const double* a1, const double* a2, const double* a3, const double* a4, double* a5);
extern void h805(const double* a1, const double* a2, const int* a3, int* a4);
extern double EQ_ask_length_tolerance(void);

static const int kZeroMode = 0;
static const double kOne = 1.0;

void h502(int const* a1, double const* a2, double const* a3, double const* a4,
          double const* a5, double const* a6, double const* a7, int* a8,
          double* a9, double* a10)
{
    double out2[2];
    h270(a7, a2, a5, a6, out2);
    double v16 = out2[0];
    double v52 = out2[1];
    double v17 = v52 * v52;
    double v19 = sqrt(v16 * v16 + v52 * v52);
    double v20 = *a3;

    double v21 = _mm_cvtsd_f64(_mm_max_sd(_mm_set_sd(1.0), _mm_set_sd(v19)));
    double v35 = 0.0, v36 = 0.0, v34 = 0.0, v37 = 0.0;
    if (*a1 - 3 >= 0)
    {
        if (*a1 == 3)
        {
            double v38 = v52 * -2.0;
            double v39 = v38 * v38 - v16 * v20 * 4.0;

            if (!(EQ_ask_length_tolerance() >= fabs(v39 / (v21 * v21))))
            {
                *a8 = 1;
                if (v39 < 0.0)
                    return;
                *a8 = 3;
                double v40 = sqrt(v39);
                v36 = (v40 - v38) * 0.5;
                v37 = (-v38 - v40) * 0.5;
                v35 = v36 * v36 / *a3;
                v34 = v37 * v37 / *a3;
                goto L27;
            }
        }
        else
        {
            double v41 = v20 * v20;
            double v42 = *a4 * *a4;
            double v43 = v42 * v41 - v16 * v16 * v42 + v17 * v41;

            if (!(EQ_ask_length_tolerance() >= fabs(v43 - 0.0))
                && !(EQ_ask_length_tolerance() >= fabs(v43 / (v42 * v41) - 0.0)))
            {
                *a8 = 1;
                if (v43 < 0.0)
                    return;
                double v44 = sqrt(v43);
                double v45 = v52 * v16;
                double v46 = (v17 + v42) * *a3;
                double v47 = (v52 * v16 + v44) * *a4 / v46;
                double v48 = (*a4 * v16 - *a3 * v52 * v47) / (*a3 * *a4);
                if (v48 <= 0.0 || EQ_ask_length_tolerance() >= fabs(v48 - 0.0))
                {
                    v35 = v52;
                    v36 = v52;
                }
                else
                {
                    *a8 = 2;
                    v35 = *a3 / v48;
                    v36 = v47 * *a4 / v48;
                }
                double v49 = (v45 - v44) * *a4 / v46;
                double v50 = (*a4 * v16 - *a3 * v52 * v49) / (*a3 * *a4);
                if (v50 <= 0.0 || EQ_ask_length_tolerance() >= fabs(v50 - 0.0))
                {
                    v34 = v52;
                    v37 = v52;
                }
                else
                {
                    ++*a8;
                    v34 = *a3 / v50;
                    v37 = v49 * *a4 / v50;
                    if (*a8 != 3)
                    {
                        v35 = *a3 / v50;
                        v36 = v37;
                        goto L28;
                    }
                }
                if (*a8 - 2 < 0)
                    return;
                if (*a8 == 2)
                    goto L28;
                goto L27;
            }
        }
    }
    else
    {



        const __m128d a4v = _mm_set_sd(*a4);
        const __m128d a3v = _mm_set_sd(v20);
        const __m128d v16v = _mm_set_sd(v16);
        const __m128d v52v = _mm_set_sd(v52);
        const __m128d v22 = _mm_mul_sd(a4v, a4v);
        const __m128d v23 = _mm_mul_sd(a3v, a3v);
        const __m128d v24 = _mm_mul_sd(v16v, v22);
        const __m128d t12 = _mm_mul_sd(v52v, v23);
        const __m128d tB = _mm_mul_sd(v16v, v24);
        const __m128d v25 = _mm_mul_sd(v22, v23);
        const __m128d tA = _mm_mul_sd(t12, v52v);
        const __m128d v26v = _mm_add_sd(tA, tB);
        const __m128d v27v = _mm_sub_sd(v26v, v25);
        const double v26 = _mm_cvtsd_f64(v26v);
        const double v27 = _mm_cvtsd_f64(v27v);
        const double v25d = _mm_cvtsd_f64(v25);

        if (!(EQ_ask_length_tolerance() >= fabs(v27))
            && !(EQ_ask_length_tolerance() >= fabs(v27 / v25d - 0.0)))
        {
            *a8 = 1;
            if (v27 < 0.0)
                return;
            *a8 = 3;
            double v28 = sqrt(v27);
            const __m128d v28v = _mm_set_sd(v28);
            const __m128d v30 = _mm_mul_sd(t12, v28v);
            const __m128d v31 = _mm_mul_sd(v25, v52v);
            const __m128d v33 = _mm_mul_sd(v25, v16v);
            const __m128d v32 = _mm_mul_sd(v24, v28v);
            v34 = _mm_cvtsd_f64(_mm_div_sd(_mm_sub_sd(v33, v30), v26v));
            v35 = _mm_cvtsd_f64(_mm_div_sd(_mm_add_sd(v33, v30), v26v));
            v36 = _mm_cvtsd_f64(_mm_div_sd(_mm_sub_sd(v31, v32), v26v));
            v37 = _mm_cvtsd_f64(_mm_div_sd(_mm_add_sd(v31, v32), v26v));
            goto L27;
        }
    }
    *a8 = 4;
    a9[0] = *a7;
    a9[1] = a7[1];
    return;
L27:
    a10[0] = v34 * *a5 - v37 * *a6 + *a2;
    a10[1] = v37 * *a5 + v34 * *a6 + a2[1];
L28:
    a9[0] = v35 * *a5 - v36 * *a6 + *a2;
    a9[1] = v36 * *a5 + v35 * *a6 + a2[1];
}
