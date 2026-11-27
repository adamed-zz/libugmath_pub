



#include <cstddef>
#include <new>
namespace UGS { namespace Memory {
class CppMemory { public:
  __declspec(dllimport) static void *allocate(unsigned __int64);
  __declspec(dllimport) static void free(void *);
  __declspec(dllimport) static void free(void *, int); }; }}
namespace UGS { namespace Math {
struct Point3 { double x, y, z; };
struct Vector3 { double x, y, z; };
struct Matrix3 { double m[9]; };
struct Triple { double v[3]; };
class __declspec(novtable) alignas(8) Box3D {
public:


  Box3D();
  virtual ~Box3D();
  static void operator delete[](void *p) { Memory::CppMemory::free(p); }
  static void operator delete(void *p) { Memory::CppMemory::free(p); }
  Matrix3 matrix; Point3 origin; Vector3 length; unsigned char dirty;
  Triple corners[8]; unsigned long long cached;
};
}}
void use_array(UGS::Math::Box3D *p) { delete[] p; }
void use_new_array(int n) { UGS::Math::Box3D *p = new UGS::Math::Box3D[n]; delete[] p; }
