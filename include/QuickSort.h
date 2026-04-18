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

    static void quickSortArray(Array <T>& arr, string pivotStr,int left,int right){
        while (left < right) {
            int pivotIndex = right;


            if (pivotStr == "Centre") {
                pivotIndex = (left + right) / 2;
            } else if (pivotStr == "Left") {
                pivotIndex = left;
            } else if (pivotStr == "Random") {
                pivotIndex = left + rand() % (right - left + 1);
            } else if (pivotStr == "Right") {
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

            }
            arr.swap(&arr[j],&arr [right]);

            if (j - left < right - j) {
                quickSortArray(arr, pivotStr, left, j - 1);
                left = j + 1;
            } else {
                quickSortArray(arr, pivotStr, j + 1, right);
                right = j - 1;
            }
        }
    };


    static void quickSortSingleList(SingleLinkedList<T>& slist, string pivotStr,
                              typename SingleLinkedList<T>::Node* left,
                              typename SingleLinkedList<T>::Node* right) {

        while(!left || !right || left == right || left == right->next) {
            typename SingleLinkedList<T>::Node* pivotNode = nullptr;

            if (pivotStr == "Left") {
                pivotNode = left;
            }else if (pivotStr == "Centre") {

                typename SingleLinkedList<T>::Node* fast = left;
                pivotNode = left;

                while (fast != right && fast->next != right) {
                    pivotNode = pivotNode->next;
                    fast = fast->next->next;
                }
            }else if (pivotStr == "Random") {
                int dist = 0;
                for (auto* t = left; t != right; t = t->next) dist++;
                int rIdx = rand() % (dist + 1);
                pivotNode = left;
                for (int k = 0; k < rIdx; k++) pivotNode = pivotNode->next;
            }
            else {
                pivotNode = right;
            }


            T pivotValue = pivotNode->data;
            slist.swap(pivotNode, right);

            typename SingleLinkedList<T>::Node* j = left;
            for (typename SingleLinkedList<T>::Node* i = left; i != right; i = i->next) {
                if ((i->data)< pivotValue) {
                    slist.swap(i, j);
                    j = j->next;
                }
            }
            slist.swap(j, right);
            if (j != left) {
                typename SingleLinkedList<T>::Node* prev = left;
                while (prev->next != j) prev = prev->next;
                quickSortSingleList(slist, pivotStr, left, prev);
            }
            left = j->next;
        }
    }

    static void quickSortDoubleList (DoubleLinkedList<T>& dlist,string pivotStr,
                              typename DoubleLinkedList<T>::Node* left,
                              typename DoubleLinkedList<T>::Node* right) {
        while (left && right && left != right && left != right->next) {
            typename DoubleLinkedList<T>::Node* pivotNode = nullptr;

            if (pivotStr == "Left") pivotNode = left;
            else if (pivotStr == "Centre") {
                typename DoubleLinkedList<T>::Node* fast = left;
                pivotNode = left;
                while (fast != right && fast->next != right) {
                    pivotNode = pivotNode->next;
                    fast = fast->next->next;
                }
            } else if (pivotStr == "Random") {
                int dist = 0;
                for (auto* t = left; t != right; t = t->next) dist++;
                pivotNode = left;
                int rIdx = rand() % (dist + 1);
                for (int k = 0; k < rIdx; k++) pivotNode = pivotNode->next;
            } else pivotNode = right;

            T pVal = pivotNode->data;
            dlist.swap(pivotNode, right);

            typename DoubleLinkedList<T>::Node* j = left;
            for (typename DoubleLinkedList<T>::Node* i = left; i != right; i = i->next) {
                if ((i->data) < pVal) {
                    dlist.swap(i, j);
                    j = j->next;
                }
            }
            dlist.swap(j, right);

            if (j != left) {
                quickSortDoubleList(dlist, pivotStr, left, j->prev);
            }
            left = j->next;
        }
    }


    static void quickSortRawArray(T* arr, int left, int right) {
        if (left < right) {

            int p = partitionRaw(arr, left, right);
            quickSortRawArray(arr, left, p - 1);
            quickSortRawArray(arr, p + 1, right);
        }
    }

    static int partitionRaw(T* arr, int left, int right) {
        T pivot = arr[right];
        int i = left - 1;
        for (int j = left; j < right; j++) {
            if (arr[j] < pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[right]);
        return i + 1;
    }
};

#endif //QUICKSORT_H