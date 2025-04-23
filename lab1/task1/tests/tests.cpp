#include <gtest/gtest.h>
#include <array>
#include <algorithm>
#include "array.hpp" // Include your actual header file here

// Test fixture for Array class
template <typename T, size_t N>
class ArrayTest : public ::testing::Test {
protected:
    Array<T, N> arr;
    Array<T, N> arr_filled;
    
    void SetUp() override {
        for (size_t i = 0; i < N; ++i) {
            arr_filled[i] = static_cast<T>(i);
        }
    }
};

// Instantiate tests for different types and sizes
using Implementations = ::testing::Types<
    std::tuple<int, 0>,
    std::tuple<int, 5>,
    std::tuple<double, 10>,
    std::tuple<char, 100>
>;

TYPED_TEST_SUITE(ArrayTest, Implementations);

// Tests for Container interface
TEST(ContainerTest, IsAbstract) {
    EXPECT_TRUE(std::is_abstract<Container<int>>::value);
}

// Tests for Array constructors
TYPED_TEST(ArrayTest, DefaultConstructor) {
    using T = typename std::tuple_element<0, TypeParam>::type;
    constexpr size_t N = std::tuple_element<1, TypeParam>::value;
    
    Array<T, N> arr;
    EXPECT_EQ(arr.size(), N);
    EXPECT_EQ(arr.max_size(), N);
    EXPECT_EQ(arr.empty(), (N == 0));
}

TYPED_TEST(ArrayTest, SizeConstructor) {
    using T = typename std::tuple_element<0, TypeParam>::type;
    constexpr size_t N = std::tuple_element<1, TypeParam>::value;
    
    Array<T, N> arr;
    EXPECT_EQ(arr.size(), N);
}

TYPED_TEST(ArrayTest, CopyConstructor) {
    using T = typename std::tuple_element<0, TypeParam>::type;
    constexpr size_t N = std::tuple_element<1, TypeParam>::value;
    
    if constexpr (N > 0) {
        this->arr_filled[0] = static_cast<T>(42);
        Array<T, N> copy(this->arr_filled);
        
        EXPECT_EQ(copy.size(), N);
        EXPECT_EQ(copy[0], static_cast<T>(42));
        if (N > 1) {
            EXPECT_EQ(copy[1], static_cast<T>(1));
        }
    }
}

// Tests for Array assignment
TYPED_TEST(ArrayTest, CopyAssignment) {
    using T = typename std::tuple_element<0, TypeParam>::type;
    constexpr size_t N = std::tuple_element<1, TypeParam>::value;
    
    if constexpr (N > 0) {
        Array<T, N> arr;
        this->arr_filled[0] = static_cast<T>(99);
        arr = this->arr_filled;
        
        EXPECT_EQ(arr.size(), N);
        EXPECT_EQ(arr[0], static_cast<T>(99));
        if (N > 1) {
            EXPECT_EQ(arr[1], static_cast<T>(1));
        }
    }
}

TYPED_TEST(ArrayTest, SelfAssignment) {
    using T = typename std::tuple_element<0, TypeParam>::type;
    constexpr size_t N = std::tuple_element<1, TypeParam>::value;
    
    if constexpr (N > 0) {
        this->arr_filled[0] = static_cast<T>(7);
        this->arr_filled = this->arr_filled;
        
        EXPECT_EQ(this->arr_filled[0], static_cast<T>(7));
    }
}

// Tests for iterators
TYPED_TEST(ArrayTest, Iterators) {
    using T = typename std::tuple_element<0, TypeParam>::type;
    constexpr size_t N = std::tuple_element<1, TypeParam>::value;
    
    EXPECT_EQ(this->arr.begin(), this->arr.data());
    EXPECT_EQ(this->arr.end(), this->arr.data() + N);
    EXPECT_EQ(this->arr.cbegin(), this->arr.data());
    EXPECT_EQ(this->arr.cend(), this->arr.data() + N);
    
    if constexpr (N > 0) {
        EXPECT_NE(this->arr.begin(), this->arr.end());
    } else {
        EXPECT_EQ(this->arr.begin(), this->arr.end());
    }
}

TYPED_TEST(ArrayTest, ReverseIterators) {
    using T = typename std::tuple_element<0, TypeParam>::type;
    constexpr size_t N = std::tuple_element<1, TypeParam>::value;
    
    if constexpr (N > 0) {
        this->arr_filled[0] = static_cast<T>(1);
        this->arr_filled[N-1] = static_cast<T>(2);
        
        EXPECT_EQ(*this->arr_filled.rbegin(), static_cast<T>(2));
        EXPECT_EQ(*(this->arr_filled.rend() - 1), static_cast<T>(1));
    }
}

// Tests for element access
TYPED_TEST(ArrayTest, SubscriptOperator) {
    using T = typename std::tuple_element<0, TypeParam>::type;
    constexpr size_t N = std::tuple_element<1, TypeParam>::value;
    
    if constexpr (N > 0) {
        this->arr[0] = static_cast<T>(5);
        EXPECT_EQ(this->arr[0], static_cast<T>(5));
        
        const Array<T, N>& const_arr = this->arr;
        EXPECT_EQ(const_arr[0], static_cast<T>(5));
    }
}

TYPED_TEST(ArrayTest, AtMethod) {
    using T = typename std::tuple_element<0, TypeParam>::type;
    constexpr size_t N = std::tuple_element<1, TypeParam>::value;
    
    if constexpr (N > 0) {
        this->arr.at(0) = static_cast<T>(10);
        EXPECT_EQ(this->arr.at(0), static_cast<T>(10));
        
        const Array<T, N>& const_arr = this->arr;
        EXPECT_EQ(const_arr.at(0), static_cast<T>(10));
        
        EXPECT_THROW(this->arr.at(N), std::out_of_range);
        EXPECT_THROW(const_arr.at(N), std::out_of_range);
    } else {
        EXPECT_THROW(this->arr.at(0), std::out_of_range);
    }
}

TYPED_TEST(ArrayTest, FrontAndBack) {
    using T = typename std::tuple_element<0, TypeParam>::type;
    constexpr size_t N = std::tuple_element<1, TypeParam>::value;
    
    if constexpr (N > 0) {
        this->arr_filled.front() = static_cast<T>(20);
        this->arr_filled.back() = static_cast<T>(30);
        
        EXPECT_EQ(this->arr_filled.front(), static_cast<T>(20));
        EXPECT_EQ(this->arr_filled.back(), static_cast<T>(30));
        
        const Array<T, N>& const_arr = this->arr_filled;
        EXPECT_EQ(const_arr.front(), static_cast<T>(20));
        EXPECT_EQ(const_arr.back(), static_cast<T>(30));
    }
}

TYPED_TEST(ArrayTest, DataMethod) {
    using T = typename std::tuple_element<0, TypeParam>::type;
    constexpr size_t N = std::tuple_element<1, TypeParam>::value;
    
    EXPECT_EQ(this->arr.data(), this->arr.begin());
    
    const Array<T, N>& const_arr = this->arr;
    EXPECT_EQ(const_arr.data(), const_arr.begin());
}

// Tests for capacity
TYPED_TEST(ArrayTest, SizeAndEmpty) {
    using T = typename std::tuple_element<0, TypeParam>::type;
    constexpr size_t N = std::tuple_element<1, TypeParam>::value;
    
    EXPECT_EQ(this->arr.size(), N);
    EXPECT_EQ(this->arr.max_size(), N);
    EXPECT_EQ(this->arr.empty(), (N == 0));
}

// Tests for operations
TYPED_TEST(ArrayTest, Fill) {
    using T = typename std::tuple_element<0, TypeParam>::type;
    constexpr size_t N = std::tuple_element<1, TypeParam>::value;
    
    this->arr.fill(static_cast<T>(55));
    
    for (size_t i = 0; i < N; ++i) {
        EXPECT_EQ(this->arr[i], static_cast<T>(55));
    }
}

TYPED_TEST(ArrayTest, Swap) {
    using T = typename std::tuple_element<0, TypeParam>::type;
    constexpr size_t N = std::tuple_element<1, TypeParam>::value;
    
    if constexpr (N > 0) {
        Array<T, N> arr1;
        Array<T, N> arr2;
        
        arr1.fill(static_cast<T>(1));
        arr2.fill(static_cast<T>(2));
        
        arr1.swap(arr2);
        
        EXPECT_EQ(arr1[0], static_cast<T>(2));
        EXPECT_EQ(arr2[0], static_cast<T>(1));
    }
}

// Tests for comparison operators
TYPED_TEST(ArrayTest, EqualityOperators) {
    using T = typename std::tuple_element<0, TypeParam>::type;
    constexpr size_t N = std::tuple_element<1, TypeParam>::value;
    
    Array<T, N> arr1;
    Array<T, N> arr2;
    
    arr1.fill(static_cast<T>(1));
    arr2.fill(static_cast<T>(1));
    
    EXPECT_TRUE(arr1 == arr2);
    EXPECT_FALSE(arr1 != arr2);
    
    if constexpr (N > 0) {
        arr2[0] = static_cast<T>(2);
        EXPECT_FALSE(arr1 == arr2);
        EXPECT_TRUE(arr1 != arr2);
    }
}

TYPED_TEST(ArrayTest, RelationalOperators) {
    using T = typename std::tuple_element<0, TypeParam>::type;
    constexpr size_t N = std::tuple_element<1, TypeParam>::value;
    
    if constexpr (N > 0) {
        Array<T, N> arr1;
        Array<T, N> arr2;
        
        arr1.fill(static_cast<T>(1));
        arr2.fill(static_cast<T>(2));
        
        EXPECT_TRUE(arr1 < arr2);
        EXPECT_FALSE(arr2 < arr1);
        EXPECT_TRUE(arr1 <= arr2);
        EXPECT_FALSE(arr2 <= arr1);
        EXPECT_TRUE(arr2 > arr1);
        EXPECT_FALSE(arr1 > arr2);
        EXPECT_TRUE(arr2 >= arr1);
        EXPECT_FALSE(arr1 >= arr2);
        
        // Test three-way comparison if supported
        #if __cplusplus >= 202002L
        EXPECT_LT(arr1 <=> arr2, 0);
        EXPECT_GT(arr2 <=> arr1, 0);
        #endif
    }
}

// Test for different sizes comparison
TEST(ArrayComparisonTest, DifferentSizes) {
    Array<int, 3> arr1;
    Array<int, 4> arr2;
    
    // These should not compile if uncommented, but we can't test that here
    // EXPECT_FALSE(arr1 == arr2);
    // EXPECT_TRUE(arr1 != arr2);
}

// Test exception safety
TEST(ArrayExceptionTest, OutOfRangeAccess) {
    Array<int, 5> arr;
    EXPECT_THROW(arr.at(5), std::out_of_range);
    EXPECT_THROW(arr.at(6), std::out_of_range);
    
    const Array<int, 5>& const_arr = arr;
    EXPECT_THROW(const_arr.at(5), std::out_of_range);
    
    Array<int, 0> empty_arr;
    EXPECT_THROW(empty_arr.at(0), std::out_of_range);
}

// Test with complex types
TEST(ArrayComplexTypeTest, StringArray) {
    Array<std::string, 3> str_arr;
    str_arr[0] = "hello";
    str_arr[1] = "world";
    str_arr[2] = "!";
    
    EXPECT_EQ(str_arr.front(), "hello");
    EXPECT_EQ(str_arr.back(), "!");
    
    Array<std::string, 3> str_arr_copy = str_arr;
    EXPECT_EQ(str_arr, str_arr_copy);
    
    str_arr.fill("test");
    for (const auto& s : str_arr) {
        EXPECT_EQ(s, "test");
    }
}