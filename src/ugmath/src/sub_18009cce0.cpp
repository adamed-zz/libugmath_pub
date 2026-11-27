
































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



bool Near(double a, double b, double tol) { return std::fabs(a - b) <= tol; }

void TryAdd(double* out, int* count, double roll, double pitch, double yaw) {
    for (int i = 0; i < *count; ++i) {
        const double* e = out + 3 * i;
        if (Near(roll, e[0], 1.0e-10) && Near(pitch, e[1], 1.0e-10) &&
            Near(yaw, e[2], 1.0e-10))
            return;
    }
    double* e = out + 3 * (*count);
    e[0] = roll;
    e[1] = pitch;
    e[2] = yaw;
    ++*count;
}

void TryYaw(const double* m, double roll, double pitch, double yaw, double* out, int* count) {
    const double cp = std::cos(pitch);
    const double cy = std::cos(yaw);
    const double cr = std::cos(roll);
    if (!Near(m[0], cy * cp, 1.0e-10)) return;
    if (!Near(m[8], cr * cp, 1.0e-10)) return;
    const double sr = std::sin(roll);
    const double sp = std::sin(pitch);
    const double sy = std::sin(yaw);
    if (!Near(m[1], sp * cy * sr - sy * cr, 1.0e-10)) return;
    if (!Near(m[2], sp * cy * cr + sy * sr, 1.0e-10)) return;
    if (!Near(m[4], sy * sp * sr + cr * cy, 1.0e-10)) return;
    if (!Near(m[5], sy * sp * cr - sr * cy, 1.0e-10)) return;
    TryAdd(out, count, roll, pitch, yaw);
}

}

void sub_18009CCE0(double* a1, double* a2, double* a3, double* a4, int* a5, double* a6) {
    *a5 = 0;
    double* roll = a3;
    double* yaw = a4;
    for (int i = 0; i < 2; ++i) {
        const double pitch = a2[i];
        for (int j = 0; j < 2; ++j, ++roll) {
            TryYaw(a1, *roll, pitch, yaw[0], a6, a5);
            TryYaw(a1, *roll, pitch, yaw[1], a6, a5);
        }
        yaw += 2;
    }
}
