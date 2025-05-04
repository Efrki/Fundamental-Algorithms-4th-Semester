#include <iostream>
#include "../include/deque.hpp"

using namespace my_container;

int main() {
    try {
        // Создание дека с максимальным размером 5
        Deque<int, 5> dq;

        // Добавление элементов в конец
        dq.push_back(10);
        dq.push_back(20);
        dq.push_back(30);

        // Добавление элементов в начало
        dq.push_front(5);
        dq.push_front(1);

        // Вывод информации
        std::cout << "Размер дека: " << dq.size() 
                  << "\nПервый элемент: " << dq.front() 
                  << "\nПоследний элемент: " << dq.back() 
                  << "\nЭлемент [2]: " << dq[2] 
                  << "\nЭлемент at(3): " << dq.at(3) 
                  << std::endl;

        // Попытка добавить элемент в заполненный дек
        // dq.push_back(100); // Выбросит std::length_error

        // Удаление элементов
        dq.pop_front();
        dq.pop_back();
        std::cout << "\nПосле удаления:"
                  << "\nРазмер: " << dq.size() 
                  << "\nНовый первый элемент: " << dq.front() 
                  << "\nНовый последний элемент: " << dq.back() 
                  << std::endl;

        // Доступ к несуществующему индексу
        // std::cout << dq.at(10); // Выбросит std::out_of_range

        // Обход элементов через итераторы
        std::cout << "\nЭлементы дека: ";
        for (auto it = dq.begin(); it != dq.end(); it = dq.next(it)) {
            std::cout << *it << " ";
        }

    } catch (const std::exception& e) {
        std::cerr << "\nОшибка: " << e.what() << std::endl;
    }

    return 0;
}