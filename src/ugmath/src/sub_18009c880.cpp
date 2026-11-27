




#include <cmath>

__declspec(dllimport) int lprintf(const char* fmt, ...);

namespace UGS {
namespace Math {
struct Matrix3 {
    double m[9];
};
}
}

using UGS::Math::Matrix3;

extern "C" int sub_18009C880(const Matrix3* old_m, const Matrix3* cur_m) {
    const double* o = old_m->m;
    const double* c = cur_m->m;

    double sum = 0.0;
    for (int i = 0; i < 9; ++i) {
        const double diff = std::fabs(o[i] - c[i]);
        lprintf("Difference in element %d = % 14.12e\n", i, diff);
        sum += diff;
    }
    lprintf("Average difference = % 14.12e\n\n", sum / 9.0);

    lprintf(
        "The magnitude of X-axes cross product = % 14.12e\n",
        std::sqrt((old_m->m[1] * cur_m->m[2] - old_m->m[2] * cur_m->m[1]) *
                      (old_m->m[1] * cur_m->m[2] - old_m->m[2] * cur_m->m[1]) +
                  (old_m->m[2] * cur_m->m[0] - old_m->m[0] * cur_m->m[2]) *
                      (old_m->m[2] * cur_m->m[0] - old_m->m[0] * cur_m->m[2]) +
                  (old_m->m[0] * cur_m->m[1] - old_m->m[1] * cur_m->m[0]) *
                      (old_m->m[0] * cur_m->m[1] - old_m->m[1] * cur_m->m[0])));

    lprintf(
        "The magnitude of Y-axes cross product = % 14.12e\n",
        std::sqrt((old_m->m[4] * cur_m->m[5] - old_m->m[5] * cur_m->m[4]) *
                      (old_m->m[4] * cur_m->m[5] - old_m->m[5] * cur_m->m[4]) +
                  (old_m->m[5] * cur_m->m[3] - old_m->m[3] * cur_m->m[5]) *
                      (old_m->m[5] * cur_m->m[3] - old_m->m[3] * cur_m->m[5]) +
                  (old_m->m[3] * cur_m->m[4] - old_m->m[4] * cur_m->m[3]) *
                      (old_m->m[3] * cur_m->m[4] - old_m->m[4] * cur_m->m[3])));

    return lprintf(
        "The magnitude of Z-axes cross product = % 14.12e\n",
        std::sqrt((old_m->m[7] * cur_m->m[8] - old_m->m[8] * cur_m->m[7]) *
                      (old_m->m[7] * cur_m->m[8] - old_m->m[8] * cur_m->m[7]) +
                  (old_m->m[8] * cur_m->m[6] - old_m->m[6] * cur_m->m[8]) *
                      (old_m->m[8] * cur_m->m[6] - old_m->m[6] * cur_m->m[8]) +
                  (old_m->m[6] * cur_m->m[7] - old_m->m[7] * cur_m->m[6]) *
                      (old_m->m[6] * cur_m->m[7] - old_m->m[7] * cur_m->m[6])));
}
