
#include <new>
#include <cstddef>

namespace UGS { namespace Math {
struct Box3D {
    static void* operator new(std::size_t);
    static void* operator new(std::size_t, int);
    static void* operator new(std::size_t, char*, int);
    static void* operator new(std::size_t, void*);
    static void* operator new(std::size_t, std::align_val_t);
    static void* operator new(std::size_t, std::align_val_t, int);
    static void operator delete(void*, void*);
    static void operator delete(void*, int);
    static void operator delete(void*, char*, int);
    static void operator delete(void*, std::align_val_t);
    static void operator delete(void*, std::align_val_t, int);
    static void* operator new[](std::size_t);
    static void* operator new[](std::size_t, int);
    static void* operator new[](std::size_t, std::align_val_t);
    static void* operator new[](std::size_t, std::align_val_t, int);
    static void operator delete[](void*, int);
    static void operator delete[](void*, std::align_val_t);
    static void operator delete[](void*, std::align_val_t, int);
};
}}
namespace UGS {
class StlPoint3Less {
public:
    StlPoint3Less& operator=(const StlPoint3Less&);
    StlPoint3Less& operator=(StlPoint3Less&&);
    static void* operator new(std::size_t);
    static void* operator new(std::size_t, int);
    static void* operator new(std::size_t, char*, int);
    static void* operator new(std::size_t, std::align_val_t);
    static void* operator new(std::size_t, std::align_val_t, int);
    static void operator delete(void*, void*);
    static void operator delete(void*);
    static void operator delete(void*, int);
    static void operator delete(void*, char*, int);
    static void operator delete(void*, std::align_val_t);
    static void operator delete(void*, std::align_val_t, int);
};
}

namespace UGS { namespace Math {
void* Box3D::operator new(std::size_t n){return ::operator new(n);}
void* Box3D::operator new(std::size_t n,int){return ::operator new(n);}
void* Box3D::operator new(std::size_t n,char*,int){return ::operator new(n);}
void* Box3D::operator new(std::size_t,void* p){return p;}
void* Box3D::operator new(std::size_t n,std::align_val_t a){return ::operator new(n,a);}
void* Box3D::operator new(std::size_t n,std::align_val_t a,int){return ::operator new(n,a);}
void Box3D::operator delete(void* p,void*){}
void Box3D::operator delete(void* p,int){::operator delete(p);}
void Box3D::operator delete(void* p,char*,int){::operator delete(p);}
void Box3D::operator delete(void* p,std::align_val_t a){::operator delete(p,a);}
void Box3D::operator delete(void* p,std::align_val_t a,int){::operator delete(p,a);}
void* Box3D::operator new[](std::size_t n){return ::operator new[](n);}
void* Box3D::operator new[](std::size_t n,int){return ::operator new[](n);}
void* Box3D::operator new[](std::size_t n,std::align_val_t a){return ::operator new[](n,a);}
void* Box3D::operator new[](std::size_t n,std::align_val_t a,int){return ::operator new[](n,a);}
void Box3D::operator delete[](void* p,int){::operator delete[](p);}
void Box3D::operator delete[](void* p,std::align_val_t a){::operator delete[](p,a);}
void Box3D::operator delete[](void* p,std::align_val_t a,int){::operator delete[](p,a);}
}}

namespace UGS {
StlPoint3Less& StlPoint3Less::operator=(const StlPoint3Less&){return *this;}
StlPoint3Less& StlPoint3Less::operator=(StlPoint3Less&&){return *this;}
void* StlPoint3Less::operator new(std::size_t n){return ::operator new(n);}
void* StlPoint3Less::operator new(std::size_t n,int){return ::operator new(n);}
void* StlPoint3Less::operator new(std::size_t n,char*,int){return ::operator new(n);}
void* StlPoint3Less::operator new(std::size_t n,std::align_val_t a){return ::operator new(n,a);}
void* StlPoint3Less::operator new(std::size_t n,std::align_val_t a,int){return ::operator new(n,a);}
void StlPoint3Less::operator delete(void* p,void*){}
void StlPoint3Less::operator delete(void* p){::operator delete(p);}
void StlPoint3Less::operator delete(void* p,int){::operator delete(p);}
void StlPoint3Less::operator delete(void* p,char*,int){::operator delete(p);}
void StlPoint3Less::operator delete(void* p,std::align_val_t a){::operator delete(p,a);}
void StlPoint3Less::operator delete(void* p,std::align_val_t a,int){::operator delete(p,a);}
}
