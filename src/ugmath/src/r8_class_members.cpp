



#include <cstddef>

namespace UGS { namespace Math { namespace Clip {



class Clipper {
public:
    Clipper& operator=(const Clipper&);
private:
    Clipper();
    ~Clipper();
};

Clipper::Clipper() {}
Clipper::~Clipper() {}
Clipper& Clipper::operator=(const Clipper&) { return *this; }

}}}

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

    IAcomParameterAccess& operator=(const IAcomParameterAccess&);
    IAcomParameterAccess& operator=(IAcomParameterAccess&&);
};

IAcomParameterAccess& IAcomParameterAccess::operator=(const IAcomParameterAccess&) { return *this; }
IAcomParameterAccess& IAcomParameterAccess::operator=(IAcomParameterAccess&&) { return *this; }

}}

namespace UGS { namespace Math {
class AlgorithmVersionRestorer {
public:
    int* m_versionToRestore;
};
}}

namespace UGS { namespace Memory {


class SharedPtrCountedBase {
public:
    virtual ~SharedPtrCountedBase();
    virtual int release() { return 0; }
};

template <class T>
class SharedPtrCountedBaseImpl_p : public SharedPtrCountedBase {
public:
    explicit SharedPtrCountedBaseImpl_p(T* payload) : m_payload(payload) {}
    ~SharedPtrCountedBaseImpl_p() override;

    int m_strong = 1;
    int m_weak = 1;
    T* m_payload;
};

SharedPtrCountedBase::~SharedPtrCountedBase() {}

template <class T>
SharedPtrCountedBaseImpl_p<T>::~SharedPtrCountedBaseImpl_p() {}

template class SharedPtrCountedBaseImpl_p<UGS::Math::AlgorithmVersionRestorer>;

}}
