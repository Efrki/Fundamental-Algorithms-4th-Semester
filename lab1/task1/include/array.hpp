#pragma once
#include "container.hpp"
#include <algorithm>
#include <initializer_list>

namespace my_container
{
    template <typename T, size_t N>
    class Array final : public Container<T>
    {
    public:
        using typename Container<T>::value_type;
        using typename Container<T>::reference;
        using typename Container<T>::const_reference;
        using typename Container<T>::iterator;
        using typename Container<T>::const_iterator;
        using typename Container<T>::size_type;

        Array() = default;
        Array(std::initializer_list<T> init)
        {
            std::copy_n(init.begin(), std::min(N, init.size()), data_);
        }
        Array(const Array &) = default;
        Array(Array &&) = default;
        Array &operator=(const Array &) = default;
        Array &operator=(Array &&) = default;
        ~Array() = default;

    private:
        T data_{N};
    };
}