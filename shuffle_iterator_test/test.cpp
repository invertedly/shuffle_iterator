#include "pch.h"

#include <forward_list>
#include <unordered_map>

#include "../shuffle_iterator/shuffle_range_sfinae.h"
//#include "../shuffle_iterator_concepts/shuffle_range_concepts.h"

TEST(Arr, Test) {
	int a[] = { 0, 4, 5, 2, 8, 1 };
	auto shuffle_a1 = make_shuffle(std::begin(a), std::end(a));
	auto shuffle_a2 = make_shuffle(std::begin(a), std::end(a));

	EXPECT_TRUE(!std::equal(a, a + 6, shuffle_a1.begin(), shuffle_a1.end()));
	EXPECT_TRUE(!std::equal(a, a + 6, shuffle_a2.begin(), shuffle_a2.end()));
	EXPECT_TRUE(!std::equal(shuffle_a1.begin(), shuffle_a1.end(), shuffle_a2.begin(), shuffle_a2.end()));
}

TEST(ForwardList, Test) {
	std::forward_list< int > a = { 0, 4, 5, 2, 8, 1 };
	auto shuffle_a1 = make_shuffle(std::begin(a), std::end(a));
	auto shuffle_a2 = make_shuffle(std::begin(a), std::end(a));

	EXPECT_TRUE(!std::equal(a.begin(), a.end(), shuffle_a1.begin(), shuffle_a1.end()));
	EXPECT_TRUE(!std::equal(a.begin(), a.end(), shuffle_a2.begin(), shuffle_a2.end()));
	EXPECT_TRUE(!std::equal(shuffle_a1.begin(), shuffle_a1.end(), shuffle_a2.begin(), shuffle_a2.end()));
}

TEST(UnorderedMap, Test) {
	std::unordered_map< int, int > a = {
		{ 0, 0 }, { 4, 0 }, { 5, 0 }, { 2, 0 }, { 8, 0 }, { 1, 0 }
	};
	auto shuffle_a1 = make_shuffle(std::begin(a), std::end(a));
	auto shuffle_a2 = make_shuffle(std::begin(a), std::end(a));

	EXPECT_TRUE(!std::equal(a.begin(), a.end(), shuffle_a1.begin(), shuffle_a1.end()));
	EXPECT_TRUE(!std::equal(a.begin(), a.end(), shuffle_a2.begin(), shuffle_a2.end()));
	EXPECT_TRUE(!std::equal(shuffle_a1.begin(), shuffle_a1.end(), shuffle_a2.begin(), shuffle_a2.end()));
}