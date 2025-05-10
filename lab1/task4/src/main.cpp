#include <iostream>
#include "../include/stack.hpp"
#include "../../task3/include/deque.hpp"

using namespace my_container;

int main() {
    try {
        Stack<int, List, 5> stack;

        stack.push(10);
        stack.push(20);
        stack.push(30);

        std::cout << "Верхний элемент: " << stack.top() << std::endl;
        std::cout << "Размер стека: " << stack.size() << std::endl;

        stack.pop();
        std::cout << "\nПосле удаления:\n";
        std::cout << "Верхний элемент: " << stack.top() << std::endl;
        std::cout << "Размер стека: " << stack.size() << std::endl;

        stack.push(40);
        stack.push(50);
        stack.push(60);
    

    } catch (const std::exception& e) {
        std::cerr << "\nОшибка: " << e.what() << std::endl;
    }

    try {
        Stack<int> empty_stack;
        empty_stack.pop();

    } catch (const std::exception& e) {
        std::cerr << "\nОшибка: " << e.what() << std::endl;
    }

    try {
        Stack<int, Deque, 3> deque_stack;
        deque_stack.push(100);
        deque_stack.push(200);
        std::cout << "\nСтек на Deque:\n";
        std::cout << "Верхний элемент: " << deque_stack.top() << std::endl;
        deque_stack.push(300);
        deque_stack.push(400);

    } catch (const std::exception& e) {
        std::cerr << "\nОшибка: " << e.what() << std::endl;
    }

    return 0;
}