#include <iostream>
#include <vector>
#include <list>
#include "SortingAlgorithms.h"

int main()
{
    std::vector<int> arr = { 999, 53, 487 };
    HybridSort(arr, 1);

    for (auto it = arr.begin(); it != arr.end(); ++it) {
        std::cout << *it << " ";
    }

    std::vector<std::string> list = { "something", "text", "Test", "DSA", "cat", "dog" };
    HybridSort(list, list.size() - 1);

    std::cout << std::endl;
    for (auto it = list.begin(); it != list.end(); ++it) {
        std::cout << *it << " ";
    }
}