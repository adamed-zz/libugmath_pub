
#include "ugmath/vector3f.h"

namespace UGS {
namespace Math {

Vector3f::Vector3f(const Vector3f& o) : x(o.x), y(o.y), z(o.z) {}

float* Vector3f::c_array() { return &x; }

Internals::ArrayIterator<float> Vector3f::begin() {
    Internals::ArrayIterator<float> it; it.ptr = &x; return it;
}
Internals::ArrayIterator<float> Vector3f::end() {
    Internals::ArrayIterator<float> it; it.ptr = &x + 3; return it;
}
Internals::ArrayIterator<const float> Vector3f::begin() const {
    Internals::ArrayIterator<const float> it; it.ptr = &x; return it;
}
Internals::ArrayIterator<const float> Vector3f::cend() const {
    Internals::ArrayIterator<const float> it; it.ptr = &x + 3; return it;
}

}
}

