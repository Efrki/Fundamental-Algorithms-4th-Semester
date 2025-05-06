#pragma once
#include "../../task1/include/container.hpp"
#include <cstddef>
#include <initializer_list>
#include <algorithm>
#include <stdexcept>

namespace my_container {

template <typename T, size_t N = 0>
class Vector : public Container<T, N> {
private:
    T* data_ = nullptr;
    size_t size_ = 0;
    size_t capacity_ = 0;

    void reallocate(size_t new_capacity) {
        T* new_data = new T[new_capacity];
        for (size_t i = 0; i < size_; ++i) {
            new_data[i] = std::move(data_[i]);
        }
        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    }

public:
    Vector() = default;

    explicit Vector(size_t count) : data_(new T[count]), size_(count), capacity_(count) {}

    Vector(const Vector& other) : data_(new T[other.capacity_]), size_(other.size_), capacity_(other.capacity_) {
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }

    Vector(Vector&& other) noexcept 
        : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    Vector(std::initializer_list<T> init) : data_(new T[init.size()]), size_(init.size()), capacity_(init.size()) {
        std::copy(init.begin(), init.end(), data_);
    }

    ~Vector() override {
        delete[] data_;
    }

    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] data_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            data_ = new T[capacity_];
            for (size_t i = 0; i < size_; ++i) {
                data_[i] = other.data_[i];
            }
        }
        return *this;
    }
    Vector& operator=(const Container<T, N>& other) override {
        if (this == &other) return *this;
    
        const Vector* other_vec = dynamic_cast<const Vector*>(&other);
        if (!other_vec) {
            throw std::invalid_argument("Invalid container type in Vector assignment");
        }
    
        if (other_vec->size_ > capacity_) {
            delete[] data_;
            data_ = new T[other_vec->capacity_];
            capacity_ = other_vec->capacity_;
        }
    
        size_ = 0;
        try {
            for (size_t i = 0; i < other_vec->size_; ++i) {
                data_[i] = other_vec->data_[i];
                ++size_;
            }
        } catch (...) {
            delete[] data_;
            data_ = nullptr;
            size_ = capacity_ = 0;
            throw;
        }
    
        return *this;
    }

    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            data_ = other.data_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            other.data_ = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;
        }
        return *this;
    }

    T& operator[](size_t pos) {
        return data_[pos];
    }

    const T& operator[](size_t pos) const {
        return data_[pos];
    }

    T& at(size_t pos) {
        if (pos >= size_) {
            throw std::out_of_range("Vector::at");
        }
        return data_[pos];
    }

    const T& at(size_t pos) const {
        if (pos >= size_) {
            throw std::out_of_range("Vector::at");
        }
        return data_[pos];
    }

    T& front() {
        return data_[0];
    }

    const T& front() const {
        return data_[0];
    }

    T& back() {
        return data_[size_ - 1];
    }

    const T& back() const {
        return data_[size_ - 1];
    }

    T* data() noexcept {
        return data_;
    }

    const T* data() const noexcept {
        return data_;
    }

    bool empty() const override {
        return size_ == 0;
    }

    size_t size() const override {
        return size_;
    }

    size_t capacity() const {
        return capacity_;
    }

    void reserve(size_t new_cap) {
        if (new_cap > capacity_) {
            reallocate(new_cap);
        }
    }

    void shrink_to_fit() {
        if (capacity_ > size_) {
            reallocate(size_);
        }
    }

    void clear() {
        size_ = 0;
    }

    void push_back(const T& value) {
        if (size_ >= capacity_) {
            reserve(capacity_ == 0 ? 1 : 2 * capacity_);
        }
        data_[size_++] = value;
    }

    void push_back(T&& value) {
        if (size_ >= capacity_) {
            reserve(capacity_ == 0 ? 1 : 2 * capacity_);
        }
        data_[size_++] = std::move(value);
    }

    void pop_back() {
        if (size_ > 0) {
            --size_;
        }
    }

    void insert(size_t pos, const T& value) {
        if (pos > size_) throw std::out_of_range("Vector::insert");
        if (size_ >= capacity_) reserve(capacity_ == 0 ? 1 : 2 * capacity_);
        
        for (size_t i = size_; i > pos; --i) {
            data_[i] = std::move(data_[i-1]);
        }
        data_[pos] = value;
        ++size_;
    }

    void erase(size_t pos) {
        if (pos >= size_) throw std::out_of_range("Vector::erase");
        for (size_t i = pos; i < size_-1; ++i) {
            data_[i] = std::move(data_[i+1]);
        }
        --size_;
    }

    void resize(size_t count) {
        if (count > capacity_) reserve(count);
        size_ = count;
    }

    size_t max_size() const override {
        return capacity_;
    }

    void swap(Vector& other) noexcept {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }


    T* begin() override {
        return data_;
    }

    const T* begin() const override {
        return data_;
    }

    const T* cbegin() const override {
        return data_;
    }

    T* end() override {
        return data_ + size_;
    }

    const T* end() const override {
        return data_ + size_;
    }

    const T* cend() const override {
        return data_ + size_;
    }

    bool operator==(const Container<T, N>& other) const override {
        const Vector* o = dynamic_cast<const Vector*>(&other);
        if (!o || size_ != o->size_) return false;
        for (size_t i = 0; i < size_; ++i) {
            if (data_[i] != o->data_[i]) return false;
        }
        return true;
    }

    bool operator!=(const Container<T, N>& other) const override {
        return !(*this == other);
    }

    auto operator<=>(const Vector& other) const {
        size_t min_size = std::min(size_, other.size_);
        for (size_t i = 0; i < min_size; ++i) {
            if (data_[i] != other.data_[i]) {
                return data_[i] <=> other.data_[i];
            }
        }
        return size_ <=> other.size_;
    }
};

}