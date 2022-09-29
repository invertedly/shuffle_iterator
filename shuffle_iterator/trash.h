#pragma once

#pragma once

#include <unordered_map>
#include <random>
#include <iterator>

template <typename InputIt>
requires std::input_iterator<InputIt>
class make_shuffle final
{
	using value_t = typename InputIt::value_type;

public:
	make_shuffle(const InputIt& begin, const InputIt& end)
	{
		std::random_device rd;
		std::mt19937 gen(rd());

		for (auto it = begin; it != end; /*?*/it = std::next(it))
		{
			uint32_t random_key = gen();
			shuffle_container_.insert({ random_key, *it });
		} // foreach
	}

	class iterator
	{
	public:
		value_t& operator*() { return *shuffle_container_it_.second; }
		bool operator != (const iterator& rhs)
		{
			return shuffle_container_it_ != rhs.shuffle_container_it_;
		}
		void operator ++() { std::next(shuffle_container_it_); }
	private:
		using iterator_t = typename std::unordered_multimap<uint32_t, value_t>::iterator;
		explicit iterator(const iterator_t& it) : shuffle_container_it_(it) {}
		iterator_t shuffle_container_it_;
	};

	auto begin() const
	{
		return iterator(shuffle_container_.cbegin());
	}

	auto end() const
	{
		return iterator(shuffle_container_.cend());
	}

private:
	std::unordered_multimap<uint32_t, value_t> shuffle_container_;
};

//template <typename It>
//class shuffle_range final
//{
//};

//,
//std::enable_if<
//	std::is_same<
//	typename std::iterator_traits<It>::iterator_category,
//	std::input_iterator_tag
//	>::value_type
//>
