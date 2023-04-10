#include <iostream>
#include <vector>
#include <ctime>
#include "SortingAlgorithms.h"
#include "Experimentator.h"

#define ARRAY_SIZE 2000

int main() {
	srand((unsigned)time(NULL));
	std::vector<int> arr(ARRAY_SIZE);

	double time = 0;

#if ARRAY_SIZE <= 30
	time = GetAverageExecutionTime([&arr]() {
		InsertionSort(arr, arr.size() - 1);
		}, [&arr]() {
			for (int i = 0; i < ARRAY_SIZE; ++i) {
				arr[i] = rand();
			}
		});

	std::cout << "InsertionSort: " << time << " microseconds\n";
#endif // ARRAY_SIZE <= 30

	time = GetAverageExecutionTime([&arr]() {
		QuickSort(arr, 0, arr.size() - 1);
		}, [&arr]() {
			for (int i = 0; i < ARRAY_SIZE; ++i) {
				arr[i] = rand();
			}
		});

	std::cout << "QuickSort: " << time << " microseconds\n";

	time = GetAverageExecutionTime([&arr]() {
		CountSort(arr, arr.size());
		}, [&arr]() {
			for (int i = 0; i < ARRAY_SIZE; ++i) {
				arr[i] = rand();
			}
		});

	std::cout << "CountSort: " << time << " microseconds\n";

	time = GetAverageExecutionTime([&arr]() {
		HybridSort(arr, arr.size() - 1);
		}, [&arr]() {
			for (int i = 0; i < ARRAY_SIZE; ++i) {
				arr[i] = rand();
			}
		});

	std::cout << "HybridSort: " << time << " microseconds\n";

	return 0;
}