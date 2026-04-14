//
// Created by krist on 7.04.2026.
//

#ifndef QUICKSORT_H
#define QUICKSORT_H


#include <iostream>
#include <string>
#include <ctime>

using namespace std;
template<typename  T>

class QuickSort {
public:

    static void quickSortArray(Array <T>& arr, string pivotStr,int left,int right) {
        srand(time(NULL));
        if (left >= right) {
            return;
        }
        int pivotIndex;


        if (pivotStr == "Centre") {
            pivotIndex = (left + right) / 2;
        }else if (pivotStr == "Left") {
            pivotIndex = left;
        } else if (pivotStr == "Random") {
            pivotIndex = left + rand() % (right - left + 1);
        }else if (pivotStr == "Right") {
            pivotIndex = right;
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


    static void quickSortList(SingleLinkedList<T>& list, string pivotStr,
                              typename SingleLinkedList<T>::Node* left,
                              typename SingleLinkedList<T>::Node* right) {

        if (!left || !right || left == right || left == right->next) return;


        typename SingleLinkedList<T>::Node* pivotNode = left;

        if (pivotStr == "Centre") {
            typename SingleLinkedList<T>::Node* fast = left;
            while (fast != right && fast->next != right) {
                pivotNode = pivotNode->next;
                fast = fast->next->next;
            }
        }
        else if (pivotStr == "Random") {
            int distance = 0;
            typename SingleLinkedList<T>::Node* temp = left;
            while (temp != right) { distance++; temp = temp->next; }
            int randomIndex = rand() % (distance + 1);
            pivotNode = left;
            for (int k = 0; k < randomIndex; k++) pivotNode = pivotNode->next;
        }
        else if (pivotStr == "Right") {
            pivotNode = right;
        }


        T pivotValue = pivotNode->data;
        list.swap(pivotNode, right);

        typename SingleLinkedList<T>::Node* j = left;
        for (typename SingleLinkedList<T>::Node* i = left; i != right; i = i->next) {
            if ((i->data)< pivotValue) {
                list.swap(i, j);
                j = j->next;
            }
        }
        list.swap(j, right);
        typename SingleLinkedList<T>::Node* actualPivot = j;

        if (actualPivot != left) {
            typename SingleLinkedList<T>::Node* prev = left;
            while (prev->next != actualPivot) prev = prev->next;
            quickSortList(list, pivotStr, left, prev);
        }
        quickSortList(list, pivotStr, actualPivot->next, right);
    }
};
#endif //QUICKSORT_H