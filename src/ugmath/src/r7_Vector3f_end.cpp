







#include "b36_math.h"

namespace UGS {
namespace Math {

Internals::ArrayIterator<const float> Vector3f::end() const {
    Internals::ArrayIterator<const float> it;
    it.ptr = &x + 3;
    return it;
}

}
}
