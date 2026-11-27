#pragma once































namespace UGS {
namespace Math {

class ITolerances
{
public:
    virtual ~ITolerances() = 0;
    virtual double ask_length_tolerance() = 0;
    virtual double ask_length_squared_tolerance() = 0;
    virtual int ask_number_tolerance() = 0;
};

ITolerances* GetThreadTolerances();

}
}

double __cdecl EQ_ask_length_tolerance(void);
