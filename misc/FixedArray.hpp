#pragma once
#include <cstddef>

/* Fixed-size array */

template <typename T>
class FixedArray {
	std::size_t size; /* Size of array */
	T * data;
	std::size_t i; /* Everything behind this is being used by other data */

public:
	FixedArray(const std::size_t max_items);
	~FixedArray();

	void insert(const T value);
	void clear();
	
	T * const get_data() const;
	std::size_t get_items() const;
};
