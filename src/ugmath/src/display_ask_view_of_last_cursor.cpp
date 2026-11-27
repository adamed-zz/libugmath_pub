




namespace UGS { namespace Part {
class IAcomParameterAccess {
public:
    virtual ~IAcomParameterAccess();
    virtual void s01(); virtual void s02(); virtual void s03(); virtual void s04();
    virtual void s05(); virtual void s06(); virtual void s07(); virtual void s08();
    virtual void s09(); virtual void s10(); virtual void s11(); virtual void s12();
    virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16();
    virtual void s17(); virtual void s18(); virtual void s19(); virtual void s20();
    virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24();
    virtual int  GetViewOfLastCursor();
    virtual void SetViewOfLastCursor(int);
    virtual void s27(); virtual void s28();
    virtual int  GetRootPartSystemColor();
    virtual void SetRootPartSystemColor(int);
    virtual bool GetViewBoundsDisplay();
    virtual void SetViewBoundsDisplay(bool);
    virtual bool GetViewNamesDisplay();
    virtual void SetViewNamesDisplay(bool);
    static IAcomParameterAccess *GetAcomParameterAccess();
};
} }
using UGS::Part::IAcomParameterAccess;


int DISPLAY_ask_view_of_last_cursor()
{
    return IAcomParameterAccess::GetAcomParameterAccess()->GetViewOfLastCursor();
}
