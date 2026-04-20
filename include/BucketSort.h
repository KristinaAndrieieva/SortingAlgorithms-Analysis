//
// Created by krist on 7.04.2026.
//

#ifndef BUCKETSORT_H
#define BUCKETSORT_H

#include <cmath>

#include "Array.h"
#include "QuickSort.h"
#include <iostream>
#include <math.h>

#include "DoubleLinkedList.h"

using namespace std;
template<typename  T>

class BucketSort {

    public:
    /**
         * implementacja sortowania kubełkowego dla tablicy dynamicznej Array.
         * stworzamy kubełki za wzorem, dodajemy elementy do kubełków , a następnie sortujemy każdy kubełek
         * z osobna za pomocą QuickSort.
         */
    static void bucketSortArray(Array <T>& arr) {
        int size = arr.getSize();
        if (size <= 1) {
            return;
        }

        T maxValue ,minValue;
        int countBucket = sqrt(size);
        if (countBucket < 1) countBucket = 1;
        int index;
        int newindex = 0;

        if constexpr (!is_same_v<T, string>) {
            minValue = arr.findMin();
            maxValue = arr.findMax();
            if (minValue == maxValue) return;
        }

        // Alokacja tablicy wskaźników
        Array <T>** buckets = new Array <T>*[countBucket];

        for (int i = 0; i < countBucket; i++) {
            buckets[i] = new Array<T>();
        }

        //// Distribution:
        for (int i = 0; i < size; i++) {
            T value = arr.getValue(i);

            if constexpr (is_same_v<T, string>) {
                // Wzór dla stringów
                unsigned char firstChar = (value.length() > 0) ? (unsigned char)value[0] : 0;
                index = (int)((double)firstChar / 256.0 * countBucket);
            } else {
                //wzór dla liczb
                index = (int)((double)(value - minValue) / (maxValue - minValue) * (countBucket - 1));
            }

            if(index < 0) index = 0;
            if(index >= countBucket) index = countBucket - 1;

            buckets[index]->set(value);
        }

        //sortowanie kubełków,po tym usunuęcie
        for (int i = 0; i < countBucket; i++) {
            if (buckets[i] -> getSize() > 1) {
                QuickSort <T> ::quickSortArray(*buckets[i],"Centre",0,buckets[i] -> getSize() - 1);
            }

            for (int j = 0; j < buckets[i] -> getSize(); j++) {
                arr.set(buckets[i]->getValue(j), newindex);
                newindex++;
            }
            delete buckets[i];
        }
        delete[] buckets;
    }


    /**
        * implementacja sortowania kubełkowego dla Listy jednokierunkowej SingleList.
        * stworzamy kubełki za wzorem, dodajemy elementy do kubełków , a następnie sortujemy każdy kubełek
        * z osobna za pomocą QuickSort.
        */
    static void bucketSortSingleList(SingleLinkedList<T>& slist) {
        if (slist.head == nullptr || slist.head->next == nullptr) {
            return;
        }

        T minValue, maxValue ;
        int size = slist.getSize();
        int bucketIdx;
        
        int countBucket = sqrt(size);
        if (countBucket < 1) countBucket = 1;

        if constexpr (!is_same_v<T, string>) {
            minValue = slist.findMin();
            maxValue = slist.findMax();
            if (maxValue == minValue) return;
        }

        // każdy kubełek jest teraz niezależnym obiektem
        SingleLinkedList<T>* buckets = new SingleLinkedList<T>[countBucket];


        // kopiujemy dane do kubełków.
        typename SingleLinkedList<T>::Node* currentHead = slist.head;
        while (currentHead != nullptr) {
            if constexpr (is_same_v<T, string>) {
                unsigned char firstChar = (currentHead->data.length() > 0) ? (unsigned char)currentHead->data[0] : 0;
                bucketIdx = (int)((double)firstChar / 256.0 * countBucket);
            } else {
                bucketIdx = (int)((double)(currentHead->data - minValue) / (maxValue - minValue) * (countBucket - 1));
            }

            if (bucketIdx < 0) bucketIdx = 0;
            if (bucketIdx >= countBucket) bucketIdx = countBucket - 1;

            buckets[bucketIdx].pushBack(currentHead->data);
            currentHead = currentHead->next;
        }

        slist.clear();

        //sortowanie kubełków,po tym usunuęcie
        for (int i = 0; i < countBucket; i++) {
            if (buckets[i].head != nullptr) {
                QuickSort<T>::quickSortSingleList(buckets[i], "Centre", buckets[i].head, buckets[i].getTail());

                if (slist.head == nullptr) {
                    slist.head = buckets[i].head;
                } else {
                    slist.tail->next = buckets[i].head;
                }
                slist.tail = buckets[i].getTail();
            }
        }

        for (int i = 0; i < countBucket; i++) {
            buckets[i].head = nullptr;
            buckets[i].tail = nullptr;
        }
        delete[] buckets;
    }

    /**
           * implementacja sortowania kubełkowego dla Listy dwukierunkowej DoubleList..
           * stworzamy kubełki za wzorem, dodajemy elementy do kubełków , a następnie sortujemy każdy kubełek
           * z osobna za pomocą QuickSort.
             */
    static void bucketSortDoubleList(DoubleLinkedList<T>& dlist) {
        if (dlist.head == nullptr || dlist.head->next == nullptr) return;

        T minValue, maxValue;
        int size = dlist.getSize();

        int bucketCount = sqrt(size);
        if (bucketCount < 1) bucketCount = 1;

        if constexpr (!is_same_v<T, string>) {
            minValue = dlist.findMin();
            maxValue = dlist.findMax();
            if (minValue == maxValue) return;
        }

        // każdy kubełek jest teraz niezależnym obiektem
        DoubleLinkedList<T>* buckets = new DoubleLinkedList<T>[bucketCount];


        // kopiujemy dane do kubełków.
        typename DoubleLinkedList<T>::Node* currentHead = dlist.head;
        while (currentHead != nullptr) {
            int bucketIdx;

            if constexpr (is_same_v<T, string>) {
                unsigned char firstChar = (currentHead->data.length() > 0) ? (unsigned char)currentHead->data[0] : 0;
                bucketIdx = (int)((double)firstChar / 256.0 * bucketCount);
            } else {
                bucketIdx = (int)((double)(currentHead->data - minValue) / (maxValue - minValue) * (bucketCount - 1));
            }

            if (bucketIdx < 0) bucketIdx = 0;
            if (bucketIdx >= bucketCount) bucketIdx = bucketCount - 1;

            buckets[bucketIdx].pushBack(currentHead->data);
            currentHead = currentHead->next;
        }

        dlist.clear();


        //sortowanie kubełków,po tym usunuęcie
        for (int i = 0; i < bucketCount; i++) {
            if (buckets[i].head != nullptr) {
                QuickSort<T>::quickSortDoubleList(buckets[i], "Centre", buckets[i].head, buckets[i].tail);

                if (dlist.head == nullptr) {
                    dlist.head = buckets[i].head;
                    dlist.head->prev = nullptr;
                } else {
                    dlist.tail->next = buckets[i].head;
                    buckets[i].head->prev = dlist.tail;
                }
                dlist.tail = buckets[i].tail;
            }
        }

        for (int i = 0; i < bucketCount; i++) {
            buckets[i].head = nullptr;
            buckets[i].tail = nullptr;
        }
        delete[] buckets;
    }
};

#endif //BUCKETSORT_H
