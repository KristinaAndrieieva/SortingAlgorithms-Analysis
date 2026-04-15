//
// Created by krist on 14.04.2026.
//

#ifndef SHELLSORT_H
#define SHELLSORT_H

#include "Array.h"
#include <string>
#include <cmath>

using namespace std;

template<typename T>
class ShellSort {
private:
    static void insertionSort(Array<T>& arr, int size, int gap) {
        for (int i = gap; i < size; i++) {
            T temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }

    public:
    static void shellSortArray(Array <T>& arr, string gapStr) {
        int size = arr.getSize();
        if (size <= 1) {
            return;
        }

        if (gapStr == "Option 1") {
            for (int gap = size / 2; gap > 0; gap /= 2) {
                insertionSort(arr, size, gap);
            }
        }
        else if (gapStr == "Option 2") {
            int h = 1;
            while (h < size) {
                h = 3 * h + 1;
            }
            h = h / 9;
            if (h < 1) h = 1;

            while (h >= 1) {
                insertionSort(arr, size, h);
                h /= 3;
            }
        }
    }
};

#endif //SHELLSORT_H
