//
// Created by krist on 7.04.2026.
//

#ifndef BUCKETSORT_H
#define BUCKETSORT_H

#include "Array.h"
#include "QuickSort.h"
#include <iostream>

using namespace std;
template<typename  T>

class BucketSort {

    public:

    void static bucketSortArray(Array <T>& arr) {
        int size = arr.getSize();
        if (size <= 1) {
            return;
        }

        T maxValue = arr.findMax();
        T minValue = arr.findMin();
        int countBucket = maxValue - minValue + 1;
        int index;

        Array <T>** buckets = new Array <T>*[countBucket];

        for (int i = 0; i < countBucket; i++) {
            buckets[i] = new Array <T>();
        }

        for (int i = 0; i < size; i++) {
            T value = arr.getValue(i);
            index = (int)((double)(value - minValue) / (maxValue - minValue) * (countBucket - 1));
            buckets[index] -> set(value);
        }

        int currentIdx = 0;
        for (int i = 0; i < countBucket; i++) {
            if (buckets[i] -> getSize() > 1) {
                QuickSort <T> ::quickSortArray(*buckets[i],"Centre",0,buckets[i] -> getSize() - 1);
            }

            for (int j = 0; j < buckets[i] -> getSize(); j++) {
                arr.set(buckets[i]->getValue(j), currentIdx);
                currentIdx++;
            }
            delete buckets[i];
        }

        delete[] buckets;
    }

};



#endif //BUCKETSORT_H
