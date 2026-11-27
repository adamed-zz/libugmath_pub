


#include "ugmath/graph.h"

extern "C" void* b24_graph_assign(void* a1, const void* a2);

namespace UGS {
namespace Math {

Graph& Graph::operator=(Graph const& rhs)
{
    b24_graph_assign(this, &rhs);
    return *this;
}

}
}
