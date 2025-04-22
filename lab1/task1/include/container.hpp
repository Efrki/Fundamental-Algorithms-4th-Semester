#pragma once

#include <cstddef>
namespace my_container {

template <typename T>
class Container {
public:
    virtual ~Container() = 0;

    virtual Container& operator=(const Container& other) = 0;

    virtual T* begin() = 0;
    virtual const T* begin() const = 0;
    virtual const T* cbegin() const = 0;
    virtual void clear() = 0;
    virtual T* end() = 0;
    virtual const T* end() const = 0;
    virtual const T* cend() const = 0;

    virtual bool operator==(const Container& other) const = 0;
    virtual bool operator!=(const Container& other) const = 0;

    virtual size_t size() const = 0;
    virtual size_t max_size() const = 0;
    virtual bool empty() const = 0;
};

template <typename T>
Container<T>::~Container() = default;

} // namespace my_container