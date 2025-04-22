#include <gtest/gtest.h>
#include "../include/double-linked-list.hpp"
#include <vector>

namespace {

TEST(ListTest, Constructors) {
    my_container::List<int> list1;
    EXPECT_TRUE(list1.empty());

    my_container::List<int> list2 = {1, 2, 3};
    EXPECT_EQ(list2.size(), 3);

    my_container::List<int> list3(list2);
    EXPECT_EQ(list3, list2);

    my_container::List<int> list4(std::move(list3));
    EXPECT_EQ(list4.size(), 3);
    EXPECT_TRUE(list3.empty());
}

TEST(ListTest, InsertErase) {
    my_container::List<int> list = {1, 3};
    auto it = ++list.begin();
    list.insert(it, 2);
    EXPECT_EQ(list, (my_container::List<int>{1, 2, 3}));

    it = ++list.begin();
    list.erase(it);
    EXPECT_EQ(list, (my_container::List<int>{1, 3}));
}

TEST(ListTest, PushPop) {
    my_container::List<int> list;
    list.push_back(2);
    list.push_front(1);
    EXPECT_EQ(list.back(), 2); // Теперь работает
    EXPECT_EQ(list.front(), 1); // Теперь работает

    list.pop_back();
    EXPECT_EQ(list.back(), 1);
    list.pop_front();
    EXPECT_TRUE(list.empty());
}

TEST(ListTest, Resize) {
    my_container::List<int> list = {1};
    list.resize(3, 5);
    EXPECT_EQ(list, (my_container::List<int>{1, 5, 5}));

    list.resize(1);
    EXPECT_EQ(list, (my_container::List<int>{1}));
}

TEST(ListTest, Swap) {
    my_container::List<int> a = {1, 2};
    my_container::List<int> b = {3, 4};
    a.swap(b);
    EXPECT_EQ(a, (my_container::List<int>{3, 4}));
    EXPECT_EQ(b, (my_container::List<int>{1, 2}));
}

} // namespace

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}