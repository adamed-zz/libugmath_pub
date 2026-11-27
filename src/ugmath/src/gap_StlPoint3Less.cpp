


namespace UGS {
namespace Math {
struct Point3 {
    double x;
    double y;
    double z;
};
}

class StlPoint3Less {
public:
    bool operator()(const Math::Point3& a, const Math::Point3& b) const;
};

bool StlPoint3Less::operator()(const Math::Point3& a, const Math::Point3& b) const {
    const double eps = 1e-6;
    if (a.x < b.x - eps) return true;
    if (a.x > b.x + eps) return false;
    if (a.y < b.y - eps) return true;
    if (a.y > b.y + eps) return false;
    if (a.z < b.z - eps) return true;
    return false;
}
}


extern "C" bool b38_stlpoint3less(const UGS::Math::Point3* a,
                                   const UGS::Math::Point3* b) {
    static const UGS::StlPoint3Less less;
    return less(*a, *b);
}
