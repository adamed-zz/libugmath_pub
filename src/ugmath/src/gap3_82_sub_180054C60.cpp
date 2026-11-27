



#include <math.h>

#include <cstdint>

namespace UGS {
namespace Math {
struct Vector2 {
    double x;
    double y;
};
}
}

void ERROR_internal(const char* file, int line, const char* msg, ...);
int VEC2_unitize(const UGS::Math::Vector2* a, double tol, double* out, UGS::Math::Vector2* outvec);

double* sub_180054C60(int n, double* pts, double tol, double* outpt, double* outvec, int* status) {
    *status = 0;
    if (n < 1) {
        ERROR_internal("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\lsfit.c", 760,
                       "There are no input points.", n);
        __debugbreak();
    }
    double r = 0.0;
    if (n == 1) {
        outpt[0] = pts[0];
        outpt[1] = pts[1];
    } else {
        double best = pts[1] * pts[1] + pts[0] * pts[0];
        int idx = 0;
        int i = 1;
        do {
            const double prev = best;
            const double s = pts[2 * i + 1] * pts[2 * i + 1] + pts[2 * i] * pts[2 * i];
            if (s > best) best = s;
            if (s > prev) idx = i;
            ++i;
        } while (i < n);
        const double* sel = pts + 2 * idx;
        outpt[0] = sel[0];
        outpt[1] = sel[1];
        r = sqrt(best);
    }
    if (!(tol > r)) {
        outvec[0] = outpt[0];
        outvec[1] = outpt[1];
        double scratch;
        return reinterpret_cast<double*>(static_cast<intptr_t>(VEC2_unitize(
            reinterpret_cast<const UGS::Math::Vector2*>(outvec), 1.0e-10, &scratch,
            reinterpret_cast<UGS::Math::Vector2*>(outvec))));
    }
    *status = 1;
    outpt[0] = 0.0;
    outpt[1] = 0.0;
    outvec[0] = 0.0;
    outvec[1] = 0.0;
    return outvec;
}
