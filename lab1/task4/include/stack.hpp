#pragma once
#include "../../task2/include/double-linked-list.hpp"
#include <stdexcept>
#include <initializer_list>
#include <utility>
#include <concepts>

namespace my_container {

template <typename C, typename T, size_t N>
concept StackContainer = requires (C c, T value) {
    { c.push_back(value) } -> std::same_as<void>;
    { c.pop_back() } -> std::same_as<void>;
    { c.back() } -> std::convertible_to<T&>;
    { static_cast<const C&>(c).back() } -> std::convertible_to<const T&>;
    { c.empty() } -> std::same_as<bool>;
    { c.size() } -> std::same_as<size_t>;
    { c.max_size() } -> std::same_as<size_t>;
    { c.swap(c) } -> std::same_as<void>;
};

template <typename T, template <typename, size_t> class Container = List, size_t N = 100> 
requires StackContainer<Container<T, N>, T, N>
class Stack {
private:
    Container<T, N> c;

public:
    Stack() = default;

    Stack(const Stack& other) : c(other.c) {}

    Stack(Stack&& other) noexcept : c(std::move(other.c)) {}

    Stack(std::initializer_list<T> init) {
        for (const auto& item : init) push(item);
    }

    Stack& operator=(const Stack& other) {
        if (this != &other) c = other.c;
        return *this;
    }

    Stack& operator=(Stack&& other) noexcept {
        c = std::move(other.c);        
        return *this;
    }

    T& top() {
        if (empty()) throw std::out_of_range("Stack is empty");
        return c.back();
    }

    const T& top() const {
        if (empty()) throw std::out_of_range("Stack is empty");
        return c.back();
    }

    bool empty() const noexcept { return c.empty(); }
    size_t size() const noexcept { return c.size(); }
    size_t max_size() const noexcept { return c.max_size(); }

    void push(const T& value) { 
        if (size() >= max_size()) throw std::length_error("Stack overflow");
        c.push_back(value); 
    }

    void push(T&& value) { 
        if (size() >= max_size()) throw std::length_error("Stack overflow");
        c.push_back(std::move(value)); 
    }

    void pop() { 
        if (empty()) throw std::out_of_range("Stack underflow");
        c.pop_back(); 
    }

    void swap(Stack& other) noexcept { c.swap(other.c); }

    bool operator==(const Stack& other) const { return c == other.c; }
    bool operator!=(const Stack& other) const { return c != other.c; }
    bool operator<(const Stack& other) const { return c < other.c; }
    bool operator<=(const Stack& other) const { return c <= other.c; }
    bool operator>(const Stack& other) const { return c > other.c; }
    bool operator>=(const Stack& other) const { return c >= other.c; }

    auto operator<=>(const Stack& other) const { return c <=> other.c; }
};

}