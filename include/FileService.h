//
// Created by krist on 23.03.2026.
//

#ifndef FILE_SERVICE_H
#define FILE_SERVICE_H
#include "Array.h"

#endif //FILE_SERVICE_H
#include <iostream>
#include <fstream>
using namespace std;
template<typename  T>

class FileService {
    public:
    static Array <T>* saveData(const string& filename) {
        ifstream file(filename);
        Array <T>* tempdata = new Array <T>;

        if (!file.is_open()) {
            cerr << "Can't open file " << filename << endl;
            return tempdata;
        }

        T value;
        while (file >> value) {
            tempdata->add(value);
        }

        file.close();
        return tempdata;
    }

};