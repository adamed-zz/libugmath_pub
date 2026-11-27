




















__declspec(dllimport) void ERROR_assertion_failed(const char* file, int line, const char* format, ...);

namespace UGS {
namespace Part {


class IAcomParameterAccess
{
public:
    static IAcomParameterAccess* GetAcomParameterAccess();


    virtual void pad00(); virtual void pad01(); virtual void pad02(); virtual void pad03();
    virtual void pad04(); virtual void pad05(); virtual void pad06(); virtual void pad07();
    virtual void pad08(); virtual void pad09(); virtual void pad10(); virtual void pad11();
    virtual void pad12(); virtual void pad13(); virtual void pad14(); virtual void pad15();
    virtual void pad16(); virtual void pad17(); virtual void pad18(); virtual void pad19();
    virtual void pad20(); virtual void pad21(); virtual void pad22(); virtual void pad23();
    virtual void pad24(); virtual void pad25(); virtual void pad26(); virtual void pad27();
    virtual void pad28(); virtual void pad29(); virtual void pad30(); virtual void pad31();
    virtual void pad32(); virtual void pad33(); virtual void pad34(); virtual void pad35();
    virtual void pad36(); virtual void pad37(); virtual void pad38(); virtual void pad39();
    virtual void pad40(); virtual void pad41(); virtual void pad42(); virtual void pad43();
    virtual void pad44(); virtual void pad45(); virtual void pad46(); virtual void pad47();
    virtual void pad48(); virtual void pad49(); virtual void pad50(); virtual void pad51();
    virtual void pad52(); virtual void pad53(); virtual void pad54(); virtual void pad55();
    virtual void pad56();


    virtual unsigned char ask_wcs_display();


    virtual void set_wcs_display(bool display);
};

}
}

void WCS_set_wcs_display(int a1)
{
    if ((unsigned int)a1 > 1)
    {
        ERROR_assertion_failed(
            "o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\wcs_ugmath.c",
            356,
            "Never condition true: %s",
            "display_status != 0 && display_status != 1");
    }
    else
    {
        UGS::Part::IAcomParameterAccess* p = UGS::Part::IAcomParameterAccess::GetAcomParameterAccess();
        if (p->ask_wcs_display() != (a1 == 1))
        {
            p->set_wcs_display(a1 == 1);
        }
    }
}
