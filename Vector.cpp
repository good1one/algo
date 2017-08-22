#include <algorithm>
#include <cstdlib>
#include <utility>
#include <string>
#include <iostream>
#include <new>


template <typename T>
struct VectorBase {
    T * data = nullptr;
    size_t cp;

    // Constructors
    //.....................................
    VectorBase() {}

    VectorBase(size_t n)
            : data(static_cast<T*>(
                           operator new (n * sizeof(T))))
            , cp(n)
    {}

    VectorBase(VectorBase&& other)
            : data(other.data)
            , cp(other.cp)  {
        other.data = nullptr;
    }

    // Deleted methods
    //.....................................
    VectorBase(const VectorBase&) = delete;
    VectorBase&operator = (const VectorBase&) = delete;

    // Methods
    //.....................................
    VectorBase&operator = (VectorBase&& other) {
        swap(other);
        return *this;
    }

    void swap(VectorBase& other) {
        std::swap(data, other.data);
        std::swap(cp, other.cp);
    }

    // Destructor
    //.....................................
    ~VectorBase() {
        operator delete(data);
    }
};


template<typename T>
class Vector {
private:
    VectorBase<T> base;
    size_t sz = 0;

    void Delete() noexcept {
        for (size_t i = 0; i < sz; ++i) {
            base.data[i].~T();
        }
    }

public:
    // Constructors
    //.....................................
    Vector() {}

    Vector(size_t n) {
        base = VectorBase<T>(n);
        sz = n;
        for (size_t i = 0; i < n; ++i) {
            new (base.data + i) T();
        }
    }

    Vector(const Vector& other) {
        base(other.sz);
        sz = other.sz;
        std::uninitialized_copy(other.base.data, other.base.data + sz, base.data);
    }

    Vector(Vector&& other) {
        base(std::move(other.base));
        sz = other.sz;
    }

    // Operator =
    //.....................................
    Vector&operator = (const Vector& other) {
        if (base.data == other.base.data) return *this;

        Vector tmp(other);
        base.swap(other.base);
        std::swap(sz, other.sz);
        return *this;
    }

    // Memory methods
    //.....................................
    void resize(size_t n) {
        if (sz > n) {
            for (size_t i = n; i < sz; ++i)
                base.data[i].~T();
        } else if (base.cp > n) {
            for (size_t i = sz; i < n; ++i)
                new (base.data + i) T();
        } else {
            VectorBase<T> tmp(n);
            std::uninitialized_copy(base.data, base.data + sz, tmp.data);
            for (size_t i = sz; i < n; ++i)
                new (tmp.data + i) T();
            Delete();

            base = std::move(tmp);
        }

        sz = n;
    }

    void reserve(size_t cp) {
        if (cp > base.cp) {
            VectorBase<T> tmp(cp);
            std::uninitialized_copy(base.data, base.data + sz, tmp.data);
            size_t n = sz;
            Delete();
            sz = n;
            base = std::move(tmp);
        }
    }

    // Push/pop + back
    //.....................................
    void push_back(const T& v) {
        if (sz == base.cp) {
            base.cp *= 2;
            if (base.cp == 0) {
                ++base.cp;
            }
            VectorBase<T> tmp(base.cp);
            new (tmp.data + sz) T(v);
            std::uninitialized_copy(base.data, base.data + sz, tmp.data);
            size_t n = sz + 1;

            Delete();
            sz = n;
            base = std::move(tmp);
        } else {
            new (base.data + sz) T(v);
            ++sz;
        }
    }

    void push_back(T&& v) {
        if (sz == base.cp) {
            base.cp *= 2;
            if (base.cp == 0) {
                ++base.cp;
            }

            VectorBase<T> tmp(base.cp);
            new (tmp.data + sz) T(std::move(v));
            std::uninitialized_copy(base.data, base.data + sz, tmp.data);
            size_t n = sz + 1;
            Delete();
            sz = n;

            base = std::move(tmp);
        } else {
            new (base.data + sz) T(std::move(v));
            ++sz;
        }
    }

    void pop_back() {
        --sz;
        base.data[sz].~T();
    }

    // Size/Capacity
    //.....................................
    size_t size() const {
        return sz;
    }

    size_t capacity() const {
        return base.cp;
    }

    // Operator []
    //.....................................
    T& operator[] (size_t i) {
        return base.data[i];
    }

    const T& operator[] (size_t i) const {
        return base.data[i];
    }

    // Iterators
    //.....................................
    T * begin() {
        return base.data;
    }

    const T * begin() const {
        return base.data;
    }

    T * end() {
        return base.data + sz;
    }

    const T * end() const {
        return base.data + sz;
    }

    // Destructor
    //.....................................
    ~Vector() {
        Delete();
    }
};


int main() {
    Vector<int> a;
    a.push_back(1);
    std::cout << a[0];
}

