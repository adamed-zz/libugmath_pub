










#pragma once

#include <cstddef>
#include <cstdint>
#include <cstdio>


namespace UGS {
namespace Math {

struct Point3 {
    double x;
    double y;
    double z;
};

struct Vector3 {
    double x;
    double y;
    double z;
};

}

namespace System {
namespace Loader {

class Module;
}
}
}


typedef void (*b37_ldr_sym)();


struct PLN3_s {
    UGS::Math::Point3 origin;
    UGS::Math::Vector3 normal;
};

enum PNT3_colinear_condition_t {
    PNT3_CC_UNKNOWN_0 = 0,
    PNT3_CC_NOT_COLINEAR = 1,
    PNT3_CC_P2_INSIDE = 2,
    PNT3_CC_P3_EQ_P1 = 3,
    PNT3_CC_P1P2_LONGEST = 4,
    PNT3_CC_P3_EQ_P2 = 5,
    PNT3_CC_P1P3_LONGEST = 6
};

static_assert(sizeof(UGS::Math::Point3) == 24, "Point3 必须是 24 字节");
static_assert(sizeof(PLN3_s) == 48, "PLN3_s 必须是 48 字节");







#ifdef B37_GATE_BUILD
namespace UGS {
namespace System {
namespace Loader {
UGS::System::Loader::Module* LDR_load_image(const char* name, int flag);
b37_ldr_sym LDR_find_symbol(UGS::System::Loader::Module* mod, const char* name);
void ldr_unload_module(const char* name);
}
}
}
#else
__declspec(dllimport) UGS::System::Loader::Module* LDR_load_image(const char* name, int flag);
__declspec(dllimport) b37_ldr_sym LDR_find_symbol(UGS::System::Loader::Module* mod,
                                                  const char* name);
__declspec(dllimport) void ldr_unload_module(const char* name);
namespace UGS {
namespace System {
namespace Loader {
using ::LDR_load_image;
using ::LDR_find_symbol;
using ::ldr_unload_module;
}
}
}
#endif

#ifdef B37_GATE_BUILD

void* SM_alloc(unsigned __int64 size);
void* SM_alloc(unsigned __int64 n, unsigned __int64 size);
void* SM_calloc(unsigned __int64 n, unsigned __int64 size);
void SM_free(void* p);
int SYSS_fprintf(void* iob, const char* fmt, ...);
#else
__declspec(dllimport) void* SM_alloc(unsigned __int64 size);
__declspec(dllimport) void* SM_alloc(unsigned __int64 n, unsigned __int64 size);
__declspec(dllimport) void* SM_calloc(unsigned __int64 n, unsigned __int64 size);
__declspec(dllimport) void SM_free(void* p);


namespace UGS {
namespace System {
__declspec(dllimport) int SYSS_fprintf(struct _iobuf* iob, const char* fmt, ...);
}
}
using UGS::System::SYSS_fprintf;
#endif



void merrorpush(char* const msg, int line, int level);
int merrorlevel();

bool VEC3_is_parallel(const UGS::Math::Vector3* a, const UGS::Math::Vector3* b, double tol);
double VEC3_angle_between(const UGS::Math::Vector3* a, const UGS::Math::Vector3* b,
                          const UGS::Math::Vector3* n);
double EQ_ask_length_tolerance();



bool b37_dep_PNT3_is_colinear(const UGS::Math::Point3* a1, const UGS::Math::Point3* a2,
                              const UGS::Math::Point3* a3, double a4);


extern unsigned char* g_b37_raw_base;


void mconvert_banded(double** a1, int a2, int a3, double** a4);
void mdecompose_banded(double** a1, int a2, int a3);
void mdispose_banded(double*** a1, double** a2);
void mdump_banded(double** a1, double* a2, int a3, int a4);
void msetup_banded(int a1, int a2, double*** a3, double** a4);
void msolve_banded(double** a1, int a2, int a3, double* a4);

bool PLN3_is_coincident(const PLN3_s* a1, const PLN3_s* a2, double a3, double a4);
bool PLN3_is_equal(const PLN3_s* a1, const PLN3_s* a2, double a3, double a4);
bool PLN3_is_point_on_plane(const PLN3_s* a1, const UGS::Math::Point3* a2, double a3);
bool PLN3_is_segment_intersecting(const PLN3_s* a1, const UGS::Math::Point3* a2,
                                  const UGS::Math::Point3* a3, double a4);

void PNT3_ask_closest_point(const UGS::Math::Point3* a1, const UGS::Math::Vector3* a2,
                            const UGS::Math::Point3* a3, int a4, UGS::Math::Point3* a5);
void PNT3_cartesian_to_cylindrical(UGS::Math::Point3* a1, UGS::Math::Point3* a2);
void PNT3_cartesian_to_spherical(UGS::Math::Point3* a1, UGS::Math::Point3* a2);
PNT3_colinear_condition_t PNT3_colinear_condition(const UGS::Math::Point3* a1,
                                                  const UGS::Math::Point3* a2,
                                                  const UGS::Math::Point3* a3, double a4);
bool PNT3_is_colinear(const UGS::Math::Point3* a1, const UGS::Math::Point3* a2,
                      const UGS::Math::Point3* a3, double a4);
void PNT3_spherical_to_cartesian(UGS::Math::Point3* a1, UGS::Math::Point3* a2);









void DELAUNAY_loadModule();
bool DELAUNAY_moduleLoaded();
void DELAUNAY_unloadModule();
extern "C" {
extern void* b37_delaunay_slots[72];
extern int b37_delaunay_loaded;
}


extern "C" {
typedef long long(__fastcall* b37_deriv_a)(long long ctx, double* x, double* y, int* err);
long long sub_1800A1AB0(long long a1, b37_deriv_a a2, int a3, double a4, double a5, int a6,
                        double* a7);
double sub_1800A2130(const double* a1, const double* a2, int a3);
typedef double(__fastcall* b37_cb_a2cd0)(double* y, void* ctx, long long flag);
double sub_1800A2CD0(double* a1, double* a2, double* a3, int a4, b37_cb_a2cd0 a5, void* a6,
                     int a7, int* a8, double a9);
long long sub_1800A2FC0(long long a1);
}


namespace b37c {
constexpr double kHalf = 0.5;
constexpr double kOne = 1.0;
constexpr double kRadToDeg = 57.29577951308235;
constexpr double kPi = 3.14159265358979323846;
constexpr double kTwoPi = 6.283185307179586;
constexpr double kDeg90 = 90.0;
constexpr double kDeg180 = 180.0;
constexpr double kDeg270 = 270.0;
constexpr double kDeg360 = 360.0;
constexpr double kNumberTol = 1.0e-10;
constexpr double kZero = 0.0;
}
