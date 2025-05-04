#include <iostream>
#include "../include/stack.hpp"
#include "../../task3/include/deque.hpp"

using namespace my_container;

int main() {
    try {
        // 1. Создание стека с использованием List<int, 5> по умолчанию
        Stack<int, List, 5> stack;

        // Добавление элементов
        stack.push(10);
        stack.push(20);
        stack.push(30);

        // Вывод информации
        std::cout << "Верхний элемент: " << stack.top() << std::endl;
        std::cout << "Размер стека: " << stack.size() << std::endl;

        // 2. Удаление элементов
        stack.pop();
        std::cout << "\nПосле удаления:\n";
        std::cout << "Верхний элемент: " << stack.top() << std::endl;
        std::cout << "Размер стека: " << stack.size() << std::endl;

        // 3. Попытка переполнения
        stack.push(40);
        stack.push(50);
        stack.push(60); // Выбросит исключение

    } catch (const std::exception& e) {
        std::cerr << "\nОшибка: " << e.what() << std::endl;
    }

    try {
        // 4. Работа с пустым стеком
        Stack<int> empty_stack;
        empty_stack.pop(); // Выбросит исключение

    } catch (const std::exception& e) {
        std::cerr << "\nОшибка: " << e.what() << std::endl;
    }

    // 5. Использование Deque как базового контейнера
    try {
        Stack<int, Deque, 3> deque_stack;
        deque_stack.push(100);
        deque_stack.push(200);
        std::cout << "\nСтек на Deque:\n";
        std::cout << "Верхний элемент: " << deque_stack.top() << std::endl;
        deque_stack.push(300);
        deque_stack.push(400); // Выбросит исключение

    } catch (const std::exception& e) {
        std::cerr << "\nОшибка: " << e.what() << std::endl;
    }

    return 0;
}