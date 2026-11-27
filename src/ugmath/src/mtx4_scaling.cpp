





namespace UGS {
namespace Math {
struct Point3 { double x, y, z; };
struct Vector3 { double x, y, z; };
struct TransformMatrix { double m[16]; };
}
}

void MTX4_multiply(const UGS::Math::TransformMatrix* a,
                   const UGS::Math::TransformMatrix* b,
                   UGS::Math::TransformMatrix* out);

void MTX4_scaling(const UGS::Math::Point3* origin,
                  const UGS::Math::Vector3* scale,
                  UGS::Math::TransformMatrix* out)
{
    double ox = origin->x;
    double oy = origin->y;
    double oz = origin->z;

    UGS::Math::TransformMatrix m;
    m.m[3] = -ox;
    m.m[7] = -oy;
    m.m[11] = -oz;
    m.m[0] = 1.0;
    m.m[1] = 0.0;
    m.m[2] = 0.0;
    m.m[4] = 0.0;
    m.m[5] = 1.0;
    m.m[6] = 0.0;
    m.m[8] = 0.0;
    m.m[9] = 0.0;
    m.m[10] = 1.0;
    m.m[12] = 0.0;
    m.m[13] = 0.0;
    m.m[14] = 0.0;
    m.m[15] = 1.0;

    UGS::Math::TransformMatrix s;
    s.m[0] = scale->x;
    s.m[1] = 0.0;
    s.m[2] = 0.0;
    s.m[3] = 0.0;
    s.m[4] = 0.0;
    s.m[5] = scale->y;
    s.m[6] = 0.0;
    s.m[7] = 0.0;
    s.m[8] = 0.0;
    s.m[9] = 0.0;
    s.m[10] = scale->z;
    s.m[11] = 0.0;
    s.m[12] = 0.0;
    s.m[13] = 0.0;
    s.m[14] = 0.0;
    s.m[15] = 1.0;

    UGS::Math::TransformMatrix tmp;
    MTX4_multiply(&m, &s, &tmp);

    m.m[3] = ox;
    m.m[7] = oy;
    m.m[11] = oz;
    m.m[0] = 1.0;
    m.m[1] = 0.0;
    m.m[2] = 0.0;
    m.m[4] = 0.0;
    m.m[5] = 1.0;
    m.m[6] = 0.0;
    m.m[8] = 0.0;
    m.m[9] = 0.0;
    m.m[10] = 1.0;
    m.m[12] = 0.0;
    m.m[13] = 0.0;
    m.m[14] = 0.0;
    m.m[15] = 1.0;

    MTX4_multiply(&tmp, &m, out);
}
