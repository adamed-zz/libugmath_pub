














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

double EQ_ask_length_squared_tolerance()
{
    return UGS::Math::GetThreadTolerances()->ask_length_squared_tolerance();
}
