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

class QuickSort {
public:

    void static quickSortArray(Array <T>& arr, string pivotStr,int left,int right) {
        if (left >= right) {
            return;
        }
        int pivotIndex;


        if (pivotStr == "Centre") {
            pivotIndex = (left + right) / 2;
        }else if (pivotStr == "Left") {
            pivotIndex = left;
        } else if (pivotStr == "Random") {
            pivotIndex = arr.RandomIndex();
        }

        T pivotValue = arr[pivotIndex];

        arr.swap(&arr[pivotIndex],&arr [right]);

        int j = left;
        for (int i = left; i < right; i++ ) {
            if (arr[i] < pivotValue) {
                arr.swap(&arr[i],&arr [j]);
                j++;
            }

        };

        arr.swap(&arr[j],&arr [right]);
        quickSortArray(arr,pivotStr,left,j - 1);
        quickSortArray(arr,pivotStr,j + 1,right);
    };
};