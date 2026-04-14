//
// Created by krist on 21.03.2026.
//

#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;
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
        capacity = 0;
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

    void reserve(int newCapacity) {
        if (data != nullptr) delete[] data;
        data = new T[newCapacity];
        capacity = newCapacity;
        size = 0;
    }


    void set (T x) {
        if (size == capacity) {
            int newcapacity = (capacity == 0)? 1 : capacity + 1;
            alocate(newcapacity);
        }

        data[size] = x;
        size++;
    }

    T& operator[](int index) {
        return data[index];
    }

    void set (T x ,int index) {
        if (index <= size && index >= 0) {
            data[index] = x;
        } else {
            std::cout << "index out of range" << std::endl;
        }
    }



    T findMax () {
        if (size == 0) {
            return T();
        }

        T max = data[0];
        for (int i = 1; i < size; i++) {
            if (max < data[i]) {
                max = data[i];
            }
        }
        return max;
    }


    T findMin () {
        if (size == 0) {
            return T();
        }

        T min = data[0];
        for (int i = 1; i < size; i++) {
            if (min > data[i]) {
                min = data[i];
            }
        }
        return min;
    }

    T getValue (int index) {
        return data[index];
    }


    void swap (T* a,T* b) {
        T temp = *a;
        *a = *b;
        *b = temp;
    }


    ~Array() {
        delete[] data;
    }

    int getSize (){
        return size;
    }

};
#endif //ARRAY_H
