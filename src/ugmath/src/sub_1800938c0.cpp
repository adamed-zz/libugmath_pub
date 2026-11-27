










#include <cstdint>

namespace dev_detail {

struct Strided {
    void* data;
    std::int64_t stride;
};

struct SrcPacked {
    void* data;
};

struct Desc {
    unsigned char pad[0x48];
    std::int64_t width;
    std::int64_t height;
};

struct Args {
    Strided* dst;
    SrcPacked* src;
    void* unknown;
    Desc* desc;
};

}

extern "C" void sub_1800938C0(dev_detail::Args* a) {


    std::int64_t row = 0;
    std::int64_t n = 0;
    if (a->desc->height <= 0) return;
    do {
        if (a->desc->width < n) n = a->desc->width;
        std::int64_t k = 0;
        if (n >= 4) {
            const std::int64_t limit = n - 3;
            do {
                ((void**)a->dst->data)[row * a->dst->stride + k] =
                    (void*)((unsigned long long*)a->src->data)[3 * row + k];
                ((void**)a->dst->data)[row * a->dst->stride + k + 1] =
                    (void*)((unsigned long long*)a->src->data)[3 * row + k + 1];
                ((void**)a->dst->data)[row * a->dst->stride + k + 2] =
                    (void*)((unsigned long long*)a->src->data)[3 * row + k + 2];
                ((void**)a->dst->data)[row * a->dst->stride + k + 3] =
                    (void*)((unsigned long long*)a->src->data)[3 * row + k + 3];
                k += 4;
            } while (k < limit);
        }
        while (k < n) {
            ((void**)a->dst->data)[row * a->dst->stride + k] =
                (void*)((unsigned long long*)a->src->data)[3 * row + k];
            ++k;
        }
        if (k < a->desc->width) {
            ((void**)a->dst->data)[k * (a->dst->stride + 1)] =
                (void*)((unsigned long long*)a->src->data)[4 * k];
            ++k;
        }
        for (; k < a->desc->width; ++k)
            ((void**)a->dst->data)[row * a->dst->stride + k] = nullptr;
        n = ++row;
    } while (row < a->desc->height);
}
