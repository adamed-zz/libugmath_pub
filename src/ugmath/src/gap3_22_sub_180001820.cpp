






#include <string.h>

extern "C" void* sub_180001800(void* p);

struct Vec3
{
    double c[3];
};




#pragma optimize("g", off)
extern "C" Vec3* sub_180001820(Vec3* out, double s, const Vec3* v)
{
    Vec3 t;
    sub_180001800(&t);
    t.c[0] = v->c[0] * s;
    t.c[1] = v->c[1] * s;
    t.c[2] = v->c[2] * s;
    memcpy(out, &t, 0x18);
    return out;
}
#pragma optimize("g", on)
