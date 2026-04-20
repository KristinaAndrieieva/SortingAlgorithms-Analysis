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
    //struktue węzła
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


    // dodawanie elementu na koniec tablicy
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


    //dodaje już istnejący węzeł
    void pushNode(Node* newNode) {
        if (!newNode) return;
        newNode->next = nullptr;
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }


    //usuwa wszystkie elementy
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


    //zamienia elementy miejscami
    void swap(Node* a, Node* b) {
        if (a == nullptr || b == nullptr) return;
        T temp = a->data;
        a->data = b->data;
        b->data = temp;
    }


    int getSize() const {
        return size;
    }


    void clearSize() {
        size = 0;
    }


    Node* getTail() {
        Node* temp = head;
        if (!temp) return nullptr;
        while (temp->next != nullptr) temp = temp->next;
        return temp;
    }


    // szuka największy element
    T findMax() {
        if (head == nullptr) return T();
        T maxValue = head->data;
        Node* temp = head->next;

        while (temp != nullptr) {
            if (temp->data > maxValue) {
                maxValue = temp->data;
            }
            temp = temp->next;
        }
        return maxValue;
    }

    // szuka najmniejszy element
    T findMin() {
        if (head == nullptr) return T();
        T minValue = head->data;
        Node* temp = head->next;

        while (temp != nullptr) {
            if ((temp->data) < minValue) {
                minValue = temp->data;
            }
            temp = temp->next;
        }
        return minValue;
    }


    //robi sortowanie przez wstawianie dla shellsort
    void insertionSort(int gap) {
        for (int i = gap; i < size; i++) {
            for (int j = i; j >= gap; j -= gap) {
                Node* nodeJ = getNodeAt(j);
                Node* nodePrevGap = getNodeAt(j - gap);

                if (nodePrevGap->data > nodeJ->data) {
                    this->swap(nodePrevGap, nodeJ);
                } else {
                    break;
                }
            }
        }
    }


    //pobiera węzeł o konkretnym indeksie
    Node* getNodeAt(int index) {
        if (index < 0 || index >= size) return nullptr;

        Node* curr = head;
        for (int i = 0; i < index && curr != nullptr; i++) {
            curr = curr->next;
        }
        return curr;
    }
};
#endif //SINGLELIST_H
