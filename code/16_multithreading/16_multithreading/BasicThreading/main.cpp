#include <iostream>
#include <vector>
#include <chrono>
#include <mutex>
#include <thread>

using std::cout;    using std::endl;
using std::string;  using std::vector;

const size_t kNumThreads = 10;
static std::mutex mtx;

void greet(int id) {
    cout << "Thread " << id << ": Hello world!" << endl;
}

int main() {
    cout << "Greetings from my threads..." << endl;

    // Create threads

    // Wait for threads to finish

    cout << "All greetings done!" << endl;

    return 0;
}
