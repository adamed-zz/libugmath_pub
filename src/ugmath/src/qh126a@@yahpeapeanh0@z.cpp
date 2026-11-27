













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



#include <cstring>

int h126a(double** a1, int a2, double** a3) {
    typedef unsigned long long QWORD;
    typedef unsigned char BYTE;
    __int64 v3 = a2;
    int* v6 = static_cast<int*>(SM_alloc(4ULL * v3));
    void* v7 = SM_alloc(8 * v3);
    double v19;
    unsigned int v8 = ludcmp_a(a1, (int)v3, v6, &v19);
    if (v8) {
        SM_free(v6);
        SM_free(v7);
        return v8;
    }
    if ((int)v3 > 0) {
        for (__int64 i = 0; i < v3; ++i) {
            memset(v7, 0, 8 * v3);
            *((QWORD*)v7 + i) = 0x3FF0000000000000LL;
            lubksb_a(a1, (int)v3, v6, (double*)v7);
            __int64 v11 = 0;
            if (v3 < 4) {
                goto LABEL9;
            }
            {
                double** v12 = a3 + 1;
                __int64 v13 = (BYTE*)v7 - (BYTE*)a3;
                do {
                    __int64 v14 = *(__int64*)((BYTE*)v12 + v13 - 8);
                    v11 += 4;
                    __int64 v15 = (__int64)(*reinterpret_cast<double**>(v12 - 1));
                    v12 += 4;
                    *(QWORD*)(v15 + 8 * i) = v14;
                    *reinterpret_cast<QWORD*>(&(*(v12 - 4))[i]) =
                        *reinterpret_cast<QWORD*>((BYTE*)v12 + v13 - 32);
                    *reinterpret_cast<QWORD*>(&(*(v12 - 3))[i]) =
                        *reinterpret_cast<QWORD*>((BYTE*)v12 + v13 - 24);
                    *reinterpret_cast<QWORD*>(&(*(v12 - 2))[i]) =
                        *reinterpret_cast<QWORD*>((BYTE*)v12 + v13 - 16);
                } while (v11 < v3 - 3);
            }
            if (v11 < v3) {
LABEL9:
                double** v16 = &a3[v11];
                do {
                    double* v17 = *v16;
                    ++v11;
                    double v18 =
                        *reinterpret_cast<double*>((BYTE*)v16 + ((BYTE*)v7 - (BYTE*)a3));
                    ++v16;
                    v17[i] = v18;
                } while (v11 < v3);
            }
        }
    }
    SM_free(v6);
    SM_free(v7);
    return 0;
}
