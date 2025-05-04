#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <algorithm>
#include "../include/array.hpp"

namespace {

using namespace my_container;

// Тесты конструкторов
TEST(ArrayConstructors, DefaultConstructor) {
    Array<int, 5> arr;
    EXPECT_EQ(arr.size(), 5);
    EXPECT_FALSE(arr.empty());
}

TEST(ArrayConstructors, ValueConstructor) {
    Array<std::string, 3> arr("test");
    EXPECT_EQ(arr[0], "test");
    EXPECT_EQ(arr[2], "test");
}

TEST(ArrayConstructors, InitializerList) {
    Array<int, 5> arr{1, 2, 3};
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[2], 3);
    EXPECT_EQ(arr[4], 0);
}

TEST(ArrayConstructors, CopyConstructor) {
    Array<int, 4> src{1, 2, 3, 4};
    Array<int, 4> dest(src);
    EXPECT_TRUE(std::equal(src.begin(), src.end(), dest.begin()));
}

// Тесты операторов присваивания
TEST(ArrayAssignment, ContainerAssignment) {
    Array<int, 3> src{1, 2, 3};
    Array<int, 3> dest;
    Container<int, 3>& ref = dest;
    ref = src;
    EXPECT_EQ(dest[2], 3);
}

TEST(ArrayAssignment, ArrayAssignment) {
    Array<int, 4> src{4, 3, 2, 1};
    Array<int, 4> dest;
    dest = src;
    EXPECT_EQ(dest[3], 1);
}

// Тесты итераторов
TEST(ArrayIterators, ReverseIterators) {
    Array<int, 5> arr{1, 2, 3, 4, 5};
    std::vector<int> reversed(arr.rbegin(), arr.rend());
    EXPECT_EQ(reversed, std::vector<int>({5, 4, 3, 2, 1}));
}

TEST(ArrayIterators, ConstIterators) {
    const Array<int, 3> arr{10, 20, 30};
    EXPECT_EQ(*arr.cbegin(), 10);
    EXPECT_EQ(*(arr.cend() - 1), 30);
}

// Тесты доступа к элементам
TEST(ArrayAccess, ElementAccess) {
    Array<int, 5> arr;
    arr.fill(42);
    arr[3] = 99;
    
    EXPECT_EQ(arr.at(0), 42);
    EXPECT_EQ(arr[3], 99);
    EXPECT_THROW(arr.at(5), std::out_of_range);
}

TEST(ArrayAccess, FrontBackData) {
    Array<int, 4> arr{100, 200, 300, 400};
    EXPECT_EQ(arr.front(), 100);
    EXPECT_EQ(arr.back(), 400);
    EXPECT_EQ(arr.data()[2], 300);
}

// Тесты сравнения
TEST(ArrayComparison, Equality) {
    Array<int, 3> a1{1, 2, 3};
    Array<int, 3> a2{1, 2, 3};
    Array<int, 3> a3{1, 2, 4};
    
    EXPECT_TRUE(a1 == a2);
    EXPECT_TRUE(a1 != a3);
    EXPECT_TRUE(a1 < a3);
    EXPECT_TRUE(a3 > a1);
    EXPECT_TRUE(a1 <= a2);
    EXPECT_TRUE(a3 >= a1);
}

// Тесты специальных методов
TEST(ArrayMethods, FillAndSwap) {
    Array<int, 4> arr1;
    arr1.fill(5);
    Array<int, 4> arr2{1, 2, 3, 4};
    arr1.swap(arr2);
    
    EXPECT_EQ(arr1[3], 4);
    EXPECT_EQ(arr2[2], 5);
}

// Тесты пограничных случаев
TEST(ArrayEdgeCases, EmptyArray) {
    Array<int, 0> arr;
    EXPECT_TRUE(arr.empty());
    EXPECT_THROW(arr.front(), std::out_of_range);
    EXPECT_THROW(arr.back(), std::out_of_range);
}

TEST(ArrayEdgeCases, ThreeWayComparison) {
    Array<int, 3> a1{1, 2, 3};
    Array<int, 3> a2{1, 2, 4};
    auto cmp = a1 <=> a2;
    EXPECT_TRUE(cmp < 0);
}

// Проверка полиморфного поведения
TEST(ArrayPolymorphism, BaseClassInterface) {
    Array<double, 2>* arr = new Array<double, 2>{1.1, 2.2};
    Container<double, 2>* cont = arr;
    
    EXPECT_EQ(cont->size(), 2);
    EXPECT_DOUBLE_EQ(*cont->begin(), 1.1);
    delete arr;
}
TEST(ArrayComparison, LessThanOperator) {
    Array<int, 3> a{1, 2, 3};
    Array<int, 3> b{2, 3, 4};
    EXPECT_TRUE(a < b);
}

TEST(ArrayComparison, ThreeWayComparison) {
    Array<int, 3> a{1, 2, 3};
    Array<int, 3> b{1, 2, 4};
    auto cmp = a <=> b;
    EXPECT_TRUE(cmp < 0);
}
TEST(ArrayIterators, ConstReverseIterators) {
    const Array<int, 4> arr{1, 2, 3, 4};
    std::vector<int> reversed(arr.crbegin(), arr.crend());
    EXPECT_EQ(reversed, std::vector<int>({4, 3, 2, 1}));
}
TEST(ArrayConstructors, SizeValueConstructor) {
    Array<int, 5> arr(3, 42);
    EXPECT_EQ(arr[0], 42);
    EXPECT_EQ(arr[2], 42);
    EXPECT_EQ(arr[3], 0); // Остальные элементы инициализированы 0
}
TEST(ArrayEdgeCases, FrontBackEmpty) {
    Array<int, 0> arr;
    EXPECT_THROW(arr.front(), std::out_of_range);
    EXPECT_THROW(arr.back(), std::out_of_range);
}
TEST(ArrayPolymorphism, VirtualMethods) {
    Array<int, 2>* arr = new Array<int, 2>{1, 2};
    Container<int, 2>* cont = arr;
    
    // Проверка виртуальных методов
    EXPECT_EQ(cont->size(), 2);
    EXPECT_EQ(*cont->begin(), 1);
    delete arr;
}
TEST(ArrayAssignment, SelfAssignment) {
    Array<int, 3> arr{1, 2, 3};
    arr = arr; // Проверка на самоприсваивание
    EXPECT_EQ(arr[2], 3);
}
// Тесты для array.hpp
TEST(ArrayConstMethods, MaxSize) {
    const Array<int, 5> arr;
    EXPECT_EQ(arr.max_size(), 5);
}

TEST(ArrayConstMethods, ConstSubscriptOperator) {
    const Array<int, 3> arr{1, 2, 3};
    EXPECT_EQ(arr[0], 1);
    EXPECT_THROW(arr[3], std::out_of_range);
}

TEST(ArrayConstMethods, ConstAtMethod) {
    const Array<std::string, 2> arr{"hello", "world"};
    EXPECT_EQ(arr.at(1), "world");
    EXPECT_THROW(arr.at(2), std::out_of_range);
}

TEST(ArrayConstMethods, ConstFrontBack) {
    const Array<int, 4> arr{10, 20, 30, 40};
    EXPECT_EQ(arr.front(), 10);
    EXPECT_EQ(arr.back(), 40);

    const Array<int, 0> empty_arr;
    EXPECT_THROW(empty_arr.front(), std::out_of_range);
    EXPECT_THROW(empty_arr.back(), std::out_of_range);
}

TEST(ArrayConstMethods, ConstData) {
    const Array<double, 3> arr{1.1, 2.2, 3.3};
    const double* ptr = arr.data();
    EXPECT_DOUBLE_EQ(ptr[1], 2.2);
}

// Тесты для container.hpp через Array
TEST(ContainerInterface, VirtualAssignment) {
    Array<int, 2> src{5, 10};
    Array<int, 2> dest;
    Container<int, 2>& cont = dest;
    
    cont = src;
    EXPECT_EQ(dest[0], 5);
    EXPECT_EQ(dest[1], 10);
}

TEST(ContainerInterface, Iterators) {
    Array<char, 4> arr{'a', 'b', 'c', 'd'};
    Container<char, 4>& cont = arr;
    
    auto it = cont.begin();
    EXPECT_EQ(*it, 'a');
    EXPECT_EQ(*(cont.end() - 1), 'd');

    const Container<char, 4>& ccont = arr;
    EXPECT_EQ(*ccont.begin(), 'a');
    EXPECT_EQ(*ccont.cbegin(), 'a');
}

TEST(ContainerInterface, Comparisons) {
    Array<int, 3> a1{1, 2, 3};
    Array<int, 3> a2{1, 2, 3};
    Array<int, 3> a3{1, 2, 4};
    
    Container<int, 3>& c1 = a1;
    Container<int, 3>& c2 = a2;
    Container<int, 3>& c3 = a3;
    
    EXPECT_TRUE(c1 == c2);
    EXPECT_TRUE(c1 != c3);
}

TEST(ContainerInterface, SizeEmpty) {
    Array<float, 0> empty_arr;
    EXPECT_TRUE(empty_arr.empty());
    EXPECT_EQ(empty_arr.size(), 0);

    Array<float, 5> arr;
    EXPECT_FALSE(arr.empty());
    EXPECT_EQ(arr.size(), 5);
}
TEST(ArrayReverseIterators, ConstReverseIteration) {
    const my_container::Array<int, 4> arr{1, 2, 3, 4};
    
    // Проверка rbegin()/rend()
    std::vector<int> reversed;
    for (auto it = arr.rbegin(); it != arr.rend(); ++it) {
        reversed.push_back(*it);
    }
    EXPECT_EQ(reversed, (std::vector<int>{4, 3, 2, 1}));
}

TEST(ArrayAssignment, ContainerAssignmentInvalidType) {
    class MockContainer : public my_container::Container<int, 3> {
        int data[3] = {0};
    public:
        // Реализация всех чисто виртуальных методов
        MockContainer& operator=(const Container& other) override {
            const MockContainer* otherMock = dynamic_cast<const MockContainer*>(&other);
            if (otherMock) {
                std::copy(otherMock->data, otherMock->data + 3, data);
            }
            return *this;
        }
        
        int* begin() override { return data; }
        const int* begin() const override { return data; }
        const int* cbegin() const override { return data; }
        int* end() override { return data + 3; }
        const int* end() const override { return data + 3; }
        const int* cend() const override { return data + 3; }
        bool operator==(const Container&) const override { return false; }
        bool operator!=(const Container&) const override { return true; }
        size_t size() const override { return 3; }
        size_t max_size() const override { return 3; }
        bool empty() const override { return false; }
    };

    my_container::Array<int, 3> arr{1, 2, 3};
    MockContainer mock;
    my_container::Container<int, 3>& cont_ref = mock;
    
    // Сохраняем исходное состояние
    const int initial_values[] = {1, 2, 3};
    
    // Выполняем присваивание
    arr = cont_ref;
    
    // Проверяем что объект не изменился
    EXPECT_TRUE(std::equal(arr.begin(), arr.end(), initial_values));
}


} // namespace

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

