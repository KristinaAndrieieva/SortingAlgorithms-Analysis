cmake_minimum_required(VERSION 3.10)

project(SortingAlgorithmsAnalysis)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
        src/main.cpp
        include/Array.h
        include/SingleLinkedList.h
        include/FileService.h
        include/DoubleLinkedList.h
        include/BucketSort.h
        include/QuickSort.h
        include/ShellSort.h
        lib/Parameters.h
        lib/Parameters.cpp
        include/Controller.h
        include/Tree.h
        include/Stack.h
)
add_executable(SortingAlgorithms_Analysis ${SOURCES})
target_include_directories(SortingAlgorithms_Analysis PRIVATE include)
target_include_directories(SortingAlgorithms_Analysis PRIVATE include lib)
target_compile_options(SortingAlgorithms_Analysis PRIVATE -Wall -Wextra)