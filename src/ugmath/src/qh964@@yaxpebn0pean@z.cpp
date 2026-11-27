










#include <emmintrin.h>
#include <intrin.h>

int  b15_checking_level();
void b15_MTX3_multiply_t(const double*, const double*, double*);
int  b15_MTX3_init_x_y_z(const double*, const double*, const double*, double*);
int  b15_MTX3_init(const double*, const double*, double*);
int  b15_MTX3_ortho_normalize(double*);
int  b15_MTX3_is_ortho_normal(const double*);
int  b15_MTX3_is_equal(const double*, const double*, double);
int  b15_print_matrix(const char*, const double*);


int  b15_lp_msg(const char* fmt);
int  b15_lp_row(const char* fmt, const char* tag, double, double, double);
int  b15_lp_1d(const char* fmt, double);
void b15_error_note(const char*, int, const char*);
void b15_error_internal(const char*, int, const char*);

static const char* const kSrc = "o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\h964.c";
static const char* const kMsg172 = "Old method of h964() failed to produce a matrix";
static const char* const kMsg221 = "First attempt in h964() failed to produce a matrix";
static const char* const kMsg266 =
    "V14 version of h964() produced different result than V15 version.";




__declspec(noinline) static double h964_det(const double* m)
{
    __m128d m0 = _mm_load_sd(m + 0);
    __m128d m1 = _mm_load_sd(m + 1);
    __m128d m2 = _mm_load_sd(m + 2);
    __m128d m3 = _mm_load_sd(m + 3);
    __m128d m4 = _mm_load_sd(m + 4);
    __m128d m5 = _mm_load_sd(m + 5);
    __m128d m6 = _mm_load_sd(m + 6);
    __m128d m7 = _mm_load_sd(m + 7);
    __m128d m8 = _mm_load_sd(m + 8);

    __m128d a = _mm_sub_sd(_mm_mul_sd(m4, m0), _mm_mul_sd(m3, m1));
    __m128d b = _mm_sub_sd(_mm_mul_sd(m5, m1), _mm_mul_sd(m4, m2));
    __m128d c = _mm_sub_sd(_mm_mul_sd(m3, m2), _mm_mul_sd(m5, m0));
    __m128d d = _mm_add_sd(_mm_mul_sd(b, m6), _mm_mul_sd(c, m7));
    d = _mm_add_sd(d, _mm_mul_sd(a, m8));
    return _mm_cvtsd_f64(d);
}

void h964(const double* a1, const double* a2, double* a3)
{
    double v15[9];
    double m2[9];
    int inited = 0;
    int v5 = 1;
    const int cl = b15_checking_level();

    v15[0] = 0.0; v15[1] = 0.0; v15[2] = 0.0;
    v15[3] = 0.0; v15[4] = 0.0; v15[5] = 0.0;
    v15[6] = 0.0; v15[7] = 0.0; v15[8] = 0.0;

    m2[0] = 1.0; m2[1] = 0.0; m2[2] = 0.0;
    m2[3] = 0.0; m2[4] = 1.0; m2[5] = 0.0;
    m2[6] = 0.0; m2[7] = 0.0; m2[8] = 1.0;

    if (cl >= 1)
    {
        inited = 1;
        b15_MTX3_multiply_t(a2, a1, v15);

        __m128d one = _mm_set_sd(1.0);
        __m128d amask = _mm_castsi128_pd(_mm_set1_epi64x(0x7FFFFFFFFFFFFFFFll));
        __m128d s = _mm_load_sd(a2 + 12);
        __m128d adiff = _mm_and_pd(_mm_sub_sd(s, one), amask);

        if (_mm_comile_sd(adiff, _mm_set_sd(1e-10)) == 0)
        {
            __m128d r = _mm_div_sd(one, _mm_and_pd(s, amask));
            __m128d rr = _mm_unpacklo_pd(r, r);
            __m128d q = _mm_div_sd(one, s);
            __m128d qq = _mm_unpacklo_pd(q, q);
            double row0[3], row1[3], row2[3];

            row0[2] = _mm_cvtsd_f64(_mm_mul_sd(_mm_load_sd(v15 + 2), r));
            _mm_storeu_pd(row0, _mm_mul_pd(_mm_loadu_pd(v15 + 0), rr));
            double r1z = _mm_cvtsd_f64(_mm_mul_sd(_mm_load_sd(v15 + 5), r));
            _mm_storeu_pd(row1, _mm_mul_pd(_mm_loadu_pd(v15 + 3), rr));
            _mm_storeu_pd(row2, _mm_mul_pd(_mm_loadu_pd(v15 + 6), qq));
            row1[2] = r1z;
            row2[2] = _mm_cvtsd_f64(_mm_mul_sd(_mm_load_sd(v15 + 8), q));

            inited = b15_MTX3_init_x_y_z(row0, row1, row2, v15);
            if (!inited)
                b15_error_note(kSrc, 172, kMsg172);
            else if (h964_det(v15) < 0.0)
            {
                b15_lp_msg("Old method of h964() returning a left-handed matrix\n");
                inited = -1;
            }
        }
        else
        {
            double d = h964_det(v15);
            if (d < 0.0)
            {
                b15_lp_msg("Old method of h964() returning a left-handed matrix\n");
                inited = -1;
            }
            else if (!inited)
                b15_error_note(kSrc, 172, kMsg172);
        }
    }

    b15_MTX3_multiply_t(a2, a1, m2);

    double t[6];
    t[0] = m2[0]; t[1] = m2[1]; t[2] = m2[2];
    t[3] = m2[3]; t[4] = m2[4]; t[5] = m2[5];
    if (!b15_MTX3_init(t, t + 3, a3))
    {
        v5 = 0;
        if (cl >= 1)
            b15_error_note(kSrc, 221, kMsg221);
        b15_print_matrix("transformation matrix", a2);
        b15_print_matrix("orginal csys matrix", a1);
        if (cl >= 1)
        {
            b15_lp_row("%s\n       % 14.12e % 14.12e % 14.12e\n",
                        "X axis", t[0], t[1], t[2]);
            b15_lp_row("%s\n       % 14.12e % 14.12e % 14.12e\n",
                        "Y axis", t[3], t[4], t[5]);
        }
        b15_MTX3_ortho_normalize(m2);
        a3[0] = m2[0]; a3[1] = m2[1]; a3[2] = m2[2];
        a3[3] = m2[3]; a3[4] = m2[4]; a3[5] = m2[5];
        a3[6] = m2[6]; a3[7] = m2[7]; a3[8] = m2[8];
        b15_print_matrix("h964 output", a3);
    }

    if (cl >= 1 && inited > 0 && v5 &&
        b15_MTX3_is_ortho_normal(a1) &&
        b15_MTX3_is_ortho_normal(v15) &&
        !b15_MTX3_is_equal(a3, v15, 0.00000001))
    {
        b15_print_matrix("transformation matrix", a2);
        b15_print_matrix("orginal csys matrix", a1);
        b15_lp_1d("transformation scale factor = % 14.12e\n", a2[12]);
        b15_print_matrix("V14 output result", v15);
        b15_print_matrix("V15 output result", a3);
        b15_error_internal(kSrc, 266, kMsg266);
        __debugbreak();
    }
}
