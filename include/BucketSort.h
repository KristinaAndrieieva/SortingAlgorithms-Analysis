//
// Created by krist on 7.04.2026.
//

#ifndef BUCKETSORT_H
#define BUCKETSORT_H
#include "Array.h"
#include "QuickSort.h"

template<typename  T>

class BucketSort {


    public:
    BucketSort();

    void static bucketSortArray(Array <T>& arr) {
        int size = arr.getSize();
        if (size <= 1) {
            return;
        }
        T maxValue = arr.findMax();
        T minValue = arr.findMin();
        T countBucket = maxValue - minValue + 1;
        int index;

        Array <T>** buckets = new Array <T>*[countBucket];

        for (int i = 0; i < countBucket; i++) {
            buckets[i] = new Array <T>();
        }

        for (int i = 0; i < size; i++) {
            T value = arr.getValue(i);
            index = (int)(value - minValue)* (countBucket-1) / (maxValue - minValue);
            buckets[index] -> set(value);
        }

        for (int i = 0; i < countBucket; i++) {
            if (buckets[i] -> getSize() > 1) {
                QuickSort<T>::quickSortArray(*buckets[i]);
            }
        }

        for (int i = 0; i < countBucket; i++) {
            for (int j = 0; j < buckets[i] -> getSize(); j++) {
                arr.setValue(j, buckets[i] -> getValue(j));
            }
            delete[] buckets[i];
        }

        delete[] buckets;
    }

};



#endif //BUCKETSORT_H
