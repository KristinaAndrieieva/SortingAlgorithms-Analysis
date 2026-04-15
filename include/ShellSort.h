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

    public:
    static void shellSortArray(Array <T>& arr, string gapStr) {
        int size = arr.getSize();
        if (size <= 1) {
            return;
        }

        if (gapStr == "Option 1") {
            for (int gap = size / 2; gap > 0; gap /= 2) {
                arr.insertionSort(gap);
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
                arr.insertionSort(h);
                h /= 3;
            }
        }
    }


    static void shellSortSingleList(SingleLinkedList<T>& slist, string gapStr) {
        int n = slist.getSize();
        if (n <= 1) return;

        if (gapStr == "Option 1") {
            for (int gap = n / 2; gap > 0; gap /= 2) {
                slist.insertionSort(gap);
            }
        }
        else if (gapStr == "Option 2") {
            int hs = 1;
            while (hs < n) {
                hs = 3 * hs + 1;
            }
            int h = hs / 9;
            if (h < 1) h = 1;

            while (h >= 1) {
                slist.insertionSort(h);
                h /= 3;
            }
        }
    }

    static void shellSortDoubleList(DoubleLinkedList<T>& dlist, string gapStr) {
        int n = dlist.getSize();
        if (n <= 1) return;

        if (gapStr == "Option 1") {
            for (int gap = n / 2; gap > 0; gap /= 2) {
                dlist.insertionSort(gap);
            }
        } else if (gapStr == "Option 2") {
            int hs = 1;
            while (hs < n) hs = 3 * hs + 1;
            int h = hs / 9;
            if (h < 1) h = 1;
            while (h >= 1) {
                dlist.insertionSort(h);
                h /= 3;
            }
        }
    }
};

#endif //SHELLSORT_H
