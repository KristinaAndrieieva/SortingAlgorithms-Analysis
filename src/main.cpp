#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>

// Twoje nagłówki
#include "Array.h"
#include "SingleLinkedList.h"
#include "FileService.h"
#include "QuickSort.h"
#include "BucketSort.h"

// Biblioteka prowadzącego
#include "Parameters.h"

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
                }

                for (int i = 0; i < array->getSize(); i++) {
                    cout << (*array)[i] << " ";
                }
                cout << endl;

                delete array;
            }
        }
    }
    else if (Parameters::runMode == Parameters::RunModes::benchmark) {
        cout << "Tryb benchmark nie jest jeszcze w pelni zaimplementowany." << endl;
    }

    return 0;
}