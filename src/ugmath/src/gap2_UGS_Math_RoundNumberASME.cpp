












#include <cmath>

namespace UGS {
namespace Math {

int GetNthDecimalDigit(double x, int n);
double RoundUpNumber(double x, int n);
double RoundDownNumber(double x, int n);

}
}

double EQ_ask_length_tolerance();

namespace UGS {
namespace Math {

double RoundNumberASME(double x, int n) {
    const int np1 = n + 1;
    const int d = GetNthDecimalDigit(x, np1);
    if (d > 5) return RoundUpNumber(x, n);
    if (d == 5) {
        double ip;
        const double frac =
            std::fabs(std::modf(std::pow(10.0, (double)np1) * x, &ip));


        if (!(EQ_ask_length_tolerance() >= frac)) return RoundUpNumber(x, n);
        const int t = (n > 0) ? GetNthDecimalDigit(x, n) : (int)std::fabs(x);
        if (t % 2 == 1) return RoundUpNumber(x, n);
    }
    return RoundDownNumber(x, n);
}

}
}
