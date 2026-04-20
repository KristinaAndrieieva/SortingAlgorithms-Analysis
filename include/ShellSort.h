//
// Created by krist on 14.04.2026.
//

#ifndef SHELLSORT_H
#define SHELLSORT_H

#include "Array.h"
#include <string>


using namespace std;

template<typename T>
class ShellSort {

    public:
    /**
         * ShellSort dla tablicy
         * Wybiera sekwencji odstępu , dalej na podstawie tego wykonuje sortowanie dla tablicy
         */
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
            while (h < size / 3) {
                h = 3 * h + 1;
            }
            while (h >= 1) {
                arr.insertionSort(h);
                h /= 3;
            }
        }
    }


    /**
         * ShellSort dla singlelist
         * Wybiera sekwencji odstępu , dalej na podstawie tego wykonuje sortowanie dla singlelist
         */
    static void shellSortSingleList(SingleLinkedList<T>& slist, string gapStr) {
        int size = slist.getSize();
        if (size <= 1) return;

        if (gapStr == "Option 1") {
            for (int gap = size / 2; gap > 0; gap /= 2) {
                slist.insertionSort(gap);
            }
        }
        else if (gapStr == "Option 2") {
            int hs = 1;
            while (hs < size/3) {
                hs = 3 * hs + 1;
            }
            while (hs >= 1) {
                slist.insertionSort(hs);
                hs /= 3;
            }
        }
    }

    /**
         * ShellSort dla doublelist
         * Wybiera sekwencji odstępu , dalej na podstawie tego wykonuje sortowanie dla doublelist
         */
    static void shellSortDoubleList(DoubleLinkedList<T>& dlist, string gapStr) {
        int size = dlist.getSize();
        if (size <= 1) return;

        if (gapStr == "Option 1") {
            for (int gap = size / 2; gap > 0; gap /= 2) {
                dlist.insertionSort(gap);
            }
        } else if (gapStr == "Option 2") {
            int hd = 1;
            while (hd < size/3) {
                hd = 3 * hd + 1;
            }
            while (hd >= 1) {
                dlist.insertionSort(hd);
                hd /= 3;
            }


        }
    }
};

#endif //SHELLSORT_H
