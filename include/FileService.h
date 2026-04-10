//
// Created by krist on 23.03.2026.
//

#ifndef FILE_SERVICE_H
#define FILE_SERVICE_H
#endif //FILE_SERVICE_H

#include "Array.h"
#include <iostream>
#include <fstream>

using namespace std;
template<typename  T>

class FileService {
    public:

    static Array <T>* loadData(const string& filename) {
        ifstream file(filename);
        Array <T>* tempdata = new Array <T>;
        T value;

        if (!file.is_open()) {
            cerr << "Can't open file " << filename << endl;
            delete tempdata;
            return nullptr;
        }

        while (file >> value) {
            tempdata->set(value);
        }

        file.close();
        return tempdata;
    }

};