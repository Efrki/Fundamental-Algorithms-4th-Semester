#include <iostream>
#include "../include/vector.hpp" // Предполагается, что ваш класс Vector находится в этом файле

using namespace my_container;

int main() {
    // Тестирование конструкторов
    Vector<int> v1; // Конструктор по умолчанию
    Vector<int> v2(5); // Конструктор с размером
    Vector<int> v3 = {1, 2, 3, 4, 5}; // Конструктор со списком инициализации
    Vector<int> v4(v3); // Конструктор копирования
    Vector<int> v5(std::move(v4)); // Конструктор перемещения

    // Тестирование методов доступа
    std::cout << "v3[2] = " << v3[2] << std::endl;
    std::cout << "v3.at(3) = " << v3.at(3) << std::endl;
    std::cout << "v3.front() = " << v3.front() << std::endl;
    std::cout << "v3.back() = " << v3.back() << std::endl;
    std::cout << "v3.data() = " << v3.data() << std::endl;

    // Тестирование методов емкости
    std::cout << "v3.size() = " << v3.size() << std::endl;
    std::cout << "v3.capacity() = " << v3.capacity() << std::endl;
    std::cout << "v3.empty() = " << std::boolalpha << v3.empty() << std::endl;

    // Тестирование модификаторов
    v3.push_back(6);
    std::cout << "After push_back: ";
    for (const auto& item : v3) {
        std::cout << item << " ";
    }
    std::cout << std::endl;

    v3.pop_back();
    std::cout << "After pop_back: ";
    for (const auto& item : v3) {
        std::cout << item << " ";
    }
    std::cout << std::endl;

    v3.insert(2, 10);
    std::cout << "After insert: ";
    for (const auto& item : v3) {
        std::cout << item << " ";
    }
    std::cout << std::endl;

    v3.erase(2);
    std::cout << "After erase: ";
    for (const auto& item : v3) {
        std::cout << item << " ";
    }
    std::cout << std::endl;

    v3.resize(10);
    std::cout << "After resize: size = " << v3.size() << std::endl;

    v3.clear();
    std::cout << "After clear: size = " << v3.size() << std::endl;

    // Тестирование операторов сравнения
    Vector<int> a = {1, 2, 3};
    Vector<int> b = {1, 2, 3};
    Vector<int> c = {4, 5, 6};

    std::cout << "a == b: " << (a == b) << std::endl;
    std::cout << "a != c: " << (a != c) << std::endl;
    std::cout << "a < c: " << (a < c) << std::endl;
    std::cout << "c > a: " << (c > a) << std::endl;

    return 0;
}