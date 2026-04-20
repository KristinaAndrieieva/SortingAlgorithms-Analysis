//
// Created by krist on 14.04.2026.
//

#ifndef CONTROLLER_H
#define CONTROLLER_H


#include "Parameters.h"
#include "FileService.h"
#include "QuickSort.h"
#include "ShellSort.h"
#include "BucketSort.h"
#include "Tree.h"

#include <chrono>
#include <iostream>
#include <algorithm>

using namespace std;
class Controller {
public:
    static void run() {
        switch (Parameters::dataType) {
            case Parameters::DataTypes::typeInt: runMode<int>(); break;
            case Parameters::DataTypes::typeFloat: runMode<float>(); break;
            case Parameters::DataTypes::typeDouble: runMode<double>(); break;
            case Parameters::DataTypes::typeString: runMode<string>(); break;
            case Parameters::DataTypes::tyleUnsignedInt:runMode<unsigned int>(); break;
            default: cerr << "Nie ma takiego typu danych w programie!" << endl;
        }
    }

private:
    template<typename  T>
    static void runMode() {
        if (Parameters::runMode == Parameters::RunModes::singleFile) {
            runSingleFile<T>();
        } else if (Parameters::runMode == Parameters::RunModes::benchmark) {
            runBenchmark<T>();
        }
    }


    template<typename  T>
    static void runSingleFile() {
        if (Parameters::inputFile.empty() || Parameters::outputFile.empty()) {
            cerr << "Blad: Nie podano pliku wejsciowego lub wyjsciowego!" << endl;
            return;
        }

        if (Parameters::structure == Parameters::Structures::array) {
            Array<T>* array = FileService<T>::loadDataArray(Parameters::inputFile);
            if (array == nullptr) return;

            chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();

            SortOnArray<T>(*array);

            chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
            chrono::duration<double, milli> elapsed = end - start;
            cout << "Czas wykonania: " << elapsed.count() << " ms" << endl;

            FileService<T>::saveToFile(Parameters::outputFile, array);
            delete array;

        }else if (Parameters::structure == Parameters::Structures::singleList) {

            SingleLinkedList<T>* slist = FileService<T>::loadDataSingleLinkedlist(Parameters::inputFile);
            if (slist == nullptr) return;

            chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();

            SortOnSingleList<T>(*slist);

            chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
            chrono::duration<double, milli> elapsed = end - start;
            cout << "Czas wykonania: " << elapsed.count() << " ms" << endl;

            FileService<T>::saveToFile(Parameters::outputFile, slist);
            delete slist;

        }else if(Parameters::structure == Parameters::Structures::doubleList) {

            DoubleLinkedList<T>* dlist = FileService<T>::loadDataDoubleLinkedlist(Parameters::inputFile);
            if (dlist == nullptr) return;

            chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();

            SortOnDoubleList<T>(*dlist);

            chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
            chrono::duration<double, milli> elapsed = end - start;
            cout << "Czas wykonania: " << elapsed.count() << " ms" << endl;

            FileService<T>::saveToFile(Parameters::outputFile, dlist);
            delete dlist;
        }else if (Parameters::structure == Parameters::Structures::binaryTree) {

            int size = 0;
            T* rawData = FileService<T>::loadToRawArray(Parameters::inputFile, size);

            if (rawData == nullptr) return;

            Tree<T> bst;
            chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();

            bst.build(rawData, size);
            bst.sort(rawData);

            chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
            chrono::duration<double, milli> elapsed = end - start;

            cout << "Czas wykonania : " << elapsed.count() << " ms" << endl;

            FileService<T>::saveToFile(Parameters::outputFile, rawData, size);

            delete[] rawData;

        }else if (Parameters::structure == Parameters::Structures::stack) {

            int size = 0;
            T* rawData = FileService<T>::loadToRawArray(Parameters::inputFile, size);

            if (rawData == nullptr) return;

            Stack<T> stack(size);
            for(int i = 0; i < size; i++) stack.push(rawData[i]);

            chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();

            stack.drainToArray(rawData);
            QuickSort<T>::quickSortRawArray(rawData, 0, size - 1);

            chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
            chrono::duration<double, milli> elapsed = end - start;

            cout << "Czas wykonania (Stack): " << elapsed.count() << " ms" << endl;

            FileService<T>::saveToFile(Parameters::outputFile, rawData, size);

            delete[] rawData;
        }
    }


    template<typename  T>
    static void SortOnArray(Array<T>& array) {
        if (Parameters::algorithm == Parameters::Algorithms::quick) {
            QuickSort<T>::quickSortArray(array, getPivotStr(), 0, array.getSize() - 1);
        } else if (Parameters::algorithm == Parameters::Algorithms::shell) {
            ShellSort<T>::shellSortArray(array, getGapStr());
        } else if (Parameters::algorithm == Parameters::Algorithms::bucket) {
            BucketSort<T>::bucketSortArray(array);
        }
    }

    template<typename  T>
    static void SortOnSingleList(SingleLinkedList<T>& slist) {
        if (Parameters::algorithm == Parameters::Algorithms::quick) {
            QuickSort<T>::quickSortSingleList(slist, getPivotStr(),slist.head, slist.getTail());
        } else if (Parameters::algorithm == Parameters::Algorithms::shell) {
            ShellSort<T>::shellSortSingleList(slist, getGapStr());
        } else if (Parameters::algorithm == Parameters::Algorithms::bucket) {
            BucketSort<T>::bucketSortSingleList(slist);
        }
    }

    template<typename  T>
    static void SortOnDoubleList(DoubleLinkedList<T>& dlist) {
        if (Parameters::algorithm == Parameters::Algorithms::quick) {
            QuickSort<T>::quickSortDoubleList(dlist, getPivotStr(), dlist.head, dlist.getTail());
        } else if (Parameters::algorithm == Parameters::Algorithms::shell) {
            ShellSort<T>::shellSortDoubleList(dlist, getGapStr());
        } else if (Parameters::algorithm == Parameters::Algorithms::bucket) {
            BucketSort<T>::bucketSortDoubleList(dlist);
        }
    }

    static string getPivotStr() {
        if (Parameters::pivot == Parameters::Pivots::left) return "Left";
        if (Parameters::pivot == Parameters::Pivots::middle) return "Centre";
        if (Parameters::pivot == Parameters::Pivots::random) return "Random";
        return "Right";
    }

    static string getGapStr() {
        return (Parameters::shellParameter == Parameters::ShellParameters::option2) ? "Option 2" : "Option 1";
    }

    template<typename  T>
    static void runBenchmark() {
        int size = Parameters::structureSize;
        int repeats = Parameters::iterations;
        string algName;
        string structName;
        string typeName;

        if (Parameters::resultsFile.empty()) {
            cerr << "Blad: Nie podano pliku " << endl;
            return;
        }

        if (size <= 0 || repeats <= 0) {
            cerr << "Blad: Rozmiar i liczba iteracji musza byc wieksze od 0!" << endl;
            return;
        }

        switch(Parameters::algorithm) {
            case Parameters::Algorithms::bucket:algName = "BucketSort";    break;
            case Parameters::Algorithms::shell:algName = "ShellSort";     break;
            case Parameters::Algorithms::quick:algName = "QuickSort";     break;
            default: algName = "Nieznany";
        }

        switch(Parameters::structure) {
            case Parameters::Structures::array: structName = "Tablica"; break;
            case Parameters::Structures::singleList: structName = "Lista jednokierunkowa"; break;
            case Parameters::Structures::doubleList: structName = "Lista dwukierunkowa"; break;

            case Parameters::Structures::binaryTree:
                structName = "Drzewo binarne";
            algName = "Null";
            break;

            case Parameters::Structures::stack:
                structName = "Stos";
            algName = "Null";
            break;
            default: structName = "Nieznana";
        }

        if constexpr (is_same_v<T, int>) {
            typeName = "int";
        }else if constexpr (is_same_v<T, float>) {
            typeName = "float";
        }else if constexpr (is_same_v<T, double>) {
            typeName = "double";
        }else if constexpr (is_same_v<T, string>) {
            typeName = "string";
        }else if(is_same_v<T,unsigned int>) {
            typeName = "unsigned int";
        }else {
            typeName = "nieznany";
        }

        string pivotVal = "NULL";
        if (Parameters::algorithm == Parameters::Algorithms::quick) pivotVal = getPivotStr();

        string shellVal = "NULL";
        if (Parameters::algorithm == Parameters::Algorithms::shell) shellVal = getGapStr();

        string disName = "Random";
        if (Parameters::distribution == Parameters::Distribution::ascending) disName = "Ascending";
        if (Parameters::distribution == Parameters::Distribution::descending) disName = "Descending";
        if (Parameters::distribution == Parameters::Distribution::random) disName = "Random";
        if (Parameters::distribution == Parameters::Distribution::ascending50Per) disName = "Ascending50Per";



        double totalTime = 0;
        bool allSortedCorrectly = true;

        for (int r = 0; r < repeats; r++) {
            double currentElapsed = 0;
            string currentStatus = "NIE";

            if (Parameters::structure == Parameters::Structures::array) {
                Array<T>* data = FileService<T>::generateRandomArray(size);
                prepareDistribution(data->getRawPointer(), size, Parameters::distribution);

                chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
                SortOnArray<T>(*data);
                chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();

                currentStatus = isSorted(*data);
                currentElapsed = chrono::duration<double, milli>(end - start).count();
                delete data;
            }
            else if (Parameters::structure == Parameters::Structures::singleList) {

                T* temp = new T[size];
                for(int i = 0; i < size; i++) temp[i] = FileService<T>::generateRandomValue();

                prepareDistribution(temp, size, Parameters::distribution);

                auto* data = new SingleLinkedList<T>();
                for(int i = 0; i < size; i++) data->pushBack(temp[i]);

                chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
                SortOnSingleList<T>(*data);
                chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();

                currentStatus = isSorted(*data);
                currentElapsed = chrono::duration<double, milli>(end - start).count();
                delete data;
                delete[] temp;

            }
            else if (Parameters::structure == Parameters::Structures::doubleList) {

                T* temp = new T[size];
                for(int i = 0; i < size; i++) temp[i] = FileService<T>::generateRandomValue();

                prepareDistribution(temp, size, Parameters::distribution);

                auto* data = new DoubleLinkedList<T>();
                for(int i = 0; i < size; i++) data->pushBack(temp[i]);

                chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
                SortOnDoubleList<T>(*data);
                chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();

                currentStatus = isSorted(*data);
                currentElapsed = chrono::duration<double, milli>(end - start).count();
                delete data;
                delete[] temp;

            }else if (Parameters::structure == Parameters::Structures::binaryTree) {
                int n = size;
                T* tempArr = new T[n];

                for(int i = 0; i < n; i++) {
                    tempArr[i] = FileService<T>::generateRandomValue();
                }

                Tree<T> tree;

                chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();

                tree.build(tempArr, n);
                tree.sort(tempArr);

                chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();

                currentStatus = isSorted(tempArr,size);

                chrono::duration<double, milli> elapsed = end - start;
                currentElapsed = elapsed.count();

                delete[] tempArr;

            }else if (Parameters::structure == Parameters::Structures::stack) {
                Stack<T> stack(size);
                T* tempArr = new T[size];
                for(int i = 0; i < size; i++) stack.push(FileService<T>::generateRandomValue());

                chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();

                stack.drainToArray(tempArr);
                QuickSort<T>::quickSortRawArray(tempArr, 0, size - 1);

                chrono::high_resolution_clock::time_point end =chrono::high_resolution_clock::now();

                currentStatus = isSorted(tempArr, size);

                chrono::duration<double, milli> elapsed = end - start;
                currentElapsed = elapsed.count();
                delete[] tempArr;
            }


            if (currentStatus == "NIE") {
                allSortedCorrectly = false;
            }

            totalTime += currentElapsed;

            FileService<T>::saveBenchmark(
                Parameters::resultsFile,
                (r + 1),
                algName,
                structName,
                typeName,
                size,
                pivotVal,
                shellVal,
                disName,
                currentElapsed
            );
        }


        double averageTime = totalTime / repeats;
        FileService<T>::saveBenchmarkSummary(Parameters::resultsFile, averageTime);

        cout << "Ilisc prob: " << repeats << endl;
        cout << "Sredni czas: " << averageTime << " ms" << endl;

        if (allSortedCorrectly) {
            cout << "Posortowane: Tak" << endl;
        } else {
            cout << "Posortowane: Nie" << endl;
        }

        cout << "Wyniki zapisano w: " << Parameters::resultsFile << endl;
    }


    template<typename T>
    static string isSorted(Array<T>& arr) {
        for (int i = 0; i < arr.getSize() - 1; i++) {
            if (arr.getValue(i) > arr.getValue(i + 1)) return "NIE";
        }
        return "TAK";
    }

    template<typename T>
    static string isSorted(SingleLinkedList<T>& slist) {
        typename SingleLinkedList<T>::Node* curr = slist.head;
        while (curr != nullptr && curr->next != nullptr) {
            if (curr->data > curr->next->data) return "NIE";
            curr = curr->next;
        }
        return "TAK";
    }

    template<typename T>
    static string isSorted(DoubleLinkedList<T>& dlist) {
        typename DoubleLinkedList<T>::Node* curr = dlist.head;
        while (curr != nullptr && curr->next != nullptr) {
            if (curr->data > curr->next->data) return "NIE";
            curr = curr->next;
        }
        return "TAK";
    }

    template<typename T>
    static string isSorted(T* arr, int size) {
        if (arr == nullptr || size <= 0) return "NIE";
        for (int i = 0; i < size - 1; i++) {
            if (arr[i] > arr[i + 1]) return "NIE";
        }
        return "TAK";
    }

    template<typename T>
    static void prepareDistribution(T* arr, int size, Parameters::Distribution dist) {
        if (dist == Parameters::Distribution::random) {
            return;
        }
        sort(arr, arr + size);

        if (dist == Parameters::Distribution::descending) {
            reverse(arr, arr + size);
        }
        else if (dist == Parameters::Distribution::ascending50Per) {
            for (int i = size / 2; i < size; i++) {
                arr[i] = FileService<T>::generateRandomValue();
            }
        }
    }
};
#endif //CONTROLLER_H
