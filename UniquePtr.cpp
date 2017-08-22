#include <cstddef>
#include <memory>
#include <iostream>


template <typename T, typename Deleter = std::default_delete<T>>
class UniquePtr {
private:
    std::tuple<T*, Deleter> data;

public:
    // Default constructors
    //.....................................
    UniquePtr() {
        std::get<0>(data) = nullptr;
        std::get<1>(data) = Deleter();
    }

    explicit UniquePtr(T * _ptr) {
        std::get<0>(data) = _ptr;
        _ptr = nullptr;
        std::get<1>(data) = Deleter();
    }

    UniquePtr(UniquePtr&& other) {
        data = other.data;
        std::get<0>(other.data) = nullptr;
    }

    explicit UniquePtr(T * _ptr, Deleter _d) {
        std::get<0>(data) = _ptr;
        _ptr = nullptr;
        std::get<1>(data) = _d;
    }


    // Operator =
    //.....................................
    UniquePtr& operator = (std::nullptr_t) {
        std::get<1>(data)(std::get<0>(data));
        std::get<0>(data) = nullptr;
        return *this;
    }

    UniquePtr& operator = (UniquePtr&& other) {
        std::get<1>(data)(std::get<0>(data));
        data = other.data;
        std::get<0>(other.data) = nullptr;
        return *this;
    }

    // Operator *
    //.....................................
    const T& operator * () const {
        return *(std::get<0>(data));
    }

    T& operator * () {
        return *(std::get<0>(data));
    }

    // Operator ->
    //.....................................
    T * operator -> () const {
        return std::get<0>(data);
    }

    // Methods
    //.....................................
    T * release() {
        T * tmp = std::get<0>(data);
        std::get<0>(data) = nullptr;
        return tmp;
    }

    void reset(T * other) {
        std::get<1>(data)(std::get<0>(data));
        std::get<0>(data) = other;
        other = nullptr;
    }

    void swap(UniquePtr& other) {
        std::swap(data, other.data);
    }

    T * get() const noexcept {
        return std::get<0>(data);
    }

    explicit operator bool() const {
        return std::get<0>(data) != nullptr;
    }

    // Deleter
    //.....................................
    Deleter get_deleter() {
        return std::get<1>(data);
    }

    const Deleter get_deleter() const {
        return std::get<1>(data);
    }

    // Destructor
    //.....................................
    ~UniquePtr() noexcept {
        std::get<1>(data)(std::get<0>(data));
    }

    // Deleted methods
    //.....................................
    UniquePtr(const UniquePtr& other) = delete;
    UniquePtr& operator = (UniquePtr& other) = delete;
};


int main() {
    UniquePtr<int> a(new int(1));
    std::cout << *a;
}

