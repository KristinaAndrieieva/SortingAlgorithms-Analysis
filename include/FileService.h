//
// Created by krist on 23.03.2026.
//

#ifndef FILE_SERVICE_H
#define FILE_SERVICE_H

#include "DoubleLinkedList.h"
#include "SingleLinkedList.h"
#include "Array.h"
#include <iostream>
#include <fstream>


using namespace std;
template<typename  T>

class FileService {
public:

    static Array <T>* loadDataArray(const string& filename) {
        ifstream file(filename);
        Array <T>* tempdata = new Array <T>;
        int size ;
        T value;

        if (!file.is_open()) {
            cerr << "Can't open file " << filename << endl;
            delete tempdata;
            return nullptr;
        }
        if (file >> size ) {
            cout << size << " elementow w pliku" << endl;
        }

        while (file >> value) {
            tempdata->set(value);
        }

        file.close();
        return tempdata;
    }


    static SingleLinkedList<T>* loadDataSingleLinkedlist(const string& filename) {
        ifstream file(filename);
        SingleLinkedList<T>* tempdata = new SingleLinkedList<T>;
        int size;
        T value;

        if (!file.is_open()) {
            cerr << "Can't open file " << filename << endl;
            delete tempdata;
            return nullptr;
        }

        if (file >> size) {
            for (int i = 0; i < size; i++) {
                if (file >> value) {
                    tempdata->pushBack(value);
                } else {
                    break;
                }
            }
        }

        file.close();
        return tempdata;
    }


    static DoubleLinkedList<T>* loadDataDoubleLinkedlist(const string& filename) {
        ifstream file(filename);

        DoubleLinkedList<T>* tempdata = new DoubleLinkedList<T>();
        int size;
        T value;

        if (!file.is_open()) {
            cerr << "Can't open file " << filename << endl;
            delete tempdata;
            return nullptr;
        }

        if (file >> size) {
            for (int i = 0; i < size; i++) {
                if (file >> value) {
                    tempdata->pushBack(value);
                } else {
                    break;
                }
            }
        }

        file.close();
        return tempdata;
    }
};

#endif //FILE_SERVICE_H