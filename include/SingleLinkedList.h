//
// Created by krist on 21.03.2026.
//

#ifndef SINGLELIST_H
#define SINGLELIST_H

#include <iostream>

template <typename T>

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
    }

    void clear() {}
};
#endif //SINGLELIST_H
