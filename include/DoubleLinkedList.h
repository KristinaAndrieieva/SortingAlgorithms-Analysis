//
// Created by krist on 24.03.2026.
//
#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H

#endif //DOUBLELINKEDLIST_H

template<typename  T>
class DoubleLinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;

        Node (T x){
            data = x;
            next = nullptr;
            prev = nullptr;
        }
    };

};