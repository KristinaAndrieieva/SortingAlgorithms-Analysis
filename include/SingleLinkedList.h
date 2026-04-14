//
// Created by krist on 21.03.2026.
//

#ifndef SINGLELIST_H
#define SINGLELIST_H

#include <iostream>

using namespace std;
template<typename  T>

class SingleLinkedList {
    public:
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

    SingleLinkedList() {
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    ~SingleLinkedList() {
        clear();
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

    void pushNode(Node* newNode) {
        if (!newNode) return;
        newNode->next = nullptr;
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    void clear() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        size = 0;
    }


    Node* getPrevious(Node* target) {
        if (target == head || target == nullptr) return nullptr;
        Node* temp = head;
        while (temp != nullptr && temp->next != target) {
            temp = temp->next;
        }
        return temp;
    }

    void swap(Node* a, Node* b) {
        if (a == nullptr || b == nullptr) return;
        T temp = a->data;
        a->data = b->data;
        b->data = temp;
    }

    Node* getHead() { return head; }
    Node* getTail() {
        Node* temp = head;
        if (!temp) return nullptr;
        while (temp->next != nullptr) temp = temp->next;
        return temp;
    }
};
#endif //SINGLELIST_H
