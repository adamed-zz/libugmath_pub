#include <memory>










namespace UGS {
namespace Math {

class ITolerances {
public:
    virtual ~ITolerances();
    virtual double GetA() const = 0;
    virtual double GetB() const = 0;
    virtual int GetC() const = 0;
};





extern std::unique_ptr<ITolerances> g_default_tolerances;

void SetGlobalTolerances(std::unique_ptr<ITolerances>&& p)
{
    g_default_tolerances = std::move(p);
}

}
}
