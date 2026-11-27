







namespace UGS {
namespace Math {

struct TransformMatrix {
    double m[4][4];
};

}
}

bool MTX4_is_reflection(const UGS::Math::TransformMatrix* tm)
{
    return (tm->m[2][2] * tm->m[1][1] - tm->m[2][1] * tm->m[1][2]) * tm->m[0][0]
         - (tm->m[2][2] * tm->m[0][1] - tm->m[2][1] * tm->m[0][2]) * tm->m[1][0]
         + (tm->m[1][2] * tm->m[0][1] - tm->m[1][1] * tm->m[0][2]) * tm->m[2][0] < 0.0;
}
