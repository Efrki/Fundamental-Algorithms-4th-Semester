#include <iostream>
#include "../include/deque.hpp"

using namespace my_container;

int main() {
    try {
        Deque<int, 5> dq;

        dq.push_back(10);
        dq.push_back(20);
        dq.push_back(30);

        dq.push_front(5);
        dq.push_front(1);

        std::cout << "Размер дека: " << dq.size() 
                  << "\nПервый элемент: " << dq.front() 
                  << "\nПоследний элемент: " << dq.back() 
                  << "\nЭлемент [2]: " << dq[2] 
                  << "\nЭлемент at(3): " << dq.at(3) 
                  << std::endl;


        dq.pop_front();
        dq.pop_back();
        std::cout << "\nПосле удаления:"
                  << "\nРазмер: " << dq.size() 
                  << "\nНовый первый элемент: " << dq.front() 
                  << "\nНовый последний элемент: " << dq.back() 
                  << std::endl;


        std::cout << "\nЭлементы дека: ";
        for (auto it = dq.begin(); it != dq.end(); it = dq.next(it)) {
            std::cout << *it << " ";
        }

    } catch (const std::exception& e) {
        std::cerr << "\nОшибка: " << e.what() << std::endl;
    }

    return 0;
}