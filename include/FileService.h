//
// Created by krist on 23.03.2026.
//

#ifndef FILE_SERVICE_H
#define FILE_SERVICE_H

#include "DoubleLinkedList.h"
#include "SingleLinkedList.h"
#include "Array.h"
#include "Tree.h"
#include "Stack.h"
#include <iostream>
#include <fstream>
#include <type_traits>
#include <string>
#include <cstdlib>


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

    static Tree<T>* loadDataTree(const string& filename) {
        ifstream file(filename);
        Tree<T>* tempdata = new Tree<T>();
        int size;
        T value;

        if (!file.is_open()) return nullptr;

        if (file >> size) {
            T* arr = new T[size];
            for (int i = 0; i < size; i++) {
                if (file >> value) arr[i] = value;
            }
            tempdata->build(arr, size);
            delete[] arr;
        }
        file.close();
        return tempdata;
    }


    static T* loadToRawArray(const string& filename, int& outSize) {
        ifstream file(filename);
        if (!file.is_open()) return nullptr;

        if (!(file >> outSize)) return nullptr;

        T* arr = new T[outSize];
        for (int i = 0; i < outSize; i++) {
            if (!(file >> arr[i])) break;
        }
        file.close();
        return arr;
    }


    static void saveToFile(const std::string& filename, Array<T>* data) {
        std::ofstream outFile(filename);
        if (!outFile.is_open()) return;
        outFile << data->getSize() << "\n";
        for (int i = 0; i < data->getSize(); i++) {
            outFile << data->getValue(i) << "\n";
        }
        outFile.close();
    }


    static void saveToFile(const std::string& filename, SingleLinkedList<T>* data) {
        std::ofstream outFile(filename);
        if (!outFile.is_open()) return;

        int count = 0;
        typename SingleLinkedList<T>::Node* temp = data->head;
        while (temp) {
            count++;
            temp = temp->next;
        }

        outFile << count << "\n";
        typename SingleLinkedList<T>::Node* curr = data->head;
        while (curr) {
            outFile << curr->data << "\n";
            curr = curr->next;
        }
        outFile.close();
    }


    static void saveToFile(const std::string& filename, DoubleLinkedList<T>* data) {
        std::ofstream outFile(filename);
        if (!outFile.is_open()) return;

        int count = 0;
        typename DoubleLinkedList<T>::Node* temp = data->head;
        while (temp) {
            count++;
            temp = temp->next;
        }

        outFile << count << "\n";
        typename DoubleLinkedList<T>::Node* curr = data->head;
        while (curr) {
            outFile << curr->data << "\n";
            curr = curr->next;
        }
        outFile.close();
    }



    static void saveToFile(const string& filename, Tree<T>* data, int size) {
        ofstream outFile(filename);
        if (!outFile.is_open()) return;

        T* tempArray = new T[size];
        data->sort(tempArray);

        outFile << size << "\n";
        for (int i = 0; i < size; i++) {
            outFile << tempArray[i] << "\n";
        }
        delete[] tempArray;
        outFile.close();
    }


    static void saveToFile(const string& filename, T* arr, int size) {
        ofstream outFile(filename);
        if (!outFile.is_open()) return;

        outFile << size << "\n";
        for (int i = 0; i < size; i++) {
            outFile << arr[i] << "\n";
        }
        outFile.close();
    }


    static void saveBenchmark(const string& fileName, int iteration, const string& alg,
                                  const string& structure, const string& type,
                                  int size, const string& pivot,
                                  const string& shell, double time) {

        ifstream checkFile(fileName);
        bool exists = checkFile.good();
        checkFile.close();

        ofstream outFile(fileName, ios::app);
        if (!outFile.is_open()) return;

        if (!exists) {
            outFile << "Nr_Proby;Algorytm;Struktura;Typ_Danych;Rozmiar;Pivot;Shell_Option;Czas_ms\n";
        }

        outFile << iteration << ";" << alg << ";" << structure << ";" << type << ";"
                << size << ";" << pivot << ";" << shell << ";" << time << "\n";

        outFile.close();
    }


    static void saveBenchmarkSummary(const string& fileName, double avgTime) {
        ofstream outFile(fileName, ios::app);
        if (outFile.is_open()) {
            outFile << "\nSREDNIA;;;;; ; ;" << avgTime << "\n";
            outFile.close();
        }
    }


    static Array<T>* generateRandomArray(int size) {
        Array<T>* arr = new Array<T>(size);
        for (int i = 0; i < size; i++) {
            arr->set(generateRandomValue(), i);
        }
        return arr;
    }

    static SingleLinkedList<T>* generateRandomSingleList(int size) {
        SingleLinkedList<T>* list = new SingleLinkedList<T>();
        for (int i = 0; i < size; i++) {
            list->pushBack(generateRandomValue());
        }
        return list;
    }

    static DoubleLinkedList<T>* generateRandomDoubleList(int size) {
        DoubleLinkedList<T>* list = new DoubleLinkedList<T>();
        for (int i = 0; i < size; i++) {
            list->pushBack(generateRandomValue());
        }
        return list;
    }


    static Tree<T>* generateRandomTree(int size) {
        Tree<T>* tree = new Tree<T>();
        T* tempArr = new T[size];
        for (int i = 0; i < size; i++) {
            tempArr[i] = generateRandomValue();
        }

        tree->build(tempArr, size);
        delete[] tempArr;
        return tree;
    }


    static Stack<T>* generateRandomStack(int size) {
        Stack<T>* s = new Stack<T>();
        for (int i = 0; i < size; i++) {
            s->push(generateRandomValue());
        }
        return s;
    }

    static T generateRandomValue() {

        if constexpr (is_same_v<T, int>) {
            return rand() % 100000;
        }else if constexpr (is_same_v<T, float> || is_same_v<T, double>) {
            return static_cast<T>(rand()) / (static_cast<T>(RAND_MAX / 1000.0));

        }else if constexpr (is_same_v<T, string>) {

            string str = "";
            static const char alphanum[] = "abcdefghijklmnopqrstuvwxyz";
            for (int i = 0; i < 8; ++i) {
                str += alphanum[rand() % (sizeof(alphanum) - 1)];
            }
            return str;
        }
        return T();
    }
};

#endif //FILE_SERVICE_H