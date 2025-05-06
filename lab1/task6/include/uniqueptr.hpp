#ifndef MY_SMART_PTR_UNIQUE_PTR_HPP
#define MY_SMART_PTR_UNIQUE_PTR_HPP

#include <utility>
#include <cstddef>

namespace my_smart_ptr {

template <typename T>
class UniquePtr {
    T* ptr_{nullptr};

public:
    constexpr UniquePtr() noexcept = default;
    explicit UniquePtr(T* ptr) noexcept : ptr_(ptr) {}
    UniquePtr(UniquePtr&& other) noexcept : ptr_(other.ptr_) { other.ptr_ = nullptr; }

    ~UniquePtr() { delete ptr_; }

    UniquePtr& operator=(UniquePtr&& other) noexcept {
        if (this != &other) {
            reset(other.release());
        }
        return *this;
    }

    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;

    T* get() const noexcept { return ptr_; }
    T& operator*() const { return *ptr_; }
    T* operator->() const noexcept { return ptr_; }
    explicit operator bool() const noexcept { return ptr_ != nullptr; }

    T* release() noexcept {
        T* temp = ptr_;
        ptr_ = nullptr;
        return temp;
    }

    void reset(T* ptr = nullptr) noexcept {
        T* old = ptr_;
        ptr_ = ptr;
        delete old;
    }

    void swap(UniquePtr& other) noexcept {
        std::swap(ptr_, other.ptr_);
    }
};

template <typename T>
void swap(UniquePtr<T>& lhs, UniquePtr<T>& rhs) noexcept {
    lhs.swap(rhs);
}

template <typename T>
class UniquePtr<T[]> {
    T* ptr_{nullptr};

public:
    constexpr UniquePtr() noexcept = default;
    explicit UniquePtr(T* ptr) noexcept : ptr_(ptr) {}
    UniquePtr(UniquePtr&& other) noexcept : ptr_(other.ptr_) { other.ptr_ = nullptr; }

    ~UniquePtr() { delete[] ptr_; }

    UniquePtr& operator=(UniquePtr&& other) noexcept {
        if (this != &other) {
            reset(other.release());
        }
        return *this;
    }

    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;

    T* get() const noexcept { return ptr_; }
    T& operator[](std::size_t i) const { return ptr_[i]; }
    explicit operator bool() const noexcept { return ptr_ != nullptr; }

    T* release() noexcept {
        T* temp = ptr_;
        ptr_ = nullptr;
        return temp;
    }

    void reset(T* ptr = nullptr) noexcept {
        T* old = ptr_;
        ptr_ = ptr;
        delete[] old;
    }

    void swap(UniquePtr& other) noexcept {
        std::swap(ptr_, other.ptr_);
    }
};

template <typename T>
void swap(UniquePtr<T[]>& lhs, UniquePtr<T[]>& rhs) noexcept {
    lhs.swap(rhs);
}

}

#endif
