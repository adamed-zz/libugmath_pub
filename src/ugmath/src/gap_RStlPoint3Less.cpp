




namespace UGS {
namespace Math {
struct Point3 {
    double x;
    double y;
    double z;
};
}

struct StlPoint3Less {
    static double m_disTol;
    bool operator()(const Math::Point3& a2, const Math::Point3& a3) const;
};


double StlPoint3Less::m_disTol = 1.0e-6;

bool StlPoint3Less::operator()(const Math::Point3& a2,
                               const Math::Point3& a3) const {
    bool result = true;
    if (!(a3.x - m_disTol > a2.x)) {
        if (a2.x > a3.x + m_disTol) return false;
        if (!(a3.y - m_disTol > a2.y)) {
            if (a2.y > a3.y + m_disTol) return false;
            if (!(a3.z - m_disTol > a2.z)) return false;
        }
    }
    return result;
}
}
