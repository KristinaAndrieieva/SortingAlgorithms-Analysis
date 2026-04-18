#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>


#include "Array.h"
#include "SingleLinkedList.h"
#include "FileService.h"
#include "QuickSort.h"
#include "BucketSort.h"
#include "Controller.h"
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

    Controller::run();

};