#ifndef SORTING_ALGORITHMS_H
#define SORTING_ALGORITHMS_H

#include <memory>
#include <vector>

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
	void MergeSort(Container<T, std::allocator<T> >& arr, const size_t& begin, const size_t& end) {
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
	if (n <= 30) {
		InsertionSort(arr, n);
	}
	else {
		QuickSort(arr, 0, n);
	}
}

#endif