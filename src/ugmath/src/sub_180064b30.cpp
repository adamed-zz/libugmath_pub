













namespace UGS {
namespace Math {

struct Matrix3 {
    double m[9];
};
struct Point3 {
    double x;
    double y;
    double z;
};

class Box3D {
public:
    Point3 GetCentroid() const;
    Point3 GetXYZCorner() const;

    void* vftable;
    Matrix3 matrix;
    Point3 origin;
    double length[3];
    unsigned char dirty;
    unsigned char pad[7];
    double cache[8][3];
    double radiusCache;
};

static_assert(sizeof(Box3D) == 336, "Box3D 必须为 336 字节");
static_assert(sizeof(Matrix3) == 72, "Matrix3 必须为 72 字节");

Point3 Box3D::GetCentroid() const {
    if (dirty) {
        Point3 out;
        out.x = cache[7][0];
        out.y = cache[7][1];
        out.z = cache[7][2];
        return out;
    }
    const Point3 corner = GetXYZCorner();
    Point3 out;
    out.x = (corner.x + origin.x) * 0.5;
    out.y = (corner.y + origin.y) * 0.5;
    out.z = (corner.z + origin.z) * 0.5;
    return out;
}

}
}
