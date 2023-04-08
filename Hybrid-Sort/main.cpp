#include <iostream>
#include <vector>
#include "SortingAlgorithms.h"

int main()
{
    std::vector<int> arr = { 6, 9, 7, 65, 654, 645, 24, 0, 8 };
    HybridSort(arr, arr.size() - 1);

    for (int i = 0; i < arr.size(); ++i) {
        std::cout << arr[i] << " ";
    }
}