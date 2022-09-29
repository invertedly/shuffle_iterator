#include "pch.h"

#include <forward_list>
#include <unordered_map>

#include "../shuffle_iterator/shuffle_range.h"

TEST(Arr, Test) {
	int a[] = { 0, 4, 5, 2, 8, 1 };
	auto shuffle_a1 = shuffle_range(a, a + 6);
	auto shuffle_a2 = shuffle_range(a, a + 6);

	EXPECT_TRUE(!std::equal(a, a + 6, shuffle_a1.begin(), shuffle_a1.end()));
	EXPECT_TRUE(!std::equal(a, a + 6, shuffle_a2.begin(), shuffle_a2.end()));
	EXPECT_TRUE(!std::equal(shuffle_a1.begin(), shuffle_a2.end(), shuffle_a2.begin(), shuffle_a2.end()));
}

TEST(ForwardList, Test) {
	std::forward_list< int > a = { 0, 4, 5, 2, 8, 1 };
	auto shuffle_a1 = shuffle_range(a.begin(), a.end());
	auto shuffle_a2 = shuffle_range(a.begin(), a.end());

	EXPECT_TRUE(!std::equal(a.begin(), a.end(), shuffle_a1.begin(), shuffle_a1.end()));
	EXPECT_TRUE(!std::equal(a.begin(), a.end(), shuffle_a2.begin(), shuffle_a2.end()));
	EXPECT_TRUE(!std::equal(shuffle_a1.begin(), shuffle_a2.end(), shuffle_a2.begin(), shuffle_a2.end()));
}

TEST(UnorderedMap, Test) {
	std::unordered_map< int, int > a = {
		{ 0, 0 }, { 4, 0 }, { 5, 0 }, { 2, 0 }, { 8, 0 }, { 1, 0 }
	};
	auto shuffle_a1 = shuffle_range(a.begin(), a.end());
	auto shuffle_a2 = shuffle_range(a.begin(), a.end());

	EXPECT_TRUE(!std::equal(a.begin(), a.end(), shuffle_a1.begin(), shuffle_a1.end()));
	EXPECT_TRUE(!std::equal(a.begin(), a.end(), shuffle_a2.begin(), shuffle_a2.end()));
	EXPECT_TRUE(!std::equal(shuffle_a1.begin(), shuffle_a2.end(), shuffle_a2.begin(), shuffle_a2.end()));
}