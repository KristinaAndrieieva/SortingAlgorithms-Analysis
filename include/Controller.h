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
            case Parameters::DataTypes::typeInt:          runMode<int>(); break;
            case Parameters::DataTypes::typeFloat:        runMode<float>(); break;
            case Parameters::DataTypes::typeDouble:       runMode<double>(); break;
            case Parameters::DataTypes::typeString:       runMode<std::string>(); break;
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
        }

        else if (Parameters::structure == Parameters::Structures::singleList) {
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
        std::cout << "Uruchamiam benchmark..." << std::endl;
    }
};
#endif //CONTROLLER_H
