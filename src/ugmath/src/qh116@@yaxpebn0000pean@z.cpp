


















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

void h116(const double* a1, const double* a2, const double* a3, const double* a4,
          const double* a5, double* a6) {
    a6[0] = a1[1] * a3[0] + a1[0] * a2[0] + a1[2] * a4[0] + a1[3] * a5[0];
    a6[1] = a2[1] * a1[0] + a3[1] * a1[1] + a4[1] * a1[2] + a5[1] * a1[3];
    a6[2] = a2[2] * a1[0] + a3[2] * a1[1] + a4[2] * a1[2] + a5[2] * a1[3];
}
