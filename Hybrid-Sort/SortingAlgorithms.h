#ifndef SORTING_ALGORITHMS_H
#define SORTING_ALGORITHMS_H

#include <memory>

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
	void Merge(Container<T, std::allocator<T> >& arr, const size_t& left, const size_t& mid, const size_t& right) {
		const size_t arr1Size = mid - left + 1;
		const size_t arr2Size = right - mid;

		std::vector<T>leftArr(arr.begin() + left, arr.begin() + left + arr1Size);
		std::vector<T>rightArr(arr.begin() + mid + 1, arr.begin() + mid + 1 + arr2Size);

		size_t arr1Index = 0;
		size_t arr2Index = 0;
		size_t mergedArrayIndex = left;

		while (arr1Index < arr1Size && arr2Index < arr2Size) {
			if (leftArr[arr1Index] <= rightArr[arr2Index]) {
				arr[mergedArrayIndex] = leftArr[arr1Index];
				++arr1Index;
			}
			else {
				;
				arr[mergedArrayIndex] = rightArr[arr2Index];
				++arr2Index;
			}
			++mergedArrayIndex;
		}

		while (arr1Index < arr1Size) {
			arr[mergedArrayIndex] = leftArr[arr1Index];
			++arr1Index;
			++mergedArrayIndex;
		}

		while (arr2Index < arr2Size) {
			arr[mergedArrayIndex] = rightArr[arr2Index];
			++arr2Index;
			++mergedArrayIndex;
		}
	}

	template< template < typename, typename > class Container, typename T >
	static void MergeSort(Container<T, std::allocator<T> >& arr, const size_t& begin, const size_t& end) {
		if (begin >= end)
			return;

		size_t mid = begin + (end - begin) / 2;
		MergeSort(arr, begin, mid);
		MergeSort(arr, mid + 1, end);
		Merge(arr, begin, mid, end);
	}
}

template< template < typename, typename > class Container, typename T >
void MergeSort(Container<T, std::allocator<T> >&arr, const size_t& n) {
	details::MergeSort(arr, 0, n);
}

#endif