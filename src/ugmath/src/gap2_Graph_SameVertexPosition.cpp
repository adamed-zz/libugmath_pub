





#include "kits/b26_kit/b26_types.h"

#include <cmath>

namespace UGS {
namespace Math {

bool Graph::SameVertexPosition(const IndexedPoint3& a,
                               const IndexedPoint3& b) {
    const double dx = a.second.x - b.second.x;
    const double dy = a.second.y - b.second.y;
    const double dz = a.second.z - b.second.z;
    const double d2 = dx * dx + dy * dy + dz * dz;
    const double d = std::sqrt(d2);
    return m_distanceTolerance >= std::fabs(d);
}

}
}
