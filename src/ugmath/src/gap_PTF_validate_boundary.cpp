




#include <stddef.h>

namespace UGS {
namespace Math {
struct Point2 {
    double x;
    double y;
};
}
}

struct PTF_tri_s {
    int a;
    int b;
    int c;
    int n0;
    int n1;
    int n2;
};

extern "C" __declspec(dllimport) void* SM_alloc(size_t n);
extern "C" __declspec(dllimport) void SM_free(void* p);
extern "C" char sub_1800A89B0(int, const double*, int, int*, PTF_tri_s*, int*);

bool PTF_validate_boundary(int a1, UGS::Math::Point2* a2) {
    const int v2 = a1 - 2;
    int v7 = 0;
    if (v2 <= 0) return false;
    void* v5 = SM_alloc(24LL * v2);
    sub_1800A89B0(a1, (const double*)a2, v2, &v7, (PTF_tri_s*)v5, nullptr);
    if (v7 != v2) return false;
    SM_free(v5);
    return true;
}
