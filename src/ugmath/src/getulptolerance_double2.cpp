




















#include <algorithm>

namespace UGS {
namespace Math {

namespace {
union DoubleBits {
    double d;
    unsigned long long u;
};
}

double GetULPTolerance(const double& value)
{
    DoubleBits in;
    in.d = value;


    unsigned int hi = static_cast<unsigned int>(in.u >> 48);
    int e = static_cast<int>((hi >> 4) & 0x7FFu) - 53;
    if (e < 2) {
        e = 2;
    }

    double tolerance;

    *reinterpret_cast<unsigned int*>(reinterpret_cast<char*>(&tolerance) + 2) = 0;
    *reinterpret_cast<unsigned short*>(&tolerance) = 0;
    *reinterpret_cast<unsigned short*>(reinterpret_cast<char*>(&tolerance) + 6) =
        static_cast<unsigned short>(static_cast<unsigned short>((e + 1) << 4) & 0x7FF0);

    return tolerance;
}

double GetULPTolerance(const double& a, const double& b)
{


    if (a > b) {
        if (b > 0.0) {
            return std::max(GetULPTolerance(b), 2.220446049250313e-16);
        }
        if (a > 0.0) {

            return 2.220446049250313e-16;
        }
    }
    return std::max(GetULPTolerance(a), 2.220446049250313e-16);
}

}
}
