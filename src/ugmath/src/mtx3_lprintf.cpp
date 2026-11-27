





#include <cmath>

__declspec(dllimport) int lprintf(const char* fmt, ...);

namespace UGS {
namespace Math {

struct Matrix3 {
    double m[9];
};

static inline double mtx_max2(double a, double b) { return a > b ? a : b; }

}
}

using UGS::Math::Matrix3;

void __cdecl MTX3_lprintf(int indent, const char* label, const Matrix3* mat) {
    double mx = -1.0;
    double t;
    t = std::fabs(mat->m[0]); mx = UGS::Math::mtx_max2(t, mx);
    t = std::fabs(mat->m[1]); mx = UGS::Math::mtx_max2(t, mx);
    t = std::fabs(mat->m[2]); mx = UGS::Math::mtx_max2(t, mx);
    t = std::fabs(mat->m[3]); mx = UGS::Math::mtx_max2(t, mx);
    t = std::fabs(mat->m[4]); mx = UGS::Math::mtx_max2(t, mx);
    t = std::fabs(mat->m[5]); mx = UGS::Math::mtx_max2(t, mx);
    t = std::fabs(mat->m[6]); mx = UGS::Math::mtx_max2(t, mx);
    t = std::fabs(mat->m[7]); mx = UGS::Math::mtx_max2(t, mx);
    t = std::fabs(mat->m[8]); mx = UGS::Math::mtx_max2(t, mx);
    int width = 11;
    while (mx > 10.0) {
        mx /= 10.0;
        ++width;
    }
    if (label)
        lprintf("%*s%s\n", indent, "", label);
    const double* row = mat->m;
    for (int r = 0; r < 3; ++r) {
        lprintf("%*s  ", indent, "");
        const double* p = row;
        for (int c = 0; c < 3; ++c) {
            lprintf(" % *.*f", width, 8, *p);
            p += 3;
        }
        lprintf("\n");
        ++row;
    }
}
