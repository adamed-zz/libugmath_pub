









#include <cmath>
#include <cstdint>

namespace UGS {
namespace Math {

int GetNthDecimalDigit(double x, int n) {
    if (n < 1) return 0;
    const double p1 = std::pow(10.0, (double)n);
    const double q = std::pow(10.0, (double)(n - 1));
    const double p = p1 * x;
    double a;
    double b;
    if (x >= 0.0) {
        a = std::floor(p);
        b = std::floor(q * x);
    } else {
        a = std::ceil(p);
        b = std::ceil(q * x);
    }
    return (int)(std::fabs(a - b * 10.0) + 0.5);
}

}
}
