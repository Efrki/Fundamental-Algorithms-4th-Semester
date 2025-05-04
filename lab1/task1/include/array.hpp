// #pragma once

// #include <algorithm>
// #include <cstddef>
// #include <stdexcept>

// #include "container.hpp"

// namespace my_container {

// template <typename T, size_t N>
// class Array final : public Container<T, N> {
//    private:
// 	T* data_;
// 	size_t size_;

//    public:
// 	using value_type = T;
// 	using pointer = T*;
// 	using const_pointer = const T*;
// 	using reference = value_type&;
// 	using const_reference = const value_type&;

// 	using iterator = value_type*;
// 	using const_iterator = const value_type*;

// 	using size_type = std::size_t;
// 	using difference_type = std::ptrdiff_t;

// 	using reverse_iterator = std::reverse_iterator<iterator>;
// 	using const_reverse_iterator = std::reverse_iterator<const_iterator>;

// 	Array() : data_(nullptr), size_(0) {}
// 	explicit Array(size_t size) : data_(new T[size]), size_(size) {}
// 	Array(size_t size, const T& value) : size_(size) { std::fill(data_, data_ + size, value); }
// 	Array(const Array& other) : size_(other.size_), data_(new T[other.size_]) {
// 		std::copy(other.data_, other.data_ + other.size_, data_);
// 	}
	
// 	~Array() override { delete[] data_; }

// 	Array& operator=(const Container<T, N>& other) override {
// 		const Array* otherArray = dynamic_cast<const Array*>(&other);
// 		if (this != otherArray) {
// 			delete[] data_;
// 			size_ = otherArray->size_;
// 			data_ = new T[size_];
// 			std::copy(otherArray->data_, otherArray->data_ + size_, data_);
// 		}
// 		return *this;
// 	}

// 	iterator begin() override { return data_; }
// 	const_iterator begin() const override { return data_; }
// 	const_iterator cbegin() const override { return data_; }
// 	iterator end() override { return data_ + size_; }
// 	const_iterator end() const override { return data_ + size_; }
// 	const_iterator cend() const override { return data_ + size_; }
// 	reverse_iterator rbegin() { return reverse_iterator(end()); }
// 	const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
// 	const_reverse_iterator crbegin() const { return const_reverse_iterator(end()); }
// 	reverse_iterator rend() { return reverse_iterator(begin()); }
// 	const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }
// 	const_reverse_iterator crend() const { return const_reverse_iterator(begin()); }

// 	constexpr size_type size() const override { return N; }
// 	constexpr size_type max_size() const override { return N; }
// 	bool empty() const override { return size_ == 0; }

// 	T& operator[](size_t index) {
// 		if (index >= size_) {
// 			throw std::out_of_range("Index out of range");
// 		}
// 		return data_[index];
// 	}

// 	const T& operator[](size_t index) const {
// 		if (index >= size_) {
// 			throw std::out_of_range("Index out of range");
// 		}
// 		return data_[index];
// 	}

// 	void fill(const T& value) { std::fill_n(data_, data_ + size_, value); }
// 	reference at(size_type pos) {
// 		if (pos > N) {
// 			throw std::out_of_range("Index out of range");
// 		}
// 		return data_[pos];
// 	}

//     void swap(Array& other) { std::swap_ranges(begin(), end(), other.begin()); }

// 	const_reference at(size_type pos) const {
// 		if (pos > N) {
// 			throw std::out_of_range("Index out of range");
// 		}
// 		return data_[pos];
// 	}

// 	reference front() { return *begin(); }
// 	const_reference front() const { return *begin(); }
// 	reference back() { return N ? *(end() - 1) : *end(); }
// 	const_reference back() const { return N ? *(end() - 1) : *end(); }

// 	T* data() { return std::addressof(data_[0]); }
// 	const T* data() const { return std::addressof(data_[0]); }

//     inline bool operator==(const Container<T, N>& other) const override {
//         const Array<T, N>* other_array = dynamic_cast<const Array<T, N>*>(&other);
//         if (other_array == nullptr) return false;
//         return *this == *other_array;
//     }

//     inline bool operator!=(const Container<T, N>& other) const override {
//         return !(*this == other);
//     }
    // inline bool operator<(const Array& other){
    //     return std::lexicographical_compare(this->begin(), this->end(), other.begin(), other.end());
    // }
    // inline bool operator>(const Array& other){
    //     return other < *this;
    // }
    // inline bool operator<=(const Array& other){
    //     return !(other < *this);
    // }
    // inline bool operator>=(const Array& other){
    //     return !(*this < other);
    // }
    // auto operator<=>(const Array& other) const {
    //     return std::lexicographical_compare_three_way(this->begin(), this->end(), other.begin(), other.end());
    // }
// 	Array(const std::initializer_list<T> initList) : Container<T, N>() {
// 		this->size_ = N;
// 		std::copy(initList.begin(), initList.end(), this->data_);
// 		for (size_t i = initList.size(); i < N; i++)
// 		{
// 			data_[i] = 0;
// 		}
		
// 	}
	
	
// };

// }  // namespace my_container

#pragma once
#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include "container.hpp"

namespace my_container {

template <typename T, size_t N>
class Array final : public Container<T, N> {
private:
    T* data_;

public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = value_type&;
    using const_reference = const value_type&;
    using iterator = value_type*;
    using const_iterator = const value_type*;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    Array() : data_(new T[N]{}) {}
    explicit Array(const T& value) : data_(new T[N]) {
        std::fill(data_, data_ + N, value);
    }
    Array(const Array& other) : data_(new T[N]) {
        std::copy(other.data_, other.data_ + N, data_);
    }
    Array(const std::initializer_list<T>& initList) : data_(new T[N]) {
        size_t i = 0;
        for (const auto& item : initList) {
            if (i >= N) break;
            data_[i++] = item;
        }
        for (; i < N; ++i) data_[i] = T{};
    }
	Array(size_t size, const T& value) : data_(new T[N]) {
		if (size > N) throw std::invalid_argument("Size exceeds capacity");
		std::fill(data_, data_ + size, value);
		std::fill(data_ + size, data_ + N, T{});
	}
	

    ~Array() override { delete[] data_; }

    Array& operator=(const Container<T, N>& other) override {
		const Array* otherArray = dynamic_cast<const Array*>(&other);
		if (otherArray) return *this = *otherArray;
		return *this;
	}
	
    Array& operator=(const Array& other) {
        if (this != &other) {
            std::copy(other.data_, other.data_ + N, data_);
        }
        return *this;
    }

    iterator begin() override { return data_; }
    const_iterator begin() const override { return data_; }
    const_iterator cbegin() const override { return data_; }
    iterator end() override { return data_ + N; }
    const_iterator end() const override { return data_ + N; }
    const_iterator cend() const override { return data_ + N; }

    reverse_iterator rbegin() { return reverse_iterator(end()); }
    const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
    reverse_iterator rend() { return reverse_iterator(begin()); }
    const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }
	const_reverse_iterator crbegin() const { return const_reverse_iterator(end()); }
	const_reverse_iterator crend() const { return const_reverse_iterator(begin()); }

    constexpr size_type size() const override { return N; }
    constexpr size_type max_size() const override { return N; }
    bool empty() const override { return N == 0; }

    T& operator[](size_t index) {
        if (index >= N) throw std::out_of_range("Index out of range");
        return data_[index];
    }

    const T& operator[](size_t index) const {
        if (index >= N) throw std::out_of_range("Index out of range");
        return data_[index];
    }

    void fill(const T& value) { std::fill_n(data_, N, value); }

    reference at(size_type pos) {
        if (pos >= N) throw std::out_of_range("Index out of range");
        return data_[pos];
    }

    const_reference at(size_type pos) const {
        if (pos >= N) throw std::out_of_range("Index out of range");
        return data_[pos];
    }

    void swap(Array& other) { std::swap_ranges(data_, data_ + N, other.data_); }

    reference front() { 
		if (N == 0) throw std::out_of_range("Array is empty");
		return *data_; }
    const_reference front() const { 
		if (N == 0) throw std::out_of_range("Array is empty");
		return *data_; }
	reference back() { 
		if (N == 0) throw std::out_of_range("Array is empty");
		return data_[N - 1]; 
	}
	const_reference back() const { 
		if (N == 0) throw std::out_of_range("Array is empty");
		return data_[N - 1]; 
	}

    T* data() { return data_; }
    const T* data() const { return data_; }

    bool operator==(const Container<T, N>& other) const override {
        const Array* otherArray = dynamic_cast<const Array*>(&other);
        if (!otherArray) return false;
        return std::equal(data_, data_ + N, otherArray->data_);
    }

    bool operator!=(const Container<T, N>& other) const override {
        return !(*this == other);
    }

	inline bool operator<(const Array& other){
        return std::lexicographical_compare(this->begin(), this->end(), other.begin(), other.end());
    }

    inline bool operator>(const Array& other){
        return other < *this;
    }

    inline bool operator<=(const Array& other){
        return !(other < *this);
    }

    inline bool operator>=(const Array& other){
        return !(*this < other);
    }
    
    auto operator<=>(const Array& other) const {
        return std::lexicographical_compare_three_way(this->begin(), this->end(), other.begin(), other.end());
    }
};

} // namespace my_container
