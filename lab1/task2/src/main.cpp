#include <iostream>
#include "../include/double-linked-list.hpp"

using namespace my_container;

int main() {
    try {
        List<int, 5> myList;

        myList.push_back(10);
        myList.push_front(5);
        myList.push_back(20);

        std::cout << "Размер списка: " << myList.size() << std::endl;
        std::cout << "Первый элемент: " << myList.front() << std::endl;
        std::cout << "Последний элемент: " << myList.back() << std::endl;

        auto pos = myList.begin();
        pos = myList.next(pos);
        myList.insert(pos, 15);

        std::cout << "Элементы списка: ";
        for (auto it = myList.begin(); it != myList.end(); it = myList.next(it)) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;

        pos = myList.next(myList.begin());
        myList.erase(pos);

        std::cout << "Элементы после удаления: ";
        for (auto it = myList.begin(); it != myList.end(); it = myList.next(it)) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;

        List<int, 5> myList2 = {5, 10, 20};
        std::cout << "Списки равны? " << (myList == myList2 ? "Да" : "Нет") << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    return 0;
}