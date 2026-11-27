





#include "ugmath/b36_math.h"


int  MTX3_init(const UGS::Math::Vector3* a1, const UGS::Math::Vector3* a2,
               UGS::Math::Matrix3* out);
int  MTX3_init_x_y_z(const UGS::Math::Vector3* x, const UGS::Math::Vector3* y,
                     const UGS::Math::Vector3* z, UGS::Math::Matrix3* out);
bool MTX3_is_equal(const UGS::Math::Matrix3* a, const UGS::Math::Matrix3* b, double tol);


extern "C" long long sub_18004A260(double*, double*, double*, double*, double*, double*);
extern "C" void*     sub_18004BDB0();
extern "C" long long sub_18004BDF0(double*, double*, double*, double*, double*, double*);
extern "C" int       sub_180047D80(const char*, const double*);


__declspec(dllimport) int  ERROR_lprintf(const char* fmt, ...);
__declspec(dllimport) void ERROR_note(const char* file, int line, const char* msg, ...);
__declspec(dllimport) void ERROR_internal(const char* file, int line, const char* msg, ...);




long long b15_A260(double* a1, double* a2, double* a3, double* a4, double* a5, double* a6)
{
    return sub_18004A260(a1, a2, a3, a4, a5, a6);
}

long long b15_BDB0()
{
    return (long long)sub_18004BDB0();
}

long long b15_BDF0(double* a1, double* a2, double* a3, double* a4, double* a5, double* a6)
{
    return sub_18004BDF0(a1, a2, a3, a4, a5, a6);
}

int b15_print_matrix(const char* a1, const double* a2)
{
    return sub_180047D80(a1, a2);
}




static inline const UGS::Math::Vector3* V(const double* p)
{
    return reinterpret_cast<const UGS::Math::Vector3*>(p);
}
static inline const UGS::Math::Matrix3* M(const double* p)
{
    return reinterpret_cast<const UGS::Math::Matrix3*>(p);
}
static inline UGS::Math::Matrix3* MW(double* p)
{
    return reinterpret_cast<UGS::Math::Matrix3*>(p);
}

int b15_MTX3_init(const double* a1, const double* a2, double* out)
{
    return MTX3_init(V(a1), V(a2), MW(out));
}

int b15_MTX3_init_x_y_z(const double* x, const double* y, const double* z, double* out)
{
    return MTX3_init_x_y_z(V(x), V(y), V(z), MW(out));
}

int b15_MTX3_is_equal(const double* a, const double* b, double tol)
{
    return MTX3_is_equal(M(a), M(b), tol) ? 1 : 0;
}

int b15_MTX3_is_ortho_normal(const double* m)
{
    return MTX3_is_ortho_normal(M(m)) ? 1 : 0;
}

void b15_MTX3_multiply_t(const double* a, const double* b, double* out)
{
    MTX3_multiply_t(M(a), M(b), MW(out));
}

void b15_MTX3_multiply(const double* a, const double* b, double* out)
{
    MTX3_multiply(M(a), M(b), MW(out));
}

int b15_MTX3_ortho_normalize(double* m)
{
    return MTX3_ortho_normalize(MW(m)) ? 1 : 0;
}




void vcru3(const double* u, const double* v, int* flag, double* out);
void vunt3(const double* v, int* flag, double* out);

void b15_vcru3(const double* u, const double* v, int* ok, double* out)
{
    vcru3(u, v, ok, out);
}

void b15_vunt3(const double* v, int* ok, double* out)
{
    vunt3(v, ok, out);
}




void h964(const double* a1, const double* a2, double* a3);

void b15_h964(const double* a1, const double* a2, double* a3)
{
    h964(a1, a2, a3);
}




int b15_checking_level()
{
    return MACH__checking_level;
}

int b15_lp_msg(const char* fmt)
{
    return ERROR_lprintf(fmt);
}

int b15_lp_1d(const char* fmt, double a)
{
    return ERROR_lprintf(fmt, a);
}

int b15_lp_row(const char* fmt, const char* tag, double a, double b, double c)
{
    return ERROR_lprintf(fmt, tag, a, b, c);
}

void b15_error_note(const char* file, int line, const char* msg)
{
    ERROR_note(file, line, msg);
}

void b15_error_internal(const char* file, int line, const char* msg)
{
    ERROR_internal(file, line, msg);
}
