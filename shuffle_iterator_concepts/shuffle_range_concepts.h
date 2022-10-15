#pragma once

#include <random>
#include <algorithm>
#include <numeric>
#include <ranges>
#include <iterator>

template <typename Iterator, bool = std::random_access_iterator<Iterator>>
class shuffle_range final
{
public:
	explicit shuffle_range(Iterator first, Iterator last) : offsets_(std::distance(first, last)), first_(first), last_(last)
	{
		std::random_device rd;
		std::mt19937 random_value_generator(rd());

		std::iota(offsets_.begin(), offsets_.end(), 0);

		std::ranges::shuffle(
			offsets_,
			random_value_generator
		);
	}

private:
	std::vector<size_t> offsets_;
	Iterator first_;
	Iterator last_;

public:
	class iterator final
	{
	private:
		using offset_iterator_type = std::vector<size_t>::iterator;
		using internal_iterator_value_type = typename std::iterator_traits<Iterator>::value_type;

		offset_iterator_type offsets_iterator_;
		const Iterator internal_data_begin_;

	public:
		using iterator_category = std::input_iterator_tag;
		using value_type = std::add_const_t<internal_iterator_value_type>;
		using reference = std::add_lvalue_reference_t<value_type>;
		using pointer = std::add_pointer_t<value_type>;
		using difference_type = void;

		explicit iterator(const Iterator& internal_data_begin, const offset_iterator_type& offset_iterator) :
			offsets_iterator_(offset_iterator), internal_data_begin_(internal_data_begin) { }

		reference operator*() const
		{
			return *std::next(internal_data_begin_, *offsets_iterator_);
		}
		iterator& operator++()
		{
			++offsets_iterator_;
			return *this;
		}
		bool operator==(const iterator& rhs) const
		{
			return offsets_iterator_ == rhs.offsets_iterator_;
		}
	};

	auto begin()
	{
		return iterator(first_, offsets_.begin());
	}

	auto end()
	{
		return iterator(first_, offsets_.end());
	}
};

template <typename Iterator>
class shuffle_range<Iterator, false> final
{
public:
	explicit shuffle_range(Iterator first, Iterator last)
	{
		std::random_device rd;
		std::mt19937 random_value_generator(rd());

		for (auto iter = first; iter != last; iter++)
		{
			input_range_.push_back(iter);
		}

		std::ranges::shuffle(
			input_range_,
			random_value_generator
		);
	}

private:
	std::vector<Iterator> input_range_;

public:
	class iterator final
	{
	private:
		using internal_iterator_type = typename std::vector<Iterator>::iterator;
		using internal_iterator_value_type = typename std::iterator_traits<Iterator>::value_type;

		internal_iterator_type internal_data_iterator_;

	public:
		using iterator_category = std::input_iterator_tag;
		using value_type = std::add_const_t<internal_iterator_value_type>;
		using reference = std::add_lvalue_reference_t<value_type>;
		using pointer = std::add_pointer_t<value_type>;
		using difference_type = void;

		explicit iterator(const internal_iterator_type& iterator) : internal_data_iterator_(iterator) {}

		reference operator*() const
		{
			return **internal_data_iterator_;
		}
		iterator& operator++()
		{
			++internal_data_iterator_;
			return *this;
		}
		bool operator==(const iterator& rhs) const
		{
			return internal_data_iterator_ == rhs.internal_data_iterator_;
		}
	};

	auto begin()
	{
		return iterator(input_range_.begin());
	}

	auto end()
	{
		return iterator(input_range_.end());
	}
};

template <std::input_iterator Iterator>
shuffle_range<Iterator> make_shuffle(Iterator begin, Iterator end)
{
	return shuffle_range<Iterator>(begin, end);
}
