#pragma once

namespace UGS { namespace Math { namespace Internals {
template <class T>
class ArrayIterator {
public:
    T* ptr;
    ArrayIterator() noexcept : ptr(nullptr) {}
    ArrayIterator(const ArrayIterator& o) noexcept : ptr(o.ptr) {}
    ArrayIterator& operator=(const ArrayIterator& o) noexcept { ptr = o.ptr; return *this; }
    ~ArrayIterator() noexcept {}
};
}}}
