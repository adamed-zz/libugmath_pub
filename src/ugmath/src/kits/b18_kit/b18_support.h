

#pragma once

#include "b18_kit.h"



struct B18AcomBlock
{
    unsigned char pad[0x608];
    int count;
    unsigned int arr[512];
};
static_assert(offsetof(B18AcomBlock, count) == 0x608, "acom.count offset");
static_assert(offsetof(B18AcomBlock, arr) == 0x60C, "acom.arr offset");

extern B18AcomBlock g_acom;
extern void (*g_cb)();
extern unsigned char g_ingrip;
extern int g_cuval;


struct B18B120Block
{

    unsigned char q[8][16];
    long long x;
    int n;
};
static_assert(offsetof(B18B120Block, x) == 0x80, "b120.x offset");
static_assert(offsetof(B18B120Block, n) == 0x88, "b120.n offset");
extern B18B120Block g_b120;


namespace UGS
{
namespace Part
{
class IAcomParameterAccess
{
public:

    static IAcomParameterAccess *GetAcomParameterAccess();


    virtual void slot00(double *);
    virtual void slot08();
    virtual void slot10();
    virtual void slot18();
    virtual double slot20d();
    virtual void slot28(double *);
    virtual void slot30(double *);
    virtual void slot38(double *);
    virtual void slot40(double *);
    virtual void slot48(double *);
    virtual void slot50(double *);
    virtual void slot58(double *);
    virtual void slot60(double *);
    virtual void slot68(double *);
    virtual void slot70(double *);
    virtual void slot78(double *);
    virtual void slot80(double *);
    virtual void slot88(double *);
    virtual void slot90(double *);
    virtual void slot98(double *);
    virtual void slotA0(double *);
    virtual void slotA8(double *);
    virtual void slotB0(double *);
    virtual void slotB8(double *);
    virtual void slotC0(double *);
    virtual void slotC8(double *);
    virtual void slotD0(double *);
    virtual void slotD8(double *);
    virtual void slotE0(double *);
    virtual void slotE8(double *);
    virtual void slotF0(double *);
    virtual void slotF8(double *);
    virtual void slot100(double *);
    virtual void slot108(double *);
    virtual void slot110(double *);
    virtual void slot118(double *);
    virtual void slot120(double *);
    virtual void slot128(double *);
    virtual void slot130(double *);
    virtual double *slot138();
    virtual void slot140v(double *);
    virtual void slot148(double *);
    virtual double *slot150v();
    virtual void slot158v(double *);
};
}
}


inline double *b18_acom_mtx(UGS::Part::IAcomParameterAccess *p) { return p->slot138(); }
inline double *b18_acom_pt(UGS::Part::IAcomParameterAccess *p) { return p->slot150v(); }
inline void b18_acom_take_vec(UGS::Part::IAcomParameterAccess *p, double *v) { p->slot140v(v); }
inline void b18_acom_put_vec(UGS::Part::IAcomParameterAccess *p, double *v) { p->slot158v(v); }


void map10(const double *a1, double *a2);
void map11(const double *a1, double *a2);
void mapvaw(double *a1, double *a2);
void mapvwa(double *a1, double *a2);



void h053(const double *a1, const double *a2, double *a3);

void h805(const double *a1, const double *a2, const int *a3, int *a4);



B18GlobPtrs b18_dev_globals();
