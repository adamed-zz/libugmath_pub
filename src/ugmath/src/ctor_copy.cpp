







#pragma once


#include <cstddef>
#include <new>
#include <utility>
#include <vector>

namespace UGS {
namespace Memory {

class CppMemory {
 public:
  __declspec(dllimport) static void *__cdecl allocate(std::size_t n);
  __declspec(dllimport) static void __cdecl free(void *p);
};



template <class T>
class SMAlloc {
 public:
  using value_type = T;

  SMAlloc() noexcept = default;
  template <class U>
  SMAlloc(const SMAlloc<U> &) noexcept {}

  T *allocate(std::size_t n) {
    return n ? static_cast<T *>(CppMemory::allocate(n * sizeof(T))) : nullptr;
  }
  void deallocate(T *p, std::size_t) noexcept { CppMemory::free(p); }

  template <class U, class... A>
  void construct(U *p, A &&...a) {
    ::new (static_cast<void *>(p)) U(std::forward<A>(a)...);
  }
  template <class U>
  void destroy(U *p) {
    p->~U();
  }

  template <class U>
  bool operator==(const SMAlloc<U> &) const noexcept { return true; }
  template <class U>
  bool operator!=(const SMAlloc<U> &) const noexcept { return false; }
};

}
}

struct Solver_data_s {
  int i0;
  int i4;
  void *p8;
  void *p10;
  int i18;

  void *p20;
  void *p28;
  void *p30;
  std::vector<double, UGS::Memory::SMAlloc<double>> v38;
  std::vector<int, UGS::Memory::SMAlloc<int>> v50;
  int i68;

  Solver_data_s() = default;
  explicit Solver_data_s(int x);
  Solver_data_s(const Solver_data_s &s);
  Solver_data_s &operator=(const Solver_data_s &s);
};

static_assert(offsetof(Solver_data_s, v38) == 0x38, "layout");
static_assert(offsetof(Solver_data_s, v50) == 0x50, "layout");
static_assert(offsetof(Solver_data_s, i68) == 0x68, "layout");

Solver_data_s::Solver_data_s(const Solver_data_s &s)
    : i0(s.i0), i4(s.i4), p8(s.p8), p10(s.p10), i18(s.i18), p20(s.p20),
      p28(s.p28), p30(s.p30), v38(s.v38), v50(s.v50), i68(s.i68) {}
