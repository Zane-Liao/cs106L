
#include <iostream>
#include <vector>
#include <chrono>
#include <mutex>
#include <thread>
#include "ostreamlock.h"

using std::cout;    using std::endl;
using std::vector;  using std::string;


void greet(size_t i) {
    cout << oslock << "Thread " << i << ": Hello world!" << endl << osunlock;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    cout << oslock << "Thread " << i << ": Happy Week 9!" << endl << osunlock;

}

int main() {
    cout << "You are about to be greeted!!!" << endl;
    std::thread thread1(greet, 1);
    std::thread thread2(greet, 2);
    thread1.join();
    thread2.join();
    cout << "Finished" << endl;
}



