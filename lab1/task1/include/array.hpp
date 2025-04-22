#pragma once

#include "container.hpp"
#include <initializer_list>
#include <stdexcept>
#include <compare>
#include <iterator>
#include <utility>

namespace my_container {

template <typename T, size_t N>
class Array final : public Container<T> {
public:
    using value_type = T;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;
    using iterator = T*;
    using const_iterator = const T*;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    Array() = default;

    Array(std::initializer_list<T> init) {
        if (init.size() != N) {
            throw std::invalid_argument("Invalid initializer list size");
        }
        std::copy(init.begin(), init.end(), data_);
    }

    Array(const Array& other) {
        std::copy(other.data_, other.data_ + N, data_);
    }

    Array(Array&& other) noexcept {
        for (size_t i = 0; i < N; ++i) {
            data_[i] = std::move(other.data_[i]);
        }
    }

    ~Array(){
        if(N > 0){
            delete[] data_;
        }
    }

    Array& operator=(const Array& other) {
        if (this != &other) {
            std::copy(other.data_, other.data_ + N, data_);
        }
        return *this;
    }

    Array& operator=(Array&& other) noexcept {
        for (size_t i = 0; i < N; ++i) {
            data_[i] = std::move(other.data_[i]);
        }
        return *this;
    }

    Array& operator=(const Container<T>& other) override {
        const Array* arr = dynamic_cast<const Array*>(&other);
        if (!arr) {
            throw std::invalid_argument("Invalid assignment");
        }
        return *this = *arr;
    }

    reference at(size_type pos) {
        if (pos >= N) {
            throw std::out_of_range("Index out of range");
        }
        return data_[pos];
    }

    const_reference at(size_type pos) const {
        if (pos >= N) {
            throw std::out_of_range("Index out of range");
        }
        return data_[pos];
    }

    reference operator[](size_type pos) { return data_[pos]; }
    const_reference operator[](size_type pos) const { return data_[pos]; }

    reference front() { return data_[0]; }
    const_reference front() const { return data_[0]; }

    reference back() { return data_[N - 1]; }
    const_reference back() const { return data_[N - 1]; }

    pointer data() noexcept { return data_; }
    const_pointer data() const noexcept { return data_; }

    iterator begin() noexcept override { return data_; }
    const_iterator begin() const noexcept override { return data_; }
    const_iterator cbegin() const noexcept override { return data_; }

    iterator end() noexcept override { return data_ + N; }
    const_iterator end() const noexcept override { return data_ + N; }
    const_iterator cend() const noexcept override { return data_ + N; }

    reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
    const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }
    const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(cend()); }

    reverse_iterator rend() noexcept { return reverse_iterator(begin()); }
    const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }
    const_reverse_iterator crend() const noexcept { return const_reverse_iterator(cbegin()); }

    bool empty() const noexcept override { return N == 0; }
    size_type size() const noexcept override { return N; }
    size_type max_size() const noexcept override { return N; }

    void fill(const T& value) { std::fill(data_, data_ + N, value); }

    void swap(Array& other) noexcept(std::is_nothrow_swappable_v<T>) {
        for (size_t i = 0; i < N; ++i) {
            std::swap(data_[i], other.data_[i]);
        }
    }

    bool operator==(const Container<T>& other) const override {
        const Array* arr = dynamic_cast<const Array*>(&other);
        return arr && *this == *arr;
    }

    bool operator!=(const Container<T>& other) const override {
        return !(*this == other);
    }

    bool operator==(const Array& other) const {
        return std::equal(data_, data_ + N, other.data_);
    }

    bool operator!=(const Array& other) const { return !(*this == other); }

    bool operator<(const Array& other) const {
        return std::lexicographical_compare(data_, data_ + N, other.data_, other.data_ + N);
    }

    bool operator<=(const Array& other) const { return !(other < *this); }
    bool operator>(const Array& other) const { return other < *this; }
    bool operator>=(const Array& other) const { return !(*this < other); }

    auto operator<=>(const Array& other) const {
        return std::lexicographical_compare_three_way(data_, data_ + N, other.data_, other.data_ + N);
    }

private:
    T* data_ = N > 0 ? new T[N]() : nullptr;
};

} // namespace my_container
