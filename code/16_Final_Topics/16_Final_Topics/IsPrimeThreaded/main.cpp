
#include <iostream>
#include <vector>
#include <chrono>
#include <mutex>
#include <thread>
#include "ostreamlock.h"

using std::cout;    using std::endl;
using std::vector;  using std::string;


bool prime = true;

const size_t kNumToCheck = 1909664501;
const size_t kNumThreads = 8;

void threadIsPrime(size_t beg, size_t end, size_t threadNum) {
    for(size_t i = beg; i < end; ++i) {
        if(kNumToCheck % i == 0) {
            prime = false;
        }
    }
    cout << oslock << "Thread " << threadNum << " done!" << endl << osunlock;
}

bool isPrime(size_t num) {
    for(size_t i = 2; i < num; ++i) {
        if(num % i == 0) {
            return false;
        }
    }
    return true;
}


int main() {
//    cout << "Running..." << endl;
//    auto t1 = std::chrono::high_resolution_clock::now();
//    if(isPrime(kNumToCheck)) {
//        cout << "Is prime!" << endl;
//    } else {
//        cout << "Not prime" << endl;
//    }
//    auto t2 = std::chrono::high_resolution_clock::now();
//    cout << "Time taken: "
//         << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << endl;


    vector<std::thread> threads;
    size_t div = kNumToCheck/kNumThreads;
    size_t beg = 0, end = 0;
    cout << "Running threads ..." << endl;
    auto t3 = std::chrono::high_resolution_clock::now();
    for(size_t i = 0; i < kNumThreads; ++i) {
        beg = std::max(size_t{2},i*div);
        end = (i+1)*div;

        threads.push_back(std::thread(threadIsPrime, beg, end, i));
    }
    for(std::thread& thread : threads) {
        thread.join();
    }
    if(prime) {
        cout << "Is prime!" << endl;
    } else {
        cout << "Not prime" << endl;
    }
    auto t4 = std::chrono::high_resolution_clock::now();
    cout << "Time taken: "
         << std::chrono::duration_cast<std::chrono::milliseconds>(t4 - t3).count() << endl;

    return 0;
}
