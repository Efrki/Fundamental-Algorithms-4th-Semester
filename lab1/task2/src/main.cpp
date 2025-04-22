#include <iostream>
#include "double-linked-list.hpp"

int main() {
    using namespace my_container;

    // Создание и инициализация списка
    List<int> my_list = {10, 20, 30};
    
    // Вставка элемента через собственный итератор
    auto it = my_list.list_begin();
    ++it; // Переход ко второму элементу
    my_list.insert(it, 15);
    
    // Вывод списка
    std::cout << "List after insertion: ";
    for (auto it = my_list.list_begin(); it != my_list.list_end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";
    
    // Удаление элемента
    it = my_list.list_begin();
    ++it;
    my_list.erase(it);
    
    // Вывод после удаления
    std::cout << "List after deletion: ";
    for (auto it = my_list.list_begin(); it != my_list.list_end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";
    
    // Тестирование граничных случаев
    my_list.push_front(5);
    my_list.push_back(40);
    
    std::cout << "Final list: ";
    for (const auto& num : my_list) {
        std::cout << num << " "; // Используем range-based for из Container
    }
    
    return 0;
}