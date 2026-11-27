























#include <cstdint>

extern "C" double sub_18007E9C0(void* vecs, void* unused, void* len_obj);
extern "C" std::int64_t sub_18008D790(std::int64_t rows, std::int64_t cols,
                                      void* a_desc, void* b_desc,
                                      std::int64_t c_ptr, std::int64_t c_stride,
                                      double alpha);

namespace dev_detail {


struct DotVecs {
    std::int64_t f0;
    const double* v1;
    std::int64_t f2;
    std::int64_t f3;
    const double* v2;
};


struct DotLen {
    unsigned char pad[0x98];
    std::int64_t len;
};


struct ADesc {
    std::int64_t ptr;
    std::int64_t ld;
};


struct BDesc {
    const double* ptr;
    std::int64_t stride;
};

}

extern "C" std::int64_t sub_180093A90(std::int64_t a1, std::int64_t a2,
                                      std::int64_t a3, std::int64_t a4,
                                      std::int64_t a5, std::int64_t a6,
                                      double* a7, std::int64_t a8, double* a9) {
    using dev_detail::ADesc;
    using dev_detail::BDesc;
    using dev_detail::DotLen;
    using dev_detail::DotVecs;

    const std::int64_t n = a2 < a1 ? a2 : a1;
    if (n <= 0) {

        volatile unsigned char stack_slot = 0;
        return (std::int64_t)(std::uintptr_t)&stack_slot;
    }

    double* const A = (double*)a3;
    const double* const B = (const double*)a5;
    std::int64_t block = 0;
    do {
        std::int64_t nb = n - block;
        if (nb > 8) nb = 8;
        if (nb > 0) {

            double* c = a7 + block * a8;
            const std::int64_t row_stride = a4;
            std::int64_t j = 0;
            do {
                const std::int64_t cnt = nb - 1 - j;
                double acc;
                if (cnt > 0) {
                    DotVecs vecs;
                    vecs.f0 = 0;
                    vecs.v1 = A + (block + j) * row_stride + block + j + 1;
                    vecs.f2 = 0;
                    vecs.f3 = 0;
                    vecs.v2 = B + block + j + 1;
                    DotLen len;
                    for (unsigned i = 0; i < sizeof len.pad; ++i) len.pad[i] = 0;
                    len.len = cnt;
                    acc = sub_18007E9C0(&vecs, nullptr, &len);
                    acc = acc * *a9 + *c;
                    *c = acc;
                } else {
                    acc = *c;
                }
                const double bj = B[block + j];
                *c = bj * *a9 + acc;
                c += a8;
                ++j;
            } while (j < nb);
        }
        const std::int64_t rest = a2 - nb - block;
        if (rest > 0) {
            ADesc ad;
            ad.ptr = (std::int64_t)(std::uintptr_t)(
                A + block * a4 + block + nb);
            ad.ld = a4;
            BDesc bd;
            bd.ptr = B + block + nb;
            bd.stride = a6;



            sub_18008D790(nb, rest, &ad, &bd,
                          (std::int64_t)(std::uintptr_t)(a7 + block * a8), a8,
                          *a9);
        }
        block += 8;
    } while (block < n);
    return a8 << 6;
}
