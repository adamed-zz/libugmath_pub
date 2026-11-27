








#include <cstddef>

struct D3
{
    double x;
    double y;
    double z;
};

struct LSFIT_simple_developable_geom_s
{
    int      f0;

    D3       b08;
    D3       b20;
    D3       b38;
    void*    p50;
    void*    p58;
    void*    p60;
    void*    p68;
    void*    p70;
    void*    p78;
    D3       b80;
};

static_assert(sizeof(LSFIT_simple_developable_geom_s) == 0x98, "layout");
static_assert(offsetof(LSFIT_simple_developable_geom_s, b08) == 0x08, "layout");
static_assert(offsetof(LSFIT_simple_developable_geom_s, b20) == 0x20, "layout");
static_assert(offsetof(LSFIT_simple_developable_geom_s, b38) == 0x38, "layout");
static_assert(offsetof(LSFIT_simple_developable_geom_s, p50) == 0x50, "layout");
static_assert(offsetof(LSFIT_simple_developable_geom_s, p78) == 0x78, "layout");
static_assert(offsetof(LSFIT_simple_developable_geom_s, b80) == 0x80, "layout");

void LSFIT_copy_simple_developable_geom(LSFIT_simple_developable_geom_s* src,
                                        LSFIT_simple_developable_geom_s* dst)
{
    dst->f0  = src->f0;
    dst->b08 = src->b08;
    dst->b20 = src->b20;
    dst->b38 = src->b38;
    dst->p50 = src->p50;
    dst->p58 = src->p58;
    dst->p60 = src->p60;
    dst->p68 = src->p68;
    dst->p70 = src->p70;
    dst->p78 = src->p78;
    dst->b80 = src->b80;
}
