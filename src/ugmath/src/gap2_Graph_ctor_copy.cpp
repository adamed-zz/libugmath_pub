

#define B24_CPPMEMORY_DLLIMPORT __declspec(dllimport)
#include "kits/b24_kit/b24_types.h"
#include <new>

using namespace UGS::Math;

extern "C" GraphLayout* b24_graph_assign(GraphLayout* self, const GraphLayout* src);

extern "C" __declspec(noinline) GraphLayout* b24_graph_copy(GraphLayout* self,
                                                            const GraphLayout* src) {
    self->m_vertexCount = 0;
    self->m_vertexArray = nullptr;
    self->m_edgeCount = 0;
    self->m_edgeArray = nullptr;
    ::new ((void*)&self->m_vertices) DoubleVector();
    ::new ((void*)&self->m_edges) IntVector();
    if (self != src) b24_graph_assign(self, src);
    return self;
}
