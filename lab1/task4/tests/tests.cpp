#include <gtest/gtest.h>
#include "../include/stack.hpp"

namespace my_container {

TEST(StackTest, DefaultConstructor) {
    Stack<int> st;
    EXPECT_TRUE(st.empty());
    EXPECT_EQ(st.size(), 0);
}

TEST(StackTest, InitializerListConstructor) {
    Stack<int> st = {1, 2, 3};
    EXPECT_EQ(st.size(), 3);
    EXPECT_EQ(st.top(), 3);
}

TEST(StackTest, CopyConstructor) {
    Stack<int> orig = {4, 5, 6};
    Stack<int> copy(orig);
    EXPECT_EQ(orig.size(), copy.size());
    EXPECT_EQ(orig.top(), copy.top());
}

TEST(StackTest, MoveConstructor) {
    Stack<int> orig = {7, 8, 9};
    Stack<int> moved(std::move(orig));
    EXPECT_TRUE(orig.empty());
    EXPECT_EQ(moved.top(), 9);
}

TEST(StackTest, CopyAssignment) {
    Stack<int> orig = {10, 20};
    Stack<int> copy;
    copy = orig;
    EXPECT_EQ(orig.size(), copy.size());
    EXPECT_EQ(orig.top(), copy.top());
}

TEST(StackTest, MoveAssignment) {
    Stack<int> orig = {30, 40};
    Stack<int> moved;
    moved = std::move(orig);
    EXPECT_TRUE(orig.empty());
    EXPECT_EQ(moved.top(), 40);
}

TEST(StackTest, TopAccess) {
    Stack<int> st = {100, 200};
    EXPECT_EQ(st.top(), 200);
    st.pop();
    EXPECT_EQ(st.top(), 100);
}

TEST(StackTest, EmptyStackAccess) {
    Stack<int> st;
    EXPECT_THROW(st.top(), std::out_of_range);
}

TEST(StackTest, CapacityMethods) {
    Stack<int, List, 3> st;
    EXPECT_EQ(st.max_size(), 3);
    st.push(1);
    EXPECT_EQ(st.size(), 1);
    EXPECT_FALSE(st.empty());
}

TEST(StackTest, PushPopOperations) {
    Stack<int> st;
    st.push(1);
    st.push(2);
    EXPECT_EQ(st.top(), 2);
    st.pop();
    EXPECT_EQ(st.top(), 1);
}

TEST(StackTest, OverflowHandling) {
    Stack<int, List, 2> st;
    st.push(1);
    st.push(2);
    EXPECT_THROW(st.push(3), std::length_error);
}

TEST(StackTest, UnderflowHandling) {
    Stack<int> st;
    EXPECT_THROW(st.pop(), std::out_of_range);
}

TEST(StackTest, SwapOperation) {
    Stack<int> st1 = {1, 2};
    Stack<int> st2 = {3, 4};
    st1.swap(st2);
    EXPECT_EQ(st1.top(), 4);
    EXPECT_EQ(st2.top(), 2);
}

TEST(StackTest, ComparisonOperators) {
    Stack<int> st1 = {1, 2, 3};
    Stack<int> st2 = {1, 2, 3};
    Stack<int> st3 = {4, 5};

    EXPECT_TRUE(st1 == st2);
    EXPECT_TRUE(st1 != st3);
    EXPECT_TRUE(st3 > st1);
    EXPECT_TRUE(st1 < st3);
}

#if __cplusplus >= 202002L
TEST(StackTest, ThreeWayComparison) {
    Stack<int> st1 = {1, 2};
    Stack<int> st2 = {3, 4};
    EXPECT_TRUE((st1 <=> st2) < 0);
}
#endif

}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}