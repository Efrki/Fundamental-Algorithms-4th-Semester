#include <gtest/gtest.h>
#include "../include/deque.hpp"

namespace my_container {

TEST(DequeTest, DefaultConstructor) {
    Deque<int, 5> dq;
    EXPECT_TRUE(dq.empty());
    EXPECT_EQ(dq.size(), 0);
}

TEST(DequeTest, InitializerListConstructor) {
    Deque<int, 5> dq = {1, 2, 3};
    EXPECT_EQ(dq.size(), 3);
    EXPECT_EQ(dq.front(), 1);
    EXPECT_EQ(dq.back(), 3);
}

TEST(DequeTest, CopyConstructor) {
    Deque<int, 5> orig = {4, 5, 6};
    Deque<int, 5> copy(orig);
    EXPECT_EQ(orig.size(), copy.size());
    EXPECT_EQ(orig[0], copy[0]);
    EXPECT_EQ(orig[2], copy[2]);
}

TEST(DequeTest, MoveConstructor) {
    Deque<int, 5> orig = {7, 8, 9};
    Deque<int, 5> moved(std::move(orig));
    EXPECT_TRUE(orig.empty());
    EXPECT_EQ(moved.size(), 3);
}

TEST(DequeTest, AssignmentOperator) {
    Deque<int, 5> orig = {10, 20};
    Deque<int, 5> copy;
    copy = orig;
    EXPECT_EQ(orig.size(), copy.size());
    EXPECT_EQ(orig.front(), copy.front());
}

TEST(DequeTest, ElementAccess) {
    Deque<int, 5> dq = {100, 200, 300};
    
    // operator[]
    EXPECT_EQ(dq[0], 100);
    EXPECT_EQ(dq[2], 300);
    
    // at()
    EXPECT_EQ(dq.at(1), 200);
    EXPECT_THROW(dq.at(3), std::out_of_range);
    
    // front/back
    EXPECT_EQ(dq.front(), 100);
    EXPECT_EQ(dq.back(), 300);
}

TEST(DequeTest, Iterators) {
    Deque<int, 5> dq = {5, 10, 15};
    int sum = 0;
    for (auto it = dq.begin(); it != dq.end(); it = dq.next(it)) {
        sum += *it;
    }
    EXPECT_EQ(sum, 30);

    // Reverse
    sum = 0;
    for (auto it = dq.rbegin(); it != dq.rend(); it = dq.prev(it)) {
        sum += *it;
    }
    EXPECT_EQ(sum, 30);
}

TEST(DequeTest, Modifiers) {
    Deque<int, 5> dq;
    
    // push_back/pop_back
    dq.push_back(1);
    dq.push_back(2);
    EXPECT_EQ(dq.back(), 2);
    dq.pop_back();
    EXPECT_EQ(dq.back(), 1);
    
    // push_front/pop_front
    dq.push_front(0);
    EXPECT_EQ(dq.front(), 0);
    dq.pop_front();
    EXPECT_EQ(dq.front(), 1);
    
    // insert
    auto pos = dq.begin();
    dq.insert(pos, 99);
    EXPECT_EQ(dq.front(), 99);
    
    // erase
    dq.erase(pos);
    EXPECT_EQ(dq.size(), 1);
    
    // resize
    dq.resize(3);
    EXPECT_EQ(dq.size(), 3);
    EXPECT_EQ(dq[2], 0);
}

TEST(DequeTest, Comparisons) {
    Deque<int, 5> dq1 = {1, 2, 3};
    Deque<int, 5> dq2 = {1, 2, 3};
    Deque<int, 5> dq3 = {4, 5};
    
    EXPECT_TRUE(dq1 == dq2);
    EXPECT_TRUE(dq1 != dq3);
    EXPECT_TRUE(dq3 > dq1);
}

TEST(DequeTest, EdgeCases) {
    Deque<int, 2> dq;
    
    // max_size
    dq.push_back(1);
    dq.push_back(2);
    EXPECT_THROW(dq.push_back(3), std::length_error);
    
    // clear
    dq.clear();
    EXPECT_TRUE(dq.empty());
}

} // namespace my_container

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}