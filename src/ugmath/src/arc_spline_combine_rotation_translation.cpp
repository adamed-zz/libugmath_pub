








typedef unsigned long long u64;

namespace UGS {
namespace Math {

struct Matrix3 {
    double m[9];
};

struct TransformMatrix {
    double m[16];
};

}
}

void ARC_SPLINE_combine_rotation_translation(
    UGS::Math::Matrix3* a1,
    UGS::Math::TransformMatrix* a2,
    UGS::Math::TransformMatrix* a3)
{
    const u64* s = reinterpret_cast<const u64*>(a1);
    const u64* t = reinterpret_cast<const u64*>(a2);
    u64* d = reinterpret_cast<u64*>(a3);

    d[0] = s[0];
    d[1] = s[1];
    d[2] = s[2];
    d[3] = 0;
    d[4] = s[3];
    d[5] = s[4];
    d[6] = s[5];
    d[7] = 0;
    d[8] = s[6];
    d[9] = s[7];
    d[10] = s[8];
    d[11] = 0;
    d[12] = t[12];
    d[13] = t[13];
    d[14] = t[14];
    d[15] = 0x3FF0000000000000ull;
}
