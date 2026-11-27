






#include <cstdlib>

namespace UGS { namespace Memory {
class CppMemory {
public:
    __declspec(dllimport) static void free(void* p);
};
} }

extern "C" void sub_180033770(void* self, void* p)
{
    UGS::Memory::CppMemory::free(p);
}
