//
// Created by krist on 21.03.2026.
//

#ifndef SINGLELIST_H
#define SINGLELIST_H

#include <iostream>

using namespace std;
template<typename  T>

class SingleLinkedList {
    private:
    struct Node {
        T data;
        Node *next;

        Node (T x) {
            data = x;
            next = nullptr;
        }
    };

    Node* head;
    Node* tail;
    int size;

    public:
    SingleLinkedList() {
        head = nullptr;
        size = 0;
    };

    ~SingleLinkedList() {
        clear();
    }

    void push(T x) {
        Node* newNode = new Node(x);
        newNode->next = head;
        head = newNode;
        if (tail == nullptr) tail == head;
        size++;
    }

    void pushBack(T x) {
        Node* newNode = new Node(x);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    void clear() {}
};
#endif //SINGLELIST_H
