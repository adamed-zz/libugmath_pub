






















#include <cmath>

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
    bool DoesBoxIntersect(Box3D& other);

    Point3 GetXYZCorner() const;
    double GetRadius() const;
    bool IsBoxAligned(const Box3D& other) const;

private:
    void deriveData();
    bool getIntersectStatus(const Box3D& other, double tolerance) const;

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

bool Box3D::DoesBoxIntersect(Box3D& other) {
    deriveData();
    other.deriveData();


    double otherX;
    double otherY;
    double otherZ;
    if (other.dirty) {
        otherX = other.cache[7][0];
        otherY = other.cache[7][1];
        otherZ = other.cache[7][2];
    } else {
        const Point3 corner = other.GetXYZCorner();
        otherX = (corner.x + other.origin.x) * 0.5;
        otherY = (corner.y + other.origin.y) * 0.5;
        otherZ = (corner.z + other.origin.z) * 0.5;
    }

    double thisX;
    double thisY;
    double thisZ;
    if (dirty) {
        thisX = cache[7][0];
        thisY = cache[7][1];
        thisZ = cache[7][2];
    } else {
        const Point3 corner = GetXYZCorner();
        thisX = (corner.x + origin.x) * 0.5;
        thisY = (corner.y + origin.y) * 0.5;
        thisZ = (corner.z + origin.z) * 0.5;
    }

    const double dx = thisX - otherX;
    const double dy = thisY - otherY;
    const double dz = thisZ - otherZ;
    const double distanceSquared = dy * dy + dx * dx + dz * dz;
    const double distance = std::sqrt(distanceSquared);
    if (distance > other.GetRadius() + GetRadius() + 1.0e-10) {
        return false;
    }

    const bool status = getIntersectStatus(other, 1.0e-10);
    if (status && !IsBoxAligned(other)) {
        return other.getIntersectStatus(*this, 1.0e-10);
    }
    return status;
}

}
}
