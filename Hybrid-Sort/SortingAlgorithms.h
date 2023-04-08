#ifndef SORTING_ALGORITHMS_H
#define SORTING_ALGORITHMS_H

#include <memory>
#include <vector>

#define INSERTION_SORT_ARRAY_SIZE 30
#define QUICK_SORT_ARRAY_SIZE 2000

template< template < typename, typename > class Container, typename T >
void InsertionSort(Container<T, std::allocator<T> >& arr, const size_t& n) {
	if (n > 0) {
		InsertionSort(arr, n - 1);
		int32_t x = arr[n];
		int32_t j = n - 1;

		while (j >= 0 && arr[j] > x) {
			arr[j + 1] = arr[j];
			--j;
		}

		arr[j + 1] = x;
	}
}

namespace details {
	template< template < typename, typename > class Container, typename T >
	int Partition(Container<T, std::allocator<T> >& arr, const size_t& low, const size_t& top) {
		T pivot = arr[low];
		int i = low - 1;
		int j = top + 1;

		while (true) {
			do {
				++i;
			} while (arr[i] < pivot);

			do {
				--j;
			} while (arr[j] > pivot);

			if (i >= j)
				return j;

			std::swap(arr[i], arr[j]);
		}
	}
}

template< template < typename, typename > class Container, typename T >
void QuickSort(Container<T, std::allocator<T> >& arr, const size_t& low, const size_t& top) {
	if (low >= top) {
		return;
	}

	int partition = details::Partition(arr, low, top);

	QuickSort(arr, low, partition);
	QuickSort(arr, partition + 1, top);
}

template< template < typename, typename > class Container, typename T >
void CountSort(Container<T, std::allocator<T> >& arr, const size_t& n) {
	T max = arr[0];
	
	for (int i = 1; i < n; ++i) {
		if (arr[i] > max) {
			max = arr[i];
		}
	}

	std::vector<T> output(max + 1);
	std::vector<T> count(max + 1);

	for (int i = 0; i < n; ++i) {
		++count[arr[i]];
	}

	for (int i = 1; i <= max; ++i) {
		count[i] += count[i - 1];
	}

	for (int i = n - 1; i >= 0; --i) {
		output[count[arr[i]] - 1] = arr[i];
		--count[arr[i]];
	}

	for (int i = 0; i < n; ++i) {
		arr[i] = output[i];
	}
}

template< template < typename, typename > class Container, typename T >
void HybridSort(Container<T, std::allocator<T> >& arr, const size_t& n) {
	if (n <= INSERTION_SORT_ARRAY_SIZE) {
		InsertionSort(arr, n);
	}
	else if (n > INSERTION_SORT_ARRAY_SIZE && n < QUICK_SORT_ARRAY_SIZE) {
		QuickSort(arr, 0, n);
	}
	else {
		CountSort(arr, n + 1);
	}
}

#endif