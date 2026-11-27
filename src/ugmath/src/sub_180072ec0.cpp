






#include <cstdlib>

extern "C" void* sub_180079AB0(unsigned long long n);
extern "C" void* sub_180079A60(unsigned long long n);
extern "C" long long sub_18008A960(long long* a1, long long a2);

namespace {


struct Vec8 {
    void* data;
    long long size;
};


struct Vec4 {
    void* data;
    long long size;
};





struct Obj {
    void* mat;
    long long rows;
    long long cols;
    Vec8 v1;
    Vec4 v2;
    Vec8 v3;
    Vec8 v4;
    Vec8 v5;
    Vec8 v6;
    unsigned short flag;
    unsigned char pad[6];
};



inline void make_vec8(Vec8& v, unsigned long long n) {
    v.data = nullptr;
    v.size = 0;
    std::free(nullptr);
    v.data = sub_180079AB0(n);
    v.size = (long long)n;
}

inline void make_vec4(Vec4& v, unsigned long long n) {
    v.data = nullptr;
    v.size = 0;
    std::free(nullptr);
    v.data = sub_180079A60(n);
    v.size = (long long)n;
}

}

extern "C" Obj* sub_180072EC0(Obj* self, const double* src) {
    self->mat = nullptr;
    self->rows = 0;
    self->cols = 0;
    std::free(nullptr);

    double* m = (double*)sub_180079AB0(6);
    self->mat = m;
    self->rows = 3;
    self->cols = 2;
    for (int i = 0; i < 6; i += 2) {
        m[i] = src[i];
        m[i + 1] = src[i + 1];
    }
    make_vec8(self->v1, 2);
    make_vec4(self->v2, 2);
    make_vec8(self->v3, 2);
    make_vec8(self->v4, 2);
    make_vec8(self->v5, 2);
    make_vec8(self->v6, 2);
    self->flag = 0;
    sub_18008A960((long long*)self, 0);
    return self;
}
