#include <gtest/gtest.h>
#include "array.hpp"
#include <algorithm>
#include <numeric>
#include <string>

namespace {

// Тесты для N > 0
TEST(ArrayRegular, ElementAccess) {
    my_container::Array<int, 5> arr;
    arr[2] = 42;
    EXPECT_EQ(arr.at(2), 42);
    EXPECT_THROW(arr.at(5), std::out_of_range);
    
    const auto& carr = arr;
    EXPECT_EQ(carr[2], 42);
    EXPECT_THROW(carr.at(5), std::out_of_range);
}

TEST(ArrayRegular, FrontBackData) {
    my_container::Array<std::string, 3> arr = {"A", "B", "C"};
    EXPECT_EQ(arr.front(), "A");
    EXPECT_EQ(arr.back(), "C");
    EXPECT_STREQ(arr.data()[1].c_str(), "B");
}

TEST(ArrayRegular, Iterators) {
    my_container::Array<int, 4> arr = {8, 6, 4, 2};
    
    // Проверка изменения через итератор
    *arr.begin() = 10;
    EXPECT_EQ(arr[0], 10);
    
    // Константные итераторы
    const auto& carr = arr;
    EXPECT_EQ(*carr.cbegin(), 10);
    EXPECT_EQ(*(carr.cend()-1), 2);
}

TEST(ArrayRegular, ReverseIterators) {
    my_container::Array<int, 5> arr = {1, 2, 3, 4, 5};
    std::vector<int> reversed(arr.rbegin(), arr.rend());
    EXPECT_EQ(reversed, (std::vector<int>{5, 4, 3, 2, 1}));
}

TEST(ArrayRegular, FillAndSwap) {
    my_container::Array<int, 4> arr1;
    arr1.fill(7);
    
    my_container::Array<int, 4> arr2 = {1, 2, 3, 4};
    arr1.swap(arr2);
    
    EXPECT_EQ(arr1[0], 1);
    EXPECT_EQ(arr2[0], 7);
}

TEST(ArrayRegular, Comparisons) {
    my_container::Array<int, 3> a = {1, 2, 3};
    my_container::Array<int, 3> b = {1, 2, 4};
    my_container::Array<int, 3> c = {1, 5, 0};
    
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(a > b);
    EXPECT_TRUE(a != b);
    EXPECT_TRUE(c > a);  // Лексикографическое сравнение
}

// Тесты для N = 0
TEST(ArrayZeroSize, Basic) {
    my_container::Array<int, 0> arr;
    EXPECT_TRUE(arr.empty());
    EXPECT_EQ(arr.size(), 0);
    EXPECT_THROW(arr.at(0), std::out_of_range);
}

TEST(ArrayZeroSize, Comparisons) {
    my_container::Array<std::string, 0> a;
    my_container::Array<std::string, 0> b;
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
    EXPECT_FALSE(a < b);
}

TEST(ArrayZeroSize, Iterators) {
    my_container::Array<double, 0> arr;
    EXPECT_EQ(arr.begin(), nullptr);
    EXPECT_EQ(arr.end(), nullptr);
    EXPECT_EQ(arr.rbegin(), arr.rend());
}

// Тесты перемещающей семантики
TEST(ArrayMove, StringMove) {
    my_container::Array<std::string, 2> arr1 = {"hello", "world"};
    auto arr2 = std::move(arr1);
    
    EXPECT_TRUE(arr1[0].empty());  // Проверка перемещения
    EXPECT_EQ(arr2[0], "hello");
}

TEST(ArrayMove, SelfAssignment) {
    my_container::Array<int, 3> arr = {1, 2, 3};
    arr = arr;
    EXPECT_EQ(arr[0], 1);  // Нет UB для self-move
}

// Тесты разных типов данных
struct Point {
    int x, y;
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

TEST(ArrayTypes, UserType) {
    my_container::Array<Point, 2> arr = {{{1,2}, {3,4}}};
    arr[1].x = 5;
    EXPECT_EQ(arr[1].x, 5);
}

} // namespace

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
