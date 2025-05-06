#include "gtest/gtest.h"
#include "../include/uniqueptr.hpp"

using my_smart_ptr::UniquePtr;

class Dummy {
    public:
    int x;
    Dummy(int v) : x(v) {}
    int get() const { return x; }
};

TEST(UniquePtrTest, DefaultConstructor) {
    UniquePtr<int> up;
    EXPECT_FALSE(up);
    EXPECT_EQ(up.get(), nullptr);
}

TEST(UniquePtrTest, PointerConstructorAndAccess) {
    UniquePtr<int> up(new int(5));
    EXPECT_TRUE(up);
    EXPECT_EQ(*up, 5);
    *up = 10;
    EXPECT_EQ(*up, 10);
}

TEST(UniquePtrTest, ArrowOperator) {
    UniquePtr<Dummy> up(new Dummy(7));
    EXPECT_EQ(up->get(), 7);
}

TEST(UniquePtrTest, MoveConstructor) {
    UniquePtr<int> original(new int(3));
    UniquePtr<int> moved(std::move(original));
    EXPECT_FALSE(original);
    EXPECT_TRUE(moved);
    EXPECT_EQ(*moved, 3);
}

TEST(UniquePtrTest, MoveAssignment) {
    UniquePtr<int> p1(new int(1));
    UniquePtr<int> p2;
    p2 = std::move(p1);
    EXPECT_FALSE(p1);
    EXPECT_TRUE(p2);
    EXPECT_EQ(*p2, 1);
}

TEST(UniquePtrTest, Release) {
    UniquePtr<int> up(new int(9));
    int* raw = up.release();
    EXPECT_FALSE(up);
    EXPECT_EQ(*raw, 9);
    delete raw;
}

TEST(UniquePtrTest, Reset) {
    UniquePtr<int> up(new int(2));
    up.reset(new int(4));
    EXPECT_TRUE(up);
    EXPECT_EQ(*up, 4);
    up.reset();
    EXPECT_FALSE(up);
}

TEST(UniquePtrTest, Swap) {
    UniquePtr<int> a(new int(100));
    UniquePtr<int> b(new int(200));
    a.swap(b);
    EXPECT_EQ(*a, 200);
    EXPECT_EQ(*b, 100);
    swap(a, b);
    EXPECT_EQ(*a, 100);
    EXPECT_EQ(*b, 200);
}

// Array specialization tests
TEST(UniquePtrArrayTest, DefaultConstructor) {
    UniquePtr<int[]> up;
    EXPECT_FALSE(up);
    EXPECT_EQ(up.get(), nullptr);
}

TEST(UniquePtrArrayTest, PointerConstructorAndIndex) {
    UniquePtr<int[]> up(new int[2]{8,9});
    EXPECT_TRUE(up);
    EXPECT_EQ(up[0], 8);
    EXPECT_EQ(up[1], 9);
}

TEST(UniquePtrArrayTest, MoveConstructor) {
    UniquePtr<int[]> orig(new int[1]{5});
    UniquePtr<int[]> moved(std::move(orig));
    EXPECT_FALSE(orig);
    EXPECT_TRUE(moved);
    EXPECT_EQ(moved[0], 5);
}

TEST(UniquePtrArrayTest, MoveAssignment) {
    UniquePtr<int[]> a(new int[1]{1});
    UniquePtr<int[]> b;
    b = std::move(a);
    EXPECT_FALSE(a);
    EXPECT_TRUE(b);
    EXPECT_EQ(b[0], 1);
}

TEST(UniquePtrArrayTest, ReleaseAndReset) {
    UniquePtr<int[]> up(new int[2]{3,4});
    int* raw = up.release();
    EXPECT_FALSE(up);
    EXPECT_EQ(raw[0], 3);
    delete[] raw;
    up.reset(new int[1]{7});
    EXPECT_TRUE(up);
    EXPECT_EQ(up[0], 7);
    up.reset();
    EXPECT_FALSE(up);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
