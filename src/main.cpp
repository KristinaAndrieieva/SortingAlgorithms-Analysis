//
// Created by krist on 21.03.2026.
//
#include <iostream>
#include <fstream>

#include "Array.h"
#include "FileService.h"

int main() {
    Array<int> array = FileService<int>::saveData("data.txt");
    for (int i = 0; i < array.getSize(); i++) {
        std::cout << array[i] << std::endl;
    }

}
