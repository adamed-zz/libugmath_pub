





























































#include <cstddef>
#include <exception>
#include <new>
#include <typeinfo>


extern "C" int b37_delaunay_loaded;

namespace UGS
{
namespace Error
{
class Exception : public std::exception
{
public:
    virtual void doDefaultStartAction(const char* file, int line, int recover_type) const;
    [[noreturn]] void Rethrow() const;

protected:
    unsigned char m_reserved[0x78];
};

class Severe : public Exception
{
public:
    Severe();
    ~Severe();
    const Exception& Convert(const std::exception& ex);
};
}
}

extern "C" void* sub_1800B8970(void*  , void* frame)
{
    char* f = static_cast<char*>(frame);
    UGS::Error::Severe* severe =
        ::new (static_cast<void*>(f + 0x40)) UGS::Error::Severe();

    void* p = *reinterpret_cast<void**>(f + 0x30);


    void* cast = dynamic_cast<UGS::Error::Exception*>(static_cast<std::exception*>(p));

    void* obj = cast ? p : const_cast<void*>(static_cast<const void*>(
                                 &severe->Convert(*static_cast<std::exception*>(p))));

    void** vt = *reinterpret_cast<void***>(obj);
    reinterpret_cast<void(__fastcall*)(void*, const char*, int, void*)>(vt[2])(
        obj, "o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\Part_Mesh_Delaunay.c", 0x7e, nullptr);
    b37_delaunay_loaded = 0;
    vt = *reinterpret_cast<void***>(obj);
    reinterpret_cast<void(__fastcall*)(void*)>(vt[4])(obj);
    vt = *reinterpret_cast<void***>(obj);
    reinterpret_cast<void(__fastcall*)(void*, void*)>(vt[3])(obj, nullptr);


    severe->UGS::Error::Severe::~Severe();
    return nullptr;
}
