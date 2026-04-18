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
#include <chrono>
#include <iostream>

using namespace std;
class Controller {
public:
    static void run() {
        switch (Parameters::dataType) {
            case Parameters::DataTypes::typeInt: runMode<int>(); break;
            case Parameters::DataTypes::typeFloat: runMode<float>(); break;
            case Parameters::DataTypes::typeDouble: runMode<double>(); break;
            case Parameters::DataTypes::typeString: runMode<std::string>(); break;
            default: std::cerr << "Nie ma takiego typu danych w programie!" << std::endl;
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
        if (Parameters::inputFile.empty()) {
            std::cerr << "Blad!" << std::endl;
            return;
        }

        if (Parameters::structure == Parameters::Structures::array) {
            Array<T>* array = FileService<T>::loadDataArray(Parameters::inputFile);
            if (array == nullptr) return;

            std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

            SortOnArray<T>(*array);

            std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> elapsed = end - start;
            std::cout << "Czas wykonania: " << elapsed.count() << " ms" << std::endl;

            if (array->getSize() < 100) {
                std::cout << "Dane po sortowaniu: ";
                for(int i = 0; i < array->getSize(); i++) {
                    std::cout << array->getValue(i) << " ";
                }
                std::cout << std::endl;
            }

            delete array;
        }else if (Parameters::structure == Parameters::Structures::singleList) {

            SingleLinkedList<T>* slist = FileService<T>::loadDataSingleLinkedlist(Parameters::inputFile);
            if (slist == nullptr) return;

            std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

            SortOnSingleList<T>(*slist);

            std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> elapsed = end - start;
            std::cout << "Czas wykonania: " << elapsed.count() << " ms" << std::endl;

            if (slist->getSize() < 100) {
                std::cout << "Dane po sortowaniu (SingleList): ";
                auto* curr = slist->head;
                while (curr != nullptr) {
                    std::cout << curr->data << " ";
                    curr = curr->next;
                }
                std::cout << std::endl;
            }
            delete slist;

        }else if(Parameters::structure == Parameters::Structures::doubleList) {

            DoubleLinkedList<T>* dlist = FileService<T>::loadDataDoubleLinkedlist(Parameters::inputFile);
            if (dlist == nullptr) return;

            std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

            SortOnDoubleList<T>(*dlist);

            std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> elapsed = end - start;
            std::cout << "Czas wykonania: " << elapsed.count() << " ms" << std::endl;
            delete dlist;
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

    static std::string getPivotStr() {
        if (Parameters::pivot == Parameters::Pivots::left) return "Left";
        if (Parameters::pivot == Parameters::Pivots::middle) return "Centre";
        if (Parameters::pivot == Parameters::Pivots::random) return "Random";
        return "Right";
    }

    static std::string getGapStr() {
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
            std::cerr << "Blad: Nie podano pliku " << std::endl;
            return;
        }

        if (size <= 0 || repeats <= 0) {
            std::cerr << "Blad: Rozmiar i liczba iteracji musza byc wieksze od 0!" << std::endl;
            return;
        }

        switch(Parameters::algorithm) {
            case Parameters::Algorithms::bucket:    algName = "BubbleSort";    break;
            case Parameters::Algorithms::shell:     algName = "ShellSort";     break;
            case Parameters::Algorithms::quick:     algName = "QuickSort";     break;
            default: algName = "Nieznany";
        }

        switch(Parameters::structure) {
            case Parameters::Structures::array:      structName = "Tablica"; break;
            case Parameters::Structures::singleList: structName = "Lista jednokierunkowa"; break;
            case Parameters::Structures::doubleList: structName = "Lista dwukierunkowa"; break;
            default: structName = "Nieznana";
        }

        if constexpr (is_same_v<T, int>) {
            typeName = "int";
        }else if constexpr (is_same_v<T, float>) {
            typeName = "float";
        }else if constexpr (is_same_v<T, double>) {
            typeName = "double";
        }else if constexpr (is_same_v<T, std::string>) {
            typeName = "string";
        }else {
            typeName = "nieznany";
        }

        string pivotVal = "NULL";
        if (Parameters::algorithm == Parameters::Algorithms::quick) pivotVal = getPivotStr();

        string shellVal = "NULL";
        if (Parameters::algorithm == Parameters::Algorithms::shell) shellVal = getGapStr();

        double totalTime = 0;
        bool allSortedCorrectly = true;

        for (int r = 0; r < repeats; r++) {
            double currentElapsed = 0;
            std::string currentStatus = "NIE";

            if (Parameters::structure == Parameters::Structures::array) {
                Array<T>* data = FileService<T>::generateRandomArray(size);

                std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
                SortOnArray<T>(*data);
                std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();

                currentStatus = isSorted(*data);
                currentElapsed = std::chrono::duration<double, std::milli>(end - start).count();
                delete data;
            }
            else if (Parameters::structure == Parameters::Structures::singleList) {
                SingleLinkedList<T>* data = FileService<T>::generateRandomSingleList(size);

                std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
                SortOnSingleList<T>(*data);
                std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();

                currentStatus = isSorted(*data);
                currentElapsed = std::chrono::duration<double, std::milli>(end - start).count();
                delete data;
            }
            else if (Parameters::structure == Parameters::Structures::doubleList) {
                DoubleLinkedList<T>* data = FileService<T>::generateRandomDoubleList(size);

                std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
                SortOnDoubleList<T>(*data);
                std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();

                currentStatus = isSorted(*data);
                currentElapsed = std::chrono::duration<double, std::milli>(end - start).count();
                delete data;
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
                currentElapsed
            );
        }


        double averageTime = totalTime / repeats;
        FileService<T>::saveBenchmarkSummary(Parameters::resultsFile, averageTime);

        std::cout << "Ilisc prob: " << repeats << std::endl;
        std::cout << "Sredni czas: " << averageTime << " ms" << std::endl;

        if (allSortedCorrectly) {
            std::cout << "Posortowane: Tak" << std::endl;
        } else {
            std::cout << "Posortowane: Nie" << std::endl;
        }

        std::cout << "Wyniki zapisano w: " << Parameters::resultsFile << std::endl;
    }


    template<typename T>
    static std::string isSorted(Array<T>& arr) {
        for (int i = 0; i < arr.getSize() - 1; i++) {
            if (arr.getValue(i) > arr.getValue(i + 1)) return "NIE";
        }
        return "TAK";
    }

    template<typename T>
    static std::string isSorted(SingleLinkedList<T>& slist) {
        typename SingleLinkedList<T>::Node* curr = slist.head;
        while (curr != nullptr && curr->next != nullptr) {
            if (curr->data > curr->next->data) return "NIE";
            curr = curr->next;
        }
        return "TAK";
    }

    template<typename T>
    static std::string isSorted(DoubleLinkedList<T>& dlist) {
        typename DoubleLinkedList<T>::Node* curr = dlist.head;
        while (curr != nullptr && curr->next != nullptr) {
            if (curr->data > curr->next->data) return "NIE";
            curr = curr->next;
        }
        return "TAK";
    }
};
#endif //CONTROLLER_H
