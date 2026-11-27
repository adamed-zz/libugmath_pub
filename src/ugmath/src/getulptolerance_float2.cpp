








#include <algorithm>

namespace UGS {
namespace Math {

namespace {
union FloatBits {
    float f;
    unsigned int u;
};
}


float GetULPTolerance(const float& value)
{
    FloatBits in;
    in.f = value;

    int e = static_cast<int>(static_cast<unsigned char>(in.u >> 23)) - 24;
    if (e < 2) {
        e = 2;
    }

    float tolerance;
    *reinterpret_cast<unsigned short*>(&tolerance) = 0;
    *reinterpret_cast<unsigned short*>(reinterpret_cast<char*>(&tolerance) + 2) =
        static_cast<unsigned short>(static_cast<unsigned short>((e + 1) << 7) & 0x7F80);

    return tolerance;
}

float GetULPTolerance(const float& a, const float& b)
{

    if (a > b) {
        if (b > 0.0f) {
            return std::max(GetULPTolerance(b), 1.1920928955078125e-07f);
        }
        if (a > 0.0f) {

            return 1.1920928955078125e-07f;
        }
    }
    return std::max(GetULPTolerance(a), 1.1920928955078125e-07f);
}

}
}
