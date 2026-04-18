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
    Node* root = nullptr;

    void clear(Node* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }


    void insert(Node*& node, T val) {
        if (!node) node = new Node(val);
        else if (val < node->data) insert(node->left, val);
        else insert(node->right, val);
    }

    void inOrder(Node* node, T* arr, int& index) {
        if (!node) return;
        inOrder(node->left, arr, index);
        arr[index++] = node->data;
        inOrder(node->right, arr, index);
    }

public:
    Tree() : root(nullptr) {}

    ~Tree() {
        clear(root);
    }

    void build(T* arr, int size) {
        for(int i = 0; i < size; i++) {
            insert(root, arr[i]);
        }
    }

    void sort(T* outArray) {
        int index = 0;
        inOrder(root, outArray, index);
    }
};
#endif //TREE_H
