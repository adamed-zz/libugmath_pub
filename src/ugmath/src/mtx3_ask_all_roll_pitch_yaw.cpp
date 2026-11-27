
































#pragma once

#include <cmath>
#include <cstddef>
#include <cstdint>
#include <initializer_list>
#include <stdexcept>
#include <string>

#ifdef B36_GATE_BUILD
#define B36_IMPORT
#else
#define B36_IMPORT __declspec(dllimport)
#endif

namespace UGS {
namespace Memory {

#ifdef B36_GATE_BUILD
class CppMemory {
public:
    static void* allocate(unsigned __int64 size);
    static void free(void* p);
};
#else
class __declspec(dllimport) CppMemory {
public:
    static void* allocate(unsigned __int64 size);
    static void free(void* p);
};
#endif


template <class T>
class SMAlloc {
public:
    using value_type = T;

    SMAlloc() noexcept = default;
    template <class U>
    SMAlloc(const SMAlloc<U>&) noexcept {}

    T* allocate(std::size_t n) {
        return static_cast<T*>(CppMemory::allocate(n * sizeof(T)));
    }
    void deallocate(T* p, std::size_t) noexcept { CppMemory::free(p); }

    template <class U>
    struct rebind {
        using other = SMAlloc<U>;
    };
};

template <class T, class U>
bool operator==(const SMAlloc<T>&, const SMAlloc<U>&) noexcept {
    return true;
}
template <class T, class U>
bool operator!=(const SMAlloc<T>&, const SMAlloc<U>&) noexcept {
    return false;
}

}
}

using SMString = std::basic_string<char, std::char_traits<char>, UGS::Memory::SMAlloc<char>>;

namespace UGS {
namespace Math {

struct Vector2 {
    double x, y;
};

struct Vector3 {
    double x, y, z;
    SMString ToString() const;
};


struct Matrix2 {
    double m[4];
};


struct Matrix3 {
    double m[9];
};


struct TransformMatrix {
    double m[16];
};

namespace Internals {





template <class T>
class ArrayIterator {
public:
    T* ptr;

    ArrayIterator() noexcept : ptr(nullptr) {}
    ArrayIterator(const ArrayIterator& other) noexcept : ptr(other.ptr) {}
    ArrayIterator& operator=(const ArrayIterator& other) noexcept {
        ptr = other.ptr;
        return *this;
    }
    ~ArrayIterator() noexcept {}
};

}


struct Vector3f {
    float x, y, z;

    Vector3f() {}
    explicit Vector3f(std::initializer_list<float> values);
    Internals::ArrayIterator<const float> cbegin() const;
    Internals::ArrayIterator<const float> end() const;
    SMString ToString() const;
};

}
}




enum MTX_foreign_status_e {
    MTX_FOREIGN_OK = 0,
    MTX_FOREIGN_REFLECTION = 1,
    MTX_FOREIGN_SCALE = 2,
    MTX_FOREIGN_NOFIXUP = 3
};



struct Solver_data_s {
    int kind;
    int count;
    void** ptr1;
    void** ptr2;
    int mode;
    void** rows1;
    void** rows2;
    void* pool;
    void* vecA;
    void* vecA_end;
    void* vecA_cap;
    void* vecB;
    void* vecB_end;
    void* vecB_cap;
    int flag;

    ~Solver_data_s();
    void allocate(int n, int m);
};


B36_IMPORT void* SM_alloc(unsigned __int64 size);
B36_IMPORT void* SM_alloc(unsigned __int64 n, unsigned __int64 size);
B36_IMPORT void* SM_calloc(unsigned __int64 n, unsigned __int64 size);
B36_IMPORT void SM_free(void* p);
B36_IMPORT char* SM_sprintf(const char* fmt, ...);

B36_IMPORT int lprintf(const char* fmt, ...);
B36_IMPORT void ERROR_assertion_failed(const char* file, int line, const char* fmt, ...);
B36_IMPORT void ERROR_note(const char* file, int line, const char* fmt, ...);

extern "C" {
B36_IMPORT extern bool RDEBUG__enabled;
B36_IMPORT int RDEBUG_ask_flag(const char* name, bool flag);
}

extern int MACH__checking_level;




int MTX2_init(const UGS::Math::Vector2* x, const UGS::Math::Vector2* y,
              UGS::Math::Matrix2* out);

int VEC2_unitize(const UGS::Math::Vector2* v, double tol, double* len,
                 UGS::Math::Vector2* out);
int VEC3_unitize(const UGS::Math::Vector3* v, double tol, double* len,
                 UGS::Math::Vector3* out);
int VEC3_ask_perpendicular(const UGS::Math::Vector3* v, UGS::Math::Vector3* out);

bool MTX3_is_ortho_normal(const UGS::Math::Matrix3* m, double tolerance);
bool MTX3_is_ortho_normal(const UGS::Math::Matrix3* m);
bool MTX3_ortho_normalize(UGS::Math::Matrix3* m);
bool MTX3_apply_scale_factor(UGS::Math::Matrix3* m, double tolerance, double* scale);
bool MTX3_get_scale_factor(const UGS::Math::Matrix3* m, double* scale);
void MTX3_multiply(const UGS::Math::Matrix3* a, const UGS::Math::Matrix3* b,
                   UGS::Math::Matrix3* out);
void MTX3_lprintf(int level, const char* fmt, const UGS::Math::Matrix3* m);

bool sub_18009C3E0(UGS::Math::Matrix3* m);

int MTX4_invert(const UGS::Math::TransformMatrix* src, UGS::Math::TransformMatrix* dst);
void MTX4_multiply(const UGS::Math::TransformMatrix* a, const UGS::Math::TransformMatrix* b,
                   UGS::Math::TransformMatrix* out);




void MTX3_ask_all_roll_pitch_yaw(const UGS::Math::Matrix3* m, int* count,
                                 const double (&angles)[3]);
MTX_foreign_status_e MTX3_fixup_foreign(UGS::Math::Matrix3* m, bool foreign, double* scale);
int MTX3_can_be_fixed_up(const UGS::Math::Matrix3* m);
int MTX3_init_x(const UGS::Math::Vector3* x, UGS::Math::Matrix3* out);
int MTX3_init_z(const UGS::Math::Vector3* z, UGS::Math::Matrix3* out);
void MTX3_init_no_check(const UGS::Math::Vector3* x, const UGS::Math::Vector3* y,
                        UGS::Math::Matrix3* out);
void MTX3_multiply_t(const UGS::Math::Matrix3* a, const UGS::Math::Matrix3* b,
                     UGS::Math::Matrix3* out);


extern "C" {


int sub_180099BE0(bool check, UGS::Math::Matrix3* m, bool foreign, double* scale);


void sub_18009CB00(double* x, double* y);


void sub_18009CCE0(double* m, double* pitch, double* roll, double* yaw, int* count,
                   double* out);


int sub_18009D300(UGS::Math::Matrix3* m);


void sub_18009FBD0(const UGS::Math::Vector3* t1, const UGS::Math::Matrix3* a,
                   const UGS::Math::Vector3* t2, const UGS::Math::Matrix3* b,
                   UGS::Math::TransformMatrix* out);


int sub_18009AF10(int indent, const char* name, unsigned int n, double* mat);

}


extern int dword_1800E1B34;


extern "C" void* sub_180097730(void* str, const char* src, std::size_t n);


extern "C" void sub_180097710();



namespace {
constexpr double kPi = 3.141592653589793;

double ClampAsinArg(double v) {
    if (std::fabs(v) > 0.99999999999999) return (v <= 0.0) ? -1.0 : 1.0;
    return v;
}
}

void MTX3_ask_all_roll_pitch_yaw(const UGS::Math::Matrix3* a1, int* a2,
                                 const double (&a3)[3]) {
    const double* m = a1->m;
    double pitch[2];
    double roll[4];
    double yaw[4];
    const double s = -m[6];
    if (std::fabs(s) <= 0.9999999999) {
        const double p = std::asin(s);
        const double alt = kPi - p;
        const double cp = std::cos(p);
        const double calt = std::cos(alt);
        pitch[0] = p;
        pitch[1] = alt;
        yaw[0] = std::asin(ClampAsinArg(m[3] / cp));
        yaw[1] = kPi - yaw[0];
        roll[0] = std::asin(ClampAsinArg(m[7] / cp));
        roll[1] = kPi - roll[0];
        yaw[2] = std::asin(ClampAsinArg(m[3] / calt));
        yaw[3] = kPi - yaw[2];
        roll[2] = std::asin(ClampAsinArg(m[7] / calt));
        roll[3] = kPi - roll[2];
    } else {
        pitch[0] = kPi * 0.5;
        pitch[1] = -kPi * 0.5;
        const double v7 = m[5];
        double t0;
        double t1;
        if (std::fabs(v7) <= 0.99999999999999) {
            t0 = std::asin(v7);
            t1 = t0;
        } else {
            const double sgn = (v7 <= 0.0) ? -1.0 : 1.0;
            t0 = sgn * kPi * 0.5;
            t1 = t0;
        }
        const double v12 = m[2];
        if (std::fabs(v12 - std::cos(t0)) > 1.0e-10) t0 = kPi - t0;
        double u = -t1;
        if (std::fabs(v12 - -std::cos(u)) > 1.0e-10) u = kPi - u;
        yaw[0] = 0.0;
        yaw[1] = t0;
        yaw[2] = 0.0;
        yaw[3] = u;
        roll[0] = -t0;
        roll[1] = 0.0;
        roll[2] = u;
        roll[3] = 0.0;
    }
    sub_18009CCE0(const_cast<double*>(m), pitch, roll, yaw, a2,
                  const_cast<double*>(&a3[0]));
}
