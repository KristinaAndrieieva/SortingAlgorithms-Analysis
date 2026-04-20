//
// Created by krist on 18.04.2026.
//

#ifndef STACK_H
#define STACK_H

using namespace std;

template<typename T>
class Stack {
private:
    T* table;
    int capacity;
    int topIndex;

    //zwiększa pamięć dla tablicy,ktora przechowywa dane ze stosu
    void resize() {
        capacity += 1;
        T* newTable = new T[capacity];
        for (int i = 0; i <= topIndex; i++) {
            newTable[i] = table[i];
        }
        delete[] table;
        table = newTable;
    }

public:
    Stack(int initialCapacity = 10) : capacity(initialCapacity), topIndex(-1) {
        table = new T[capacity];
    }

    ~Stack() {
        delete[] table;
    }


    //dodaje element na góre stosu
    void push(T val) {
        if (topIndex == capacity - 1) resize();
        table[++topIndex] = val;
    }


    //zgejmuje elemnt z góry stosu
    void pop() {
        if (isEmpty()) return;
        topIndex--;
    }


    // zwraca wartosc na górze
    T top() const {
        if (isEmpty()) throw runtime_error("Stos jest przepelniony");
        return table[topIndex];
    }


    //sprawdza czy stos pusty
    bool isEmpty() const {
        return topIndex == -1;
    }

    int size() const {
        return topIndex + 1;
    }

    // zapisuje gtne element stosu do tablicy i potem go zdejmuje
    void drainToArray(T* arr) {
        int i = 0;
        while (!isEmpty()) {
            arr[i++] = top();
            pop();
        }
    }
};

#endif //STACK_H
