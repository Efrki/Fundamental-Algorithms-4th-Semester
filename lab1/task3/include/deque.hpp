#pragma once
#include "../../task2/include/double-linked-list.hpp"

namespace my_container {

    template <typename T, size_t N>
    class Deque : public List<T, N> {
    public:
        // Конструкторы
        Deque() = default;
        Deque(const Deque& other) : List<T, N>(other) {}
        Deque(Deque&& other) noexcept : List<T, N>(std::move(other)) {}
        Deque(std::initializer_list<T> init) : List<T, N>(init) {}
    
        // Операторы присваивания
        Deque& operator=(const Deque& other) {
            List<T, N>::operator=(other);
            return *this;
        }
        
        Deque& operator=(Deque&& other) noexcept {
            List<T, N>::operator=(std::move(other));
            return *this;
        }
    
        // Методы доступа с проверкой индекса
        T& at(size_t pos) {
            return const_cast<T&>(static_cast<const Deque*>(this)->at(pos));
        }
    
        const T& at(size_t pos) const {
            if (pos >= this->size()) throw std::out_of_range("Deque index out of range");
            return *get_iterator_at(pos);
        }
    
        T& operator[](size_t pos) {
            return const_cast<T&>(static_cast<const Deque*>(this)->operator[](pos));
        }
    
        const T& operator[](size_t pos) const {
            return *get_iterator_at(pos);
        }
    
    private:
        // Вспомогательный метод для доступа по индексу (константная версия)
        const T* get_iterator_at(size_t pos) const {
            if (pos >= this->size()) return nullptr;
            const T* it = this->begin();
            for (size_t i = 0; i < pos; ++i) {
                // Используем const_cast для вызова неконстантного next()
                it = this->next(const_cast<T*>(it));
            }
            return it;
        }
    
    public:
        // Переопределение методов List
        using List<T, N>::front;
        using List<T, N>::back;
        using List<T, N>::begin;
        using List<T, N>::end;
        using List<T, N>::rbegin;
        using List<T, N>::rend;
        using List<T, N>::empty;
        using List<T, N>::size;
        using List<T, N>::max_size;
        using List<T, N>::clear;
        using List<T, N>::insert;
        using List<T, N>::erase;
        using List<T, N>::push_back;
        using List<T, N>::pop_back;
        using List<T, N>::push_front;
        using List<T, N>::pop_front;
        using List<T, N>::resize;
        using List<T, N>::swap;
    
        // Операторы сравнения
        bool operator==(const Deque& other) const {
            return List<T, N>::operator==(other);
        }
    
        auto operator<=>(const Deque& other) const {
            return List<T, N>::operator<=>(other);
        }
    };
    
    } // namespace my_container