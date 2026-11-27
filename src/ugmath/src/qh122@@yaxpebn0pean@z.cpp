

















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




#include <emmintrin.h>

static __forceinline __m128d h122_mul(__m128d x, __m128d y) { return _mm_mul_sd(x, y); }
static __forceinline __m128d h122_add(__m128d x, __m128d y) { return _mm_add_sd(x, y); }

void h122(const double* a1, const double* a2, double* a3) {
    __m128d s, t;
    s = h122_mul(_mm_load_sd(a1 + 0), _mm_load_sd(a2 + 0));
    t = h122_mul(_mm_load_sd(a1 + 1), _mm_load_sd(a2 + 1));
    s = h122_add(s, t);
    t = h122_mul(_mm_load_sd(a1 + 2), _mm_load_sd(a2 + 2));
    _mm_store_sd(a3 + 0, h122_add(s, t));

    s = h122_mul(_mm_load_sd(a2 + 0), _mm_load_sd(a1 + 3));
    t = h122_mul(_mm_load_sd(a1 + 4), _mm_load_sd(a2 + 1));
    s = h122_add(s, t);
    t = h122_mul(_mm_load_sd(a1 + 5), _mm_load_sd(a2 + 2));
    _mm_store_sd(a3 + 1, h122_add(s, t));

    s = h122_mul(_mm_load_sd(a1 + 6), _mm_load_sd(a2 + 0));
    t = h122_mul(_mm_load_sd(a2 + 1), _mm_load_sd(a1 + 7));
    s = h122_add(s, t);
    t = h122_mul(_mm_load_sd(a2 + 2), _mm_load_sd(a1 + 8));
    _mm_store_sd(a3 + 2, h122_add(s, t));

    s = h122_mul(_mm_load_sd(a1 + 1), _mm_load_sd(a2 + 4));
    t = h122_mul(_mm_load_sd(a2 + 3), _mm_load_sd(a1 + 0));
    s = h122_add(s, t);
    t = h122_mul(_mm_load_sd(a2 + 5), _mm_load_sd(a1 + 2));
    _mm_store_sd(a3 + 3, h122_add(s, t));

    s = h122_mul(_mm_load_sd(a2 + 3), _mm_load_sd(a1 + 3));
    t = h122_mul(_mm_load_sd(a1 + 4), _mm_load_sd(a2 + 4));
    s = h122_add(s, t);
    t = h122_mul(_mm_load_sd(a1 + 5), _mm_load_sd(a2 + 5));
    _mm_store_sd(a3 + 4, h122_add(s, t));

    s = h122_mul(_mm_load_sd(a2 + 4), _mm_load_sd(a1 + 7));
    t = h122_mul(_mm_load_sd(a2 + 3), _mm_load_sd(a1 + 6));
    s = h122_add(s, t);
    t = h122_mul(_mm_load_sd(a2 + 5), _mm_load_sd(a1 + 8));
    _mm_store_sd(a3 + 5, h122_add(s, t));

    s = h122_mul(_mm_load_sd(a1 + 1), _mm_load_sd(a2 + 7));
    t = h122_mul(_mm_load_sd(a2 + 6), _mm_load_sd(a1 + 0));
    s = h122_add(s, t);
    t = h122_mul(_mm_load_sd(a2 + 8), _mm_load_sd(a1 + 2));
    _mm_store_sd(a3 + 6, h122_add(s, t));

    s = h122_mul(_mm_load_sd(a2 + 6), _mm_load_sd(a1 + 3));
    t = h122_mul(_mm_load_sd(a1 + 4), _mm_load_sd(a2 + 7));
    s = h122_add(s, t);
    t = h122_mul(_mm_load_sd(a1 + 5), _mm_load_sd(a2 + 8));
    _mm_store_sd(a3 + 7, h122_add(s, t));

    s = h122_mul(_mm_load_sd(a2 + 7), _mm_load_sd(a1 + 7));
    t = h122_mul(_mm_load_sd(a2 + 6), _mm_load_sd(a1 + 6));
    s = h122_add(s, t);
    t = h122_mul(_mm_load_sd(a2 + 8), _mm_load_sd(a1 + 8));
    _mm_store_sd(a3 + 8, h122_add(s, t));
}
