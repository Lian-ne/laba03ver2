#pragma once

#include <iostream>

namespace Sorting {

enum class ArrayType {
    StaticArray = 1,
    DynamicArray
};

struct FunctionResult {
    int permutationsCount;
    int comparisonsCount;
};

[[nodiscard]] FunctionResult CalculateBubbleSort(int* array, bool isAscending, size_t arraySize);
[[nodiscard]] FunctionResult CalculateSelectionSort(int* array, bool isAscending, size_t arraySize);

void RunStaticArraySort(int* array);
void RunDynamicArraySort(int* array, size_t arraySize);

void SelectTask();
void StartApp();
}  // namespace Sorting
