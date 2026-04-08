//
// Created by krist on 7.04.2026.
//

#ifndef QUICKSORT_H
#define QUICKSORT_H
#endif //QUICKSORT_H

#include <iostream>
#include <string>

using namespace std;
template<typename  T>

class QuickSort{
public:
    QuickSort();

    void static quickSortArray(Array <T>& arr, string pivotStr) {
        int size = arr.getSize();
        if (size < 1) {
            return;
        }
        int left = 0, right = size - 1;
        int pivot,i;

        if (pivotStr == "Centre") {
            i = (left + right) / 2;
        }else if (pivotStr == "Left") {
            i = left;
        } else if (pivotStr == "Random") {
            i = arr.RandomIndex();
        }

        pivot = arr[i];
        arr[i] = arr[right];

    };
};
