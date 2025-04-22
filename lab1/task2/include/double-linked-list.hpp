#pragma once
#include "../../task1/include/container.hpp"
#include <initializer_list>
#include <stdexcept>
#include <iterator>
#include <limits>
#include <algorithm>

namespace my_container {

template <typename T>
class List : public Container<T> {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        
        Node(const T& d, Node* p = nullptr, Node* n = nullptr)
            : data(d), prev(p), next(n) {}
    };

    Node* head = nullptr;
    Node* tail = nullptr;
    size_t list_size = 0;

public:
    // Итераторы
    class iterator {
        Node* ptr;
    public:
        friend class List<T>;

        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        iterator(Node* p = nullptr) : ptr(p) {}
        reference operator*() const { return ptr->data; }
        pointer operator->() const { return &ptr->data; }
        iterator& operator++() { ptr = ptr->next; return *this; }
        iterator operator++(int) { auto tmp = *this; ++*this; return tmp; }
        iterator& operator--() { ptr = ptr->prev; return *this; }
        iterator operator--(int) { auto tmp = *this; --*this; return tmp; }
        bool operator==(const iterator& other) const { return ptr == other.ptr; }
        bool operator!=(const iterator& other) const { return ptr != other.ptr; }
    };

    class const_iterator {
        const Node* ptr;
    public:
        friend class List<T>;

        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = const T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;

        const_iterator(const Node* p = nullptr) : ptr(p) {}
        reference operator*() const { return ptr->data; }
        pointer operator->() const { return &ptr->data; }
        const_iterator& operator++() { ptr = ptr->next; return *this; }
        const_iterator operator++(int) { auto tmp = *this; ++*this; return tmp; }
        const_iterator& operator--() { ptr = ptr->prev; return *this; }
        const_iterator operator--(int) { auto tmp = *this; --*this; return tmp; }
        bool operator==(const const_iterator& other) const { return ptr == other.ptr; }
        bool operator!=(const const_iterator& other) const { return ptr != other.ptr; }
    };

    // Конструкторы
    List() = default;
    
    List(std::initializer_list<T> init) {
        for (const auto& item : init) push_back(item);
    }
    
    List(const List& other) {
        for (const auto& item : other) push_back(item);
    }
    
    List(List&& other) noexcept 
        : head(other.head), tail(other.tail), list_size(other.list_size) {
        other.head = other.tail = nullptr;
        other.list_size = 0;
    }

    ~List() override { clear(); }

    // Операторы присваивания
    List& operator=(const List& other) {
        if (this != &other) {
            List temp(other);
            swap(temp);
        }
        return *this;
    }

    List& operator=(List&& other) noexcept {
        swap(other);
        return *this;
    }

    Container<T>& operator=(const Container<T>& other) override {
        const List* ptr = dynamic_cast<const List*>(&other);
        if (!ptr) throw std::bad_cast();
        return *this = *ptr;
    }

    // Виртуальные методы Container
    T* begin() override { return empty() ? nullptr : &head->data; }
    const T* begin() const override { return empty() ? nullptr : &head->data; }
    const T* cbegin() const override { return begin(); }
    T* end() override { return nullptr; }
    const T* end() const override { return nullptr; }
    const T* cend() const override { return nullptr; }

    bool operator==(const Container<T>& other) const override {
        const List* ptr = dynamic_cast<const List*>(&other);
        if (!ptr || size() != ptr->size()) return false;
        return std::equal(begin(), end(), ptr->begin());
    }

    bool operator!=(const Container<T>& other) const override {
        return !(*this == other);
    }

    bool empty() const override { return list_size == 0; }
    size_t size() const override { return list_size; }
    size_t max_size() const override { 
        return std::numeric_limits<size_t>::max() / sizeof(Node);
    }

    void clear() override {
        while (!empty()) pop_front();
    }

    // Доступ к элементам
    T& front() {
        if (empty()) throw std::out_of_range("List is empty");
        return head->data;
    }

    const T& front() const {
        if (empty()) throw std::out_of_range("List is empty");
        return head->data;
    }

    T& back() {
        if (empty()) throw std::out_of_range("List is empty");
        return tail->data;
    }

    const T& back() const {
        if (empty()) throw std::out_of_range("List is empty");
        return tail->data;
    }

    // Модификаторы
    void push_back(const T& value) {
        Node* new_node = new Node(value, tail, nullptr);
        if (tail) tail->next = new_node;
        else head = new_node;
        tail = new_node;
        ++list_size;
    }

    void push_front(const T& value) {
        Node* new_node = new Node(value, nullptr, head);
        if (head) head->prev = new_node;
        else tail = new_node;
        head = new_node;
        ++list_size;
    }

    void pop_back() {
        if (empty()) throw std::out_of_range("List is empty");
        Node* to_delete = tail;
        tail = tail->prev;
        if (tail) tail->next = nullptr;
        else head = nullptr;
        delete to_delete;
        --list_size;
    }

    void pop_front() {
        if (empty()) throw std::out_of_range("List is empty");
        Node* to_delete = head;
        head = head->next;
        if (head) head->prev = nullptr;
        else tail = nullptr;
        delete to_delete;
        --list_size;
    }

    iterator insert(iterator pos, const T& value) {
        if (pos == end()) {
            push_back(value);
            return iterator(tail);
        }
        if (pos == begin()) {
            push_front(value);
            return begin();
        }
        
        Node* current = pos.ptr;
        Node* new_node = new Node(value, current->prev, current);
        current->prev->next = new_node;
        current->prev = new_node;
        ++list_size;
        return iterator(new_node);
    }

    iterator erase(iterator pos) {
        if (pos == end()) return pos;
        
        Node* to_delete = pos.ptr;
        Node* next_node = to_delete->next;
        
        if (to_delete->prev) 
            to_delete->prev->next = next_node;
        else 
            head = next_node;
        
        if (next_node) 
            next_node->prev = to_delete->prev;
        else 
            tail = to_delete->prev;
        
        delete to_delete;
        --list_size;
        return iterator(next_node);
    }

    void resize(size_t new_size, const T& value = T()) {
        while (list_size > new_size) pop_back();
        while (list_size < new_size) push_back(value);
    }

    void swap(List& other) noexcept {
        std::swap(head, other.head);
        std::swap(tail, other.tail);
        std::swap(list_size, other.list_size);
    }

    // Собственные итераторы
    iterator begin() noexcept { return iterator(head); }
    const_iterator begin() const noexcept { return const_iterator(head); }
    iterator end() noexcept { return iterator(nullptr); }
    const_iterator end() const noexcept { return const_iterator(nullptr); }
};

} // namespace my_container