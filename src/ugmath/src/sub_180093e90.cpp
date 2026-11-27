













#include <cstdint>
#include <cstdlib>
#include <new>

namespace dev_detail {

struct IndexBuffer {
    std::uint32_t* data;
    std::int64_t count;
};

__declspec(noinline) void* AllocIndices(std::int64_t count) {
    void* p = std::malloc((size_t)count * 4);
    if (!p) throw std::bad_alloc();
    return p;
}

}

extern "C" void sub_180093E90(dev_detail::IndexBuffer* self, std::int64_t n) {
    if (n != self->count) {
        std::free(self->data);
        if (n > 0)
            self->data = static_cast<std::uint32_t*>(dev_detail::AllocIndices(n));
        else
            self->data = nullptr;
    }
    self->count = n;
    int count = (int)n;
    for (int i = 0; i < count; ++i) self->data[i] = (std::uint32_t)i;
}
