//
// Created by krist on 24.03.2026.
//
#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H


template<typename  T>
class DoubleLinkedList {
public:

    //struktue węzła
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


    // dodawanie elementu na koniec tablicy
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


    //dodaje już istnejący węzeł
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


    //zwraca element poprzedni
    Node* getPrevious(Node* temp) {
        if (temp == nullptr) return nullptr;
        return temp->prev;
    }


    //zamienia elementy miejscami
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


    // szuka największy element
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

    // szuka najmniejszy element
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

    //pobiera węzeł o konkretnym indeksie
    Node* getNodeAt(int index) {
        if (index < 0 || index >= size) {
            return nullptr;
        }
        if (index < size / 2) {
            Node* curr = head;
            for (int i = 0; i < index; i++) {
                curr = curr->next;
            }
            return curr;
        } else {
            Node* curr = tail;
            for (int i = size - 1; i > index; i--) {
                curr = curr->prev;
            }
            return curr;
        }
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
};
#endif //DOUBLELINKEDLIST_H