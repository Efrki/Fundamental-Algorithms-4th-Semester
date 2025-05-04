#pragma once
#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <algorithm>
#include "../../task1/include/container.hpp"

namespace my_container {

template <typename T, size_t N>
class List : public Container<T, N> {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;
        Node(const T& val = T(), Node* n = nullptr, Node* p = nullptr)
            : data(val), next(n), prev(p) {}
    };

    Node* head;
    Node* tail;
    size_t current_size;

public:
    // Конструкторы
    List() : head(nullptr), tail(nullptr), current_size(0) {}

    List(const List& other) : List() {
        for (Node* curr = other.head; curr != nullptr; curr = curr->next) {
            push_back(curr->data);
        }
    }

    List(List&& other) noexcept 
        : head(other.head), tail(other.tail), current_size(other.current_size) {
        other.head = nullptr;
        other.tail = nullptr;
        other.current_size = 0;
    }

    List(std::initializer_list<T> init) : List() {
        for (const auto& item : init) {
            push_back(item);
        }
    }

    // Деструктор
    ~List() {
        clear();
    }

    // Операторы присваивания
    List& operator=(const List& other) {
        if (this != &other) {
            clear();
            for (Node* curr = other.head; curr != nullptr; curr = curr->next) {
                push_back(curr->data);
            }
        }
        return *this;
    }
    List& operator=(const Container<T, N>& other) override {
        // Проверка на самоприсваивание через базовый класс
        if (this == &other) return *this;
    
        // Динамическое приведение типа для безопасности
        const List* other_list = dynamic_cast<const List*>(&other);
        if (!other_list) {
            throw std::invalid_argument("Container type mismatch in assignment");
        }
    
        // Очистка текущих данных
        clear();
    
        // Копирование элементов из other_list
        for (const Node* curr = other_list->head; curr != nullptr; curr = curr->next) {
            push_back(curr->data);
        }
    
        return *this;
    }

    List& operator=(List&& other) noexcept {
        if (this != &other) {
            clear();
            head = other.head;
            tail = other.tail;
            current_size = other.current_size;
            other.head = nullptr;
            other.tail = nullptr;
            other.current_size = 0;
        }
        return *this;
    }

    // Методы доступа
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

    // Итераторы (возвращают указатели на данные)
    T* begin() override { 
        return head ? &head->data : nullptr; 
    }

    const T* begin() const override { 
        return head ? &head->data : nullptr; 
    }

    const T* cbegin() const override { 
        return begin(); 
    }

    T* end() override { 
        return nullptr; 
    }

    const T* end() const override { 
        return nullptr; 
    }

    const T* cend() const override { 
        return end(); 
    }
    T* next(T* current) const {
        if (!current) return nullptr;
        Node* node = reinterpret_cast<Node*>(reinterpret_cast<char*>(current) - offsetof(Node, data));
        return node->next ? &node->next->data : nullptr;
    }

    T* rbegin()  { return tail ? &tail->data : nullptr; }
    const T* rbegin() const  { return tail ? &tail->data : nullptr; }
    const T* crbegin() const  { return tail ? &tail->data : nullptr; }
    T* rend()  { return nullptr; }
    const T* rend() const  { return nullptr; }
    const T* crend() const  { return nullptr; }
    T* prev(T* current) const {
        if (!current) return nullptr;
        Node* node = reinterpret_cast<Node*>(reinterpret_cast<char*>(current) - offsetof(Node, data));
        return node->prev ? &node->prev->data : nullptr;
    }
    // Ёмкость
    Node* getNodeFromDataPtr(T* dataPtr) const {
        if (!dataPtr) return nullptr;
        return reinterpret_cast<Node*>(reinterpret_cast<char*>(dataPtr) - offsetof(Node, data));
    }

    bool empty() const override { return current_size == 0; }
    size_t size() const override { return current_size; }
    size_t max_size() const override { return N; }

    // Модификаторы
    void clear() {
        while (!empty()) {
            pop_front();
        }
    }

    void push_back(const T& value) {
        if (current_size >= N) throw std::length_error("List max size exceeded");
        Node* newNode = new Node(value, nullptr, tail);
        if (tail) {
            tail->next = newNode;
        } else {
            head = newNode;
        }
        tail = newNode;
        ++current_size;
    }

    void pop_back() {
        if (empty()) return;
        Node* temp = tail;
        tail = tail->prev;
        if (tail) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }
        delete temp;
        --current_size;
    }

    void push_front(const T& value) {
        if (current_size >= N) throw std::length_error("List max size exceeded");
        Node* newNode = new Node(value, head, nullptr);
        if (head) {
            head->prev = newNode;
        } else {
            tail = newNode;
        }
        head = newNode;
        ++current_size;
    }

    void pop_front() {
        if (empty()) return;
        Node* temp = head;
        head = head->next;
        if (head) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
        delete temp;
        --current_size;
    }

    T* insert(T* pos, const T& value) {
        if (current_size >= N) throw std::length_error("List max size exceeded");
        if (pos == nullptr) {
            push_back(value);
            return &tail->data;
        }
        Node* target = getNodeFromDataPtr(pos);
        Node* newNode = new Node(value, target, target->prev);
        if (target->prev) {
            target->prev->next = newNode;
        } else {
            head = newNode;
        }
        target->prev = newNode;
        ++current_size;
        return &newNode->data;
    }

    T* erase(T* pos) {
        if (pos == nullptr) return nullptr;
        Node* target = getNodeFromDataPtr(pos);
        Node* nextNode = target->next;
        if (target->prev) {
            target->prev->next = nextNode;
        } else {
            head = nextNode;
        }
        if (target == tail) {
            tail = target->prev;
        }
        if (nextNode) nextNode->prev = target->prev;
        delete target;
        --current_size;
        return nextNode ? &nextNode->data : nullptr;
    }

    void resize(size_t count) {
        if (count > N) throw std::length_error("Resize exceeds max size");
        while (current_size > count) pop_back();
        while (current_size < count) push_back(T());
    }

    void swap(List& other) noexcept {
        std::swap(head, other.head);
        std::swap(tail, other.tail);
        std::swap(current_size, other.current_size);
    }

    // Операторы сравнения
    bool operator==(const Container<T, N>& other) const override {
        const List& otherList = static_cast<const List&>(other);
        if (size() != otherList.size()) return false;
        const Node* curr1 = head;
        const Node* curr2 = otherList.head;
        while (curr1 && curr2) {
            if (curr1->data != curr2->data) return false;
            curr1 = curr1->next;
            curr2 = curr2->next;
        }
        return true;
    }

    bool operator!=(const Container<T, N>& other) const override {
        return !(*this == other);
    }

    bool operator<(const List& other) const {
        const Node* curr1 = head;
        const Node* curr2 = other.head;
        while (curr1 && curr2) {
            if (curr1->data < curr2->data) return true;
            if (curr2->data < curr1->data) return false;
            curr1 = curr1->next;
            curr2 = curr2->next;
        }
        return curr2 != nullptr;
    }

    bool operator<=(const List& other) const {
        return !(other < *this);
    }

    bool operator>(const List& other) const {
        return other < *this;
    }

    bool operator>=(const List& other) const {
        return !(*this < other);
    }

    // Для C++20 можно добавить operator<=>
    auto operator<=>(const List& other) const {
        const Node* curr1 = head;
        const Node* curr2 = other.head;
        while (curr1 && curr2) {
            if (auto cmp = curr1->data <=> curr2->data; cmp != 0) return cmp;
            curr1 = curr1->next;
            curr2 = curr2->next;
        }
        return curr1 ? std::strong_ordering::greater :
               curr2 ? std::strong_ordering::less :
               std::strong_ordering::equal;
    }
};

} // namespace my_container