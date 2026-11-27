





#include <cstddef>
#include <vector>

namespace UGS { namespace Memory {
template <class T>
class SMAlloc
{
public:
    using value_type = T;
    SMAlloc() = default;
    template <class U> SMAlloc(const SMAlloc<U> &) {}
    T *allocate(std::size_t) { return nullptr; }
    void deallocate(T *, std::size_t) {}
    template <class U> bool operator==(const SMAlloc<U> &) const { return true; }
    template <class U> bool operator!=(const SMAlloc<U> &) const { return false; }
};
} }

union BOX3_s;

namespace UGS { namespace Math {

struct Graph
{
    void InteriorUnconnectedEdges(BOX3_s const &,
                                  std::vector<int, UGS::Memory::SMAlloc<int> > &,
                                  std::vector<int, UGS::Memory::SMAlloc<int> > &) const;
};

void Graph::InteriorUnconnectedEdges(BOX3_s const &,
                                     std::vector<int, UGS::Memory::SMAlloc<int> > &,
                                     std::vector<int, UGS::Memory::SMAlloc<int> > &) const
{
}

} }
