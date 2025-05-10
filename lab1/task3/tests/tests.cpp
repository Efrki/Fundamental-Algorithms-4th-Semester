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

	EXPECT_EQ(dq[0], 100);
	EXPECT_EQ(dq[2], 300);

	EXPECT_EQ(dq.at(1), 200);
	EXPECT_THROW(dq.at(3), std::out_of_range);

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

	sum = 0;
	for (auto it = dq.rbegin(); it != dq.rend(); it = dq.prev(it)) {
		sum += *it;
	}
	EXPECT_EQ(sum, 30);
}

TEST(DequeTest, Modifiers) {
	Deque<int, 5> dq;

	dq.push_back(1);
	dq.push_back(2);
	EXPECT_EQ(dq.back(), 2);
	dq.pop_back();
	EXPECT_EQ(dq.back(), 1);

	dq.push_front(0);
	EXPECT_EQ(dq.front(), 0);
	dq.pop_front();
	EXPECT_EQ(dq.front(), 1);

	auto pos = dq.begin();
	dq.insert(pos, 99);
	EXPECT_EQ(dq.front(), 99);

	dq.erase(pos);
	EXPECT_EQ(dq.size(), 1);

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

	dq.push_back(1);
	dq.push_back(2);

	dq.clear();
	EXPECT_TRUE(dq.empty());
}
TEST(DequeAssignmentTest, CopyAssignment) {
	Deque<int, 5> src;
	src.push_back(1);
	src.push_back(2);

	Deque<int, 5> dest;
	const Container<int, 5>& base_src = src;
	dest = base_src;

	ASSERT_EQ(dest.size(), 2);
	ASSERT_EQ(dest.front(), 1);
	ASSERT_EQ(dest.back(), 2);

	src.push_back(3);
	ASSERT_EQ(dest.size(), 2);
}

TEST(DequeAssignmentTest, MoveAssignment) {
	Deque<int, 5> src;
	src.push_back(10);
	src.push_back(20);

	Deque<int, 5> dest;
	dest = std::move(src);

	ASSERT_EQ(dest.size(), 2);
	ASSERT_EQ(dest.front(), 10);
	ASSERT_EQ(dest.back(), 20);

	ASSERT_TRUE(src.empty());
	ASSERT_EQ(src.size(), 0);

	Deque<int, 5> dest2 = Deque<int, 5>{30, 40};
	ASSERT_EQ(dest2.size(), 2);
	ASSERT_EQ(dest2.back(), 40);
}

TEST(DequeAssignmentTest, SelfAssignment) {
	Deque<int, 5> deque;
	deque.push_back(100);

	const Container<int, 5>& base = deque;
	deque = base;
	ASSERT_EQ(deque.size(), 1);
	ASSERT_EQ(deque.front(), 100);

	deque = deque;
	ASSERT_EQ(deque.size(), 1);
}

}  // namespace my_container

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}