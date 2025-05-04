// #pragma once

// #include <cstddef>
// namespace my_container {

// template <typename T, size_t N>
// class Container {
// public:
//     Container() = default;
//     Container(const Container& other) = default;
//     virtual ~Container() = 0;

//     virtual Container& operator=(const Container& other) = 0;

//     virtual T* begin() = 0;
//     virtual const T* begin() const = 0;
//     virtual const T* cbegin() const = 0;
//     virtual T* end() = 0;
//     virtual const T* end() const = 0;
//     virtual const T* cend() const = 0;

//     virtual bool operator==(const Container& other) const = 0;
//     virtual bool operator!=(const Container& other) const = 0;

//     virtual size_t size() const = 0;
//     virtual size_t max_size() const = 0;
//     virtual bool empty() const = 0;
// };

// template <typename T, size_t N>
// Container<T, N>::~Container() = default;

// } // namespace my_container

#pragma once
#include <cstddef>

namespace my_container {

template <typename T, size_t N>
class Container {
public:
    virtual ~Container() = default;
    virtual Container& operator=(const Container& other) = 0;

    virtual T* begin() = 0;
    virtual const T* begin() const = 0;
    virtual const T* cbegin() const = 0;
    virtual T* end() = 0;
    virtual const T* end() const = 0;
    virtual const T* cend() const = 0;

    virtual bool operator==(const Container& other) const = 0;
    virtual bool operator!=(const Container& other) const = 0;

    virtual size_t size() const = 0;
    virtual size_t max_size() const = 0;
    virtual bool empty() const = 0;
};

} // namespace my_container