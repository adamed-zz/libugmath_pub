






















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
    bool ExpandToIncludePoint(const Point3& point);

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

bool Box3D::ExpandToIncludePoint(const Point3& point) {
    dirty = 0;
    bool result = false;
    bool shifted = false;
    double nx = 0.0;
    double ny = 0.0;
    double nz = 0.0;

    const double dx = point.x - origin.x;
    const double dy = point.y - origin.y;
    const double dz = point.z - origin.z;
    const double lx = (matrix.m[1] * dy + matrix.m[0] * dx) + matrix.m[2] * dz;
    const double ly = (matrix.m[3] * dx + matrix.m[4] * dy) + matrix.m[5] * dz;
    const double lz = (matrix.m[6] * dx + matrix.m[7] * dy) + matrix.m[8] * dz;


    if (!(lx < 0.0)) {
        if (lx > length[0]) {
            length[0] = lx;
            result = true;
        }
    } else {
        shifted = true;
        result = true;
        nx = lx;
        length[0] = length[0] - lx;
    }
    if (!(ly < 0.0)) {
        if (ly > length[1]) {
            length[1] = ly;
            result = true;
        }
    } else {
        shifted = true;
        result = true;
        ny = ly;
        length[1] = length[1] - ly;
    }



    if (lz < 0.0) {
        result = true;
        shifted = true;
        nz = lz;
        length[2] = length[2] - lz;
    } else if (lz > length[2]) {
        length[2] = lz;
        result = true;
    }

    if (shifted) {
        const double ox = ((matrix.m[3] * ny + matrix.m[0] * nx) +
                           matrix.m[6] * nz) + origin.x;
        const double oy = ((matrix.m[4] * ny + matrix.m[1] * nx) +
                           matrix.m[7] * nz) + origin.y;
        const double oz = ((matrix.m[5] * ny + matrix.m[2] * nx) +
                           matrix.m[8] * nz) + origin.z;
        origin.x = ox;
        origin.y = oy;
        origin.z = oz;
    }
    return result;
}

}
}
