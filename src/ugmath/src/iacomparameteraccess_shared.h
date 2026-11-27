#pragma once
























namespace UGS {
namespace Math {
struct Matrix3;
}

namespace Part {


class IAcomParameterAccess
{
public:
    IAcomParameterAccess();
    virtual ~IAcomParameterAccess() = 0;

    virtual double p01() = 0;
    virtual void p02() = 0;
    virtual void p03() = 0;
    virtual double p04() = 0;
    virtual void p05() = 0;
    virtual void p06() = 0;
    virtual void p07() = 0;
    virtual void p08() = 0;
    virtual void p09() = 0;
    virtual void p10() = 0;
    virtual void p11() = 0;
    virtual void p12() = 0;
    virtual void p13() = 0;
    virtual void p14() = 0;
    virtual void p15() = 0;
    virtual void p16() = 0;
    virtual void p17() = 0;
    virtual void p18() = 0;
    virtual void p19() = 0;
    virtual void p20() = 0;
    virtual void p21() = 0;
    virtual void p22() = 0;
    virtual void p23() = 0;
    virtual void p24() = 0;
    virtual void p25() = 0;
    virtual void p26() = 0;
    virtual void p27() = 0;
    virtual void p28() = 0;
    virtual void p29() = 0;
    virtual void p30() = 0;
    virtual void p31() = 0;
    virtual void p32() = 0;
    virtual void p33() = 0;
    virtual void p34() = 0;
    virtual void p35() = 0;
    virtual void p36() = 0;
    virtual void p37() = 0;
    virtual void p38() = 0;



    virtual void* p39() = 0;


    virtual void p40() = 0;

    virtual void p41(const UGS::Math::Matrix3* m) = 0;



    virtual void* p42() = 0;

    virtual void p43() = 0;
    virtual void p44() = 0;
    virtual unsigned int p45() = 0;
    virtual void p46(unsigned int v) = 0;
    virtual unsigned int p47() = 0;
    virtual void p48(unsigned int v) = 0;
    virtual void p49() = 0;
    virtual void p50() = 0;
    virtual unsigned int p51() = 0;
    virtual void p52(unsigned int v) = 0;
    virtual unsigned int p53() = 0;
    virtual void p54(unsigned int v) = 0;
    virtual bool p55() = 0;
    virtual void p56(bool v) = 0;
    virtual unsigned char p57() = 0;
    virtual void p58() = 0;
    virtual void p59() = 0;
    virtual void p60() = 0;
    virtual void p61() = 0;
    virtual void p62() = 0;
    virtual void p63() = 0;
    virtual void p64() = 0;



protected:
    virtual void RegisterMe(IAcomParameterAccess* p) const;

public:
    static IAcomParameterAccess* GetAcomParameterAccess();
};

}
}
