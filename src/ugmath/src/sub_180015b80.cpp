





#include <cstddef>


__declspec(dllimport) void* __cdecl SM_alloc(size_t size);

namespace {

struct BCDF_zeros {
    void* q00;
    void* q08;
    void* q10;
    void* q18;
    void* q20;
    void* q28;
    void* q30;
    void* q38;
    void* q40;
    void* q48;
    void* q50;
    void* q58;
    void* q60;
    void* q68;
    void* q70;
    void* q78;
    void* q80;
    unsigned char b88;
    unsigned char pad89[3];
    unsigned int d8C;
};

}

extern "C" void* sub_180015B80() {
    BCDF_zeros* r = static_cast<BCDF_zeros*>(SM_alloc(sizeof(BCDF_zeros)));
    r->q00 = nullptr;
    r->q10 = nullptr;
    r->q08 = nullptr;
    r->q18 = nullptr;
    r->q20 = nullptr;
    r->q48 = nullptr;
    r->q28 = nullptr;
    r->q30 = nullptr;
    r->q50 = nullptr;
    r->q38 = nullptr;
    r->q40 = nullptr;
    r->q58 = nullptr;
    r->d8C = 0;
    r->q80 = nullptr;
    r->q60 = nullptr;
    r->q68 = nullptr;
    r->b88 = 0;
    r->q70 = nullptr;
    r->q78 = nullptr;
    return r;
}
