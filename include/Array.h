//
// Created by krist on 21.03.2026.
//

#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <ctime>


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

    Array(int s) {
        size = s;
        data = new T[s];
    }

    ~Array() {
        delete[] data;
    }

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

    void insertionSort(int gap) {
        for (int i = gap; i < size; i++) {
            T temp = data[i];
            int j;
            for (j = i; j >= gap && data[j - gap] > temp; j -= gap) {
                data[j] = data[j - gap];
            }
            data[j] = temp;
        }
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
            cout << "index out of range" << endl;
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


    int getSize (){
        return size;
    }

    double stringToDouble(string s) {
        double val = 0;
        if (s.length() > 0) val += (unsigned char)s[0] * 256;
        if (s.length() > 1) val += (unsigned char)s[1];
        return val;
    }

    T* getRawPointer() {
        return data;
    }

};
#endif //ARRAY_H
