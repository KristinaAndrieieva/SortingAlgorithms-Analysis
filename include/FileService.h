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

/**
       *  klasa FileService odpowiada za obsługę plików (odczyt/zapis)
       * oraz generowanie losowych zestawów danych do testów.
       */
class FileService {
public:
    // wczytuje dane z pliku i zappisuje do tablicy
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


    // wczytuje dane z pliku i zappisuje do singlefile
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


    // wczytuje dane z pliku i zappisuje do doublelist
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

    // wczytuje dane z pliku i zappisuje do drzewa
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


    // wczytuje dane z pliku i zappisuje do surowej tablicy, wzraca wskaznik do pamieci
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


    // zapisuje dane wynikowe do pliku tekstowego dla tablicy
    static void saveToFile(const string& filename, Array<T>* data) {
        ofstream outFile(filename);
        if (!outFile.is_open()) return;
        outFile << data->getSize() << "\n";
        for (int i = 0; i < data->getSize(); i++) {
            outFile << data->getValue(i) << "\n";
        }
        outFile.close();
    }


    // zapisuje dane wynikowe do pliku tekstowego dla singlelist
    static void saveToFile(const string& filename, SingleLinkedList<T>* data) {
        ofstream outFile(filename);
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


    // zapisuje dane wynikowe do pliku tekstowego dla doublelist
    static void saveToFile(const string& filename, DoubleLinkedList<T>* data) {
        ofstream outFile(filename);
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



    // zapisuje dane wynikowe do pliku tekstowego dla drzewa
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


    // zapisuje dane wynikowe do pliku tekstowego dla stosu
    static void saveToFile(const string& filename, T* arr, int size) {
        ofstream outFile(filename);
        if (!outFile.is_open()) return;

        outFile << size << "\n";
        for (int i = 0; i < size; i++) {
            outFile << arr[i] << "\n";
        }
        outFile.close();
    }


    //zapisuje wyniki benchmarku do pliku csv
    static void saveBenchmark(const string& fileName, int iteration, const string& alg,
                                  const string& structure, const string& type,
                                  int size, const string& pivot,
                                  const string& shell,const string& distribution, double time) {

        ifstream checkFile(fileName);
        bool exists = checkFile.good();
        checkFile.close();

        ofstream outFile(fileName, ios::app);
        if (!outFile.is_open()) return;

        if (!exists) {
            outFile << "Nr_Proby;Algorytm;Struktura;Typ_Danych;Rozmiar;Pivot;Shell_Option;Distribution;Czas_ms\n";
        }

        outFile << iteration << ";" << alg << ";" << structure << ";" << type << ";"
                << size << ";" << pivot << ";" << shell << ";" << distribution << ";" << time << "\n";

        outFile.close();
    }


    // zapisuje srednia dla wyników
    static void saveBenchmarkSummary(const string& fileName, double avgTime) {
        ofstream outFile(fileName, ios::app);
        if (outFile.is_open()) {
            outFile << "\nSREDNIA;;;;; ; ;" << avgTime << "\n";
            outFile.close();
        }
    }


    //generuje wartości losowe dla badań na tablicach
    static Array<T>* generateRandomArray(int size) {
        Array<T>* arr = new Array<T>(size);
        for (int i = 0; i < size; i++) {
            arr->set(generateRandomValue(), i);
        }
        return arr;
    }

    //generuje wartości losowe dla badań na listach jednokierunkowych
    static SingleLinkedList<T>* generateRandomSingleList(int size) {
        SingleLinkedList<T>* list = new SingleLinkedList<T>();
        for (int i = 0; i < size; i++) {
            list->pushBack(generateRandomValue());
        }
        return list;
    }

    //generuje wartości losowe dla badań na listach dwukierunkowych
    static DoubleLinkedList<T>* generateRandomDoubleList(int size) {
        DoubleLinkedList<T>* list = new DoubleLinkedList<T>();
        for (int i = 0; i < size; i++) {
            list->pushBack(generateRandomValue());
        }
        return list;
    }


    //generuje wartości losowe dla badań na drzewie
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

    //generuje wartości losowe dla badań na stosie
    static Stack<T>* generateRandomStack(int size) {
        Stack<T>* s = new Stack<T>();
        for (int i = 0; i < size; i++) {
            s->push(generateRandomValue());
        }
        return s;
    }


    // generuje losowa wartość ktore jest potem używana w metodach generateRanddom
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