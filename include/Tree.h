//
// Created by krist on 18.04.2026.
//

#ifndef TREE_H
#define TREE_H
template<typename T>
class Tree {
    struct Node {
        T data;
        Node *left, *right;
        Node(T val) {
            data = val;
            left = nullptr;
            right = nullptr;
        }
    };
    Node* root;

    //usuwa całe drzewo z pamieci
    void clear(Node* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }


    //wstawia wartosc do drzewa
    void insert(Node*& node, T val) {
        if (!node) {
            node = new Node(val);
        } else if (val < node->data) {
            insert(node->left, val);
        } else {
            insert(node->right, val);
        }
    }

    //ta kolejnosc odwiedza elementyrosnąco
    void inOrder(Node* node, T* arr, int& index) {
        if (!node) return;
        inOrder(node->left, arr, index);
        arr[index++] = node->data;
        inOrder(node->right, arr, index);
    }

public:
    Tree() {
        root = nullptr;
    }

    ~Tree() {
        clear(root);
    }

    //buduje drzewo na podstawie tablicy
    void build(T* arr, int size) {
        for(int i = 0; i < size; i++) {
            insert(root, arr[i]);
        }
    }

    //sortuje dane poprzez wypisywanie je do tablicy
    void sort(T* out) {
        int index = 0;
        inOrder(root, out, index);
    }
};
#endif //TREE_H
