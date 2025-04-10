#pragma once

template <typename T>
class Container
{
public:
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using iterator = T *;
    using const_iterator = const T *;
    using size_type = std::size_t;

    virtual ~Container() = default;
    virtual Container() = default;
    virtual Container(const Container &) = default;

    virtual Container &operator=(const Container &) = default;
    virtual bool operator==(const Container &other) const = 0;
    virtual bool operator!=(const Container &other) const = 0;

    virtual iterator begin() noexcept = 0;
    virtual const_iterator cbegin() const noexcept = 0;
    virtual iterator end() noexcept = 0;
    virtual const_iterator cend() const noexcept = 0;

    virtual reference operator[](size_type pos) = 0;
    virtual const_reference operator[](size_type pos) const = 0;

    virtual size_type size() const noexcept = 0;
    virtual size_type max_size() const noexcept = 0;
    virtual bool empty() const noexcept = 0;
};
