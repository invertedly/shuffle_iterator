#pragma once

#include <random>
#include <algorithm>
#include <numeric>
#include <ranges>

template <typename Iterator>
constexpr static bool is_random_access_iterator_v = std::is_convertible_v< 
	typename std::iterator_traits<Iterator>::iterator_category,
	std::random_access_iterator_tag
>;

template <typename Iterator>
constexpr static bool is_input_iterator_v = std::is_convertible_v< 
	typename std::iterator_traits<Iterator>::iterator_category,
	std::input_iterator_tag
>;


template <typename Iterator, bool = is_random_access_iterator_v<Iterator>>
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

		offset_iterator_type offsets_iterator_;
		const Iterator internal_data_begin_;

	public:
		using iterator_category = std::input_iterator_tag;
		using value_type = std::add_const_t<typename std::iterator_traits<Iterator>::value_type>;
		using reference = std::add_lvalue_reference_t<value_type>;
		using pointer = std::add_pointer_t<value_type>;
		using difference_type = void;

		explicit iterator(Iterator internal_data_begin, offset_iterator_type offset_iterator) noexcept :
		offsets_iterator_(std::move(offset_iterator)), internal_data_begin_(std::move(internal_data_begin)) { }

		reference operator*() const
		{
			return *std::next(internal_data_begin_, *offsets_iterator_);
		}
		iterator& operator++() noexcept
		{
			++offsets_iterator_;
			return *this;
		}
		iterator operator++(int) noexcept
		{
			iterator result = *this;
			++ *this;
			return result;
		}
		bool operator==(const iterator& rhs) const noexcept
		{
			return offsets_iterator_ == rhs.offsets_iterator_;
		}
	};

	auto begin() noexcept
	{
		return iterator(first_, offsets_.begin());
	}

	auto end() noexcept
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

		for (auto iter = first; iter != last; ++iter)
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

		internal_iterator_type internal_data_iterator_;

	public:
		using iterator_category = std::input_iterator_tag;
		using value_type = std::add_const_t<typename std::iterator_traits<Iterator>::value_type>;
		using reference = std::add_lvalue_reference_t<value_type>;
		using pointer = std::add_pointer_t<value_type>;
		using difference_type = void;

		explicit iterator(internal_iterator_type iterator) noexcept : internal_data_iterator_(std::move(iterator)) {}

		reference operator*() const
		{
			return **internal_data_iterator_;
		}
		iterator& operator++() noexcept
		{
			++internal_data_iterator_;
			return *this;
		}
		iterator operator++(int) noexcept
		{
			iterator result = *this;
			++* this;
			return result;
		}
		bool operator==(const iterator& rhs) const noexcept
		{
			return internal_data_iterator_ == rhs.internal_data_iterator_;
		}
	};

	auto begin() noexcept
	{
		return iterator(input_range_.begin());
	}

	auto end() noexcept
	{
		return iterator(input_range_.end());
	}
};

template <typename Iterator, typename = std::enable_if_t<is_input_iterator_v<Iterator>>>
shuffle_range<Iterator> make_shuffle(Iterator begin, Iterator end)
{
	return shuffle_range<Iterator>(begin, end);
}
