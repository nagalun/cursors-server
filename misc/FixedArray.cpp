#include "FixedArray.hpp"
#include "../types.hpp"

#include <cstdlib>
#include <cstring>

template <typename T>
FixedArray<T>::FixedArray(const std::size_t max_items)
: size(max_items),
  data((T *)std::malloc(size * sizeof(T))),
  i(0) {
	if (data == nullptr) {
		throw; /* Hm... */
	} else {
		std::memset((void *)data, 0, size);
	}
}

template <typename T>
FixedArray<T>::~FixedArray() {
	std::free(data);
}

template <typename T>
void FixedArray<T>::insert(const T value) {
	const std::size_t remaining = size - i;
	if(remaining != 0) { /* Check if space is available */
		data[i] = value;
		++i;
	}
}

template <typename T>
void FixedArray<T>::clear() {
	i = 0;
	/* std::memset((void *)data, 0, size); */
}

template <typename T>
T * const FixedArray<T>::get_data() const {
	return data;
}

template <typename T>
size_t FixedArray<T>::get_items() const {
	return i;
}

template class FixedArray<point_t>;
template class FixedArray<line_t>;
