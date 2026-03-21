//
// Created by krist on 21.03.2026.
//

#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>

template<typename  T>
class Array {

private:
    T* data;
    int size;

public:
    Array() {
        data = nullptr;
        size = 0;
    };

    void alocate(int n) {
        if (data != nullptr) delete[] data;
        data = new T[n];
        size = n;
    }

    ~Array() {
        delete[] data;
    }

};
#endif //ARRAY_H
