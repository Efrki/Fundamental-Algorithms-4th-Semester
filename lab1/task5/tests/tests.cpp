#include <gtest/gtest.h>
#include "../include/vector.hpp"
#include <stdexcept>

using namespace my_container;

TEST(VectorTest, Constructors) {
    Vector<int> v1;
    EXPECT_EQ(v1.size(), 0);
    EXPECT_TRUE(v1.empty());

    Vector<int> v2(5);
    EXPECT_EQ(v2.size(), 5);
    EXPECT_GE(v2.capacity(), 5);

    Vector<int> v3 = {1, 2, 3};
    EXPECT_EQ(v3.size(), 3);
    EXPECT_EQ(v3[0], 1);

    Vector<int> v4(v3);
    EXPECT_EQ(v4.size(), 3);
    EXPECT_EQ(v4[1], 2);

    Vector<int> v5(std::move(v4));
    EXPECT_EQ(v5.size(), 3);
    EXPECT_TRUE(v4.empty());
}

TEST(VectorTest, AssignmentOperators) {
    Vector<int> v1 = {1, 2, 3};
    Vector<int> v2;

    v2 = v1;
    EXPECT_EQ(v2.size(), 3);
    EXPECT_EQ(v2[2], 3);

    Vector<int> v3;
    v3 = std::move(v2);
    EXPECT_EQ(v3.size(), 3);
    EXPECT_TRUE(v2.empty());

    Container<int, 0>& c = v1;
    Vector<int> v4;
    v4 = c;
    EXPECT_EQ(v4.size(), 3);
}


TEST(VectorTest, ElementAccess) {
    Vector<int> v = {10, 20, 30};

    EXPECT_EQ(v[1], 20);
    v[1] = 25;
    EXPECT_EQ(v[1], 25);

    EXPECT_EQ(v.at(2), 30);
    EXPECT_THROW(v.at(3), std::out_of_range);

    EXPECT_EQ(v.front(), 10);
    EXPECT_EQ(v.back(), 30);

    EXPECT_NE(v.data(), nullptr);
}

TEST(VectorTest, CapacityMethods) {
    Vector<int> v;
    EXPECT_TRUE(v.empty());
    
    v.reserve(10);
    EXPECT_GE(v.capacity(), 10);
    
    v = {1, 2, 3};
    EXPECT_EQ(v.size(), 3);
    
    v.shrink_to_fit();
    EXPECT_EQ(v.capacity(), 3);
}

TEST(VectorTest, Modifiers) {
    Vector<int> v;

    v.push_back(10);
    v.push_back(20);
    EXPECT_EQ(v.size(), 2);
    
    v.pop_back();
    EXPECT_EQ(v.back(), 10);

    v.insert(1, 15);
    EXPECT_EQ(v[1], 15);
    
    v.erase(0);
    EXPECT_EQ(v[0], 15);

    v.resize(5);
    EXPECT_EQ(v.size(), 5);
    
    v.clear();
    EXPECT_TRUE(v.empty());
}

TEST(VectorTest, ComparisonOperators) {
    Vector<int> a = {1, 2, 3};
    Vector<int> b = {1, 2, 3};
    Vector<int> c = {4, 5};

    EXPECT_TRUE(a == b);
    EXPECT_TRUE(a != c);
    EXPECT_TRUE(c > a);
    EXPECT_TRUE(a < c);
    EXPECT_TRUE(a <= b);
    EXPECT_TRUE(c >= a);
}

TEST(VectorTest, Exceptions) {
    Vector<int> v;

    EXPECT_THROW(v.at(0), std::out_of_range);
    EXPECT_THROW(v.insert(1, 10), std::out_of_range);
    EXPECT_THROW(v.erase(0), std::out_of_range);
}

TEST(VectorTest, IteratorValidity) {
    Vector<int> v = {1, 2, 3};
    auto it = v.begin();
    
    EXPECT_EQ(*it, 1);
    v.push_back(4);
    EXPECT_NE(it, v.begin()); 
}

TEST(VectorTest, IteratorMethods) {
    Vector<int> v = {1, 2, 3};

    EXPECT_EQ(*v.begin(), 1);
    EXPECT_EQ(*(v.end() - 1), 3);
    EXPECT_NE(v.begin(), v.end());

    const Vector<int>& cv = v;
    EXPECT_EQ(*cv.cbegin(), 1);
    EXPECT_EQ(*(cv.cend() - 1), 3);
    EXPECT_NE(cv.cbegin(), cv.cend());
}

TEST(VectorTest, ConstIteratorMethods) {
    const Vector<int> v = {1, 2, 3};

    EXPECT_EQ(*v.begin(), 1);
    EXPECT_EQ(*(v.end() - 1), 3);
    EXPECT_NE(v.begin(), v.end());

    EXPECT_EQ(*v.cbegin(), 1);
    EXPECT_EQ(*(v.cend() - 1), 3);
    EXPECT_NE(v.cbegin(), v.cend());
}

TEST(VectorTest, MaxSizeMethod) {
    Vector<int> v(5);
    EXPECT_EQ(v.max_size(), 5);
}

TEST(VectorTest, SwapMethod) {
    Vector<int> v1 = {1, 2, 3};
    Vector<int> v2 = {4, 5};
    v1.swap(v2);
    EXPECT_EQ(v1.size(), 2);
    EXPECT_EQ(v2.size(), 3);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}