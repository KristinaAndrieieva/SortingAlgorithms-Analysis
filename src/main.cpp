#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>


#include "Array.h"
#include "SingleLinkedList.h"
#include "FileService.h"
#include "QuickSort.h"
#include "BucketSort.h"


#include "Parameters.h"
#include "ShellSort.h"

using namespace std;

int main(int argc, char** argv) {
    srand(time(NULL));


    if (Parameters::readParameters(argc - 1, argv + 1) != 0) {
        return 1;
    }


    if (Parameters::runMode == Parameters::RunModes::help) {
        Parameters::help();
        return 0;
    }


    if (Parameters::runMode == Parameters::RunModes::singleFile) {
        if (Parameters::inputFile.empty()) {
            cerr << "Blad: Nie podano pliku wejsciowego (-i)!" << endl;
            return 1;
        }


        if (Parameters::dataType == Parameters::DataTypes::typeInt) {
            if (Parameters::structure == Parameters::Structures::array) {
                Array<int>* array = FileService<int>::loadDataArray(Parameters::inputFile);

                if (array == nullptr) return 1;

                if (Parameters::algorithm == Parameters::Algorithms::quick) {
                    string pStr = "Centre";
                    if(Parameters::pivot == Parameters::Pivots::left) pStr = "Left";
                    if(Parameters::pivot == Parameters::Pivots::random) pStr = "Random";

                    QuickSort<int>::quickSortArray(*array, pStr, 0, array->getSize() - 1);
                }
                else if (Parameters::algorithm == Parameters::Algorithms::bucket) {
                    BucketSort<int>::bucketSortArray(*array);
                }else if (Parameters::algorithm == Parameters::Algorithms::shell) {
                    string gap = "Option 1";
                    if (Parameters::shellParameter == Parameters::ShellParameters::option2) {
                        gap = "Option 2";
                    }
                    ShellSort<int>::shellSortArray(*array,gap);
                }

                for (int i = 0; i < array->getSize(); i++) {
                    cout << (*array)[i] << " ";
                }
                cout << endl;

                delete array;
            }else if (Parameters::structure == Parameters::Structures::singleList) {
                SingleLinkedList<int>* slist = FileService<int>::loadDataSingleLinkedlist(Parameters::inputFile);
                if (slist == nullptr) return 1;

                if (Parameters::algorithm == Parameters::Algorithms::quick) {

                    string pStr = "Right";
                    if (Parameters::pivot == Parameters::Pivots::left) pStr = "Left";
                    else if (Parameters::pivot == Parameters::Pivots::middle) pStr = "Centre";
                    else if (Parameters::pivot == Parameters::Pivots::random) pStr = "Random";


                    if (slist->head != nullptr) {
                        QuickSort<int>::quickSortSingleList(*slist, pStr, slist->head, slist->getTail());
                    }
                }else if (Parameters::algorithm == Parameters::Algorithms::bucket) {
                    if (slist->head != nullptr) {
                        BucketSort<int>::bucketSortSingleList(*slist);
                    }
                }else if (Parameters::algorithm == Parameters::Algorithms::shell) {
                    string gap = "Option 1";
                    if (Parameters::shellParameter == Parameters::ShellParameters::option2) {
                        gap = "Option 2";
                    }
                    ShellSort<int>::shellSortSingleList(*slist, gap);
                }

                SingleLinkedList<int>::Node* curr = slist->head;
                while (curr != nullptr) {
                    cout << curr->data << " ";
                    curr = curr->next;
                }
                cout << endl;

                delete slist;

            }else if (Parameters::structure == Parameters::Structures::doubleList) {
                DoubleLinkedList<int>* dlist = FileService<int>::loadDataDoubleLinkedlist(Parameters::inputFile);
                if (dlist == nullptr) return 1;

                if (Parameters::algorithm == Parameters::Algorithms::quick) {

                    string pStr = "Right";
                    if (Parameters::pivot == Parameters::Pivots::left) pStr = "Left";
                    else if (Parameters::pivot == Parameters::Pivots::middle) pStr = "Centre";
                    else if (Parameters::pivot == Parameters::Pivots::random) pStr = "Random";


                    if (dlist->head != nullptr) {
                        QuickSort<int>::quickSortDoubleList(*dlist, pStr, dlist->head, dlist->getTail());
                    }
                }else if (Parameters::algorithm == Parameters::Algorithms::bucket) {
                    if (dlist->head != nullptr) {
                        BucketSort<int>::bucketSortDoubleList(*dlist);
                    }
                }else if (Parameters::algorithm == Parameters::Algorithms::shell) {
                    string gap = "Option 1";
                    if (Parameters::shellParameter == Parameters::ShellParameters::option2) {
                        gap = "Option 2";
                    }
                    ShellSort<int>::shellSortDoubleList(*dlist, gap);
                }

                DoubleLinkedList<int>::Node* curr = dlist->head;
                while (curr != nullptr) {
                    cout << curr->data << " ";
                    curr = curr->next;
                }
                cout << endl;

                delete dlist;
            }
        }
        else if (Parameters::runMode == Parameters::RunModes::benchmark) {
            cout << "Tryb benchmark nie jest jeszcze w pelni zaimplementowany." << endl;
        }

        return 0;
    }
};