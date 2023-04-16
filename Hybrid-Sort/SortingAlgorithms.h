#ifndef SORTING_ALGORITHMS_H
#define SORTING_ALGORITHMS_H

#include <memory>
#include <vector>
#include <algorithm>

#define INSERTION_SORT_ARRAY_SIZE 30
#define PERCENTAGE_OF_SORTED_ITEMS 0.75

template< template < typename, typename > class Container, typename T >
void InsertionSort(Container<T, std::allocator<T> >& arr, const size_t& n) {
	if (n > 0) {
		InsertionSort(arr, n - 1);
		T x = arr[n];
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

	template < template < typename, typename > class Container, typename T >
	float GetPercentageOfSortedItems(Container<T, std::allocator<T> >& arr, const size_t& n) {
		int sortedElementCount = 0;
		
		for (int i = 1; i <= n; ++i) {
			if (arr[i] >= arr[i - 1]) {
				++sortedElementCount;
			}
			else {
				break;
			}
		}

		return sortedElementCount / (float)n;
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
void HybridSort(Container<T, std::allocator<T> >& arr, const size_t& n) {
	float sortedPercentage = details::GetPercentageOfSortedItems(arr, n);

	if (sortedPercentage == 1)
		return;

	if (sortedPercentage >= PERCENTAGE_OF_SORTED_ITEMS) {
		InsertionSort(arr, n);
	}
	
	if (n <= INSERTION_SORT_ARRAY_SIZE) {
		InsertionSort(arr, n);
	}
	else {
		QuickSort(arr, 0, n);
	}
}
#endif