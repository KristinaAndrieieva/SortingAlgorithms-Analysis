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
        BucketSort<int>::bucketSortArray(*array);
        for (int i = 0; i < array->getSize(); i++) {
            std::cout << (*array)[i] << std::endl;
        }
    }else {
        std::cout << "File Not Found" << std::endl;
    }
    delete array;
    return 0;
}
