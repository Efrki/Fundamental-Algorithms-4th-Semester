#include <gtest/gtest.h>
#include "../include/double-linked-list.hpp"

namespace my_container {

TEST(ListTest, DefaultConstructor) {
    List<int, 5> list;
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.size(), 0);
    EXPECT_EQ(list.max_size(), 0);
}

TEST(ListTest, InitializerListConstructor) {
    List<int, 5> list = {1, 2, 3};
    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 3);
}

TEST(ListTest, CopyConstructor) {
    List<int, 5> orig = {1, 2, 3};
    List<int, 5> copy(orig);
    EXPECT_EQ(orig.size(), copy.size());
    EXPECT_EQ(orig.front(), copy.front());
    EXPECT_EQ(orig.back(), copy.back());
}

TEST(ListTest, MoveConstructor) {
    List<int, 5> orig = {1, 2, 3};
    List<int, 5> moved(std::move(orig));
    EXPECT_TRUE(orig.empty());
    EXPECT_EQ(moved.size(), 3);
}

TEST(ListTest, AssignmentOperator) {
    List<int, 5> orig = {1, 2, 3};
    List<int, 5> copy;
    copy = orig;
    EXPECT_EQ(orig.size(), copy.size());
    EXPECT_EQ(orig.front(), copy.front());
}

TEST(ListTest, MoveAssignment) {
    List<int, 5> orig = {1, 2, 3};
    List<int, 5> moved;
    moved = std::move(orig);
    EXPECT_TRUE(orig.empty());
    EXPECT_EQ(moved.size(), 3);
}

TEST(ListTest, FrontBackAccess) {
    List<int, 5> list = {42, 24};
    EXPECT_EQ(list.front(), 42);
    EXPECT_EQ(list.back(), 24);
    list.pop_front();
    EXPECT_EQ(list.front(), 24);
}

TEST(ListTest, EmptyListAccess) {
    List<int, 5> list;
    EXPECT_THROW(list.front(), std::out_of_range);
    EXPECT_THROW(list.back(), std::out_of_range);
}

TEST(ListTest, Iterators) {
    List<int, 5> list = {1, 2, 3};
    int sum = 0;
    for (auto it = list.begin(); it != list.end(); it = list.next(it)) {
        sum += *it;
    }
    EXPECT_EQ(sum, 6);

    const List<int, 5> clist = {1, 2, 3};
    EXPECT_EQ(*clist.begin(), 1);
    EXPECT_EQ(clist.cbegin(), clist.begin());
}

TEST(ListTest, ReverseIterators) {
    List<int, 5> list = {1, 2, 3};
    int sum = 0;    
    for (auto it = list.rbegin(); it != list.rend(); it = list.prev(it)) {
        sum += *it;        
    }
    EXPECT_EQ(sum, 6);
}

TEST(ListTest, PushPopOperations) {
    List<int, 3> list;
    list.push_back(1);
    list.push_front(0);
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.front(), 0);
    list.pop_back();
    EXPECT_EQ(list.back(), 0);
    list.pop_front();
    EXPECT_TRUE(list.empty());
}

TEST(ListTest, InsertErase) {
    List<int, 5> list = {1, 3};
    
    int* first = list.begin();
    int* pos = list.begin();
    pos = list.next(pos);
    
    list.insert(pos, 2);
    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(*list.next(first), 2);
    
    list.erase(pos);
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.back(), 2);
}

TEST(ListTest, ClearResize) {
    List<int, 5> list = {1, 2, 3};
    list.clear();
    EXPECT_TRUE(list.empty());
    
    list.resize(3);
    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.back(), 0);
}

TEST(ListTest, Swap) {
    List<int, 5> list1 = {1, 2};
    List<int, 5> list2 = {3, 4, 5};
    list1.swap(list2);
    EXPECT_EQ(list1.size(), 3);
    EXPECT_EQ(list2.size(), 2);
}

TEST(ListTest, Comparisons) {
    List<int, 5> list1 = {1, 2};
    List<int, 5> list2 = {1, 2, 3};
    List<int, 5> list3 = {1, 2};
    
    EXPECT_TRUE(list1 == list3);
    EXPECT_TRUE(list1 != list2);
    EXPECT_TRUE(list1 < list2);
    EXPECT_TRUE(list2 > list1);
    EXPECT_TRUE(list1 <= list3);
    EXPECT_TRUE(list2 >= list1);
    
    #if __cplusplus >= 202002L
    EXPECT_TRUE((list1 <=> list3) == std::strong_ordering::equal);
    #endif
}

TEST(ListTest, ContainerAssignmentOperator) {
    List<int, 3> list;
    list.push_back(1);
    const Container<int, 3>& base_ref = list;
    list = base_ref;
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.front(), 1);

    class DummyContainer : public Container<int, 3> { Container& operator=(const Container&) override { return *this; }
    int* begin() override { return nullptr; }
    const int* begin() const override { return nullptr; }
    const int* cbegin() const override { return nullptr; }
    int* end() override { return nullptr; }
    const int* end() const override { return nullptr; }
    const int* cend() const override { return nullptr; }
    bool operator==(const Container&) const override { return false; }
    bool operator!=(const Container&) const override { return true; }
    size_t size() const override { return 0; }
    size_t max_size() const override { return 3; }
    bool empty() const override { return true; } };
    DummyContainer dummy;
    EXPECT_THROW(list = dummy, std::invalid_argument);
}

TEST(ListTest, ConstFrontBackAccess) {
    const List<int, 3> empty_list;
    EXPECT_THROW(empty_list.front(), std::out_of_range);
    EXPECT_THROW(empty_list.back(), std::out_of_range);

    const List<int, 3> list = {5, 10};
    EXPECT_EQ(list.front(), 5);
    EXPECT_EQ(list.back(), 10);
}

TEST(ListTest, EdgeIterators) {
    List<int, 3> list;
    EXPECT_EQ(list.end(), nullptr);
    EXPECT_EQ(list.cend(), nullptr);
    EXPECT_EQ(list.rend(), nullptr);
    EXPECT_EQ(list.crend(), nullptr);

    list.push_back(42);
    EXPECT_EQ(*list.rbegin(), 42);
    EXPECT_EQ(*list.crbegin(), 42);
}

TEST(ListTest, PopBackEdgeCases) {
    List<int, 3> list = {1};
    list.pop_back();
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.begin(), nullptr);
}

TEST(ListTest, PushFrontToEmpty) {
    List<int, 3> list;
    list.push_front(99);
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.front(), 99);
    EXPECT_EQ(list.back(), 99);
}

TEST(ListTest, InsertEdgeCases) {
    List<int, 5> list;
    list.insert(nullptr, 100);
    EXPECT_EQ(list.back(), 100);

    int* pos = list.begin();
    list.insert(pos, 200);
    EXPECT_EQ(list.front(), 200);
}

TEST(ListTest, EraseLastElement) {
    List<int, 3> list = {1, 2};
    int* last = list.next(list.begin());
    list.erase(last);
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.back(), 1);
}

namespace my_container {

TEST(ListTest, ContainerAssignmentOperator) {
    List<int, 3> list;
    list.push_back(1);
    const Container<int, 3>& base_ref = list;
    list = base_ref;
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.front(), 1);

    class DummyContainer : public Container<int, 3> {
    public:
        Container& operator=(const Container&) override { return *this; }
        int* begin() override { return nullptr; }
        const int* begin() const override { return nullptr; }
        const int* cbegin() const override { return nullptr; }
        int* end() override { return nullptr; }
        const int* end() const override { return nullptr; }
        const int* cend() const override { return nullptr; }
        bool operator==(const Container&) const override { return false; }
        bool operator!=(const Container&) const override { return true; }
        size_t size() const override { return 0; }
        size_t max_size() const override { return 3; }
        bool empty() const override { return true; }
    };

    DummyContainer dummy;
    EXPECT_THROW(list = dummy, std::invalid_argument);

    List<int, 3> other;
    other.push_back(2);
    other.push_back(3);
    list = other;
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.front(), 2);
    EXPECT_EQ(list.back(), 3);
}

TEST(ListTest, EraseOperations) {
    List<int, 5> list = {1, 2, 3, 4};

    auto pos = list.next(list.next(list.begin()));
    list.erase(pos);
    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.back(), 4);

    pos = list.begin();
    list.erase(pos);
    EXPECT_EQ(list.front(), 2);

    pos = list.begin();
    while (list.next(pos) != nullptr) {
        pos = list.next(pos);
    }
    list.erase(pos);
    if (!list.empty()) {
        EXPECT_EQ(list.back(), 2);
    } else {
        EXPECT_EQ(list.rbegin(), nullptr); 
    }

    EXPECT_EQ(list.erase(nullptr), nullptr);
}

TEST(ListTest, EraseLastElementFromMultiple) {
    List<int, 3> list = {1, 2, 3};
    auto pos = list.begin();
    while (list.next(pos) != nullptr) {
        pos = list.next(pos);
    }
    list.erase(pos);
    EXPECT_EQ(list.back(), 2);
}

TEST(ListTest, ReverseIterators) {
    List<int, 3> empty_list;
    EXPECT_EQ(empty_list.rbegin(), nullptr);
    EXPECT_EQ(empty_list.rend(), nullptr);

    List<int, 3> list = {10, 20, 30};
    int sum = 0;
    for (auto it = list.rbegin(); it != list.rend(); it = list.prev(it)) {
        sum += *it;
    }
    EXPECT_EQ(sum, 60);

    list.pop_back();
    EXPECT_EQ(*list.rbegin(), 20);
}
TEST(ListTest, ContainerAssignmentOperator_ZeroCoverage) {
    List<int, 3> list1 = {1, 2};
    List<int, 3> list2 = {3, 4, 5};

    Container<int, 3>* base_ptr = &list2;
    list1 = *base_ptr;

    EXPECT_EQ(list1.size(), 3);
    EXPECT_EQ(list1.front(), 3);
    EXPECT_EQ(list1.back(), 5);

    EXPECT_EQ(list2.size(), 3);
    EXPECT_EQ(list2.front(), 3);
    EXPECT_EQ(list2.back(), 5);

    List<int, 3> empty_list;
    base_ptr = &empty_list;
    list1 = *base_ptr;
    EXPECT_TRUE(list1.empty());
}

}

}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}