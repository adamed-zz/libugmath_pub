

















#include <cmath>
#include <cstdint>

#include "ugmath/b36_math.h"

int sub_18009AF10(int a1, const char* a2, unsigned int a3, double* a4) {
    double v4 = -1.0;
    int v9 = 11;
    const std::int64_t v10 = static_cast<int>(a3 * a3);
    std::int64_t v11 = 0;
    while (v11 < v10) {
        const double v17 = a4[v11++];
        v4 = std::fmax(std::fabs(v17), v4);
    }
    for (; v4 > 10.0; ++v9) v4 = v4 / 10.0;
    int ret = 0;
    if (a2) ret = lprintf("%*s%s\n", a1, "", a2);
    if (static_cast<int>(a3) > 0) {
        const std::int64_t v18 = static_cast<std::int64_t>(a3);
        const std::int64_t v20 = 8LL * static_cast<int>(a3);
        double* row = a4;
        for (std::int64_t r = 0; r < v18; ++r) {
            ret = lprintf("%*s  ", a1, "");
            double* p = row;
            for (std::int64_t c = 0; c < v18; ++c) {
                ret = lprintf(" % *.*f", v9, 8, *p);
                p = reinterpret_cast<double*>(reinterpret_cast<char*>(p) + v20);
            }
            ret = lprintf("\n");
            ++row;
        }
    }
    return ret;
}
