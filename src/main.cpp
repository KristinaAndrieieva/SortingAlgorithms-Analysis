//
// Created by krist on 21.03.2026.
//
#include <iostream>
#include <fstream>

#include "Array.h"
#include "BucketSort.h"
#include "FileService.h"
#include <ctime>
#include <cstdlib>

using namespace std;

int main() {
    srand(time(NULL));

    Array<int>* array = FileService<int>::loadData("data.txt");

    if (array != nullptr) {
        int left = 0;
        int right = array->getSize() - 1;
        cout << "Quicksort: " << endl;

        QuickSort<int>::quickSortArray(*array,"Centre",left,right);
        for (int i = 0; i < array->getSize(); i++) {
            std::cout << (*array)[i] << std::endl;
        }

    }else {
        std::cout << "File Not Found" << std::endl;
    }
    delete array;

    Array<int>* array1 = FileService<int>::loadData("data.txt");
    if (array1 != nullptr) {
        cout << "Bucketsort: " << endl;

        BucketSort<int>::bucketSortArray(*array1);
        for (int i = 0; i < array1->getSize(); i++) {
            std::cout << (*array1)[i] << std::endl;
        }

    }else {
        std::cout << "File Not Found" << std::endl;
    }
    delete array1;

    return 0;
}
