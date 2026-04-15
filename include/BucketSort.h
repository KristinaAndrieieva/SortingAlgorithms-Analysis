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
//
// using namespace std;
// template<typename  T>;

// class BucketSort {
//
//     public:
//
//     static void bucketSortArray(Array <T>& arr) {
//         int size = arr.getSize();
//         if (size <= 1) {
//             return;
//         }
//
//         T maxValue = arr.findMax();
//         T minValue = arr.findMin();
//         int countBucket = sqrt(size);
//         // int index;
//
//         Array <T>** buckets = new Array <T>*[countBucket];
//
//         for (int i = 0; i < countBucket; i++) {
//             buckets[i] = new Array <T>();
//         }
//
//         for (int i = 0; i < size; i++) {
//             T value = arr.getValue(i);
//             // index = (int)((double)(value - minValue) / (maxValue - minValue) * (countBucket - 1));
//             // buckets[index] -> set(value);
//         }
//
//         int currentIdx = 0;
//         for (int i = 0; i < countBucket; i++) {
//             if (buckets[i] -> getSize() > 1) {
//                 QuickSort <T> ::quickSortArray(*buckets[i],"Centre",0,buckets[i] -> getSize() - 1);
//             }
//
//             for (int j = 0; j < buckets[i] -> getSize(); j++) {
//                 arr.set(buckets[i]->getValue(j), currentIdx);
//                 currentIdx++;
//             }
//             delete buckets[i];
//         }
//
//         delete[] buckets;
//     }
//
//
//
//     static void bucketSortSingleList(SingleLinkedList<T>& slist) {
//         if (slist.head == nullptr || slist.head->next == nullptr) {
//             return;
//         }
//
//         T minValue = slist.findMin();
//         T maxValue = slist.findMax();
//         int size = slist.getSize();
//
//         if (maxValue == minValue) {
//             return;
//         }
//
//         int countBucket = sqrt(size);
//         SingleLinkedList<T>* buckets = new SingleLinkedList<T>[countBucket];
//
//         typename SingleLinkedList<T>::Node* curr = slist.head;
//         while (curr != nullptr) {
//             // int bucketIdx = (int)((double)(curr->data - minValue) / (maxValue - minValue) * (countBucket - 1));
//             //
//             // buckets[bucketIdx].pushBack(curr->data);
//             // curr = curr->next;
//         }
//
//         slist.head = nullptr;
//         slist.tail = nullptr;
//
//         for (int i = 0; i < countBucket; i++) {
//             if (buckets[i].head != nullptr) {
//                 QuickSort<T>::quickSortSingleList(buckets[i], "Centre", buckets[i].head, buckets[i].getTail());
//
//                 if (slist.head == nullptr) {
//                     slist.head = buckets[i].head;
//                 } else {
//                     slist.tail->next = buckets[i].head;
//                 }
//                 slist.tail = buckets[i].getTail();
//             }
//         }
//
//         for (int i = 0; i < countBucket; i++) {
//             buckets[i].head = nullptr;
//             buckets[i].tail = nullptr;
//         }
//         delete[] buckets;
//     }
//
//
//     static void bucketSortDoubleList(DoubleLinkedList<T>& dlist) {
//         if (dlist.head == nullptr || dlist.head->next == nullptr) return;
//
//         T minValue = dlist.findMin();
//         T maxValue = dlist.findMax();
//         int size = dlist.getSize();
//
//         if (minValue == maxValue) return;
//
//         int bucketCount = sqrt(size);
//         DoubleLinkedList<T>* buckets = new DoubleLinkedList<T>[bucketCount];
//
//         typename DoubleLinkedList<T>::Node* curr = dlist.head;
//         while (curr != nullptr) {
//             // int bucketIdx = (int)((double)(curr->data - minValue) / (maxValue - minValue) * (bucketCount - 1));
//             //
//             // buckets[bucketIdx].pushBack(curr->data);
//             // curr = curr->next;
//         }
//
//         dlist.head = nullptr;
//         dlist.tail = nullptr;
//
//
//         for (int i = 0; i < bucketCount; i++) {
//             if (buckets[i].head != nullptr) {
//                 QuickSort<T>::quickSortDoubleList(buckets[i], "Centre", buckets[i].head, buckets[i].tail);
//
//                 if (dlist.head == nullptr) {
//                     dlist.head = buckets[i].head;
//                     dlist.head->prev = nullptr;
//                 } else {
//                     dlist.tail->next = buckets[i].head;
//                     buckets[i].head->prev = dlist.tail;
//                 }
//                 dlist.tail = buckets[i].tail;
//             }
//         }
//
//         for (int i = 0; i < bucketCount; i++) {
//             buckets[i].head = nullptr;
//             buckets[i].tail = nullptr;
//         }
//         delete[] buckets;
//     }
// };

#endif //BUCKETSORT_H
