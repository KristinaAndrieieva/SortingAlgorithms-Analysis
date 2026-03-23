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
    int capacity;

public:
    Array() {
        data = nullptr;
        size = 0;
    };

    void alocate(int newcapacity) {
        T* newData = new T[newcapacity];

        if (data != nullptr) {
            for (int i = 0; i < size; i++) {
                newData[i] = data[i];
            }
            delete[] data;
        }
        data = newData;
        capacity = newcapacity;
    }

    void add (T x) {
         if (size == capacity) {
             int newcapacity = (capacity == 0)? 1 : capacity * 2;
             alocate(newcapacity);
        }

        data[size] = x;
        size++;
    }

    T& operator[](int index) {
        return data[index];
    }

    ~Array() {
        delete[] data;
    }

    int getSize (){
        return size;
    }

    Array(const Array& other) = delete;


};
#endif //ARRAY_H
