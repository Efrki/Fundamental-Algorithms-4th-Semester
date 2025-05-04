#include <iostream>
#include "../include/double-linked-list.hpp" // Путь к вашему заголовочному файлу

using namespace my_container;

int main() {
    try {
        // Создание списка с максимальным размером 5
        List<int, 5> myList;

        // Добавление элементов
        myList.push_back(10);
        myList.push_front(5);
        myList.push_back(20);

        // Вывод информации
        std::cout << "Размер списка: " << myList.size() << std::endl;
        std::cout << "Первый элемент: " << myList.front() << std::endl;
        std::cout << "Последний элемент: " << myList.back() << std::endl;

        // Вставка элемента
        auto pos = myList.begin();
        pos = myList.next(pos); // Переход ко второму элементу
        myList.insert(pos, 15);

        // Вывод всех элементов через итераторы
        std::cout << "Элементы списка: ";
        for (auto it = myList.begin(); it != myList.end(); it = myList.next(it)) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;

        // Удаление элемента
        pos = myList.next(myList.begin());
        myList.erase(pos);

        // Проверка после удаления
        std::cout << "Элементы после удаления: ";
        for (auto it = myList.begin(); it != myList.end(); it = myList.next(it)) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;

        // Создание второго списка и сравнение
        List<int, 5> myList2 = {5, 10, 20};
        std::cout << "Списки равны? " << (myList == myList2 ? "Да" : "Нет") << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    return 0;
}