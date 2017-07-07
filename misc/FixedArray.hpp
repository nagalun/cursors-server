#pragma once
#include <cstddef>

/* Fixed-size array */

template <typename T>
class FixedArray {
	size_t size; /* Size of array */
	T * data;
	size_t i; /* Everything behind this is being used by other data */

public:
	FixedArray(const size_t max_items);
	~FixedArray();

	void insert(const T value);
	void clear();
	
	T * const get_data() const;
	size_t get_items() const;
};
