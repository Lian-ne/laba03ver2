#include "sorting.hpp"
#include <iostream>
#include <random>

namespace {
const int kStaticArraySize = 5;

const int kMinArrayElement = 0;
const int kMaxArrayElement = 99;

[[nodiscard]] int* GenerateArray(int* array, size_t arraySize) {
    std::random_device r{};
    std::default_random_engine randomEngine(r());
    std::uniform_int_distribution distribution(kMinArrayElement, kMaxArrayElement);

    for (size_t i = 0; i < arraySize; ++i) {
        array[i] = distribution(randomEngine);
    }

    return array;
}

void CopyArray(int* sourceArray, int* newArray, size_t arraySize) {
    for (size_t i = 0; i < arraySize; ++i) {
        newArray[i] = sourceArray[i];
    }
}

void PrintSourceArray(int* array, size_t arraySize) {
    std::cout << "Исходный массив: ";
    for (size_t i = 0; i < arraySize; ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl << std::endl;
}

void PrintSortingType(bool isSelectionSort) {
    std::cout << "-------------------------------------" << std::endl;
    if (isSelectionSort) {
        std::cout << "Сортировка выбором" << std::endl;
    } else {
        std::cout << "Пузырьковая сортировка" << std::endl;
    }
    std::cout << "-------------------------------------" << std::endl;
}

void PrintArray(int* array, size_t arraySize, bool isStaticArray, bool isAscending) {
    if (isStaticArray) {
        std::cout << "Статический массив, отсортированный ";
    } else {
        std::cout << "Динамический массив, отсортированный ";
    }
    if (isAscending) {
        std::cout << "по возрастанию: ";
    } else {
        std::cout << "по убыванию: ";
    }
    for (size_t i = 0; i < arraySize; ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl << std::endl;
}

void PrintResult(Sorting::FunctionResult result) {
    std::cout << std::endl << "Количестов сравнений: " << result.comparisonsCount << std::endl;
    std::cout << "Количество перестановок: " << result.permutationsCount << std::endl;
}
}  // namespace

namespace Sorting {

[[nodiscard]] FunctionResult CalculateBubbleSort(int* array, bool isAscending, size_t arraySize) {
    int permutationsCount = 0;
    int comparisonsCount = 0;
    for (size_t i = 0; i < arraySize - 1; ++i) {
        bool swapped = false;
        for (size_t j = 0; j < arraySize - i - 1; ++j) {
            if ((array[j] > array[j + 1] && isAscending) || (array[j] < array[j + 1] && !isAscending)) {
                std::swap(array[j], array[j + 1]);
                ++permutationsCount;
                swapped = true;
            }
            ++comparisonsCount;
        }
        if (!swapped) {
            break;
        }
    }

    FunctionResult result = {permutationsCount, comparisonsCount};
    return result;
}

[[nodiscard]] FunctionResult CalculateSelectionSort(int* array, bool isAscending, size_t arraySize) {
    int permutationsCount = 0;
    int comarisonsCount = 0;
    for (size_t i = 0; i < arraySize - 1; ++i) {
        size_t changeIndex = i;
        for (size_t j = i + 1; j < arraySize; ++j) {
            if ((array[j] < array[changeIndex] && isAscending) || (array[j] > array[changeIndex] && !isAscending)) {
                changeIndex = j;
            }
            ++comarisonsCount;
        }
        if (changeIndex != i) {
            std::swap(array[i], array[changeIndex]);
            ++permutationsCount;
        }
    }
    FunctionResult result = {permutationsCount, comarisonsCount};
    return result;
}

void RunOutputFunction(int* array, size_t arraySize, bool isAscending, bool isSelectionSort) {
    FunctionResult sortingResult{};
    if (isSelectionSort) {
        sortingResult = CalculateSelectionSort(array, isAscending, arraySize);
    } else {
        sortingResult = CalculateBubbleSort(array, isAscending, arraySize);
    }

    PrintResult(sortingResult);
}

void RunStaticArraySort(int* array) {
    PrintSourceArray(array, kStaticArraySize);
    PrintSortingType(true);

    int selectionSortArray[kStaticArraySize];
    int bubbleSortArray[kStaticArraySize];

    CopyArray(array, selectionSortArray, kStaticArraySize);
    CopyArray(array, bubbleSortArray, kStaticArraySize);

    RunOutputFunction(selectionSortArray, kStaticArraySize, true, true);
    PrintArray(selectionSortArray, kStaticArraySize, true, true);

    RunOutputFunction(selectionSortArray, kStaticArraySize, true, true);
    PrintArray(selectionSortArray, kStaticArraySize, true, true);

    RunOutputFunction(selectionSortArray, kStaticArraySize, false, true);
    PrintArray(selectionSortArray, kStaticArraySize, true, false);

    PrintSortingType(false);

    RunOutputFunction(bubbleSortArray, kStaticArraySize, true, false);
    PrintArray(bubbleSortArray, kStaticArraySize, true, true);

    RunOutputFunction(bubbleSortArray, kStaticArraySize, true, false);
    PrintArray(bubbleSortArray, kStaticArraySize, true, true);

    RunOutputFunction(bubbleSortArray, kStaticArraySize, false, false);
    PrintArray(bubbleSortArray, kStaticArraySize, true, false);
}

void RunDynamicArraySort(int* array, size_t arraySize) {
    PrintSortingType(true);
    PrintSourceArray(array, arraySize);

    int* selectionSortArray = new int[arraySize];
    int* bubbleSortArray = new int[arraySize];

    CopyArray(array, selectionSortArray, arraySize);
    CopyArray(array, bubbleSortArray, arraySize);

    RunOutputFunction(selectionSortArray, arraySize, true, true);
    RunOutputFunction(selectionSortArray, arraySize, true, true);
    RunOutputFunction(selectionSortArray, arraySize, false, true);

    delete[] selectionSortArray;

    PrintSortingType(true);

    RunOutputFunction(bubbleSortArray, arraySize, true, false);
    RunOutputFunction(bubbleSortArray, arraySize, true, false);
    RunOutputFunction(bubbleSortArray, arraySize, false, false);

    delete[] bubbleSortArray;
}

void SelectTask() {
    int task{};
    std::cin >> task;

    int staticArray[kStaticArraySize]{};
    int* dynamicArray = nullptr;
    int dynamicArraySize{};

    switch (static_cast<ArrayType>(task)) {
        case ArrayType::StaticArray:
            RunStaticArraySort(GenerateArray(staticArray, kStaticArraySize));
            break;
        case ArrayType::DynamicArray:
            std::cout << "Введите размер для динамического массива: ";
            std::cin >> dynamicArraySize;

            dynamicArray = new int[dynamicArraySize];
            RunDynamicArraySort(GenerateArray(dynamicArray, dynamicArraySize), dynamicArraySize);

            delete[] dynamicArray;
            break;
        default:
            std::cout << "Введён неверный номер задачи" << std::endl;
            break;
    }
}

void StartApp() {
    char continueExecution = 'y';

    while (continueExecution == 'y') {
        std::cout << "1 - Сортировка статического массива" << std::endl;
        std::cout << "2 - Сортировка динамического массива" << std::endl;
        std::cout << "Введите (1 или 2): ";

        SelectTask();

        std::cout << "Хотите продолжить работу (y - продолжить, n - закончить): ";
        std::cin >> continueExecution;
    }
}
}  // namespace Sorting
