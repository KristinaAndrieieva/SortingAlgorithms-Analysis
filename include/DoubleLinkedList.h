//
// Created by krist on 24.03.2026.
//
#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H


template<typename  T>
class DoubleLinkedList {
public:
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

    Node* head;
    Node* tail;
    int size;


    DoubleLinkedList() {
        head = nullptr;
        tail = nullptr;
        size = 0;
    }


    ~DoubleLinkedList() {
        clear();
    }


    void pushBack(T x) {
        Node* newNode = new Node(x);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }


    void pushNode(Node* newNode) {
        if (!newNode) return;
        newNode->next = nullptr;
        newNode->prev = nullptr;

        if (head == nullptr) {
            head = tail = newNode;
        } else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
        size++;
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


    Node* getPrevious(Node* temp) {
        if (temp == nullptr) return nullptr;
        return temp->prev;
    }


    void swap(Node* a, Node* b) {
        if (a == nullptr || b == nullptr) return;
        T temp = a->data;
        a->data = b->data;
        b->data = temp;
    }

    Node* getHead() { return head; }
    Node* getTail() { return tail; }

    int getSize() const { return size; }

    void clearSize() { size = 0; }


    T findMax() {
        if (head == nullptr) return T();
        T maxValue = head->data;
        Node* temp = head->next;
        while (temp != nullptr) {
            if (temp->data > maxValue) maxValue = temp->data;
            temp = temp->next;
        }
        return maxValue;
    }


    T findMin() {
        if (head == nullptr) return T();
        T minValue = head->data;
        Node* temp = head->next;
        while (temp != nullptr) {
            if ((temp->data) < minValue) minValue = temp->data;
            temp = temp->next;
        }
        return minValue;
    }
};
#endif //DOUBLELINKEDLIST_H