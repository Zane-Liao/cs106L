#include "intvector.h"
#include "MyVector.h"
#include <vector>
#include <chrono>
#include <iostream>

using std::string;
MyVector<string> findAllWords(size_t size);

// implement your swap function here

struct Patient {
    std::string name;
    int priority;
};


int main() {

    auto start = std::chrono::high_resolution_clock::now();

    MyVector<string> names1 = findAllWords(24321234);
    MyVector<string> names2;
    names2 = findAllWords(24321234);
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Time took: " << elapsed.count() << std::endl;
}

MyVector<string> findAllWords(size_t size) {
    MyVector<string> names(size, "Ito");
    return names;
}
