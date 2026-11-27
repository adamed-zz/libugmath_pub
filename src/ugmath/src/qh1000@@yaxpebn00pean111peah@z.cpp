

















#pragma once

#include <cstddef>
#include <cstdint>




#ifdef B8_GATE_BUILD
void* SM_alloc(unsigned __int64 size);
void* SM_alloc(unsigned __int64 n, unsigned __int64 size);
void* SM_calloc(unsigned __int64 n, unsigned __int64 size);
void  SM_free(void* p);
void  movf(int const* n, double const* src, double* const dst);
#else
__declspec(dllimport) void* SM_alloc(unsigned __int64 size);
__declspec(dllimport) void* SM_alloc(unsigned __int64 n, unsigned __int64 size);
__declspec(dllimport) void* SM_calloc(unsigned __int64 n, unsigned __int64 size);
__declspec(dllimport) void  SM_free(void* p);

__declspec(dllimport) void  movf(int const* n, double const* src, double* const dst);
#endif


namespace b8env {


struct ITolerances {
    virtual ~ITolerances();
    virtual double ask_length_tolerance() const = 0;
    virtual double ask_length_squared_tolerance() const = 0;
    virtual int    ask_int_tolerance() const = 0;
};


struct IAcomParameterAccess {
    virtual ~IAcomParameterAccess();
    virtual double length_tolerance() const = 0;
    virtual double slot10() const = 0;
    virtual double slot18() const = 0;
    virtual double number_tolerance() const = 0;
};

void set_thread_tolerances(ITolerances* t);
void set_acom_parameter_access(IAcomParameterAccess* a);
void set_algorithm_version(unsigned v);

}


extern int g_b8_mode0;
extern int g_b8_mode1;
extern double g_b8_zero;



extern unsigned char* g_b8_raw_base;


double EQ_ask_length_tolerance();
double EQ_ask_length_squared_tolerance();
double EQ_ask_number_tolerance();
unsigned b8_GetAlgorithmVersion();
b8env::IAcomParameterAccess* GetAcomParameterAccess();


void h004(const double* a, const double* b, const double* c, double* det);
void h053(const double* y, const double* x, double* angle);
void h060(const double* a, const double* b, const double* c, double* angle);
void h100(const double* a, const double* m, double* out);
void h104(const double* p, const double* m, double* out);
void h105(const double* a, const double* m, double* out);
void h110(const double* src, double* dst);
void h310(const double* p1, const double* p2, const double* dir, double* dist);
void h632(const double* p1, double* v1, const double* p2, double* v2, int* code, double* out);
void h635(const double* a1, double* a2, const double* a3, double* a4, int* code, double* out);
void h636(const double* p, const double* v, const double* plane, int* code, double* out);
void h805(const double* a, const double* b, const int* mode, int* out);
int  eqz(const double* a, const double* b, const int* mode);
void vcru3(const double* a, const double* b, int* ok, double* out);
void vunt3(const double* a, int* ok, double* out);
int  VEC3_unitize(double* v, double* len);
int  VEC3_unitize(const double* v, double tol, double* len, double* out);
void MTX3_multiply(const double* a, const double* b, double* out);
bool MTX3_is_ortho_normal(const double* m);
bool MTX3_is_ortho_normal(const double* m, double tol);
bool MTX3_ortho_normalize(double* m);
int  ludcmp_a(double** a, int n, int* indx, double* d);
int  ludcmp_a_with_abort(double** a, int n, int* indx, double* d, bool (*abort)());
void lubksb_a(double** a, int n, int* indx, double* b);
void sub_180036070(int* desc, const void* a2, const void* a3, void** out);
void b8_movf(int n, const double* src, double* dst);


void h1000(const double* a1, const double* a2, const double* a3, double* a4,
           double* a5, double* a6, double* a7, int* a8);
void h1006(const int* n, const double* s, const double* src, double* dst);
void h101(const double* a, const double* m, double* out);
void h102(const double* p, const double* m, double* out);
void h106(const double* a, const double* m, const double* p, double* out);
void h111(double* const m, double* const out);
void h114(const double* p, const double* m, double* out);
void h116(const double* c, const double* a2, const double* a3, const double* a4,
          const double* a5, double* out);
void h120(const double* a, const double* b, double* out);
void h121(const double* a, const double* b, double* out);
void h122(const double* a, const double* b, double* out);
void h123(const double* a, const double* b, double* out);
void h125(const double* m, double* inv, int* singular);
int  h126a(double** a, int n, double** out);
void sub_180037EC0(int a1, int a2, int a3, double* a4, double** a5, double* a6);
double h128(double lo, double hi);
void h130(const double* m, double* out);
void h140(const double* a1, const double* a2, const double* a3, const double* a4,
          double* a5, double* a6);
void h150(const double* a, const double* b, double* out);
void h160(double* const m);
void h1600(const double* p1, const double* p2, double* dir, int* code);
void sub_180036800(int* desc, const void* a2, const void* a3, double** lu, int* indx,
                   double* out);


#include <cmath>
#include <emmintrin.h>

void h1000(const double* a1, const double* a2, const double* a3, double* a4,
           double* a5, double* a6, double* a7, int* a8) {
    *a8 = 0;

    const double m0 = a2[0] - a1[0];
    const double m1 = a2[1] - a1[1];
    const double m2 = a2[2] - a1[2];
    const double n0 = a3[0] - a1[0];
    const double n1 = a3[1] - a1[1];
    const double n2 = a3[2] - a1[2];
    const double c0 = m1 * n2 - m2 * n1;
    const double c1 = n0 * m2 - m0 * n2;
    const double c2 = m0 * n1 - n0 * m1;

    double len_m = sqrt(m0 * m0 + m1 * m1 + m2 * m2);
    int code;
    h805(&len_m, &g_b8_zero, &g_b8_mode0, &code);
    if (code == 1) {
        *a8 = 1;
        return;
    }
    double len_n = sqrt(n0 * n0 + n1 * n1 + n2 * n2);
    h805(&len_n, &g_b8_zero, &g_b8_mode0, &code);
    if (code == 1) {
        *a8 = 2;
        return;
    }
    double len_c = sqrt(c0 * c0 + c1 * c1 + c2 * c2);
    h805(&len_c, &g_b8_zero, &g_b8_mode0, &code);
    if (code == 1) {
        *a8 = 3;
        return;
    }

    const double inv_m = 1.0 / len_m;
    const double inv_n = 1.0 / len_n;
    const double inv_c = 1.0 / len_c;
    _mm_storeu_pd(a4, _mm_mul_pd(_mm_set_pd(m1, m0), _mm_set1_pd(inv_m)));
    a4[2] = m2 * inv_m;
    a4[3] = n0 * inv_n;
    a4[4] = n1 * inv_n;
    a4[5] = n2 * inv_n;
    a4[6] = c0 * inv_c;
    a4[7] = c1 * inv_c;
    a4[8] = c2 * inv_c;

    const double half_m = len_m * 0.5;
    const double half_n = len_n * 0.5;
    double p1[3];
    p1[0] = half_m * a4[0] + a1[0];
    p1[1] = half_m * a4[1] + a1[1];
    p1[2] = half_m * a4[2] + a1[2];
    double p2[3];
    p2[0] = half_n * a4[3] + a1[0];
    p2[1] = half_n * a4[4] + a1[1];
    p2[2] = half_n * a4[5] + a1[2];

    int ok;
    double d1[3];
    double d2[3];
    vcru3(a4, a4 + 6, &ok, d1);
    vcru3(a4 + 3, a4 + 6, &ok, d2);
    int h632_code;
    h632(p1, d1, p2, d2, &h632_code, a6);

    a4[0] = m0 - n0;
    a4[1] = m1 - n1;
    a4[2] = m2 - n2;
    const double diff_len = sqrt(a4[0] * a4[0] + a4[1] * a4[1] + a4[2] * a4[2]);
    *a7 = diff_len * (len_n * len_m) / (len_c * 2.0);

    a4[0] = a1[0] - a6[0];
    a4[1] = a1[1] - a6[1];
    a4[2] = a1[2] - a6[2];
    a4[3] = a3[0] - a6[0];
    a4[4] = a3[1] - a6[1];
    a4[5] = a3[2] - a6[2];
    vunt3(a4, &ok, a4);
    vunt3(a4 + 3, &ok, a4 + 3);
    vcru3(a4, a4 + 3, &ok, a4 + 6);
    vcru3(a4 + 6, a4, &ok, a4 + 3);

    double t3[3];
    t3[0] = a3[0] - a6[0];
    t3[1] = a3[1] - a6[1];
    t3[2] = a3[2] - a6[2];
    h060(a4, t3, a4 + 6, a5);

    double t2[3];
    t2[0] = a2[0] - a6[0];
    t2[1] = a2[1] - a6[1];
    t2[2] = a2[2] - a6[2];
    double ang2[3];
    h060(a4, t2, a4 + 6, ang2);

    if (*a5 < ang2[0]) {
        *a5 = 6.283185307179586 - *a5;
        const __m128d neg = _mm_set1_pd(-1.0);
        _mm_storeu_pd(a4 + 3, _mm_mul_pd(_mm_loadu_pd(a4 + 3), neg));
        a4[5] = a4[5] * -1.0;
        _mm_storeu_pd(a4 + 6, _mm_mul_pd(_mm_loadu_pd(a4 + 6), neg));
        a4[8] = a4[8] * -1.0;
    }
}
