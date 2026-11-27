








#include "ugmath/box3d.h"

namespace UGS {
namespace Math {

Point3 Box3D::GetXYZCorner() const {
    Point3 p;
    if (dirty) {
        p = *(const Point3*)&corners[6][0];
        return p;
    }
    const double lx = length[0];
    const double ly = length[1];
    const double lz = length[2];
    const double o0 = origin[0];
    const double o1 = origin[1];
    const double o2 = origin[2];
    p.x = ((o0 + matrix[0] * lx) + (o0 + matrix[3] * ly)) +
          (o0 + matrix[6] * lz) - (o0 + o0);
    p.y = ((o1 + matrix[1] * lx) + (o1 + matrix[4] * ly)) +
          (o1 + matrix[7] * lz) - (o1 + o1);
    p.z = ((o2 + matrix[2] * lx) + (o2 + matrix[5] * ly)) +
          (o2 + matrix[8] * lz) - (o2 + o2);
    return p;
}

}
}
