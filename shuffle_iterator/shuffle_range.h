#pragma once

#include <random>
#include <algorithm>
#include <numeric>
#include <ranges>

template <typename It>
class shuffle_range final
{
public:
	class iterator;

	explicit shuffle_range(It begin_it, It end_it) :
	range_begin_(begin_it),
	range_end_(end_it),
	offsets_from_begin_(std::distance(begin_it, end_it))
	{
		std::iota(
			offsets_from_begin_.begin(),
			offsets_from_begin_.end(), 
			0
		);

		std::random_device rd;
		std::mt19937 g(rd());

		std::ranges::shuffle(
			offsets_from_begin_,
			g
		);
	}

private:
	It range_begin_;
	It range_end_;
	std::vector<size_t> offsets_from_begin_;

	It get_iterator_from_offset(const size_t offset_idx) const
	{
		if (offset_idx >= offsets_from_begin_.size())
		{
			return range_end_;
		}
		It res = range_begin_;
		std::advance(
			res,
			offsets_from_begin_[offset_idx]
		);
		return res;
	}

public:
	class iterator final
	{
	private:
		using traits = std::iterator_traits<It>;

	public:
		using value_type = typename traits::value_type;
		using reference = typename traits::reference;
		using iterator_category = std::input_iterator_tag;
		using pointer = typename traits::pointer;
		using difference_type = void;

	private:
		friend class shuffle_range;
		shuffle_range* range_ptr_;
		size_t offset_idx_;
		It range_it_;

	public:
		explicit iterator(shuffle_range* shuffle_range, const size_t offset_idx = 0) :
		range_ptr_(shuffle_range),
		offset_idx_(offset_idx),
		range_it_(range_ptr_->get_iterator_from_offset(offset_idx))
		{
		}

		value_type operator*() const
		{
			return *range_it_;
		}

		iterator& operator++()
		{
			if (offset_idx_ != range_ptr_->offsets_from_begin_.size())
			{
				range_it_ = range_ptr_->get_iterator_from_offset(++offset_idx_);
			}
			return *this;
		}

		bool operator==(const iterator& rhs) const
		{
			return range_it_ == rhs.range_it_;
		}
	};

	auto begin()
	{
		return iterator(this, 0);
	}

	auto end()
	{
		return iterator(this, offsets_from_begin_.size());
	}
};